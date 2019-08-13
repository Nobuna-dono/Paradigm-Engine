#include <GameFramework/GameGear/LowRenderer/GCamera.h>

namespace ParadigmEngine
{
	namespace GameFramework
	{
		namespace GameGear
		{
			namespace LowRenderer
			{
				UMatrix4 GCamera::ComputeProjection() const
				{
					return FMetaCamera::ComputeProjection(Data);
				}

				UMatrix4 GCamera::ComputeView() const
				{
					return FMetaCamera::ComputeView(Data);
				}
			}
		}
	}
}