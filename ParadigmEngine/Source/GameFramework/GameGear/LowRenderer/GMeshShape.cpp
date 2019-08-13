#include <GameFramework/GameGear/LowRenderer/GMeshShape.h>
#include <ParadigmCore.h>

namespace ParadigmEngine
{
	namespace GameFramework
	{
		namespace GameGear
		{
			namespace LowRenderer
			{
				void GMeshShape::SetModel(const UModel& _original)
				{
					Data.TriangleCount = _original.TriangleCount;
					Data.kModel = PARADIGM_RESOURCE->ModelKey(_original.ResourceName);
					Data.kNativeModelBuffer = _original.NativeBuffers;
				}

				void GMeshShape::SetModel(const FString& _resourceName)
				{
					FMetaMeshShape::SetModel(Data, _resourceName);
				}

				void GMeshShape::SetModel(KModel _kmodel)
				{
					FMetaMeshShape::SetModel(Data, _kmodel);
				}
			}
		}
	}
}