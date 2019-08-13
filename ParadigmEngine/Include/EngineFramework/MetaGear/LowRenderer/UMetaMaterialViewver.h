#ifndef _UMETAMATERIALVIEWVER_H_
#define _UMETAMATERIALVIEWVER_H_

#include <Resource/FModel.h>
#include <Resource/FMetaMaterial.h>
#include <EngineFramework/MetaGear/ParadigmMetaGear.h>
#include <ParadigmCore.h>

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace MetaGear
		{
			namespace LowRenderer
			{
				METAGEAR_CLASS(UMetaMaterialViewver)
				{
					METAGEAR_ATTRIBUTES(UMetaMaterialViewver)
					
					public:
						////////////////////////////////////////////////
						// FUNCTIONALITY - ARCHIVAGE
						//____________________________________	
						void Archive(UArchive& out_archive)  override;
						bool Dearchive(UArchive& out_archive)  override;

					public:
						FString VertexFilename {"Resource/Shader/BasicVertex.vs"};
						FString VertexEntry{ "VertexToPixel" };
						
						FString PixelFilename{ "Resource/Shader/BasicPixel.ps" }; 
						FString PixelEntry{ "PixelToFrameBuffer" };
						
						FString GeometryFilename;
						FString GeometryEntry;
						
						FString ComputeFilename;
						FString ComputeEntry;

						FString Texture;

						KModel kModel; 
						Resource::UMetaMaterialData MaterialData;
						EPrimitiveTopology Topology{ EPrimitiveTopology::EPrimitiveTopology_TriangleList };

						bool bOutdated{ true };
				};
				SERIALIZABLE_INSTANCE(UMetaMaterialViewver)

			}
		}
	}
}
typedef ParadigmEngine::EngineFramework::MetaGear::LowRenderer::UMetaMaterialViewver UMetaMaterialViewver;

#endif