#ifndef _SHADERINTERFACEATRRIBUTES_H_
#define _SHADERINTERFACEATRRIBUTES_H_

#include <FString.h>
#include <TArray.h>

#include <NativeInterface/Graphics/NativeGraphicsHandles.h>
#include <NativeInterface/Graphics/NativeGraphicsEnums.h>

namespace ParadigmEngine
{	
	namespace NativeInterface
	{
		namespace Graphics
		{
			namespace Shader
			{				

				struct UShaderDataResource
				{
					FString Name;
					uint Size;
					void* Data;
				};

				struct UShaderDataBlockResource
				{
					UKeyRegister KeyBlockBuffer{ INVALID_KEY_REGISTER };
					/** Name of the constante buffer. */
					FString Name;
					TArray<UShaderDataResource> Resources;
					ENativeShaderType ShaderType;
					uint Size : 16;
					uint Index : 16;
				};
				
				struct UShaderTextureResource
				{
					/** Name of the resource. */
					FString Name;

					/** A key toward natives texture and sampler resource. */
					UNativeTextureResource KeysHandle;

					/** Index of the resource. */
					uint Index : 31;
					uint bOudated : 1;
										
					ENativeShaderType ShaderType;

					/** Dimension of the texture according to the shader. */
					//ENativeTextureDimensionView Dimension{ ETextureDimensionType_2D };
				};
				
				struct UTextureDescriptor
				{
					FString Filename;
					ENativeFilteringMode FilteringMode { ENativeFilteringMode::EFilteringMode_Linear };
					ENativeWrappingMode WrappingMode{ ENativeWrappingMode::EWrappingMode_Repeat };
					ENativeTextureDimension Dimension{ ENativeTextureDimension::ETextureDimension_2D };
					uint AnisotropyLevel{ 0 };
				};

				struct UShardShaderDescriptor
				{
					ENativeShaderType Type;
					FString Filename;
					FString EntryPoint;
				};

				struct UShaderResourceHandle
				{
					TArray<UShaderDataBlockResource> Data;
					TArray<UShaderTextureResource> Textures;

					UKeyRegister kInputLayoutKey{ INVALID_KEY_REGISTER };
					UKeyRegister kVertexShaderKey{ INVALID_KEY_REGISTER };
					UKeyRegister kPixelShaderKey{ INVALID_KEY_REGISTER };
					UKeyRegister kGeometryShaderKey{ INVALID_KEY_REGISTER };
					UKeyRegister kComputeShaderKey{ INVALID_KEY_REGISTER };

					/** Key to an OpenGL-specific's runtime compilation shader. Always INVALID_KEY_REGISTER if invalid Native API. */
					UKeyRegister kShaderProgramKey{ INVALID_KEY_REGISTER };
					uint bSuccessfullyCompiled{ false };
				};
			}
		}
		
		typedef ParadigmEngine::NativeInterface::Graphics::Shader::UShaderDataResource UShaderDataResource;
		typedef ParadigmEngine::NativeInterface::Graphics::Shader::UShaderTextureResource UShaderTextureResource;
		typedef ParadigmEngine::NativeInterface::Graphics::Shader::UShaderDataBlockResource UShaderDataBlockResource;
		typedef ParadigmEngine::NativeInterface::Graphics::Shader::UShaderResourceHandle UShaderResourceHandle;
	}
}

typedef ParadigmEngine::NativeInterface::Graphics::Shader::UTextureDescriptor UTextureDescriptor;
typedef ParadigmEngine::NativeInterface::Graphics::Shader::UShardShaderDescriptor UShardShaderDescriptor;
#endif