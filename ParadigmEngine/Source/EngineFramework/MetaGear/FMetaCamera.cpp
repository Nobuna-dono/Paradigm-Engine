#include <EngineFramework/MetaGear/LowRenderer/FMetaCamera.h>
#include <EngineFramework/Factory/UMetaEntity.h>
#include <FParadigmEngine.h>
#include <ParadigmMath.h>

#include <Physics/UTransform.h>

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace MetaGear
		{
			namespace LowRenderer
			{
				UMatrix4 FMetaCamera::ComputeProjection(const UMetaCamera& _metaCamera)
				{
					if (_metaCamera.Projection == EProjection::Perspective)
					{
						float screenAspect = (float)PARADIGM_GRAPHICS->GetViewportWidth(_metaCamera.DisplayTarget) / (float)PARADIGM_GRAPHICS->GetViewportHeight(_metaCamera.DisplayTarget);
						return UMatrix4({
							1.f / (screenAspect * tan(_metaCamera.FieldOfView * 0.5f)),	0.f,								0.f,							0.f,
							0.f,											1.f / (tan(_metaCamera.FieldOfView * 0.5f)),	0.f,								0.f,
							0.f,											0.f,								-((_metaCamera.Far + _metaCamera.Near) / (_metaCamera.Far - _metaCamera.Near)),	-1.f,
							0.f,											0.f,								-((2.f * _metaCamera.Far *_metaCamera.Near) / (_metaCamera.Far - _metaCamera.Near)),								0.f
						});
					}
					else
					{
						THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR("Ortographic Projection not implemented");
					}
				}

				UMatrix4 FMetaCamera::ComputeView(const UMetaCamera& _metaCamera)
				{
					UMetaTransform* transform = _metaCamera.GearedUnit->GetTransform();
					return FMatrix4::CreateLookAtLH(Core::Math::Row_Major, transform->Position, transform->Position + transform->Forward(), transform->Upward());
				}

			}
		}
	}
}