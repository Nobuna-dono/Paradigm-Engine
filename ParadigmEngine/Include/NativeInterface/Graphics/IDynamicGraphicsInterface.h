#ifndef _IDYNAMICGRAPHICSINTERFACE_H_
#define _IDYNAMICGRAPHICSINTERFACE_H_

#include <NativeInterface/Context/NativeContextAttributes.h>
#include <NativeInterface/Graphics/NativeGraphicsAttributes.h>
#include <NativeInterface/Graphics/Shader/ShaderInterfaceAttributes.h>

#include <ParadigmMath.h>
#include <FColor.h>

namespace ParadigmEngine
{
	namespace NativeInterface
	{		
		namespace Graphics
		{
			class UTexture {};
			class UShader {};
			
			struct UDynamicGraphicsInterface
			{
				UDynamicGraphicsInterface() = default;
				UDynamicGraphicsInterface(const UDynamicGraphicsInterface&) = delete;
				UDynamicGraphicsInterface& operator=(const UDynamicGraphicsInterface&) = delete;

				uint Width, Height;
			};

			class IDynamicGraphicsInterface
			{
				public:
					////////////////////////////////////////////////
					// CONSTRUCTOR - DESTRUCTOR
					//____________________________________	
					
					IDynamicGraphicsInterface() = default;
					IDynamicGraphicsInterface(const IDynamicGraphicsInterface&) = delete;
					IDynamicGraphicsInterface& operator=(const IDynamicGraphicsInterface&) = delete;

				public:
					////////////////////////////////////////////////
					// PIPELINE MODULES
					//____________________________________	
					virtual void Initialize() = 0;
					virtual void Terminate() = 0;

				public:
					////////////////////////////////////////////////
					// GRAPHICS API CONFIGURATION
					//____________________________________	
					/** Create renderer system in the target window. */
					virtual void CreateViewport(ETargetViewport _target, bool _bfullscreen = false, bool _bvsync = false) { THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }
					/** Get the first viewport, create window and renderer system. */
					virtual void CreateViewport(ETargetViewport _target, UContextAttributes _contextDesc = {}, bool _bfullscreen = false, bool _bvsync = false) { THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }
					/** Create viewport and add it to an array of viewports. */
					virtual bool CreateViewport(ETargetViewport _target, uint _width, uint _height, bool _bfullscreen = false, bool _bvsync = false, void* _HandleID = nullptr) { THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }

					/** Resize the viewport. */
					virtual void ResizeViewport(ETargetViewport _target, uint _width, uint _height) { THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); };

					/** Destroy the requested viewport. */
					virtual void DestroyViewport(ETargetViewport _viewport) { THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }

					/** Allow to create several state to specify Rasterizer mode. */
					virtual UKeyRegister CreateRasterizerState(const URasterizerDescriptor& _attrib) { THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }
					/** The depth-stencil-state interface holds a description for depth-stencil state that you can bind to the output-merger stage. */
					virtual UKeyRegister CreateDepthStencilState(const UNativeDepthStencilDescriptor& _attrib) { THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); };
					

					/** Set a the rasterizer state (Cull and Fill mode...) from the given register, do nothing if wrong. */
					virtual void SetRasterizerState(ETargetViewport _viewport, UKeyRegister _rasterStateID) { THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }
					/** Set a the depth stencil state (z-buffer algorithm...) from the given register, do nothing if wrong. */
					virtual void SetDepthStencilState(ETargetViewport _viewport, UKeyRegister _depthStateID) { THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }					
					/** Allow to enable or disable the DepthTest. Usefull for 2D orthographic rendering. (enable a default de/active-zbuffer depth stencil state. Use SetDepthStencilState instead for custom purpose) */
					virtual void SetZBuffer(ETargetViewport _viewport, bool _state) { THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }


				public:
					////////////////////////////////////////////////
					// NATIVE TEXTURE RESOURCE FUNCTIONALITY
					//____________________________________	
					/** Allow to create a native texture resource. (see @UNativeTextureResourceDescriptor) */
					virtual UKeyRegister CreateNativeTextureResource(const UNativeTextureResourceDescriptor& _attrib) { THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); };
					/** Allow to create a 1D native texture resource. (see @UNativeTextureResourceDescriptor) */
					virtual UKeyRegister CreateNativeTexture1DResource(const UNativeTextureResourceDescriptor& _attrib) { THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); };
					/** Allow to create a 2D native texture resource. (see @UNativeTextureResourceDescriptor) */
					virtual UKeyRegister CreateNativeTexture2DResource(const UNativeTextureResourceDescriptor& _attrib) { THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); };
					/** Allow to create a 3D native texture resource. (see @UNativeTextureResourceDescriptor) */
					//virtual UKeyRegister CreateTexture3DResource(UNativeTextureResourceDescriptor _attrib) { THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); };


				public:
					////////////////////////////////////////////////
					// SHADER API FUNCTIONALITY
					//____________________________________	
					/** Create shader according to the defined type. Return a register (sort of key) to the SDKDevice resource (generally buffer). */
					virtual void CreateShader(UKeyRegister& out_kNatShader, const TArray<Shader::UShardShaderDescriptor>& _shards, bool _brefresh = false)
					{ THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }
					///** Create a Vertex shader. Return a register to the SDKDevice resource. */
					//virtual void CreateVertexShader(Shader::UShaderResourceHandle& out_resourceHandle, const FString& _filename, const FString& _entryPoint = { "MainVertexShader" }) { THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }
					///** Create a Pixel shader. Return a register to the SDKDevice resource. */
					//virtual void CreatePixelShader(Shader::UShaderResourceHandle& out_resourceHandle, const FString& _filename, const FString& _entryPoint = { "MainPixelShader" }) { THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }
					///** Create a Fragment shader. Return a register to the SDKDevice resource. */
					//virtual void CreateFragmentShader(Shader::UShaderResourceHandle& out_resourceHandle, const FString& _filename, const FString& _entryPoint = { "" }) { THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }
					///** Create a Geometry shader. Return a register to the SDKDevice resource. */
					//virtual void CreateGeometryShader(Shader::UShaderResourceHandle& out_resourceHandle, const FString& _filename, const FString& _entryPoint = { "MainGeometryShader" }) { THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }
					///** Create a Compute shader. Return a register to the SDKDevice resource. */
					//virtual void CreateComputeShader(Shader::UShaderResourceHandle& out_resourceHandle, const FString& _filename, const FString& _entryPoint = { "MainComputeShader" }) { THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }
					///** Create a Program shader (Native OpenGL API). Return a register to the SDKDevice resource. */
					//virtual void CreateShaderProgram(Shader::UShaderResourceHandle& out_resourceHandle, const TArray<UKeyRegister>& _shaderRegisters, void(*callback)(int) = nullptr) { THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }
					
					/** Create a texture resource from it settings. Return a register to the SDKDevice resource. */
					virtual void CreateTextureResource(UNativeTextureResource& out_kNatTex, const UTextureDescriptor& _textureDesc) = 0;

					/** Bind the resource of the handle. */
					virtual bool BindShaderResources(UKeyRegister _kShaderResource, bool _bTryOptimize = false)
					{ THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }
					/** Bind the shader to prepare the DrawCall. */					
					virtual void BindShader(UKeyRegister _kShaderResource)
					{ THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }
					
			public:
				////////////////////////////////////////////////
				// ELEMENT ACCESS
				//____________________________________	
				virtual Shader::UShaderResourceHandle& GetShaderResourceHandle(UKeyRegister _kShaderResource)
				{ THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }
				virtual bool GetShaderResourceHandle(Shader::UShaderResourceHandle& out_shaderRes, UKeyRegister _kShaderResource) 
				{ THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }
				virtual bool SetShaderResourceHandle(const Shader::UShaderResourceHandle& _shaderRes, UKeyRegister _kShaderResource)
				{ THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }
				virtual uint GetViewportWidth(ETargetViewport _target = VIEWPORT_0)
				{ THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }
				virtual uint GetViewportHeight(ETargetViewport _target = VIEWPORT_0)
				{ THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }

				private:
					/** Build native resources from resource handle data. Must be call when all shader are create to complete the material. */
					virtual void BuildNativeShaderResources(UKeyRegister _kShaderResource)
					{ THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); };

				public:
					////////////////////////////////////////////////
					// RENDER FUNCTIONALITY
					//____________________________________						
					/** Render element. */
					virtual void DrawCall(uint _elementCount, uint _startIndex = 0) { THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }
					/** Set the mode to drawing primitive. */
					virtual void SetPrimitiveDrawingMode(ENativePrimitiveTopology _drawMode) { THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }


				public:
					////////////////////////////////////////////////
					// PIPELINE FUNCTIONNALITY
					//____________________________________	
					/** Clear all buffer of the back buffer before starting new draw. */
					virtual void BeginScene(ETargetViewport _viewport, UColor _clearColor) = 0;
					/** Swap back/user buffer to display the new frame depending of the frequency (vsync...). */
					virtual void EndScene(ETargetViewport _viewport) = 0;


				public:
					////////////////////////////////////////////////
					// BUFFER FUNCTIONALITY
					//____________________________________
					/** Bind vertex and element buffers from registers. Must be call with @BindShader. Do nothing if wrong handle. */
					virtual void BindInputAssembly(UKeyRegister _elementBufferKey, UKeyRegister _vertexBufferKey) 
					{ THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }
					/** Bind an element buffer from the register. Do nothing if wrong handle. */
					virtual void BindElementBuffer(UKeyRegister _elementBufferKey) 
					{ THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }
					/** Bind an element buffer from the register. Do nothing if wrong handle. */
					virtual void BindVertexBuffer(UKeyRegister _vertexBufferKey) 
					{ THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }

					/** Fill the input assembly according to the input laout (from vertex shader input). Arrays must have the same size. */
					virtual void CreateElementAndVertexBuffers(UKeyRegister& out_indexBufferKey, UKeyRegister& out_vertexBufferKey, const TArray<uint>& _elements, const TArray<UVertex>& _vertices)
					{ THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }					
					/** Create a element buffer from data and return it register. */
					virtual void CreateElementBuffer(UKeyRegister& out_kregister, const TArray<uint>& _indices)
					{ THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }
					/** Create a vertex buffer from data and return it register. */
					virtual void CreateVertexBuffer(UKeyRegister& out_kregister, const TArray<UVertex>& _vertices)
					{ THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }


				public:
					////////////////////////////////////////////////
					// API MISCELLANEOUS FUNCTIONALITY
					//____________________________________
					/** Fill memory card data got by the API. */
					virtual void GetVideoCardInfo(UGraphicsCardInfo& _outVideoCardInfo) { THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }


				public:
					////////////////////////////////////////////////
					// PROFILING FUNCTIONALITY
					//____________________________________					
					class FDynamicGPUProfiling
					{
						/** Inits instance and object needed by the class. */
						virtual bool Initialise() { THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }
						/** Free all resources bind by the class. */
						virtual void Shutdown() { THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }

						/** Start Frame profiling. */
						virtual void BeginFrame() = 0;
						/** Update data profiling. */
						virtual void Frame() = 0;
						/** End frame profiling. */
						virtual void EndFrame() = 0;

						/** Return the GPU frametime. */
						virtual float GetFrametime() = 0;
					};
			};

		}
	}
}
#endif