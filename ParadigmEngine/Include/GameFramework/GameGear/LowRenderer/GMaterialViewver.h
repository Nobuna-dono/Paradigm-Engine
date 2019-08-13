#ifndef _GMATERIALVIEWVER_H_
#define _GMATERIALVIEWVER_H_

//#include PROCESSOR_LINKAGE(FMaterialViewverProcessor)

#include <GameFramework/GameGear/GGear.h>
#include <GameFramework/GameGear/LowRenderer/GMeshRender.h>
#include <GameFramework/GameGear/LowRenderer/GMeshShape.h>
#include <EngineFramework/Processor/FMaterialViewverProcessor.h> 

namespace ParadigmEngine
{
	using namespace EngineFramework::MetaGear::LowRenderer;

	namespace GameFramework
	{
		namespace GameGear
		{
			namespace LowRenderer
			{
				DEFAULT_GEAR_CLASS(GMaterialViewver, UMetaMaterialViewver)
			}
		}
	}
}
typedef ParadigmEngine::GameFramework::GameGear::LowRenderer::GMaterialViewver GMaterialViewver;


#endif