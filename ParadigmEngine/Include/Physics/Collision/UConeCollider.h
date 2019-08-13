#ifndef _UCONECOLLIDER_H_
#define _UCONECOLLIDER_H_
#include "./UColliderShape.h"

namespace ParadigmEngine
{
	namespace Physics
	{
		namespace Collision
		{
			struct UConeCollider : public UColliderShape
			{
				UConeCollider(float _radius, float _height) : radius{ _radius }, height{ _height } {};
				float radius {.5f}, height{1.f};
			};

		}
	}
}
#endif // !_UCONECOLLIDER_H_
