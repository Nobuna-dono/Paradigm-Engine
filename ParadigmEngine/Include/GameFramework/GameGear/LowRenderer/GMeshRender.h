#ifndef _GMESHRENDER_H_
#define _GMESHRENDER_H_

#include <GameFramework/GameGear/GGear.h>
#include <EngineFramework/MetaGear/LowRenderer/UMetaMeshRender.h>

namespace ParadigmEngine
{
	using namespace EngineFramework::MetaGear::LowRenderer;

	namespace GameFramework
	{
		namespace GameGear
		{
			namespace LowRenderer
			{
				GEAR_CLASS(GMeshRender, UMetaMeshRender)
				{
					GEAR_CLASS_CONSTRUCTOR(GMeshRender, UMetaMeshRender);

					public:
						////////////////////////////////////////////////
						// FUNCTIONALITY
						//____________________________________	
						void SetMaterial(const FMaterial& _mat, uint _index = 0);
						FMaterial& GetMaterial(uint _index = 0);
				};
			}
		}
	}
}
typedef ParadigmEngine::GameFramework::GameGear::LowRenderer::GMeshRender GMeshRender;

#endif