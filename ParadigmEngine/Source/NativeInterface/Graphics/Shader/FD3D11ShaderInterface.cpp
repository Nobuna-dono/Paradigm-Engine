#include <NativeInterface/Graphics/Shader/FD3D11ShaderInterface.h>
#include <NativeInterface/Graphics/FD3D11Interface.h>
#include <NativeInterface/Graphics/NativeGraphicsEnums_D3D11.h>

namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Graphics
		{
			namespace Shader
			{				
				////////////////////////////////////////////////
				// PIRVATE FUNCTIONALITY
				//____________________________________	
				void FD3D11ShaderInterface::CreateShaderResourceViewFromBuffer(UShaderReflectionBufferDescription& _buffer, UShaderDataBlockResource& out_shaderResourceView)
				{
					uint count = _buffer.Description->Variables;
					out_shaderResourceView.Resources.Reserve(count);
					
					for (uint i = 0; i < count; i++)
					{
						ID3D11ShaderReflectionVariable* variable = nullptr;
						variable = _buffer.ReflectionBuffer->GetVariableByIndex(i);

						D3D11_SHADER_VARIABLE_DESC variableDesc;
						variable->GetDesc(&variableDesc);
						
						if (out_shaderResourceView.Resources.Count() < i + 1)
							out_shaderResourceView.Resources.Add({});

						if (out_shaderResourceView.Index != _buffer.RegisterIndex ||
							out_shaderResourceView.Resources[i].Name != variableDesc.Name ||
							out_shaderResourceView.Resources[i].Size != variableDesc.Size)
						{

							out_shaderResourceView.Size -= out_shaderResourceView.Resources[i].Size;

							out_shaderResourceView.Resources[i].Name = variableDesc.Name;
							out_shaderResourceView.Resources[i].Size = variableDesc.Size;
							if (out_shaderResourceView.Resources[i].Data)
							{
								free(out_shaderResourceView.Resources[i].Data);
								out_shaderResourceView.Resources[i].Data = nullptr;
							}
							out_shaderResourceView.Resources[i].Data = malloc(variableDesc.Size);

							out_shaderResourceView.Index = _buffer.RegisterIndex;
							out_shaderResourceView.Size += variableDesc.Size;
						}
					}

					if (out_shaderResourceView.Size % 16)
						THROW_PARADIGM_EXCEPTION_RANGE("HLSL Shader constant buffer with invalid size. Be sure to keep them multiple of 16 !");
				}


				////////////////////////////////////////////////
				// FUNCTIONALITY
				//___________________________________	
				FString FD3D11ShaderInterface::SendErrorMessage(ID3D10Blob* _errorMessage, HWND _windowHandle, const FString& _shaderFilename)
				{					
					FString errorLog((char*)(_errorMessage->GetBufferPointer()));
#ifdef _DEBUG
					//FPrint::Print(errorLog, EParadigmDebugLevel::WARNING_LEVEL);
#else
					//FPrint::PrintFile(errorLog, EParadigmDebugLevel::WARNING_LEVEL, "shader_error.plog");
					//MessageBox(_windowHandle, "Error compiling shader : (See shader_error.plog)", _shaderFilename, MB_OK);
#endif
					_errorMessage->Release();
					_errorMessage = nullptr;
					return errorLog;
				}

				HRESULT FD3D11ShaderInterface::CreateInputLayoutFromVertexShaderSignature(ID3DBlob* _vertexShaderBlob, ID3D11Device* _device, ID3D11InputLayout** out_inputLayout)
				{
					// Reflect shader info
					ID3D11ShaderReflection* reflection = nullptr;
					if (FAILED(D3DReflect(_vertexShaderBlob->GetBufferPointer(), _vertexShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&reflection)))
						return S_FALSE;

					// Get Shader Info
					D3D11_SHADER_DESC shaderDesc;
					reflection->GetDesc(&shaderDesc);

					// Read input layout description from shader info
					TArray<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
					inputLayoutDesc.Reserve(shaderDesc.InputParameters);
					for (unsigned int i = 0; i < shaderDesc.InputParameters; ++i)
					{
						D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
						reflection->GetInputParameterDesc(i, &paramDesc);

						// fill out input element desc
						D3D11_INPUT_ELEMENT_DESC elementDesc;
						elementDesc.SemanticName = paramDesc.SemanticName;
						elementDesc.SemanticIndex = paramDesc.SemanticIndex;
						elementDesc.InputSlot = 0;
						elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
						elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
						elementDesc.InstanceDataStepRate = 0;

						if (paramDesc.Mask == 1)
						{
							if (paramDesc.ComponentType == D3D10_REGISTER_COMPONENT_UINT32)
								elementDesc.Format = DXGI_FORMAT_R32_UINT;
							else if (paramDesc.ComponentType == D3D10_REGISTER_COMPONENT_SINT32)
								elementDesc.Format = DXGI_FORMAT_R32_SINT;
							else if (paramDesc.ComponentType == D3D10_REGISTER_COMPONENT_FLOAT32)
								elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
						}
						else if (paramDesc.Mask <= 3)
						{
							if (paramDesc.ComponentType == D3D10_REGISTER_COMPONENT_UINT32)
								elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
							else if (paramDesc.ComponentType == D3D10_REGISTER_COMPONENT_SINT32)
								elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
							else if (paramDesc.ComponentType == D3D10_REGISTER_COMPONENT_FLOAT32)
								elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
						}
						else if (paramDesc.Mask <= 7)
						{
							if (paramDesc.ComponentType == D3D10_REGISTER_COMPONENT_UINT32)
								elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
							else if (paramDesc.ComponentType == D3D10_REGISTER_COMPONENT_SINT32)
								elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
							else if (paramDesc.ComponentType == D3D10_REGISTER_COMPONENT_FLOAT32)
								elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
						}
						else if (paramDesc.Mask <= 15)
						{
							if (paramDesc.ComponentType == D3D10_REGISTER_COMPONENT_UINT32)
								elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
							else if (paramDesc.ComponentType == D3D10_REGISTER_COMPONENT_SINT32)
								elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
							else if (paramDesc.ComponentType == D3D10_REGISTER_COMPONENT_FLOAT32)
								elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
						}

						inputLayoutDesc.Add(elementDesc);
					}

					// Create InputLayout
					HRESULT hr = _device->CreateInputLayout(inputLayoutDesc.GetData(), inputLayoutDesc.Count(), _vertexShaderBlob->GetBufferPointer(), _vertexShaderBlob->GetBufferSize(), out_inputLayout);

					reflection->Release();
					return hr;
				}

				HRESULT FD3D11ShaderInterface::CreateConstantsBuffersFromShader(ENativeShaderType _type, ID3DBlob* _shaderBlob, UShaderResourceHandle& out_shaderReflection)
				{
					UShaderReflectionBufferDescription shaderBufferDesc;
					bool bNewCB = false;

					ID3D11ShaderReflection* reflection = nullptr;
					if (FAILED(D3DReflect(_shaderBlob->GetBufferPointer(), _shaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&reflection)))
						return S_FALSE;

					D3D11_SHADER_DESC desc;
					reflection->GetDesc(&desc);

					// Find all constant buffers
					uint registerIndex = 0;

					out_shaderReflection.Data.Reserve(desc.ConstantBuffers);

					for (uint i = 0; i < desc.BoundResources; ++i)
					{
						D3D11_SHADER_INPUT_BIND_DESC inputDesc;
						reflection->GetResourceBindingDesc(i, &inputDesc);

						if (inputDesc.Type == D3D10_SIT_CBUFFER)
						{
							ID3D11ShaderReflectionConstantBuffer* buffer = nullptr;
							buffer = reflection->GetConstantBufferByName(inputDesc.Name);
							
							D3D11_SHADER_BUFFER_DESC bufferDesc;
							buffer->GetDesc(&bufferDesc);
							
							for (uint j = 0; j < desc.ConstantBuffers; ++j)
							{
								D3D11_SHADER_INPUT_BIND_DESC inputResourceDesc;
								reflection->GetResourceBindingDesc(j, &inputResourceDesc);

								if (!strcmp(inputResourceDesc.Name, bufferDesc.Name))
									registerIndex = inputResourceDesc.BindPoint;
							}
							shaderBufferDesc = { { bufferDesc.Name }, registerIndex, buffer, &bufferDesc };

							// Check if this constant buffer already exist and reflect is data.
							bNewCB = true;
							for (TArray<UShaderDataBlockResource>::Iterator it = out_shaderReflection.Data.Begin(); it != out_shaderReflection.Data.End(); ++it)
							{
								// if already have this constant buffer, so works on it
								if ((*it).Name == inputDesc.Name && (*it).ShaderType == _type)
								{
									bNewCB = false;
									CreateShaderResourceViewFromBuffer(shaderBufferDesc, *it);
									break;
								}
							}

							// else add a new resource block
							if (bNewCB)
							{
								out_shaderReflection.Data.Add({});
								out_shaderReflection.Data.Back().ShaderType = _type;
								out_shaderReflection.Data.Back().Name = inputDesc.Name;
								CreateShaderResourceViewFromBuffer(shaderBufferDesc, out_shaderReflection.Data.Back());
							}

						}
						else if (inputDesc.Type == D3D10_SIT_TEXTURE)
						{
							bNewCB = true;
							for (auto it = out_shaderReflection.Textures.Begin(); it != out_shaderReflection.Textures.End(); ++it)
							{
								if ((*it).Name == inputDesc.Name && (*it).ShaderType == _type)
								{
									bNewCB = false;
									break;
								}
							}

							if(bNewCB)
								out_shaderReflection.Textures.Add({ inputDesc.Name , INVALID_KEY_REGISTER, INVALID_KEY_REGISTER, inputDesc.BindPoint, true, _type });
						}
					}

					reflection->Release();
					return S_OK;
				}

				HRESULT FD3D11ShaderInterface::ConfigureDataBlockResources(UD3D11Interface& _d3dinterface, TArray<UShaderDataBlockResource>& out_buffer)
				{
					UKeyRegister kregister;
					for (uint i = 0; i < out_buffer.Count(); ++i)
					{
						D3D11_BUFFER_DESC desc;
						desc.Usage = D3D11_USAGE_DYNAMIC;

						if (out_buffer[i].Size % 16) // if invalid padding just say it now !
							return S_FALSE;

						desc.ByteWidth = out_buffer[i].Size;
						desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
						desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
						desc.MiscFlags = 0;
						desc.StructureByteStride = 0;

						if (out_buffer[i].KeyBlockBuffer == INVALID_KEY_REGISTER)
							out_buffer[i].KeyBlockBuffer = kregister = _d3dinterface.ShaderInterface.BlockBuffers.Add({});
						else
						{
							kregister = out_buffer[i].KeyBlockBuffer;
							_d3dinterface.ShaderInterface.BlockBuffers[kregister]->Release();
						}

						if (FAILED(_d3dinterface.Device->CreateBuffer(&desc, NULL, &_d3dinterface.ShaderInterface.BlockBuffers[kregister])))
						{
							_d3dinterface.ShaderInterface.BlockBuffers.Remove(kregister);
							return S_FALSE;
						}
					}
					return S_OK;
				}

				HRESULT FD3D11ShaderInterface::ConfigureTextureResources(UD3D11Interface& _d3dinterface, TArray<UShaderTextureResource>& out_buffer)
				{
					UKeyRegister kregister;
					for (unsigned int i = 0; i < out_buffer.Count(); ++i)
					{
						D3D11_SAMPLER_DESC samplerDesc;
						samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
						samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
						samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
						samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
						samplerDesc.MipLODBias = 0.0f;
						samplerDesc.MaxAnisotropy = 1;
						samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
						samplerDesc.BorderColor[0] = 0;
						samplerDesc.BorderColor[1] = 0;
						samplerDesc.BorderColor[2] = 0;
						samplerDesc.BorderColor[3] = 0;
						samplerDesc.MinLOD = 0;
						samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
						
						if (out_buffer[i].KeysHandle.kSamplerState == INVALID_KEY_REGISTER)
							kregister = out_buffer[i].KeysHandle.kSamplerState = _d3dinterface.ShaderInterface.SamplerStates.Add({});
						else
						{
							kregister = out_buffer[i].KeysHandle.kSamplerState;
							_d3dinterface.ShaderInterface.SamplerStates[kregister]->Release();
						}
						
						if (FAILED(_d3dinterface.Device->CreateSamplerState(&samplerDesc, &_d3dinterface.ShaderInterface.SamplerStates[kregister])))
						{
							_d3dinterface.ShaderInterface.SamplerStates.Remove(kregister);
							return S_FALSE;
						}
					}
					return S_OK;
				}

				HRESULT FD3D11ShaderInterface::ConfigureShaderResourceHandle(UD3D11Interface& _d3dinterface, UShaderResourceHandle& out_shadeReflectionView)
				{
					if (FAILED(ConfigureDataBlockResources(_d3dinterface, out_shadeReflectionView.Data)) ||
						FAILED(ConfigureTextureResources(_d3dinterface, out_shadeReflectionView.Textures)))
						return S_FALSE;
					return S_OK;
				}
			}
		}
	}
}