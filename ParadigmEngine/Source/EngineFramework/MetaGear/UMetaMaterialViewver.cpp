#include <EngineFramework/MetaGear/LowRenderer/UMetaMaterialViewver.h>
#include <Resource/FResourceSupervisor.h>

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace MetaGear
		{
			namespace LowRenderer
			{
				////////////////////////////////////////////////
				// FUNCTIONALITY - ARCHIVAGE
				//____________________________________	
				void UMetaMaterialViewver::Archive(UArchive& out_archive) 
				{
					ARCHIVE_MEMBER(UMetaMaterialViewver, out_archive, 11);
					SERIALIZE_MEMBER(out_archive, VertexFilename);
					SERIALIZE_MEMBER(out_archive, VertexEntry);
					SERIALIZE_MEMBER(out_archive, PixelFilename);
					SERIALIZE_MEMBER(out_archive, PixelEntry);
					SERIALIZE_MEMBER(out_archive, GeometryFilename);
					SERIALIZE_MEMBER(out_archive, GeometryEntry);
					SERIALIZE_MEMBER(out_archive, ComputeFilename);
					SERIALIZE_MEMBER(out_archive, ComputeEntry);
					SERIALIZE_DATA(out_archive, FString("Texture"), Texture);
					FString str;
					UModel model;
					if (PARADIGM_RESOURCE->GetModel(kModel, model))
						str = model.ResourcePath;
					SERIALIZE_DATA(out_archive, FString("Model"), str);
					SERIALIZE_MEMBER(out_archive, Topology);
				}

				bool UMetaMaterialViewver::Dearchive(UArchive& out_archive)
				{
					SKIP_ARCHIVE_INFO(out_archive);
					DESERIALIZE_MEMBER(out_archive, VertexFilename);
					DESERIALIZE_MEMBER(out_archive, VertexEntry);
					DESERIALIZE_MEMBER(out_archive, PixelFilename);
					DESERIALIZE_MEMBER(out_archive, PixelEntry);
					DESERIALIZE_MEMBER(out_archive, GeometryFilename);
					DESERIALIZE_MEMBER(out_archive, GeometryEntry);
					DESERIALIZE_MEMBER(out_archive, ComputeFilename);
					DESERIALIZE_MEMBER(out_archive, ComputeEntry);
					DESERIALIZE_MEMBER(out_archive, Texture);					
					FString model;
					DESERIALIZE_MEMBER(out_archive, model);
					kModel = PARADIGM_RESOURCE->ModelKey(model);
					DESERIALIZE_MEMBER(out_archive, Topology);
					bOutdated = true;
					UKeyRegister key = PARADIGM_RESOURCE->TextureKey(Texture);
					if (key != INVALID_KEY_REGISTER)
					{
						UTexture& texture = PARADIGM_RESOURCE->Texture(key);
						FTexture::SyncResource(texture);
						if (!MaterialData.TextureValues.Count())
							MaterialData.TextureValues.Add({});
						MaterialData.TextureValues[0] = std::pair<FString, UTexture>("Albedo", texture);
					}
					return true;
				}

			}
		}
	}
}