#include <NativeInterface/Graphics/FD3D11Interface.h>
#include <NativeInterface/Graphics/Shader/FD3D11ShaderInterface.h>
#include <NativeInterface/Graphics/NativeGraphicsHandles.h>
#include <NativeInterface/Graphics/NativeGraphicsEnums_D3D11.h>
#include <ParadigmException.h>
#include <dxgidebug.h>
#include <DDSTextureLoader.h>
#include <WICTextureLoader.h>
#include <FParadigmEngine.h>
#include <D3DX11async.h>


/*if (m_InterfaceData.RenderSystems.Count())
{
	if (errorMessage)
		errorLog = Shader::FD3D11ShaderInterface::SendErrorMessage(errorMessage, m_InterfaceData.RenderSystems.Front().WindowHandle, _filename);
	else
		errorLog = "Fail to load \"" + _filename + "\". Missing shader file if persistent.";
}
throw ParadigmException(EParadigmExceptionCode::RUNTIME_ERROR, errorLog);*/
#define SHADER_RUNTIME_COMPILATION_ERROR(Filename, ErrorMessage) \
	FString errorLog;\
	if (ErrorMessage)\
		errorLog = Shader::FD3D11ShaderInterface::SendErrorMessage(ErrorMessage, nullptr, Filename);\
	else\
		errorLog = "Fail to load \"" + Filename + "\". Missing shader file if persistent.";\
	throw ParadigmException(EParadigmExceptionCode::SHADER_RUNTIME_COMPILATION_ERROR, errorLog);


namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Graphics
		{
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// PIPELINE MODULES
			//____________________________________	____________________________________	____________________________________	
#pragma region PIPELINE MODULES
			void FD3D11Interface::Initialize()
			{
				D3D_FEATURE_LEVEL featureLevel{ D3D_FEATURE_LEVEL_11_0 };

				////////////////////////////////////////////////
				// FACTORY AND ADAPTER CONFIG
				//____________________________________	
				// Create the Direct3D graphics factory 
				if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_DXGIFactory)))
					THROW_PARADIGM_EXCEPTION_NATIVE_IMPLEMENTATION_ERROR(PARADIGM_DEV_SIGNATURE_ARUMA);

				// Use the factory to create the graphics adaptor and get the screen adapter.
				if (FAILED(m_DXGIFactory->EnumAdapters(0, &m_DXGIAdapter)) || FAILED(m_DXGIAdapter->EnumOutputs(0, &m_DXGIAdapterOutput)))
					THROW_PARADIGM_EXCEPTION_NATIVE_IMPLEMENTATION_ERROR(PARADIGM_DEV_SIGNATURE_ARUMA);

				// Create the devices.
				if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG, &featureLevel, 1,
					D3D11_SDK_VERSION, &m_InterfaceData.Device, nullptr, &m_InterfaceData.DeviceContext)))
					THROW_PARADIGM_EXCEPTION_NATIVE_IMPLEMENTATION_ERROR(PARADIGM_DEV_SIGNATURE_ARUMA);

#ifdef PARADIGM_DEBUG
				m_InterfaceData.Device->QueryInterface(__uuidof(ID3D11Debug), (void**)&m_D3D11Debug);
#endif

				TArray<UShardShaderDescriptor> shardDesc;
				UShardShaderDescriptor desc;
				desc.EntryPoint = "VertexToPixel";
				desc.Filename = "Resource/Shader/NativeDebug.vs";
				desc.Type = EShaderType::EShaderType_Vertex;
				shardDesc.Add(desc);
				desc.EntryPoint = "PixelToFrameBuffer";
				desc.Filename = "Resource/Shader/NativeDebug.ps";
				desc.Type = EShaderType::EShaderType_Pixel;
				shardDesc.Add(desc);
				CreateShader(m_InterfaceData.ShaderInterface.kNativeDebugShader, shardDesc);

				// Create and set the defaults depth stencil states [0 = default (enable zbuffer), 1 = default (disable zbuffer)].
				m_InterfaceData.DeviceContext->OMSetDepthStencilState(m_InterfaceData.DepthStencilStates[CreateDepthStencilState({ ENativeDepthFunc::EDepthFunc_Less, 0, 0, 1, 1, 0 })], 1);
				m_InterfaceData.DepthStencilStates[CreateDepthStencilState({ ENativeDepthFunc::EDepthFunc_Less, 0, 0, 1, 0, 0 })];

				// Create and set default rasterzer state and primitive topology mode.
				m_InterfaceData.DeviceContext->RSSetState(m_InterfaceData.RasterizerStates[CreateRasterizerState({})]);
				SetPrimitiveDrawingMode(ENativePrimitiveTopology::EPrimitiveTopology_TriangleList);

				////////////////////////////////////////////////
				// GRAPHIC CARD INFO
				//____________________________________	
				FillGraphicsCardInfo();

				m_InterfaceData.RenderSystems.Reserve(VIEWPORT_EDITOR + 1);
				for (uint i = 0; i < (uint)VIEWPORT_EDITOR + 1; ++i)
					m_InterfaceData.RenderSystems.Add({});
			}

			void FD3D11Interface::Terminate()
			{
				try
				{
					TerminateD3D11Interface();									

					if (m_DXGIAdapterOutput)
					{
						m_DXGIAdapterOutput->Release();
						m_DXGIAdapterOutput = nullptr;
					}
					if (m_DXGIAdapter)
					{
						m_DXGIAdapter->Release();
						m_DXGIAdapter = nullptr;
					}
					if (m_DXGIFactory)
					{
						m_DXGIFactory->Release();
						m_DXGIFactory = nullptr;
					}									
				}
				catch (const ParadigmException& except)
				{
					FPrint::Print(except.SumUp(), EParadigmDebugLevel::ERROR_LEVEL);
					PARADIGM_PAUSE;
				}
			}
#pragma endregion

			
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// GRAPHICS API CONFIGURATION
			//____________________________________	____________________________________	____________________________________	
#pragma region GRAPHICS API CONFIGURATION
			void FD3D11Interface::CreateViewport(ETargetViewport _target, bool _bfullscreen, bool _bvsync)
			{				
				uint target = (uint)_target < ETargetViewport::VIEWPORT_EDITOR + 1 ? (uint)_target : 0;

				UD3D11RenderSystemAttributes& renderSystem = m_InterfaceData.RenderSystems[target];
				renderSystem.bFullscreen = _bfullscreen;		
				const UContextAttributes& context = PARADIGM_CONTEXT->GetContextAttributes(ETargetViewport(target));
				renderSystem.bVerticalSynchro = _bvsync;
				////////////////////////////////////////////////
				// DE-NUMERATOR COMPUTATION
				//____________________________________	
				ComputeRefreshRate(context.Dimension.Width, context.Dimension.Height);

				////////////////////////////////////////////////
				// renderSystem CONFIGURATION
				//____________________________________	
				CreateRenderSystem(renderSystem, (HWND)context.Handle, context.Dimension.Width, context.Dimension.Height);
			}

			void FD3D11Interface::CreateViewport(ETargetViewport _target, UContextAttributes _contextDesc, bool _bfullscreen, bool _bvsync)
			{
				PARADIGM_CONTEXT->CreateContext(_target, _contextDesc);
				CreateViewport(_target, _bfullscreen, _bvsync);				
			}

			bool FD3D11Interface::CreateViewport(ETargetViewport _target, uint _width, uint _height, bool _bfullscreen, bool _bvsync, void* _HandleID)
			{
				uint target = (uint)_target < ETargetViewport::VIEWPORT_EDITOR + 1 ? (uint)_target : 0;
				PARADIGM_CONTEXT->LinkContext(_target, _HandleID);
				UD3D11RenderSystemAttributes& renderSystem = m_InterfaceData.RenderSystems[target];
				renderSystem.bFullscreen = _bfullscreen;
				renderSystem.bVerticalSynchro = _bvsync;

				////////////////////////////////////////////////
				// DE-NUMERATOR COMPUTATION
				//____________________________________	
				ComputeRefreshRate(_width, _height);

				////////////////////////////////////////////////
				// renderSystem CONFIGURATION
				//____________________________________	
				try
				{	CreateRenderSystem(renderSystem, (HWND)_HandleID, _width, _height);		}
				catch (const ParadigmException&)
				{	return false;	}

				return true;
			}

			void FD3D11Interface::ResizeViewport(ETargetViewport _target, uint _width, uint _height)
			{
				uint target = (uint)_target < ETargetViewport::VIEWPORT_EDITOR + 1 ? (uint)_target : 0;
				
				UD3D11RenderSystemAttributes& renderSystem = m_InterfaceData.RenderSystems[target];
				//renderSystem.SwapChain->ResizeBuffers(1, _width, _height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
				//renderSystem.
				CreateRenderSystem(renderSystem, renderSystem.WindowHandle, _width, _height);
			}
			

			UKeyRegister FD3D11Interface::CreateDepthStencilState(const UNativeDepthStencilDescriptor& _attrib)
			{
				D3D11_DEPTH_STENCIL_DESC depthStencilDesc;

				ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
				
				depthStencilDesc.DepthEnable = _attrib.bDepthEnable;
				depthStencilDesc.DepthWriteMask = (D3D11_DEPTH_WRITE_MASK)_attrib.bDepthWriteMask; 
				depthStencilDesc.DepthFunc = NativeConversion(_attrib.DepthFunc);

				depthStencilDesc.StencilEnable = _attrib.bStencilEnable;
				
				depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
				depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
				depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
				depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

				depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
				depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
				depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
				depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

				UKeyRegister kregister = m_InterfaceData.DepthStencilStates.Add({});

				if (FAILED(m_InterfaceData.Device->CreateDepthStencilState(&depthStencilDesc, &m_InterfaceData.DepthStencilStates[kregister])))
					THROW_PARADIGM_EXCEPTION_NATIVE_IMPLEMENTATION_ERROR(PARADIGM_DEV_SIGNATURE_ARUMA);

				return kregister;
			}

			UKeyRegister FD3D11Interface::CreateRasterizerState(const URasterizerDescriptor& _attrib)
			{
				D3D11_RASTERIZER_DESC rasterDesc;
				ZeroMemory(&rasterDesc, sizeof(rasterDesc));

				rasterDesc.AntialiasedLineEnable = false;
				rasterDesc.CullMode = NativeConversion(_attrib.CullMode); //D3D11_CULL_BACK
				rasterDesc.DepthBias = 0;
				rasterDesc.DepthBiasClamp = 0.0f;
				rasterDesc.DepthClipEnable = true;
				
				// Determines if a triangle is front- or back-facing. If this parameter is TRUE, a triangle will be considered front-facing if its vertices are counter-clockwise on the render target and considered back-facing if they are clockwise
				rasterDesc.FillMode = NativeConversion(_attrib.FillMode); 
				
				// Set to TRUE to use the quadrilateral line anti-aliasing algorithm and to FALSE to use the alpha line anti-aliasing algorithm.
				rasterDesc.FrontCounterClockwise = _attrib.bFrontCounterClockwise; 
				
				rasterDesc.MultisampleEnable = _attrib.bMultisampleEnable; 
				rasterDesc.ScissorEnable = false;
				rasterDesc.SlopeScaledDepthBias = 0.0f;

				UKeyRegister kregister = m_InterfaceData.RasterizerStates.Add({});

				if (FAILED(m_InterfaceData.Device->CreateRasterizerState(&rasterDesc, &m_InterfaceData.RasterizerStates[kregister])))
					THROW_PARADIGM_EXCEPTION_NATIVE_IMPLEMENTATION_ERROR(PARADIGM_DEV_SIGNATURE_ARUMA);
				
				return kregister;
			}

			void FD3D11Interface::SetRasterizerState(ETargetViewport _viewport, UKeyRegister _rasterStateID)
			{
				if ((uint)_viewport >= m_InterfaceData.RenderSystems.Count())
					_viewport = ETargetViewport::VIEWPORT_0;

				m_InterfaceData.RenderSystems[_viewport].RasterizerStateKey = _rasterStateID;
			}
			
			void FD3D11Interface::SetDepthStencilState(ETargetViewport _viewport, UKeyRegister _depthStateID)
			{
				if ((uint)_viewport >= m_InterfaceData.RenderSystems.Count())
					_viewport = ETargetViewport::VIEWPORT_0;

				m_InterfaceData.RenderSystems[_viewport].DepthStencilStateKey = _depthStateID;
			}
			
			void FD3D11Interface::SetZBuffer(ETargetViewport _viewport, bool _state)
			{
				if ((uint)_viewport >= m_InterfaceData.RenderSystems.Count())
					_viewport = ETargetViewport::VIEWPORT_0;
				m_InterfaceData.RenderSystems[_viewport].DepthStencilStateKey = {(uint)_state, 1};
			}
#pragma endregion 


			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// TEXTURE RESOURCE FUNCTIONALITY
			//____________________________________	____________________________________	____________________________________	
#pragma region TEXTURE RESOURCE FUNCTIONALITY
			UKeyRegister FD3D11Interface::CreateNativeTextureResource(const UNativeTextureResourceDescriptor& _attrib)
			{
				switch (_attrib.TextureDimension)
				{
					case ETextureDimension_1D:
						return CreateNativeTexture1DResource(_attrib);
					case ETextureDimension_1DArray:
						THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR("Only @ENativeTextureDimension 'NAT_TEXTURE1D' and 'NAT_TEXTURE2D are implemented.'");
					case ETextureDimension_2D:
						return CreateNativeTexture2DResource(_attrib);
					case ETextureDimension_2DArray:
						THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR("Only @ENativeTextureDimension 'NAT_TEXTURE1D' and 'NAT_TEXTURE2D are implemented.'");
					default:
						THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR("Only @ENativeTextureDimension 'NAT_TEXTURE1D' and 'NAT_TEXTURE2D are implemented.'");
				}
			}

			UKeyRegister FD3D11Interface::CreateNativeTexture1DResource(const UNativeTextureResourceDescriptor& _attrib)
			{
				////////////////////////////////////////////////
				// TEXTURE CONFIGURATION
				//____________________________________	
				D3D11_TEXTURE1D_DESC Texture1DDesc;
				ZeroMemory(&Texture1DDesc, sizeof(Texture1DDesc));

				Texture1DDesc.Width = _attrib.Width;
				Texture1DDesc.MipLevels = 1;
				Texture1DDesc.ArraySize = 1;
				Texture1DDesc.Format = (DXGI_FORMAT)_attrib.Format;
				Texture1DDesc.Usage = (D3D11_USAGE)_attrib.Usage;
				Texture1DDesc.BindFlags = _attrib.BindFlag;
				Texture1DDesc.CPUAccessFlags = 0;
				Texture1DDesc.MiscFlags = 0;
				
				UKeyRegister kregisterTexture = m_InterfaceData.Texture1DBuffers.Add({});

				if (FAILED(m_InterfaceData.Device->CreateTexture1D(&Texture1DDesc, nullptr, &m_InterfaceData.Texture1DBuffers[kregisterTexture])))
					THROW_PARADIGM_EXCEPTION_BAD_IMPLEMENTATION(PARADIGM_DEV_SIGNATURE_ARUMA);

				return kregisterTexture;
			}
			
			UKeyRegister FD3D11Interface::CreateNativeTexture2DResource(const UNativeTextureResourceDescriptor& _attrib)
			{
				uint numQualityLevels = 0;

				if (_attrib.MultisampleCount)
				{
					m_InterfaceData.Device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, _attrib.MultisampleCount, &numQualityLevels);
					if (numQualityLevels > 0)
						numQualityLevels--;
				}

				////////////////////////////////////////////////
				// TEXTURE CONFIGURATION
				//____________________________________	
				D3D11_TEXTURE2D_DESC Texture2DDesc;
				ZeroMemory(&Texture2DDesc, sizeof(Texture2DDesc));

				Texture2DDesc.Width = _attrib.Width;
				Texture2DDesc.Height = _attrib.Height;
				Texture2DDesc.MipLevels = 1;
				Texture2DDesc.ArraySize = 1;
				Texture2DDesc.Format = (DXGI_FORMAT)_attrib.Format;
				Texture2DDesc.SampleDesc.Count = _attrib.MultisampleCount;
				Texture2DDesc.SampleDesc.Quality = numQualityLevels;
				Texture2DDesc.Usage = NativeConversion(_attrib.Usage);
				Texture2DDesc.BindFlags = NativeConversion(_attrib.BindFlag);
				Texture2DDesc.CPUAccessFlags = 0;
				Texture2DDesc.MiscFlags = 0;

				UKeyRegister kregisterTexture = m_InterfaceData.Texture2DBuffers.Add({});

				if (FAILED(m_InterfaceData.Device->CreateTexture2D(&Texture2DDesc, nullptr, &m_InterfaceData.Texture2DBuffers[kregisterTexture])))
					THROW_PARADIGM_EXCEPTION_BAD_IMPLEMENTATION(PARADIGM_DEV_SIGNATURE_ARUMA);

				return kregisterTexture;
			}
#pragma endregion 
			

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// SHADER API FUNCTIONALITY
			//____________________________________	____________________________________	____________________________________	
#pragma region SHADER API FUNCTIONALITY
			void FD3D11Interface::CreateShader(UKeyRegister& out_kNatShader, const TArray<Shader::UShardShaderDescriptor>& _shards, bool _brefresh)
			{
				if (!_shards.Count())
					out_kNatShader = INVALID_KEY_REGISTER;

				Shader::UShaderResourceHandle emptyShaderResource;
				/** Browse throw the native resource to find if can't find recyclable data. */
				for (uint i = 0; i < _shards.Count(); ++i)
				{
					FString uniqueShaderName = _shards[i].Filename + "_" + _shards[i].EntryPoint;
					switch (_shards[i].Type)
					{
					case Shader::ENativeShaderType::EShaderType_Vertex:
						if ((emptyShaderResource.kVertexShaderKey = TryRecycleShaderResource(m_InterfaceData.ShaderInterface.VertexShaders, uniqueShaderName, ENativeShaderType::EShaderType_Vertex, emptyShaderResource)) != INVALID_KEY_REGISTER)
							emptyShaderResource.kInputLayoutKey = SeekExistingShader(m_InterfaceData.ShaderInterface.InputLayouts, uniqueShaderName);
						break;
					case Shader::ENativeShaderType::EShaderType_Pixel:
						emptyShaderResource.kPixelShaderKey = TryRecycleShaderResource(m_InterfaceData.ShaderInterface.PixelShader, uniqueShaderName, ENativeShaderType::EShaderType_Pixel, emptyShaderResource);
						break;
					case Shader::ENativeShaderType::EShaderType_Geometry:
						emptyShaderResource.kGeometryShaderKey = TryRecycleShaderResource(m_InterfaceData.ShaderInterface.GeometryShader, uniqueShaderName, ENativeShaderType::EShaderType_Geometry, emptyShaderResource);
						break;
					case Shader::ENativeShaderType::EShaderType_Compute:
						emptyShaderResource.kComputeShaderKey = TryRecycleShaderResource(m_InterfaceData.ShaderInterface.ComputeShader, uniqueShaderName, ENativeShaderType::EShaderType_Compute, emptyShaderResource);
						break;
					default:
						break;
					}
				}


				if (!m_InterfaceData.ShaderInterface.ShaderResources.Contains(out_kNatShader))
					out_kNatShader = m_InterfaceData.ShaderInterface.ShaderResources.Add(emptyShaderResource);


				Shader::UShaderResourceHandle* shaderResource = &m_InterfaceData.ShaderInterface.ShaderResources[out_kNatShader];
				shaderResource->bSuccessfullyCompiled = true;

				try
				{			
					for (uint i = 0; i < _shards.Count(); ++i)
					{
						switch (_shards[i].Type)
						{
						case Shader::ENativeShaderType::EShaderType_Vertex:
							if (_brefresh || emptyShaderResource.kVertexShaderKey == INVALID_KEY_REGISTER)
								CreateVertexShader(*shaderResource, _shards[i].Filename, _shards[i].EntryPoint);
							break;
						case Shader::ENativeShaderType::EShaderType_Pixel:
							if (_brefresh || emptyShaderResource.kPixelShaderKey == INVALID_KEY_REGISTER)
								CreatePixelShader(*shaderResource, _shards[i].Filename, _shards[i].EntryPoint);
							break;
						case Shader::ENativeShaderType::EShaderType_Geometry:
							if (_brefresh || emptyShaderResource.kGeometryShaderKey == INVALID_KEY_REGISTER)
								CreateGeometryShader(*shaderResource, _shards[i].Filename, _shards[i].EntryPoint);
							break;
						case Shader::ENativeShaderType::EShaderType_Compute:
							if (_brefresh || emptyShaderResource.kComputeShaderKey == INVALID_KEY_REGISTER)
								CreateComputeShader(*shaderResource, _shards[i].Filename, _shards[i].EntryPoint);
							break;
						default:
							break;
						}
					}

					BuildNativeShaderResources(out_kNatShader);
					return;
				}
				catch (const ParadigmException& e)
				{
					shaderResource->bSuccessfullyCompiled = false;
					FPrint::Print(e.SumUp());
				}
			}
			
			void FD3D11Interface::CreateVertexShader(Shader::UShaderResourceHandle& out_resourceHandle, const FString& _filename, const FString& _entryPoint)
			{
				ID3DBlob* errorMessage = nullptr;
				ID3DBlob* vertexShaderBuffer = nullptr;
				LPCSTR profile = (m_InterfaceData.Device->GetFeatureLevel() >= D3D_FEATURE_LEVEL_11_0) ? "vs_5_0" : "vs_4_0";
				UKeyRegister kregister;
				FString uniqueShaderName = _filename + "_" + _entryPoint;


				if (FAILED(D3DX11CompileFromFile(_filename, NULL, NULL, _entryPoint, profile, D3D10_SHADER_ENABLE_STRICTNESS, 0, 0, &vertexShaderBuffer, &errorMessage, NULL)))
				{
					out_resourceHandle.bSuccessfullyCompiled = false;
					SHADER_RUNTIME_COMPILATION_ERROR(_filename, errorMessage);
				}

				// if refresh so take the key to refresh
				if (out_resourceHandle.kVertexShaderKey == INVALID_KEY_REGISTER)
					kregister = m_InterfaceData.ShaderInterface.VertexShaders.Add({ std::pair<FString, ID3D11VertexShader*>(uniqueShaderName,{}) });
				else
				{
					kregister = out_resourceHandle.kVertexShaderKey;
					m_InterfaceData.ShaderInterface.VertexShaders[kregister].second->Release();
				}

				if (FAILED(m_InterfaceData.Device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_InterfaceData.ShaderInterface.VertexShaders[kregister].second)))
				{
					out_resourceHandle.bSuccessfullyCompiled = false;
					m_InterfaceData.ShaderInterface.VertexShaders.Remove(kregister);
					if (m_InterfaceData.RenderSystems.Count())
						MessageBox(m_InterfaceData.RenderSystems.Front().WindowHandle, _filename, "Fail to create shader.", MB_OK);
					THROW_PARADIGM_EXCEPTION("Fail to create shader : " + _filename);
				}
				out_resourceHandle.kVertexShaderKey = kregister;

				
				// if refresh so take the key to refresh
				if (out_resourceHandle.kInputLayoutKey == INVALID_KEY_REGISTER)
					kregister = m_InterfaceData.ShaderInterface.InputLayouts.Add({ std::pair<FString, ID3D11InputLayout*>(uniqueShaderName,{}) });
				else
				{
					kregister = out_resourceHandle.kInputLayoutKey;
					m_InterfaceData.ShaderInterface.InputLayouts[kregister].second->Release();
				}

				if (FAILED(Shader::FD3D11ShaderInterface::CreateInputLayoutFromVertexShaderSignature(vertexShaderBuffer, m_InterfaceData.Device, &m_InterfaceData.ShaderInterface.InputLayouts[kregister].second)))
				{
					out_resourceHandle.bSuccessfullyCompiled = false;
					m_InterfaceData.ShaderInterface.InputLayouts.Remove(kregister);
					MessageBox(m_InterfaceData.RenderSystems.Front().WindowHandle, _filename, "Fail to create input layout by reflect.", MB_OK);
					THROW_PARADIGM_EXCEPTION("Fail to create input layout by reflect, shader : " + _filename);
				}			
				out_resourceHandle.kInputLayoutKey = kregister;

				if (FAILED(Shader::FD3D11ShaderInterface::CreateConstantsBuffersFromShader(Shader::ENativeShaderType::EShaderType_Vertex, vertexShaderBuffer, out_resourceHandle)))
				{
					out_resourceHandle.bSuccessfullyCompiled = false;
					if (m_InterfaceData.RenderSystems.Count())
						MessageBox(m_InterfaceData.RenderSystems.Front().WindowHandle, _filename, "Fail to create shader.", MB_OK);
					THROW_PARADIGM_EXCEPTION("Fail to reflect vertex shader : " + _filename);
				}

				// Free
				vertexShaderBuffer->Release();
				vertexShaderBuffer = 0;

			}

			void FD3D11Interface::CreatePixelShader(Shader::UShaderResourceHandle& out_resourceHandle, const FString& _filename, const FString& _entryPoint)
			{
				ID3DBlob* errorMessage = nullptr;
				ID3DBlob* pixelShaderBuffer = nullptr;
				LPCSTR profile = (m_InterfaceData.Device->GetFeatureLevel() >= D3D_FEATURE_LEVEL_11_0) ? "ps_5_0" : "ps_4_0";
				UKeyRegister kregister;
				FString uniqueShaderName = _filename + "_" + _entryPoint;


				if (FAILED(D3DX11CompileFromFile(_filename, NULL, NULL, _entryPoint, profile, D3D10_SHADER_ENABLE_STRICTNESS, 0, 0, &pixelShaderBuffer, &errorMessage, NULL)))
				{
					out_resourceHandle.bSuccessfullyCompiled = false;
					SHADER_RUNTIME_COMPILATION_ERROR(_filename, errorMessage);
				}

				if (out_resourceHandle.kPixelShaderKey == INVALID_KEY_REGISTER)
					kregister = m_InterfaceData.ShaderInterface.PixelShader.Add({ std::pair<FString, ID3D11PixelShader*>(uniqueShaderName,{}) });
				else
				{					
					kregister = out_resourceHandle.kPixelShaderKey;
					m_InterfaceData.ShaderInterface.PixelShader[kregister].second->Release();
				}

				if (FAILED(m_InterfaceData.Device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_InterfaceData.ShaderInterface.PixelShader[kregister].second)))
				{
					out_resourceHandle.bSuccessfullyCompiled = false;
					m_InterfaceData.ShaderInterface.PixelShader.Remove(kregister);
					if (m_InterfaceData.RenderSystems.Count())					
						MessageBox(m_InterfaceData.RenderSystems.Front().WindowHandle, _filename, "Fail to create shader.", MB_OK);
					
					THROW_PARADIGM_EXCEPTION("Fail to create shader : " + _filename);
				}


				if (FAILED(Shader::FD3D11ShaderInterface::CreateConstantsBuffersFromShader(Shader::ENativeShaderType::EShaderType_Pixel, pixelShaderBuffer, out_resourceHandle)))
				{
					out_resourceHandle.bSuccessfullyCompiled = false;
					if (m_InterfaceData.RenderSystems.Count())					
						MessageBox(m_InterfaceData.RenderSystems.Front().WindowHandle, _filename, "Fail to create shader.", MB_OK);					
					THROW_PARADIGM_EXCEPTION("Fail to reflect vertex shader : " + _filename);
				}

				// Free
				pixelShaderBuffer->Release();
				pixelShaderBuffer = 0;
				out_resourceHandle.kPixelShaderKey = kregister;
			}
		
			void FD3D11Interface::CreateGeometryShader(Shader::UShaderResourceHandle& out_resourceHandle, const FString& _filename, const FString& _entryPoint)
			{
				ID3DBlob* errorMessage = nullptr;
				ID3DBlob* geometryShaderBuffer = nullptr;
				LPCSTR profile = (m_InterfaceData.Device->GetFeatureLevel() >= D3D_FEATURE_LEVEL_11_0) ? "gs_5_0" : "gs_4_0";
				UKeyRegister kregister;
				FString uniqueShaderName = _filename + "_" + _entryPoint;


				if (FAILED(D3DX11CompileFromFile(_filename, NULL, NULL, _entryPoint, profile, D3D10_SHADER_ENABLE_STRICTNESS, 0, 0, &geometryShaderBuffer, &errorMessage, NULL)))
				{
					out_resourceHandle.bSuccessfullyCompiled = false;
					SHADER_RUNTIME_COMPILATION_ERROR(_filename, errorMessage);
				}

				if (out_resourceHandle.kGeometryShaderKey == INVALID_KEY_REGISTER)
					kregister = m_InterfaceData.ShaderInterface.GeometryShader.Add({ std::pair<FString, ID3D11GeometryShader*>(uniqueShaderName,{}) });
				else
				{
					kregister = out_resourceHandle.kGeometryShaderKey;
					m_InterfaceData.ShaderInterface.GeometryShader[kregister].second->Release();
				}

				if (FAILED(m_InterfaceData.Device->CreateGeometryShader(geometryShaderBuffer->GetBufferPointer(), geometryShaderBuffer->GetBufferSize(), NULL, &m_InterfaceData.ShaderInterface.GeometryShader[kregister].second)))
				{
					out_resourceHandle.bSuccessfullyCompiled = false;
					m_InterfaceData.ShaderInterface.GeometryShader.Remove(kregister);
					if (m_InterfaceData.RenderSystems.Count())
						MessageBox(m_InterfaceData.RenderSystems.Front().WindowHandle, _filename, "Fail to create shader.", MB_OK);
					THROW_PARADIGM_EXCEPTION("Fail to create shader : " + _filename);
				}

				if (FAILED(Shader::FD3D11ShaderInterface::CreateConstantsBuffersFromShader(ENativeShaderType::EShaderType_Geometry, geometryShaderBuffer, out_resourceHandle)))
				{
					out_resourceHandle.bSuccessfullyCompiled = false;
					if (m_InterfaceData.RenderSystems.Count())
						MessageBox(m_InterfaceData.RenderSystems.Front().WindowHandle, _filename, "Fail to create shader.", MB_OK);
					THROW_PARADIGM_EXCEPTION("Fail to reflect vertex shader : " + _filename);
				}

				// Free
				geometryShaderBuffer->Release();
				geometryShaderBuffer = 0;

				out_resourceHandle.kGeometryShaderKey = kregister;
			}
		
			void FD3D11Interface::CreateComputeShader(Shader::UShaderResourceHandle& out_resourceHandle, const FString& _filename, const FString& _entryPoint)
			{
				ID3DBlob* errorMessage = nullptr;
				ID3DBlob* computeShaderBuffer = nullptr;
				LPCSTR profile = (m_InterfaceData.Device->GetFeatureLevel() >= D3D_FEATURE_LEVEL_11_0) ? "cs_5_0" : "cs_4_0";
				UKeyRegister kregister;
				FString uniqueShaderName = _filename + "_" + _entryPoint;

				if (FAILED(D3DX11CompileFromFile(_filename, NULL, NULL, _entryPoint, profile, D3D10_SHADER_ENABLE_STRICTNESS, 0, 0, &computeShaderBuffer, &errorMessage, NULL)))
				{
					out_resourceHandle.bSuccessfullyCompiled = false;
					SHADER_RUNTIME_COMPILATION_ERROR(_filename, errorMessage);
				}
				if (out_resourceHandle.kComputeShaderKey == INVALID_KEY_REGISTER)
					kregister = m_InterfaceData.ShaderInterface.ComputeShader.Add({ std::pair<FString, ID3D11ComputeShader*>(uniqueShaderName,{}) });
				else
				{
					kregister = out_resourceHandle.kComputeShaderKey;
					m_InterfaceData.ShaderInterface.ComputeShader[kregister].second->Release();
				}

				if (FAILED(m_InterfaceData.Device->CreateComputeShader(computeShaderBuffer->GetBufferPointer(), computeShaderBuffer->GetBufferSize(), NULL, &m_InterfaceData.ShaderInterface.ComputeShader[kregister].second)))
				{
					out_resourceHandle.bSuccessfullyCompiled = false;
					m_InterfaceData.ShaderInterface.ComputeShader.Remove(kregister);					
					if (m_InterfaceData.RenderSystems.Count())					
						MessageBox(m_InterfaceData.RenderSystems.Front().WindowHandle, _filename, "Fail to create shader.", MB_OK);					
					THROW_PARADIGM_EXCEPTION("Fail to create shader : " + _filename);
				}

				if (FAILED(Shader::FD3D11ShaderInterface::CreateConstantsBuffersFromShader(ENativeShaderType::EShaderType_Compute, computeShaderBuffer, out_resourceHandle)))
				{
					out_resourceHandle.bSuccessfullyCompiled = false;
					if (m_InterfaceData.RenderSystems.Count())
						MessageBox(m_InterfaceData.RenderSystems.Front().WindowHandle, _filename, "Fail to create shader.", MB_OK);
					THROW_PARADIGM_EXCEPTION("Fail to reflect vertex shader : " + _filename);
				}

				// Free
				computeShaderBuffer->Release();
				computeShaderBuffer = 0;

				out_resourceHandle.kComputeShaderKey = kregister;
			}

			void FD3D11Interface::CreateSamplerState(UKeyRegister& out_register, const UTextureDescriptor& _texDesc)
			{
				D3D11_SAMPLER_DESC samplerDesc;
				samplerDesc.Filter = NativeConversion(_texDesc.FilteringMode);
				samplerDesc.AddressU = NativeConversion(_texDesc.WrappingMode);
				samplerDesc.AddressV = NativeConversion(_texDesc.WrappingMode);
				samplerDesc.AddressW = NativeConversion(_texDesc.WrappingMode);
				samplerDesc.MipLODBias = 0.0f;
				samplerDesc.MaxAnisotropy = _texDesc.AnisotropyLevel;
				samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
				samplerDesc.BorderColor[0] = 0;
				samplerDesc.BorderColor[1] = 0;
				samplerDesc.BorderColor[2] = 0;
				samplerDesc.BorderColor[3] = 0;
				samplerDesc.MinLOD = 0;
				samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

				if (!m_InterfaceData.ShaderInterface.SamplerStates.Contains(out_register))
					out_register = m_InterfaceData.ShaderInterface.SamplerStates.Add({});
				else
					m_InterfaceData.ShaderInterface.SamplerStates[out_register]->Release();
			
				// Creates the texture sampler state.
				if (FAILED(m_InterfaceData.Device->CreateSamplerState(&samplerDesc, &m_InterfaceData.ShaderInterface.SamplerStates[out_register])))
				{
					m_InterfaceData.ShaderInterface.SamplerStates.Remove(out_register);
					FPrint::Print("Failed to create sampler state.", EParadigmDebugLevel::ERROR_LEVEL);
					out_register = { INVALID_KEY_REGISTER, INVALID_KEY_REGISTER };
				}
			}
			
			void FD3D11Interface::CreateTextureResource(UNativeTextureResource& out_kNatTex, const UTextureDescriptor& _textureDesc)
			{
				// Check if this register is already use.
				if(!m_InterfaceData.ShaderInterface.ResourceViews.Contains(out_kNatTex.kResourceView))
					out_kNatTex.kResourceView = m_InterfaceData.ShaderInterface.ResourceViews.Add({});
				else				
					m_InterfaceData.ShaderInterface.ResourceViews[out_kNatTex.kResourceView]->Release();			

				if (FAILED(D3DX11CreateShaderResourceViewFromFile(m_InterfaceData.Device, _textureDesc.Filename, nullptr, nullptr, &m_InterfaceData.ShaderInterface.ResourceViews[out_kNatTex.kResourceView], nullptr)))
				{
					m_InterfaceData.ShaderInterface.ResourceViews.Remove(out_kNatTex.kResourceView);
					out_kNatTex = { INVALID_KEY_REGISTER, INVALID_KEY_REGISTER };
					return;
				}
				
				HRESULT result;

				if (FString::FPathSlicer::Extension(_textureDesc.Filename, true) == ".dds")
					result = DirectX::CreateDDSTextureFromFile(m_InterfaceData.Device, _textureDesc.Filename.ToConstWideString().c_str(), nullptr, &m_InterfaceData.ShaderInterface.ResourceViews[out_kNatTex.kResourceView]);				
				else
					result = DirectX::CreateWICTextureFromFile(m_InterfaceData.Device, _textureDesc.Filename.ToConstWideString().c_str(), nullptr, &m_InterfaceData.ShaderInterface.ResourceViews[out_kNatTex.kResourceView]);

				if(FAILED(result))
				{
					m_InterfaceData.ShaderInterface.ResourceViews.Remove(out_kNatTex.kResourceView);
					FPrint::Print("Failed to load texture : " + result, EParadigmDebugLevel::ERROR_LEVEL);
					out_kNatTex = { INVALID_KEY_REGISTER, INVALID_KEY_REGISTER };
					return;
				}

				CreateSamplerState(out_kNatTex.kSamplerState, _textureDesc);
			}

			void FD3D11Interface::BuildNativeShaderResources(UKeyRegister _kShaderResource)
			{
				Shader::FD3D11ShaderInterface::ConfigureShaderResourceHandle(m_InterfaceData, m_InterfaceData.ShaderInterface.ShaderResources[_kShaderResource]);
			}

			bool FD3D11Interface::BindShaderResources(UKeyRegister _kShaderResource, bool _bTryOptimize)
			{
				/////////////////////////////////////////////////////////////////////////////
				// RESOURCE BLOCKS BINDING
				//________________________________________________________________
				D3D11_MAPPED_SUBRESOURCE mappedResource;
				Shader::UShaderResourceHandle* shaderRes = &m_InterfaceData.ShaderInterface.ShaderResources[_kShaderResource];
				if (!shaderRes->bSuccessfullyCompiled) // if invalid or incomplete shader - Pinky shade !
					shaderRes = &m_InterfaceData.ShaderInterface.ShaderResources[m_InterfaceData.ShaderInterface.kNativeDebugShader];

				const TArray<Shader::UShaderDataBlockResource>& dabaBlock = shaderRes->Data;

				uint sizeBuff = 0;
				uint count = shaderRes->Data.Count();
				for (uint i = 0; i < count; ++i)
				{
					try
					{
						ID3D11Buffer* blockBuffer = m_InterfaceData.ShaderInterface.BlockBuffers[dabaBlock[i].KeyBlockBuffer];
					}
					catch (const ParadigmException& paradigmException)
					{
						if (paradigmException.GetParadigmExceptionCode() == EParadigmExceptionCode::OUT_OF_RANGE_ERROR)
						{
							FPrint::Print(PARADIGM_TEMPORALITY_LOCATION_DETAILS + "Constant buffer \"" + dabaBlock[i].Name + "\" no initialize.", EParadigmDebugLevel::WARNING_LEVEL);
							continue;
						}
						else
							throw;
					}

					if (FAILED(m_InterfaceData.DeviceContext->Map(m_InterfaceData.ShaderInterface.BlockBuffers[dabaBlock[i].KeyBlockBuffer], 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource)))
						return false;

					sizeBuff = 0;
					for (uint j = 0; j < dabaBlock[i].Resources.Count(); ++j)
					{
						if (!j)
							memcpy(mappedResource.pData, dabaBlock[i].Resources[j].Data, dabaBlock[i].Resources[j].Size);
						else
						{
							// Hack'no Justsu : Memory Jumpuu !
							sizeBuff += dabaBlock[i].Resources[j - 1].Size;
							memcpy((((char*)mappedResource.pData) + sizeBuff), dabaBlock[i].Resources[j].Data, dabaBlock[i].Resources[j].Size);
						}
					}

					m_InterfaceData.DeviceContext->Unmap(m_InterfaceData.ShaderInterface.BlockBuffers[dabaBlock[i].KeyBlockBuffer], 0);

					if (dabaBlock[i].ShaderType == ENativeShaderType::EShaderType_Vertex)
						m_InterfaceData.DeviceContext->VSSetConstantBuffers(dabaBlock[i].Index, 1, &m_InterfaceData.ShaderInterface.BlockBuffers[dabaBlock[i].KeyBlockBuffer]);
					else if (dabaBlock[i].ShaderType == ENativeShaderType::EShaderType_Pixel)
						m_InterfaceData.DeviceContext->PSSetConstantBuffers(dabaBlock[i].Index, 1, &m_InterfaceData.ShaderInterface.BlockBuffers[dabaBlock[i].KeyBlockBuffer]);
					else if (dabaBlock[i].ShaderType == ENativeShaderType::EShaderType_Geometry)
						m_InterfaceData.DeviceContext->GSSetConstantBuffers(dabaBlock[i].Index, 1, &m_InterfaceData.ShaderInterface.BlockBuffers[dabaBlock[i].KeyBlockBuffer]);
					else // EShaderType_Compute
						m_InterfaceData.DeviceContext->CSSetConstantBuffers(dabaBlock[i].Index, 1, &m_InterfaceData.ShaderInterface.BlockBuffers[dabaBlock[i].KeyBlockBuffer]);
				}

				/////////////////////////////////////////////////////////////////////////////
				// RESOURCE TEXTURES BINDING
				//________________________________________________________________
				TArray<Shader::UShaderTextureResource>& textures = shaderRes->Textures;
				count = textures.Count();
				UKeyRegister keyRv, keySs, knullRv, knullSs;
				
				m_InterfaceData.ShaderInterface.ResourceViews.GetRegister(0, knullRv);
				m_InterfaceData.ShaderInterface.SamplerStates.GetRegister(0, knullSs);

				if (knullRv == NULL_KEY_REGISTER || knullSs == NULL_KEY_REGISTER)
					THROW_PARADIGM_EXCEPTION("Invalid native texture bind. Did you forget to native synchronize your resource?");

				for (uint i = 0; i < count; ++i)
				{
					if (_bTryOptimize && !textures[i].bOudated)
						continue;

					keyRv = textures[i].KeysHandle.kResourceView != INVALID_KEY_REGISTER ? textures[i].KeysHandle.kResourceView : knullRv;
					keySs = textures[i].KeysHandle.kSamplerState != INVALID_KEY_REGISTER ? textures[i].KeysHandle.kSamplerState : knullSs;

					switch (textures[i].ShaderType)
					{
						case ENativeShaderType::EShaderType_Vertex:							
							m_InterfaceData.DeviceContext->VSSetShaderResources(textures[i].Index, 1, &m_InterfaceData.ShaderInterface.ResourceViews[keyRv]);
							m_InterfaceData.DeviceContext->VSSetSamplers(textures[i].Index, 1, &m_InterfaceData.ShaderInterface.SamplerStates[keySs]);
							break;
						case ENativeShaderType::EShaderType_Pixel:							
							m_InterfaceData.DeviceContext->PSSetShaderResources(textures[i].Index, 1, &m_InterfaceData.ShaderInterface.ResourceViews[keyRv]);
							m_InterfaceData.DeviceContext->PSSetSamplers(textures[i].Index, 1, &m_InterfaceData.ShaderInterface.SamplerStates[keySs]);
							break;
						case ENativeShaderType::EShaderType_Geometry:
							m_InterfaceData.DeviceContext->GSSetShaderResources(textures[i].Index, 1, &m_InterfaceData.ShaderInterface.ResourceViews[keyRv]);
							m_InterfaceData.DeviceContext->GSSetSamplers(textures[i].Index, 1, &m_InterfaceData.ShaderInterface.SamplerStates[keySs]);
							break;
						default:
							m_InterfaceData.DeviceContext->CSSetShaderResources(textures[i].Index, 1, &m_InterfaceData.ShaderInterface.ResourceViews[keyRv]);
							m_InterfaceData.DeviceContext->CSSetSamplers(textures[i].Index, 1, &m_InterfaceData.ShaderInterface.SamplerStates[keySs]);
							break;
					}
					textures[i].bOudated = false;
				}

				return true;
			}

			void FD3D11Interface::BindShader(UKeyRegister _kShaderResource)
			{
				Shader::UShaderResourceHandle* shaderRes = &m_InterfaceData.ShaderInterface.ShaderResources[_kShaderResource];
				if (!shaderRes->bSuccessfullyCompiled) // if invalid or incomplete shader - Pinky shade !
					shaderRes = &m_InterfaceData.ShaderInterface.ShaderResources[m_InterfaceData.ShaderInterface.kNativeDebugShader];

				if (shaderRes->kVertexShaderKey != INVALID_KEY_REGISTER)
				{
					m_InterfaceData.DeviceContext->VSSetShader(m_InterfaceData.ShaderInterface.VertexShaders[shaderRes->kVertexShaderKey].second, nullptr, 0);
					m_InterfaceData.DeviceContext->IASetInputLayout(m_InterfaceData.ShaderInterface.InputLayouts[shaderRes->kInputLayoutKey].second);
				}
				else
				{
					m_InterfaceData.DeviceContext->VSSetShader(nullptr, nullptr, 0);
					m_InterfaceData.DeviceContext->IASetInputLayout(nullptr);
				}

				if (shaderRes->kPixelShaderKey != INVALID_KEY_REGISTER)
					m_InterfaceData.DeviceContext->PSSetShader(m_InterfaceData.ShaderInterface.PixelShader[shaderRes->kPixelShaderKey].second, nullptr, 0);
				else
					m_InterfaceData.DeviceContext->PSSetShader(nullptr, nullptr, 0);

				if (shaderRes->kGeometryShaderKey != INVALID_KEY_REGISTER)
					m_InterfaceData.DeviceContext->GSSetShader(m_InterfaceData.ShaderInterface.GeometryShader[shaderRes->kGeometryShaderKey].second, nullptr, 0);
				else
					m_InterfaceData.DeviceContext->GSSetShader(nullptr, nullptr, 0);

				if (shaderRes->kComputeShaderKey != INVALID_KEY_REGISTER)
					m_InterfaceData.DeviceContext->CSSetShader(m_InterfaceData.ShaderInterface.ComputeShader[shaderRes->kComputeShaderKey].second, nullptr, 0);
				else
					m_InterfaceData.DeviceContext->CSSetShader(nullptr, nullptr, 0);
			}
			
#pragma endregion 


			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// ELEMENT ACCESS
			//____________________________________	____________________________________	____________________________________	
#pragma region ELEMENT ACCESS
			Shader::UShaderResourceHandle& FD3D11Interface::GetShaderResourceHandle(UKeyRegister _kShaderResource)
			{
				try
				{
					return m_InterfaceData.ShaderInterface.ShaderResources[_kShaderResource];
				}
				catch (const ParadigmException&)
				{
					throw ParadigmException(EParadigmExceptionCode::ARGUMENT_ERROR, PARADIGM_TEMPORALITY_LOCATION_DETAILS + "Invalid or corrupted key register.", EParadigmDebugLevel::WARNING_LEVEL);					
				}
			}

			bool FD3D11Interface::GetShaderResourceHandle(Shader::UShaderResourceHandle& out_shaderRes, UKeyRegister _kShaderResource)
			{				
				return m_InterfaceData.ShaderInterface.ShaderResources.Get(_kShaderResource, out_shaderRes);
			}

			bool FD3D11Interface::SetShaderResourceHandle(const Shader::UShaderResourceHandle& _shaderRes, UKeyRegister _kShaderResource)
			{
				return m_InterfaceData.ShaderInterface.ShaderResources.Replace(_kShaderResource, _shaderRes);
			}

			uint FD3D11Interface::GetViewportWidth(ETargetViewport _target)
			{
				return m_InterfaceData.RenderSystems[(uint)_target].Viewport.Width;
			}
			uint FD3D11Interface::GetViewportHeight(ETargetViewport _target)
			{
				return m_InterfaceData.RenderSystems[(uint)_target].Viewport.Height;
			}

#pragma endregion 


			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// RENDER FUNCTIONALITY
			//____________________________________	____________________________________	____________________________________	
#pragma region RENDER FUNCTIONALITY			
			void FD3D11Interface::DrawCall(uint _elementCount, uint _startIndex)
			{
				m_InterfaceData.DeviceContext->DrawIndexed(_elementCount, 0, 0);
			}

			void FD3D11Interface::SetPrimitiveDrawingMode(ENativePrimitiveTopology _drawMode) 
			{ 
				m_InterfaceData.DeviceContext->IASetPrimitiveTopology(NativeConversion(_drawMode));
			}
#pragma endregion 


			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// PIPELINE FUNCTIONNALITY
			//____________________________________	____________________________________	____________________________________	
#pragma region PIPELINE FUNCTIONALITY
			void FD3D11Interface::BeginScene(ETargetViewport _viewport, UColor _clearColor)
			{
				if (!m_InterfaceData.RenderSystems.Count())
					return;

				if ((uint)_viewport >= m_InterfaceData.RenderSystems.Count())
					_viewport = ETargetViewport::VIEWPORT_0;

				UD3D11RenderSystemAttributes& viewport = m_InterfaceData.RenderSystems[_viewport];

				// Set and clean the depth buffer and render target.
				m_InterfaceData.DeviceContext->RSSetViewports(1, &viewport.Viewport);
				m_InterfaceData.DeviceContext->ClearRenderTargetView(viewport.RenderTarget, (float*)&_clearColor);
				m_InterfaceData.DeviceContext->ClearDepthStencilView(m_InterfaceData.DepthStencilViews[viewport.DepthStencilViewKey], viewport.ClearFlag, 1.0f, 0);
				m_InterfaceData.DeviceContext->OMSetRenderTargets(1, &viewport.RenderTarget, m_InterfaceData.DepthStencilViews[viewport.DepthStencilViewKey]);
			}

			void FD3D11Interface::EndScene(ETargetViewport _viewport)
			{				
				if (!m_InterfaceData.RenderSystems.Count())
					return;
				if ((uint)_viewport >= m_InterfaceData.RenderSystems.Count())
					_viewport = ETargetViewport::VIEWPORT_0;

				UD3D11RenderSystemAttributes& viewport = m_InterfaceData.RenderSystems[_viewport];

				// Set the Rasterizer state (Cull, fill mode, ...) and the depth stencil state (z-buffer algorithm, ...).
				m_InterfaceData.DeviceContext->OMSetDepthStencilState(m_InterfaceData.DepthStencilStates[viewport.DepthStencilStateKey], 1);
				m_InterfaceData.DeviceContext->RSSetState(m_InterfaceData.RasterizerStates[viewport.RasterizerStateKey]);
								
				if (viewport.bVerticalSynchro)
					viewport.SwapChain->Present(1, 0);
				else 
					viewport.SwapChain->Present(0, 0);
			}
#pragma endregion 


			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// FUNCTIONALITY
			//____________________________________	____________________________________	____________________________________	
#pragma region FUNCTIONALITY
			void FD3D11Interface::BindInputAssembly(UKeyRegister _elementBuffer, UKeyRegister _vertexBuffer)
			{
				BindElementBuffer(_elementBuffer);
				BindVertexBuffer(_vertexBuffer);
			}

			void FD3D11Interface::BindElementBuffer(UKeyRegister _elementBufferKey) 
			{
				try
				{
					m_InterfaceData.DeviceContext->IASetIndexBuffer(m_InterfaceData.ShaderInterface.BlockBuffers[_elementBufferKey], DXGI_FORMAT_R32_UINT, 0);
				}
				PARADIGM_CATCH_AND_CUSTOM_EXCEPTION("Invalid Element buffer key. this may be due to a wrong initialization of a UMetaMeshShape - GMeshSHape.")
			}
			
			void FD3D11Interface::BindVertexBuffer(UKeyRegister _vertexBufferKey)
			{
				uint stride = sizeof(UNativeVertex);
				uint offset = 0;
				try
				{
					m_InterfaceData.DeviceContext->IASetVertexBuffers(0, 1, &m_InterfaceData.ShaderInterface.BlockBuffers[_vertexBufferKey], &stride, &offset);
				}
				PARADIGM_CATCH_AND_CUSTOM_EXCEPTION("Invalid Vertex buffer key. this may be due to a wrong initialization of a UMetaMeshShape - GMeshSHape.")
			}			

			void FD3D11Interface::CreateElementAndVertexBuffers(UKeyRegister& out_indexBufferKey, UKeyRegister& out_vertexBufferKey, const TArray<uint>& _elements, const TArray<UVertex>& _vertices)
			{
				CreateElementBuffer(out_indexBufferKey, _elements);
				CreateVertexBuffer(out_vertexBufferKey, _vertices);
			}
			
			void FD3D11Interface::CreateElementBuffer(UKeyRegister& out_kregister, const TArray<uint>& _indices)
			{
				D3D11_BUFFER_DESC indexBufferDesc;
				uint indexCount = _indices.Count();
				
				D3D11_SUBRESOURCE_DATA indexData;

				//Met en place la description du buffeur de vertex
				indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
				indexBufferDesc.ByteWidth = sizeof(uint) * _indices.Count();
				indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
				indexBufferDesc.CPUAccessFlags = 0;
				indexBufferDesc.MiscFlags = 0;
				indexBufferDesc.StructureByteStride = 0;

				// Gives the sub-resource structure a pointer to the vertex array
				indexData.pSysMem = _indices.GetData();
				indexData.SysMemPitch = 0;
				indexData.SysMemSlicePitch = 0;


				// Create the element buffer
				if (!m_InterfaceData.ShaderInterface.BlockBuffers.Contains(out_kregister))
					out_kregister = m_InterfaceData.ShaderInterface.BlockBuffers.Add({});
				else
					m_InterfaceData.ShaderInterface.BlockBuffers[out_kregister]->Release();
				if (FAILED(m_InterfaceData.Device->CreateBuffer(&indexBufferDesc, &indexData, &m_InterfaceData.ShaderInterface.BlockBuffers[out_kregister])))
				{
					FPrint::Print(PARADIGM_LOCATION + " Failed to create buffer.\n| Error Code {" + FString::ToString(GetLastError()) + "}");
					m_InterfaceData.ShaderInterface.BlockBuffers.Remove(out_kregister);					
					out_kregister = INVALID_KEY_REGISTER;
				}				
			}
			
			void FD3D11Interface::CreateVertexBuffer(UKeyRegister& out_kregister, const TArray<UVertex>& _vertices)
			{
				D3D11_BUFFER_DESC vertexBufferDesc;
				D3D11_SUBRESOURCE_DATA vertexData;

				// Vertex buffer descriptor
				vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
				vertexBufferDesc.ByteWidth = sizeof(UNativeVertex) * _vertices.Count();
				vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				vertexBufferDesc.CPUAccessFlags = 0;
				vertexBufferDesc.MiscFlags = 0;
				vertexBufferDesc.StructureByteStride = 0;

				// Sub resource descriptor
				vertexData.pSysMem = _vertices.GetData();
				vertexData.SysMemPitch = 0;
				vertexData.SysMemSlicePitch = 0;

				if (!m_InterfaceData.ShaderInterface.BlockBuffers.Contains(out_kregister))
					out_kregister = m_InterfaceData.ShaderInterface.BlockBuffers.Add({});
				else
					m_InterfaceData.ShaderInterface.BlockBuffers[out_kregister]->Release();
				if (FAILED(m_InterfaceData.Device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_InterfaceData.ShaderInterface.BlockBuffers[out_kregister])))
				{
					FPrint::Print(PARADIGM_LOCATION + " Failed to create buffer.\n| Error Code {" + (char*)GetLastError() + "}");
					m_InterfaceData.ShaderInterface.BlockBuffers.Remove(out_kregister);
					out_kregister = INVALID_KEY_REGISTER;
				}	
			}
#pragma endregion 
			

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// API MISCELLANEOUS FUNCTIONALITY
			//____________________________________	____________________________________	____________________________________	
#pragma region API MISCELLANEOUS FUNCTIONALITY

			void FD3D11Interface::GetVideoCardInfo(UGraphicsCardInfo& _outVideoCardInfo) 
			{ 
				_outVideoCardInfo = m_InterfaceData.GraphicsCardInfo;				
			}
#pragma endregion 


			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// PRIVATE FUNCTIONALITY
			//____________________________________	____________________________________	____________________________________	
#pragma region PRIVATE FUNCTIONALITY
			void FD3D11Interface::ComputeRefreshRate(uint _widthResolution, uint _heightResolution)
			{			
				uint numModes{ 0 };
				DXGI_MODE_DESC* displayModeList;

				// Gets the number of modes corresponding to the DXGI_FORMAT_R8G8B8A8_UNORM display format for the main adapter (screen).
				if (FAILED(m_DXGIAdapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL)))
					THROW_PARADIGM_EXCEPTION_NATIVE_IMPLEMENTATION_ERROR(PARADIGM_DEV_SIGNATURE_ARUMA);
				
				// Create a list to store all possible display modes for this combination of display and graphics card
				displayModeList = new DXGI_MODE_DESC[numModes];
				if (!displayModeList)
					THROW_PARADIGM_EXCEPTION_NATIVE_IMPLEMENTATION_ERROR(PARADIGM_DEV_SIGNATURE_ARUMA);

				/** Scans all display modes and finds the one that matches the screen size.
				When a match is found, stores the numerator and denominator of the refresh rate  */
				for (uint i = 0; i < numModes; i++)
				{
					if (displayModeList[i].Width == (unsigned int)_widthResolution)
					{
						if (displayModeList[i].Height == (unsigned int)_heightResolution)
						{
							m_Numerator = displayModeList[i].RefreshRate.Numerator;
							m_Denominator = displayModeList[i].RefreshRate.Denominator;
						}
					}
				}

				delete[] displayModeList;
				displayModeList = nullptr;
			}
			
			void FD3D11Interface::CreateDepthBuffer(UD3D11RenderSystemAttributes& out_renderSys, const UNativeTextureResourceDescriptor& _attrib)
			{
				D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;

				if (out_renderSys.DepthBufferTexture2DKey != INVALID_KEY_REGISTER)
				{
					m_InterfaceData.Texture2DBuffers[out_renderSys.DepthBufferTexture2DKey]->Release();
					m_InterfaceData.Texture2DBuffers.Remove(out_renderSys.DepthBufferTexture2DKey);
				}

				out_renderSys.DepthBufferTexture2DKey = CreateNativeTexture2DResource(_attrib);

				////////////////////////////////////////////////
				// DEPTH STENCIL VIEW CONFIGURATION
				//____________________________________	
				ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

				if(out_renderSys.DepthStencilViewKey == INVALID_KEY_REGISTER)
					out_renderSys.DepthStencilViewKey = m_InterfaceData.DepthStencilViews.Add({});

				depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
				depthStencilViewDesc.ViewDimension = out_renderSys.bMultisampling ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;
				depthStencilViewDesc.Texture2D.MipSlice = 0; // The index of the first mipmap level to use.
				depthStencilViewDesc.Texture2DMSArray.ArraySize = 1; // The index of the first mipmap level to use.
				depthStencilViewDesc.Texture2DMSArray.FirstArraySlice = 0; // The index of the first mipmap level to use.

				 ////////////////////////////////////////////////
				 // FIX 8 GO LEAKS?
				 //__
				if (m_InterfaceData.DepthStencilViews[out_renderSys.DepthStencilViewKey])
					m_InterfaceData.DepthStencilViews[out_renderSys.DepthStencilViewKey]->Release();

				if (FAILED(m_InterfaceData.Device->CreateDepthStencilView(m_InterfaceData.Texture2DBuffers[out_renderSys.DepthBufferTexture2DKey], &depthStencilViewDesc, &m_InterfaceData.DepthStencilViews[out_renderSys.DepthStencilViewKey])))
					THROW_PARADIGM_EXCEPTION_BAD_IMPLEMENTATION(PARADIGM_DEV_SIGNATURE_ARUMA);
			}
			
			void FD3D11Interface::CreateRenderSystem(UD3D11RenderSystemAttributes& out_renderSys, HWND _handle, uint _widthResolution, uint _heightResolution)
			{
				DXGI_SWAP_CHAIN_DESC swapChainDesc;
				ID3D11Texture2D* backBufferPtr;

				uint CountSample = 8;
				uint numQualityLevels = 0;
				m_InterfaceData.Device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, CountSample, &numQualityLevels);
				if (numQualityLevels > 0)
					numQualityLevels--;

				////////////////////////////////////////////////
				// SWAP CHAIN CONFIGURATION
				//____________________________________					
				if (!out_renderSys.SwapChain)
				{
					ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

					// Use only one back buffer.
					swapChainDesc.BufferCount = 1;

					swapChainDesc.BufferDesc.Width = _widthResolution;
					swapChainDesc.BufferDesc.Height = _heightResolution;

					swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

					swapChainDesc.BufferDesc.RefreshRate.Numerator = out_renderSys.bVerticalSynchro ? m_Numerator : 0;
					swapChainDesc.BufferDesc.RefreshRate.Denominator = out_renderSys.bVerticalSynchro ? m_Denominator : 1;

					swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

					swapChainDesc.OutputWindow = out_renderSys.WindowHandle = _handle;

					// Multisampling settings (Depth buffer must also be set !)

					swapChainDesc.SampleDesc.Count = CountSample;
					swapChainDesc.SampleDesc.Quality = numQualityLevels;

					out_renderSys.bMultisampling = CountSample ? true : false;

					swapChainDesc.Windowed = !out_renderSys.bFullscreen;

					swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
					swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

					// Set back buffer swap's effect. 
					swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;


					if (FAILED(m_DXGIFactory->CreateSwapChain(m_InterfaceData.Device, &swapChainDesc, &out_renderSys.SwapChain)))
						THROW_PARADIGM_EXCEPTION_NATIVE_IMPLEMENTATION_ERROR(PARADIGM_DEV_SIGNATURE_ARUMA);
				}
				else
				{
					m_InterfaceData.DeviceContext->RSSetViewports(0, 0);
					out_renderSys.RenderTarget->Release();
					out_renderSys.SwapChain->ResizeBuffers(1, _widthResolution, _heightResolution, DXGI_FORMAT_R8G8B8A8_UNORM, 0);									
				}

				if (FAILED(out_renderSys.SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr)))
					THROW_PARADIGM_EXCEPTION_NATIVE_IMPLEMENTATION_ERROR(PARADIGM_DEV_SIGNATURE_ARUMA);
								
				if (FAILED(m_InterfaceData.Device->CreateRenderTargetView(backBufferPtr, nullptr, &out_renderSys.RenderTarget)))
					THROW_PARADIGM_EXCEPTION_NATIVE_IMPLEMENTATION_ERROR(PARADIGM_DEV_SIGNATURE_ARUMA);

				// Free 
				backBufferPtr->Release();
				backBufferPtr = nullptr;
			
				// Viewport Configuration
				out_renderSys.Viewport.Width = (float)_widthResolution;
				out_renderSys.Viewport.Height = (float)_heightResolution;
				out_renderSys.Viewport.MinDepth = 0.f;
				out_renderSys.Viewport.MaxDepth = 1.f;
				out_renderSys.Viewport.TopLeftX = 0.f;
				out_renderSys.Viewport.TopLeftY = 0.f;

				// Set the viewport
				m_InterfaceData.DeviceContext->RSSetViewports(1, &out_renderSys.Viewport);

				UNativeTextureResourceDescriptor textAttrib {};
				textAttrib.Width = _widthResolution;
				textAttrib.Height = _heightResolution;
				textAttrib.MultisampleCount = CountSample;
				textAttrib.Format = ENativeFormat::NAT_FORMAT_D24_UNORM_S8_UINT;
				textAttrib.TextureDimension = ENativeTextureDimension::ETextureDimension_2D;
				CreateDepthBuffer(out_renderSys, textAttrib);
			}

			void FD3D11Interface::FillGraphicsCardInfo()
			{
				try
				{
					DXGI_ADAPTER_DESC adapterDesc;
					
					// Get graphics card descriptor
					if (FAILED(m_DXGIAdapter->GetDesc(&adapterDesc)))
						THROW_PARADIGM_EXCEPTION_NATIVE_IMPLEMENTATION_ERROR(PARADIGM_DEV_SIGNATURE_ARUMA);
					m_InterfaceData.GraphicsCardInfo.Memory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024); // Mo

					wstring wstr(adapterDesc.Description);
					std::string str(wstr.begin(), wstr.end());
					m_InterfaceData.GraphicsCardInfo.Name = str;										
				}
				catch (const ParadigmException& except)
				{
					FPrint::Print(except.SumUp(), EParadigmDebugLevel::CAUGHT_EXCEPTION);
				}
			}
#pragma endregion 

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// TERMINATE FUNCTIONALITY
			//____________________________________	____________________________________	____________________________________	
#pragma region 
			void FD3D11Interface::TerminateRenderSystem()
			{
				for (TArray<UD3D11RenderSystemAttributes>::Iterator it = m_InterfaceData.RenderSystems.Begin(); it != m_InterfaceData.RenderSystems.End(); ++it)
				{
					if ((*it).SwapChain)
					{
						(*it).SwapChain->SetFullscreenState(false, 0);
						(*it).SwapChain->Release();
					}
					if ((*it).RenderTarget)
						(*it).RenderTarget->Release();
					(*it).WindowHandle = nullptr;
				}
			}

			void FD3D11Interface::TerminateShaderInterface()
			{
				// Free Shader buffer
				ClearNativeShaderKeyTable(m_InterfaceData.ShaderInterface.VertexShaders);
				ClearNativeShaderKeyTable(m_InterfaceData.ShaderInterface.PixelShader);
				ClearNativeShaderKeyTable(m_InterfaceData.ShaderInterface.ComputeShader);
				ClearNativeShaderKeyTable(m_InterfaceData.ShaderInterface.GeometryShader);
				ClearNativeShaderKeyTable(m_InterfaceData.ShaderInterface.InputLayouts);
				ClearNativeKeyTable(m_InterfaceData.ShaderInterface.BlockBuffers);

				// Free Shader resources buffer
				ClearNativeKeyTable(m_InterfaceData.ShaderInterface.ResourceViews);
				ClearNativeKeyTable(m_InterfaceData.ShaderInterface.SamplerStates);

				TerminateShaderResource();
			}

			void FD3D11Interface::TerminateShaderResource()
			{
				TArray<void*> outdatedPtr;
				for (TKeyTable<UShaderResourceHandle>::Iterator itSr = m_InterfaceData.ShaderInterface.ShaderResources.Begin(); itSr != m_InterfaceData.ShaderInterface.ShaderResources.End(); ++itSr)				
					TerminateShaderDataBlockResource(*itSr, outdatedPtr);
			}

			void FD3D11Interface::TerminateShaderDataBlockResource(UShaderResourceHandle& out_resHandler, TArray<void*>& _outdatedPtr)
			{
				for (TArray<UShaderDataBlockResource>::Iterator itData = out_resHandler.Data.Begin(); itData != out_resHandler.Data.End(); ++itData)
				{
					for (TArray<UShaderDataResource>::Iterator itRes = (*itData).Resources.Begin(); itRes != (*itData).Resources.End(); ++itRes)
					{
						for (uint i = 0; i < _outdatedPtr.Count(); ++i)
						{
							if (_outdatedPtr[i] == (*itRes).Data)
							{
								(*itRes).Data = nullptr;
								continue;
							}
						}

						if ((*itRes).Data)
						{
							_outdatedPtr.Add((*itRes).Data);
							free((*itRes).Data);
							(*itRes).Data = nullptr;
						}
					}
				}
			}


			void FD3D11Interface::TerminateD3D11Interface()
			{
				TerminateRenderSystem();

				TerminateShaderInterface();

				// Free native API textures buffer
				ClearNativeKeyTable(m_InterfaceData.Texture1DBuffers);
				ClearNativeKeyTable(m_InterfaceData.Texture2DBuffers);
				ClearNativeKeyTable(m_InterfaceData.Texture3DBuffers);

				// Free native API resources buffer
				ClearNativeKeyTable(m_InterfaceData.DepthStencilStates);
				ClearNativeKeyTable(m_InterfaceData.DepthStencilViews);
				ClearNativeKeyTable(m_InterfaceData.RasterizerStates);


				// Free native API handlers
				if (m_InterfaceData.DeviceContext)
				{
					m_InterfaceData.DeviceContext->Release();
					m_InterfaceData.DeviceContext = nullptr;
				}
				if (m_InterfaceData.Device)
				{
					m_InterfaceData.Device->Release();
					m_InterfaceData.Device = nullptr;
				}

				// Leak Profiling
				if (m_D3D11Debug)
				{
					m_D3D11Debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
					m_D3D11Debug = nullptr;
				}
			}

#pragma endregion
		}
	}
}