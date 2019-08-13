#include <Resource/UTexture.h>
#include <ParadigmCore.h>


namespace ParadigmEngine
{
	namespace Resource
	{
		UTexture::UTexture()		
			: UResource()
		{
			GENERATE_ASSET_ARCHIVE(this, FString("UResource"));
			TextureType = TextureType_Default;
			TextureMode = TextureAspect_2D;
			WrappingMode = EWrappingMode::EWrappingMode_Repeat;
			FilteringMode = EFilteringMode::EFilteringMode_Linear;
			AnisotropyLevel = 0;
		}

		UTexture::UTexture(const FString& _resourcePath)
			: UResource(_resourcePath) 
		{
			TextureType = TextureType_Default;
			TextureMode = TextureAspect_2D;
			WrappingMode = EWrappingMode::EWrappingMode_Repeat;
			FilteringMode = EFilteringMode::EFilteringMode_Linear;
			AnisotropyLevel = 0;
		}

		void UTexture::FNativeSynchronizer::Synchronize(UTexture& _texture)
		{
			if (!_texture.m_bSynchronized)
			{
				UTextureDescriptor desc;
				desc.Filename = _texture.ResourcePath;
				desc.AnisotropyLevel = _texture.AnisotropyLevel;
				desc.FilteringMode = _texture.FilteringMode;
				desc.WrappingMode = _texture.WrappingMode;

				PARADIGM_GRAPHICS->CreateTextureResource(_texture.m_kNativeTextureHandle, desc);
				_texture.m_bSynchronized = true;
			}
		}

		void UTexture::Archive(UArchive& out_archive) 
		{
			SERIALIZE_ENUM(ETextureType);
			SERIALIZE_ENUM(EWrappingMode);
			SERIALIZE_ENUM(EFilteringMode);
			SERIALIZE_ENUM(ETextureAspect);

			ARCHIVE_MEMBER(UTexture,out_archive, 6);
			SERIALIZE_MEMBER(out_archive, m_ResourcePath);
			SERIALIZE_MEMBER(out_archive, m_TextureType);
			SERIALIZE_MEMBER(out_archive, m_TextureMode);
			SERIALIZE_MEMBER(out_archive, m_WrappingMode);
			SERIALIZE_MEMBER(out_archive, m_FilteringMode);
			SERIALIZE_MEMBER(out_archive, m_AnisotropyLevel);
		}

		bool UTexture::Dearchive(UArchive& out_archive) 
		{
			SKIP_ARCHIVE_INFO(out_archive);
			DESERIALIZE_MEMBER(out_archive, m_ResourcePath);
			DESERIALIZE_MEMBER(out_archive, m_TextureType);
			DESERIALIZE_MEMBER(out_archive, m_TextureMode);
			DESERIALIZE_MEMBER(out_archive, m_WrappingMode);
			DESERIALIZE_MEMBER(out_archive, m_FilteringMode);
			DESERIALIZE_MEMBER(out_archive, m_AnisotropyLevel);
			return true;
		}
	}
}