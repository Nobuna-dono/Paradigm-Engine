#pragma once
#include <IKeyTable.h>
#include <Serialization/FEnumerator.h>

namespace ParadigmEngine
{
	namespace Physics
	{
		namespace Collision
		{
			SERIALIZABLE_ENUM(EColliderShape,			
				NONE,
				BOX,
				SPHERE,
				CAPSULE,
				CYLINDER,
				CONE,
				MESH
			);

			struct UColliderShape
			{
			};
		}
	}
}

typedef ParadigmEngine::Physics::Collision::EColliderShape EColliderShape;
typedef ParadigmEngine::Physics::Collision::ENUMERATOR_TYPE(EColliderShape) ENUMERATOR_TYPE(EColliderShape);