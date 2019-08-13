#ifndef _UCAPSULECOLLIDER_H_
#define _UCAPSULECOLLIDER_H_
#include "./UColliderShape.h"

namespace ParadigmEngine
{
	namespace Physics
	{
		namespace Collision
		{
			struct UMetaCapsuleCollider : public UColliderShape
			{
				UMetaCapsuleCollider(float _radius, float _height) : radius{ _radius }, height{ _height } {};
				float radius{.5f}, height{1.f};
			};
			
		}
	}
}
#endif // !_UCAPSULECOLLIDER_H_
