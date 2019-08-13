#ifndef _GMESHSHAPE_H_
#define _GMESHSHAPE_H_

#include <GameFramework/GameGear/GGear.h>
#include <EngineFramework/MetaGear/LowRenderer/FMetaMeshShape.h>

namespace ParadigmEngine
{
	using namespace EngineFramework::MetaGear::LowRenderer;

	namespace GameFramework
	{
		namespace GameGear
		{
			namespace LowRenderer
			{

				GEAR_CLASS(GMeshShape, UMetaMeshShape)
				{
					GEAR_CLASS_CONSTRUCTOR(GMeshShape, UMetaMeshShape);

					public:
						////////////////////////////////////////////////
						// FUNCTIONALITY
						//____________________________________	
						/***/
						void SetModel(const UModel& _original);
						/***/
						void SetModel(const FString& _resourceName);
						/***/
						void SetModel(KModel _kmodel);

					public:
						////////////////////////////////////////////////
						// PROPERTY
						//____________________________________	
						CUSTOM_GETTER_PROPERTY(UModel&, Model, { return FMetaMeshShape::GetModel(Data); });
				};

			}
		}
	}
}
typedef ParadigmEngine::GameFramework::GameGear::LowRenderer::GMeshShape GMeshShape;

#endif