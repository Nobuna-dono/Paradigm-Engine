#ifndef _FMETACAMERA_H_
#define _FMETACAMERA_H_

#include <NativeInterface/Graphics/NativeGraphicsEnums.h>
#include <EngineFramework/MetaGear/LowRenderer/UMetaCamera.h>
#include <EngineFramework/Processor/FCameraProcessor.h>

#include <FLayer.h>
#include <FColor.h>

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace MetaGear
		{
			namespace LowRenderer
			{
				class FMetaCamera
				{
					public:
						////////////////////////////////////////////////
						// FUNCTIONALITY
						//____________________________________	
						/** Compute and return the projection matrix from a camera gear. (RowMajor Matrix) */
						static UMatrix4 ComputeProjection(const UMetaCamera& _metaCamera);
						/** Compute and return the view matrix from a camera gear. (RowMajor Matrix) */
						static UMatrix4 ComputeView(const UMetaCamera& _metaCamera);
				};
			}
		}
	}
}

#endif