#ifndef _UTEXTURE_H_
#define _UTEXTURE_H_

#include <Resource/UResource.h>

namespace ParadigmEngine
{
	namespace Resource
	{
		struct UTexture : public UResource
		{	
			public:
				////////////////////////////////////////////////
				// ENUMERATOR
				//____________________________________	

				SERIALIZABLE_ENUM(ETextureAspect,				
					TextureAspect_2D, 
					TextureAspect_Cubemap
				);

				SERIALIZABLE_ENUM(ETextureType,				
					TextureType_Default, 
					TextureType_NormalMap, 
					TextureType_Sprite, 
					TextureType_Cursor, 
					TextureType_LightMap
				);

			public:
				////////////////////////////////////////////////
				// CONSTRUCTOR - DESTRUCTOR
				//____________________________________	
				UTexture();
				UTexture(const FString& _resourcePath);
			
				ASSET_REPLICATION(UTexture);

			public:
				////////////////////////////////////////////////
				// FUNCTIONALITY - ARCHIVAGE
				//____________________________________	
				void Archive(UArchive& out_archive)  override;
				bool Dearchive(UArchive& out_archive)  override;

			public:
				////////////////////////////////////////////////
				// DATA
				//____________________________________	
				/** Indicate the texture's usage. */
				RESOURCE_PROPERTY(ETextureType, TextureType);
				/** Indicates type of a texture (2D texture, cubemap). */
				RESOURCE_PROPERTY(ETextureAspect, TextureMode);
				/** Wrap mode (Wrap, Clamp, Repeat(Wrap + Scale factor)) of the texture.*/
				RESOURCE_PROPERTY(EWrappingMode, WrappingMode);
				/** Indicates filter to apply on texture (Linear, Bilinear, Anisotropy). */
				RESOURCE_PROPERTY(EFilteringMode, FilteringMode);
				/** The anisotropy's level of the texture. Between [1,16](need properties or setter for safety) */
				RESOURCE_PROPERTY(uint, AnisotropyLevel);

				/** Texture's NativeResourceHandle. */
				DEFAULT_READONLY_PROPERTY(UNativeTextureResource, kNativeTextureHandle);
				

			public:
				////////////////////////////////////////////////
				// INTRA-FUNCTIONALITY CLASS
				// An Intra-class is a class which allow to manage private data of utilities. (Usefull for native functionnality)
				//____________________________________	
				/** An intra-class which manage the native buffer syncrhonization. */
				class FNativeSynchronizer
				{
					public:
						static void Synchronize(UTexture& _texture);
				};		
		};
		SERIALIZABLE_INSTANCE(UTexture)
	}
}
typedef ParadigmEngine::Resource::UTexture UTexture;
typedef ParadigmEngine::Resource::UTexture::ETextureAspect ETextureAspect;
typedef ParadigmEngine::Resource::UTexture::ETextureType ETextureType;

typedef KResource KTexture;
#endif