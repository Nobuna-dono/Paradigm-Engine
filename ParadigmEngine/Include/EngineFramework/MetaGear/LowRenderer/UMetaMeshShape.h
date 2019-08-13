#ifndef _UMETAMESHSHAPE_H_ 
#define _UMETAMESHSHAPE_H_ 

#include <Resource/UModel.h> 

#include <Property.h> 
#include <Serialization/FEnumerator.h>
#include <EngineFramework/MetaGear/ParadigmMetaGear.h>

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace MetaGear
		{
			namespace LowRenderer
			{
				SERIALIZABLE_ENUM(ERenderMode,
					Triangle,
					Line,
					Point
				);

				METAGEAR_CLASS(UMetaMeshShape)
				{
					METAGEAR_ATTRIBUTES(UMetaMeshShape)
					
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
						KModel kModel{ INVALID_KEY_REGISTER };
						EPrimitiveTopology Topology{ EPrimitiveTopology::EPrimitiveTopology_TriangleList };
						UNativeModelBuffer kNativeModelBuffer;
						uint TriangleCount;
				};
				SERIALIZABLE_INSTANCE(UMetaMeshShape)
			}
		}
	}
}
typedef ParadigmEngine::EngineFramework::MetaGear::LowRenderer::UMetaMeshShape UMetaMeshShape;

#endif