#ifndef _UMESHCOLLIDER_H_
#define _UMESHCOLLIDER_H_
#include "./UColliderShape.h"

namespace ParadigmEngine
{
	namespace Physics
	{
		namespace Collision
		{
			struct UMeshCollider : public UColliderShape
			{
				UKeyRegister mesh;
			};
		}
	}
}
#endif // !_UMESHCOLLIDER_H_