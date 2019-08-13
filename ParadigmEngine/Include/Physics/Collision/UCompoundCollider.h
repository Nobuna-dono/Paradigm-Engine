#ifndef _UCOMPOUNDCOLLIDER_H_
#define _UCOMPOUNDCOLLIDER_H_
#include "./UCollider.h"

namespace ParadigmEngine
{
	namespace Physics
	{
		namespace Collision
		{
			struct UCompoundCollider : public UMetaCollider
			{
				static const GearID GearID = 0x0015;
				//une liste de colliders???????
			};

		}
	}
}
#endif // !_UCOMPOUNDCOLLIDER_H_
