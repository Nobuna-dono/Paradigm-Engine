#ifndef _FD3D11INTERFACE_H_
#define _FD3D11INTERFACE_H_

#include <NativeInterface/Graphics/IDynamicGraphicsInterface.h>
#include <NativeInterface/Graphics/Shader/FD3D11ShaderInterface.h>
#include <TKeyTable.h>


namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Graphics
		{	
			
			struct UD3D11RenderSystemAttributes
			{
				HWND WindowHandle{nullptr};
				IDXGISwapChain* SwapChain{nullptr};
				ID3D11RenderTargetView* RenderTarget{nullptr};
				D3D11_VIEWPORT Viewport;

				UKeyRegister DepthStencilStateKey{ 0, 1 };
				/** The view of the depth buffer resource. Must be bind through @OMSetRenderTarget during @BeginScene. */
				UKeyRegister DepthStencilViewKey{ INVALID_KEY_REGISTER};
				UKeyRegister RasterizerStateKey{ 0, 1 };
				UKeyRegister DepthBufferTexture2DKey{ INVALID_KEY_REGISTER };

				ENativeClearFlag ClearFlag{ EClearFlag_Depth };
				
				uint bFullscreen : 1;
				uint bMultisampling : 1;
				uint bVerticalSynchro : 1;			
				private:
					uint : 29;
			};

			struct UD3D11ShaderInterfaceAttributes
			{				
				/** */
				TKeyTable<std::pair<FString,ID3D11VertexShader*>> VertexShaders;
				/** */
				TKeyTable<std::pair<FString, ID3D11PixelShader*>> PixelShader;
				/** */
				TKeyTable<std::pair<FString, ID3D11ComputeShader*>> ComputeShader;
				/** */
				TKeyTable<std::pair<FString, ID3D11GeometryShader*>> GeometryShader;
				/** Table of input layouts (input assembly). */
				TKeyTable<std::pair<FString, ID3D11InputLayout*>> InputLayouts;

				/** Table of HLSL (Constant) Buffer. */
				TKeyTable<ID3D11Buffer*> BlockBuffers;
				/** Table of shader resource view (texture resource).*/
				TKeyTable<ID3D11ShaderResourceView*> ResourceViews;
				/**  Table of texture sampler state. */
				TKeyTable<ID3D11SamplerState*> SamplerStates;

				TKeyTable<Shader::UShaderResourceHandle> ShaderResources;

				/** A key for the debug shader. */
				UKeyRegister kNativeDebugShader;
			};

			struct UD3D11Interface : public UDynamicGraphicsInterface
			{				
				public:				
					////////////////////////////////////////////////
					// NON COPPYABLE STRUCT CONSTRUCTOR
					//____________________________________	
					UD3D11Interface() = default;
					UD3D11Interface(const UD3D11Interface&) = delete;
					UD3D11Interface& operator=(const UD3D11Interface&) = delete;


				public:
					////////////////////////////////////////////////
					// DATA
					//____________________________________	
					/** */
					ID3D11Device* Device;
					/** */
					ID3D11DeviceContext* DeviceContext;
					/** Video card descriptor. */
					UGraphicsCardInfo GraphicsCardInfo;
					
					
					////////////////////////////////////////////////
					// RENDER SYSTEM RESOURCE
					//____________________________________	
					/** Table of depth stencil state. (The depth-stencil-state interface holds a description for depth-stencil state that you can bind to the output-merger stage.)*/
					TKeyTable<ID3D11DepthStencilState*> DepthStencilStates;
					/** Table of depth stencil view. (A depth-stencil-view interface accesses a texture resource during depth-stencil testing.)*/
					TKeyTable<ID3D11DepthStencilView*> DepthStencilViews;
					/** Table of rasterizer states. */
					TKeyTable<ID3D11RasterizerState*> RasterizerStates;
					/** Array of created render system/viewports. (see @UD3D11RenderSystemAttributes) */
					TArray<UD3D11RenderSystemAttributes> RenderSystems;


					////////////////////////////////////////////////
					// SHADER RESOURCE
					//____________________________________	
					/** Table of 1D texture buffer. */
					TKeyTable<ID3D11Texture1D*> Texture1DBuffers;
					/** Table of 2D texture buffer. */
					TKeyTable<ID3D11Texture2D*> Texture2DBuffers;
					/** Table of 3D texture buffer. */
					TKeyTable<ID3D11Texture3D*> Texture3DBuffers;		
					

					/** Hold shaders attributes. */
					UD3D11ShaderInterfaceAttributes ShaderInterface;
			};


			class FD3D11Interface : public IDynamicGraphicsInterface
			{
				public:
					////////////////////////////////////////////////
					// NON COPPYABLE CLASS CONSTRUCTOR
					//____________________________________	

					FD3D11Interface() = default;
					FD3D11Interface(const FD3D11Interface&) = delete;
					FD3D11Interface& operator=(const FD3D11Interface&) = delete;

				public:
					////////////////////////////////////////////////
					// PIPELINE MODULES
					//____________________________________	
					void Initialize() override;
					void Terminate() override;

				public:
					////////////////////////////////////////////////
					// GRAPHICS API FUNCTIONALITY
					//____________________________________	
					/** Create renderer system in the target window. */
					void CreateViewport(ETargetViewport _target, bool _bfullscreen = false, bool _bvsync = false) override;
					/** Create window and renderer system. */
					void CreateViewport(ETargetViewport _target, UContextAttributes _contextDesc = {}, bool _bfullscreen = false, bool _bvsync = false) override;
					/** Get the first viewport, create window and renderer system. */
					bool CreateViewport(ETargetViewport _target, uint _width, uint _height, bool _bfullscreen = false, bool _bvsync = false, void* _HandleID = nullptr) override;

					/** Resize the viewport. */
					void ResizeViewport(ETargetViewport _target, uint _width, uint _height) override;

					/** The depth-stencil-state interface holds a description for depth-stencil state that you can bind to the output-merger stage. (see @UNativeDepthStencilDescriptor) */
					UKeyRegister CreateDepthStencilState(const UNativeDepthStencilDescriptor& _attrib) override;
					/** Allow to create several state to specify Rasterizer mode. */
					UKeyRegister CreateRasterizerState(const URasterizerDescriptor& _attrib) override;
												

					/** Set a the rasterizer state from the given register, do nothing if wrong. */
					void SetRasterizerState(ETargetViewport _viewport, UKeyRegister _rasterStateID) override;
					/** Set a the depth state from the given register, do nothing if wrong. */
					void SetDepthStencilState(ETargetViewport _viewport, UKeyRegister _depthStateID) override;					
					/** Allow to enable or disable the DepthTest. Usefull for 2D orthographic rendering. (enable a default de/active-zbuffer depth stencil state. Use SetDepthStencilState instead for custom purpose) */
					void SetZBuffer(ETargetViewport _viewport, bool _state) override;
				
			
				public:
					////////////////////////////////////////////////
					// TEXTURE RESOURCE FUNCTIONALITY
					//____________________________________	
					/** Allow to create a native texture resource. (see @UNativeTextureResourceDescriptor) */
					UKeyRegister CreateNativeTextureResource(const UNativeTextureResourceDescriptor& _attrib) override;
					/** Allow to create a 1D native texture resource. (see @UNativeTextureResourceDescriptor) */
					UKeyRegister CreateNativeTexture1DResource(const UNativeTextureResourceDescriptor& _attrib) override;
					/** Allow to create a 2D native texture resource. (see @UNativeTextureResourceDescriptor) */
					UKeyRegister CreateNativeTexture2DResource(const UNativeTextureResourceDescriptor& _attrib) override;					


				public:
					////////////////////////////////////////////////
					// SHADER API FUNCTIONALITY
					//____________________________________	
					/** Create shader according to the defined type and fill the resourceHandle. */
					void CreateShader(UKeyRegister& out_kNatShader, const TArray<Shader::UShardShaderDescriptor>& _shards, bool _brefresh = false) override;
										
					/** Create a texture resource from it settings. Return a register to the SDKDevice resource. */
					void CreateTextureResource(UNativeTextureResource& out_kNatTex, const UTextureDescriptor& _textureDesc) override;
					
					/** Bind the resource of the handle. */
					bool BindShaderResources(UKeyRegister _kShaderResource, bool _bTryOptimize = false) override;
					/** Bind the shader to prepare the DrawCall. */
					void BindShader(UKeyRegister _kShaderResource) override;
				

				private:
					////////////////////////////////////////////////
					// PRIVATE UTILITY
					//____________________________________
					/** Create a Vertex shader and fill the resourceHandle. */
					void CreateVertexShader(Shader::UShaderResourceHandle& out_resourceHandle, const FString& _filename, const FString& _entryPoint = { "MainVertexShader" });
					/** Create a Pixel/Fragment shader. Return a register to the SDKDevice resource. */
					void CreatePixelShader(Shader::UShaderResourceHandle& out_resourceHandle, const FString& _filename, const FString& _entryPoint = { "MainPixelShader" });
					/** Create a Geometry shader and fill the resourceHandle. */
					void CreateGeometryShader(Shader::UShaderResourceHandle& out_resourceHandle, const FString& _filename, const FString& _entryPoint = { "MainGeometryShader" });
					/** Create a Compute shader and fill the resourceHandle.  */
					void CreateComputeShader(Shader::UShaderResourceHandle& out_resourceHandle, const FString& _filename, const FString& _entryPoint = { "MainComputeShader" });

					/** Verify if this shader already exist and return it's key, else return INVALID_KEY_REGISTER.*/
					template<typename T>
					UKeyRegister SeekExistingShader(T& _tableToProspect, FString _uniqueShaderName);

					template<typename T>
					UKeyRegister TryRecycleShaderResource(T& _tableToProspect, FString _uniqueShaderName, ENativeShaderType _shaderType, UShaderResourceHandle& out_resourceHandle);

					/** Create the sampler state of texture from descriptor. */
					void CreateSamplerState(UKeyRegister& out_register, const UTextureDescriptor& _texDesc);

					/** Build native resources from shader resource handle data. Must be call when all shader are create to complete the material. */
					void BuildNativeShaderResources(UKeyRegister _kShaderResource) override;
			
			
				public:
					////////////////////////////////////////////////
					// ELEMENT ACCESS
					//____________________________________	
					Shader::UShaderResourceHandle& GetShaderResourceHandle(UKeyRegister _kShaderResource) override;
					bool GetShaderResourceHandle(Shader::UShaderResourceHandle& out_shaderRes, UKeyRegister _kShaderResource) override;
					bool SetShaderResourceHandle(const Shader::UShaderResourceHandle& _shaderRes, UKeyRegister _kShaderResource) override;
					uint GetViewportWidth(ETargetViewport _target = ETargetViewport::VIEWPORT_0) override;
					uint GetViewportHeight(ETargetViewport _target = ETargetViewport::VIEWPORT_0) override;

				public:
					////////////////////////////////////////////////
					// RENDER FUNCTIONALITY
					//____________________________________
					/** Render element. */
					void DrawCall(uint _elementCount, uint _startIndex = 0)override;
					/** Set the mode to drawing primitive. */
					void SetPrimitiveDrawingMode(ENativePrimitiveTopology _drawMode) override;


				public:
					////////////////////////////////////////////////
					// PIPELINE FUNCTIONNALITY
					//____________________________________	
					/** Clear all buffer of the back buffer before starting new draw. */
					void BeginScene(ETargetViewport _viewport, UColor _clearColor) override;
					/** Swap back/user buffer to display the new frame depending of the frequency (vsync...). */
					void EndScene(ETargetViewport _viewport) override;


				public:
					////////////////////////////////////////////////
					// BUFFER FUNCTIONALITY
					//____________________________________
					/** Bind a vertex array from the register. Must be call with @BindShader. Do nothing if wrong handle. */
					void BindInputAssembly(UKeyRegister _elementBuffer, UKeyRegister _vertexBuffer) override;					
					/** Bind an element buffer from the register. Do nothing if wrong handle. */
					void BindElementBuffer(UKeyRegister _elementBufferKey) override;
					/** Bind an element buffer from the register. Do nothing if wrong handle. */
					void BindVertexBuffer(UKeyRegister _vertexBufferKey) override;

					/** Fill the input assembly according to the input laout (from vertex shader input). */
					void CreateElementAndVertexBuffers(UKeyRegister& out_indexBufferKey, UKeyRegister& out_vertexBufferKey, const TArray<uint>& _elements, const TArray<UVertex>& _vertices) override;
					/** Create a element buffer from data and return it register. */
					void CreateElementBuffer(UKeyRegister& out_kregister, const TArray<uint>& _indices) override;
					/** Create a vertex buffer from data and return it register. */
					void CreateVertexBuffer(UKeyRegister& out_kregister, const TArray<UVertex>& _vertices) override;


				public:
					////////////////////////////////////////////////
					// API MISCELLANEOUS FUNCTIONALITY
					//____________________________________
					/** Fill memory card data got by the API. */
					void GetVideoCardInfo(UGraphicsCardInfo& _outVideoCardInfo) override;


				private:
					////////////////////////////////////////////////
					// PRIVATE FUNCTIONALITY 
					//____________________________________
					/** The depth buffer is a 2D texture which holds depth information. Under Direct3D11 it need a specific DepthStencilView to be bind. */
					void CreateDepthBuffer(UD3D11RenderSystemAttributes& out_renderSys, const UNativeTextureResourceDescriptor& _attrib);

					/** Create the render system, this include backbuffer, depthbuffer and viewport configuration. */
					void CreateRenderSystem(UD3D11RenderSystemAttributes& out_viewport, HWND _handle, uint _widthResolution, uint _heightResolution);

					void ComputeRefreshRate(uint _widthResolution, uint _heightResolution);
					void FillGraphicsCardInfo();

				private:
					////////////////////////////////////////////////
					// TERMINATE FUNCTIONALITY
					//____________________________________	
					void TerminateRenderSystem();
					void TerminateShaderInterface();
					void TerminateShaderResource();
					void TerminateShaderDataBlockResource(UShaderResourceHandle& out_resHandler, TArray<void*>& _outdatedPtr);
					void TerminateD3D11Interface();					
					template<typename T>
					void ClearNativeShaderKeyTable(T& _table);
					template<typename T>
					void ClearNativeKeyTable(T& _table);

				private:
					////////////////////////////////////////////////
					// DATA
					//____________________________________
					IDXGIFactory* m_DXGIFactory;
					IDXGIAdapter* m_DXGIAdapter;
					IDXGIOutput* m_DXGIAdapterOutput;
					ID3D11Debug* m_D3D11Debug;

					UD3D11Interface m_InterfaceData;
					uint m_Numerator{ 0 }, m_Denominator{ 0 };
			};
		}
	}
}
#include <NativeInterface/Graphics/FD3D11Interface.inl>

typedef ParadigmEngine::NativeInterface::Graphics::IDynamicGraphicsInterface IDynamicGraphicsInterface;
typedef ParadigmEngine::NativeInterface::Graphics::FD3D11Interface FD3D11Interface;
#endif

