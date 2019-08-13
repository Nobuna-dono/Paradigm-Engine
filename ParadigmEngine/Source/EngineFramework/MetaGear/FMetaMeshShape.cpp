#include <EngineFramework/MetaGear/LowRenderer/FMetaMeshShape.h>
#include <ParadigmCore.h>

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace MetaGear
		{
			namespace LowRenderer
			{
				void FMetaMeshShape::SetModel(UMetaMeshShape& out_meta, const FString& _resourceName)
				{
					out_meta.kModel = PARADIGM_RESOURCE->ModelKey(_resourceName);
					UModel model;
					if (PARADIGM_RESOURCE->GetModel(out_meta.kModel, model))
					{
						out_meta.kNativeModelBuffer = model.NativeBuffers;
						out_meta.TriangleCount = model.TriangleCount;
					}
					else
					{
						out_meta.kNativeModelBuffer = {INVALID_KEY_REGISTER,INVALID_KEY_REGISTER };
						out_meta.TriangleCount = 0;
					}
				}

				void FMetaMeshShape::SetModel(UMetaMeshShape& out_meta, KModel _kmodel)
				{
					out_meta.kModel = _kmodel;
					UModel model;
					if (PARADIGM_RESOURCE->GetModel(out_meta.kModel, model))
					{
						out_meta.kNativeModelBuffer = model.NativeBuffers;
						out_meta.TriangleCount = model.TriangleCount;
					}
					else
					{
						out_meta.kNativeModelBuffer = { INVALID_KEY_REGISTER,INVALID_KEY_REGISTER };
						out_meta.TriangleCount = 0;
					}
				}

				UModel& FMetaMeshShape::GetModel(UMetaMeshShape& out_meta)
				{
					return PARADIGM_RESOURCE->Model(out_meta.kModel);
				}
			}
		}
	}
}