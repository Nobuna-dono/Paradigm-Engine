#ifndef _USPHERECOLLIDER_H_
#define _USPHERECOLLIDER_H_
#include "./UCollider.h"

namespace ParadigmEngine
{
	namespace Physics
	{
		namespace Collision
		{
			struct USphereCollider : public UColliderShape
			{
				USphereCollider(float _in) : radius{ _in } {};
				float radius{.5f};
			};
		}
	}
}
#endif // !_USPHERECOLLIDER_H_
