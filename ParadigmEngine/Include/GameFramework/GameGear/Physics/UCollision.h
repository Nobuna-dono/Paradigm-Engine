#ifndef _UCOLLISION2_H_
#define _UCOLLISION2_H_
#include <Physics/Collision/UCollision.h>
namespace ParadigmEngine
{
	namespace GameFramework
	{
		namespace GameGear
		{
			namespace Physics
			{
				struct GCollider;

				struct UCollision
				{
	//				UCollision(ParadigmEngine::Physics::Collision::UCollision&);
					GCollider* m_Object1;
					GCollider* m_Object2;
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
}

#endif // !_UCOLLISION2_H_