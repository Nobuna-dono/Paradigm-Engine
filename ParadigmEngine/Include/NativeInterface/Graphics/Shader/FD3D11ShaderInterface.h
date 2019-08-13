#ifndef _FD3D11SHADERINTERFACE_H_
#define _FD3D11SHADERINTERFACE_H_

#include <NativeInterface/Graphics/Shader/ShaderInterfaceAttributes.h>

#include <d3d11.h>
#include <D3Dcompiler.h>
//#include <D3DX11async.h>

namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Graphics
		{
			struct UD3D11Interface;

			namespace Shader
			{
				struct UShaderReflectionBufferDescription
				{
					FString Name;
					uint RegisterIndex;
					ID3D11ShaderReflectionConstantBuffer* ReflectionBuffer{ nullptr };
					D3D11_SHADER_BUFFER_DESC* Description;
				};

				class FD3D11ShaderInterface
				{
					public:
						////////////////////////////////////////////////
						// CONSTRUCTOR
						//____________________________________	
						FD3D11ShaderInterface() = delete;
						FD3D11ShaderInterface(const FD3D11ShaderInterface&) = delete;
						FD3D11ShaderInterface& operator=(const FD3D11ShaderInterface&) = delete;
					
					private:
						////////////////////////////////////////////////
						// PIRVATE FUNCTIONALITY
						//____________________________________	
						static void CreateShaderResourceViewFromBuffer(UShaderReflectionBufferDescription& _buffer, UShaderDataBlockResource& out_shaderResourceView);

				
					public:
						////////////////////////////////////////////////
						// FUNCTIONALITY
						//___________________________________	
						static FString SendErrorMessage(ID3D10Blob* _errorMessage, HWND _windowHandle, const FString& _shaderFilename);

						static HRESULT CreateInputLayoutFromVertexShaderSignature(ID3DBlob* _vertexShaderBlob, ID3D11Device* _device, ID3D11InputLayout** out_inputLayout);
						
						static HRESULT CreateConstantsBuffersFromShader(ENativeShaderType _type, ID3DBlob* _shaderBlob, UShaderResourceHandle& out_shaderReflection);

						static HRESULT ConfigureDataBlockResources(UD3D11Interface& _d3dinterface, TArray<UShaderDataBlockResource>& out_buffer);

						static HRESULT ConfigureTextureResources(UD3D11Interface& _d3dinterface, TArray<UShaderTextureResource>& out_buffer);

						/** Code to auto generate constant buffer binding configuration from resourceView... I think I begin to be good. */
						static HRESULT ConfigureShaderResourceHandle(UD3D11Interface& _d3dinterface, UShaderResourceHandle& out_shadeReflectionView);
				};
			}
		}
	}
}

#endif