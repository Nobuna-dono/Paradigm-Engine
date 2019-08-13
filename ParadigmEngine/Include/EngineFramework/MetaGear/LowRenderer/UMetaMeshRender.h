#ifndef _UMETAMESHRENDER_H_
#define _UMETAMESHRENDER_H_

#include <Resource/UModel.h>
#include <Resource/FMaterial.h>
#include <EngineFramework/MetaGear/ParadigmMetaGear.h>

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace MetaGear
		{
			namespace LowRenderer
			{
				METAGEAR_CLASS(UMetaMeshRender)
				{
					METAGEAR_ATTRIBUTES(UMetaMeshRender)

					public:
						////////////////////////////////////////////////
						// FUNCTIONALITY - ARCHIVAGE
						//____________________________________	
						void Archive(UArchive& out_archive)  override;
						bool Dearchive(UArchive& out_archive)  override;

					public:
						TArray<FMaterial> Materials;
						bool bCastShadow;
						bool bReceiveShadow;
						bool bPadding1;
						bool bPadding2;
				};
				SERIALIZABLE_INSTANCE(UMetaMeshRender)
			}
		}
	}
}
typedef ParadigmEngine::EngineFramework::MetaGear::LowRenderer::UMetaMeshRender UMetaMeshRender;

#endif
