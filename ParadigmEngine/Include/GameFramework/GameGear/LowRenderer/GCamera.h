#ifndef _GCAMERA_H_
#define _GCAMERA_H_

#include <GameFramework/GameGear/GGear.h>
#include <EngineFramework/MetaGear/LowRenderer/FMetaCamera.h>
#include <EngineFramework/Processor/FCameraProcessor.h>


namespace ParadigmEngine
{	
	using namespace EngineFramework::MetaGear::LowRenderer;

	namespace GameFramework
	{
		namespace GameGear
		{	
			namespace LowRenderer
			{
				GEAR_CLASS(GCamera, UMetaCamera) //: public GGear<UMetaCamera>
				{
					GEAR_CLASS_CONSTRUCTOR(GCamera, UMetaCamera);					
					
					public:
						////////////////////////////////////////////////
						// FUNCTIONALITY
						//____________________________________	
						/** Compute and return the projection matrix from a camera gear. */
						UMatrix4 ComputeProjection() const;
						/** Compute and return the view matrix from a camera gear. */
						UMatrix4 ComputeView() const;

				};
			}
		}
	}
}

typedef ParadigmEngine::GameFramework::GameGear::LowRenderer::GCamera GCamera;
#endif