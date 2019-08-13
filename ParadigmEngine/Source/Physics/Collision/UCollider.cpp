#include <Physics/Collision/UCollider.h>
#include <Physics/Collider.h>
#include <Physics/FTransform.h>
#include <EngineFramework/Factory/UMetaEntity.h>

namespace ParadigmEngine
{
	namespace Physics
	{
		namespace Collision
		{
			void UMetaCollider::_SetShape(const EColliderShape& _value)
			{
				if (m_Shape != _value)
				{
					m_Shape = _value;
					UMetaTransform* tr = GearedUnit->GetTransform();
					FVector3 scale = tr ? tr->Scale : FVector3::One;
					switch (m_Shape)
					{
						case ParadigmEngine::Physics::Collision::NONE:
							if (ShapeData) delete ShapeData;
							ShapeData = nullptr;
							break;
						case ParadigmEngine::Physics::Collision::BOX:
							if (ShapeData) delete ShapeData;
							ShapeData = new UMetaBoxCollider(scale);
							break;
						case ParadigmEngine::Physics::Collision::SPHERE:
							if (ShapeData) delete ShapeData;
							ShapeData = new USphereCollider(scale.x*.5f);
							break;
						case ParadigmEngine::Physics::Collision::CAPSULE:
							if (ShapeData) delete ShapeData;
							ShapeData = new UMetaCapsuleCollider(scale.x*.5f, scale.y);
							break;
						case ParadigmEngine::Physics::Collision::CYLINDER:
							if (ShapeData) delete ShapeData;
							ShapeData = new UCylindreCollider(scale.x*.5f, scale.y);
							break;
						case ParadigmEngine::Physics::Collision::CONE:
							if (ShapeData) delete ShapeData;
							ShapeData = new UConeCollider(scale.x *.5f, scale.y);
							break;
						case ParadigmEngine::Physics::Collision::MESH:
							if (ShapeData) delete ShapeData;
							ShapeData = new UMeshCollider();
							break;
						default:
							break;
					}
				}
			}
		}
	}
}