#ifndef _UCYLINDRECOLLIDER_H_
#define _UCYLINDRECOLLIDER_H_
#include "./UColliderShape.h"

namespace ParadigmEngine
{
	namespace Physics
	{
		namespace Collision
		{
			struct UCylindreCollider : public UColliderShape
			{
				UCylindreCollider(float _radius, float _height) : radius{ _radius }, height{ _height } {};
				float radius {.5f}, height {1.f};
			};

		}
	}
}
#endif // !_UCYLINDRECOLLIDER_H_
