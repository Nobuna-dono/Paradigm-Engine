#ifndef _UCOLLISION_H_
#define _UCOLLISION_H_
#include <ParadigmMath.h>

namespace ParadigmEngine
{
	namespace Physics
	{
		namespace Collision
		{
			class UMetaCollider;
		}
	}

	namespace Physics
	{
		namespace Collision
		{
			struct UCollision
			{
				UMetaCollider* m_Object1;
				UMetaCollider* m_Object2;
				UVector3 m_localPointA;
				UVector3 m_localPointB;
				UVector3 m_positionWorldOnB;
				UVector3 m_normalWorldOnB;

				float m_distance1;
				float m_combinedFriction;
				float m_combinedRollingFriction;//torsional friction orthogonal to contact normal, useful to make spheres stop rolling forever
				float m_combinedSpinningFriction;//torsional friction around contact normal, useful for grasping objects
				float m_combinedRestitution;

				int	m_contactPointFlags;

				float m_appliedImpulse;
				float m_appliedImpulseLateral1;
				float m_appliedImpulseLateral2;
				float m_contactMotion1;
				float m_contactMotion2;

				float m_combinedContactStiffness1;
				float m_combinedContactDamping1;

				float m_frictionCFM;

				int m_lifeTime;//lifetime of the contactpoint in frames

				UVector3 m_lateralFrictionDir1;
				UVector3 m_lateralFrictionDir2;
			};
		}
	}
}
#endif // !_UCOLLISION_H_

