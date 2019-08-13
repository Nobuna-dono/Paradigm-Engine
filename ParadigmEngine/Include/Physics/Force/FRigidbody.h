#ifndef _RIGIDBODY_H_
#define _RIGIDBODY_H_

#include <Physics/Force/URigidbody.h>

namespace ParadigmEngine
{
	namespace Physics
	{
		namespace Force
		{
			class FRigidbody
			{
				private:
					FRigidbody() = default;

				public:

				static UVector3	GetTotalTorque(UMetaRigidbody&);
				static void		ApplyTorque(UMetaRigidbody&, const UVector3 _torque);
				static UVector3 GetTotalForce(UMetaRigidbody&);
				static void		ApplyForce(UMetaRigidbody&, const UVector3 _force, const UVector3 _applicationPosition = {0,0,0});

				static void		ClearForces(UMetaRigidbody&);

				static UVector3 GetLinearVelocity(UMetaRigidbody&);
				static UVector3 GetAngularVelocity(UMetaRigidbody&);

				static void		SetLinearVelocity(UMetaRigidbody&, const UVector3&);
				static void		SetAngularVelocity(UMetaRigidbody&, const UVector3&);

				static UVector3 GetCenterOfMass(UMetaRigidbody&);
				static void		SetCenterOfMass(UMetaRigidbody&, const UVector3&);

				static UVector3 GetGravity(const UMetaRigidbody& _rig);
				static void SetGravity(const UMetaRigidbody& _rig, UVector3 _vec);
			};
		}
	}
}

typedef ParadigmEngine::Physics::Force::FRigidbody FRigidbody;
#endif // !_RIGIDBODY_H_
