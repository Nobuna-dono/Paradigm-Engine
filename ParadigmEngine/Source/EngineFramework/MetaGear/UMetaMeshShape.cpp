#include <EngineFramework/MetaGear/LowRenderer/FMetaMeshShape.h>
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
				void UMetaMeshShape::Archive(UArchive& out_archive) 
				{
					ARCHIVE_MEMBER(UMetaMeshShape, out_archive, 2);
					FString str;
					UModel model;
					if (PARADIGM_RESOURCE->GetModel(kModel, model))
						str = model.ResourcePath;
					SERIALIZE_DATA(out_archive, FString("Model"), str);
					SERIALIZE_ENUM(EPrimitiveTopology);
					SERIALIZE_MEMBER(out_archive, Topology);
				}

				bool UMetaMeshShape::Dearchive(UArchive& out_archive) 
				{
					SKIP_ARCHIVE_INFO(out_archive);
					FString model;
					DESERIALIZE_MEMBER(out_archive, model);
					kModel = PARADIGM_RESOURCE->ModelKey(model);
					FMetaMeshShape::SetModel(*this, kModel);
					DESERIALIZE_MEMBER(out_archive, Topology);
					return true;
				}
			}
		}
	}
}