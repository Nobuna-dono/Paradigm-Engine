#ifndef _UBOXCOLLIDER_H_
#define _UBOXCOLLIDER_H_
#include "UColliderShape.h"
#include <ParadigmMath.h>

namespace ParadigmEngine
{
	namespace Physics
	{
		namespace Collision
		{
			struct UMetaBoxCollider : public UColliderShape
			{
				UMetaBoxCollider(UVector3 _vec) : size{_vec} {};
				UVector3 size;
			};
		}
	}
}
typedef ParadigmEngine::Physics::Collision::UMetaBoxCollider UMetaBoxCollider;
#endif // !_UBOXCOLLIDER_H_
