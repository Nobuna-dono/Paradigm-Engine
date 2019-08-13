#include <Physics/Force/FRigidbody.h>
#include <NativeInterface/Physics/IDynamicPhysicsInterface.h>
#include <FParadigmEngine.h>

namespace ParadigmEngine
{
	namespace Physics
	{
		namespace Force
		{

			UVector3 FRigidbody::GetTotalTorque(UMetaRigidbody& _rigid)
			{
				return PARADIGM_PHYSICS.Interface->GetTotalTorque(_rigid);
			}

			void FRigidbody::ApplyTorque(UMetaRigidbody& _rigid, const UVector3 _Torque)
			{
				PARADIGM_PHYSICS.Interface->ApplyTorque(_rigid, _Torque);
			}

			UVector3 FRigidbody::GetTotalForce(UMetaRigidbody& _rigid)
			{
				return PARADIGM_PHYSICS.Interface->GetTotalForce(_rigid);
			}

			void FRigidbody::ApplyForce(UMetaRigidbody& _rigid, const UVector3 _Force, const UVector3 _applicationPosition)
			{
				PARADIGM_PHYSICS.Interface->ApplyForce(_rigid, _Force, _applicationPosition);
			}

			void FRigidbody::ClearForces(UMetaRigidbody& _rigid)
			{
				PARADIGM_PHYSICS.Interface->ClearForces(_rigid);
			}

			UVector3 FRigidbody::GetLinearVelocity(UMetaRigidbody& _rigid)
			{
				return PARADIGM_PHYSICS.Interface->GetLinearVelocity(_rigid);
			}

			UVector3 FRigidbody::GetAngularVelocity(UMetaRigidbody& _rigid)
			{
				return PARADIGM_PHYSICS.Interface->GetAngularVelocity(_rigid);
			}

			void FRigidbody::SetLinearVelocity(UMetaRigidbody& _rigid, const UVector3& _velocity)
			{
				PARADIGM_PHYSICS.Interface->SetLinearVelocity(_rigid, _velocity);
			}

			void FRigidbody::SetAngularVelocity(UMetaRigidbody& _rigid, const UVector3& _velocity)
			{
				PARADIGM_PHYSICS.Interface->SetAngularVelocity(_rigid, _velocity);
			}

			UVector3 FRigidbody::GetCenterOfMass(UMetaRigidbody& _rigid)
			{
				return PARADIGM_PHYSICS.Interface->GetCenterOfMass(_rigid);
			}
			void FRigidbody::SetCenterOfMass(UMetaRigidbody& _rigid, const UVector3& _position)
			{
				PARADIGM_PHYSICS.Interface->SetCenterOfMass(_rigid, _position);

			}

			void FRigidbody::SetGravity(const UMetaRigidbody& _rig, UVector3 _vec)
			{
				PARADIGM_PHYSICS.Interface->SetOneGravity(_rig,_vec);
			}

			UVector3 FRigidbody::GetGravity(const UMetaRigidbody& _rig)
			{
				return PARADIGM_PHYSICS.Interface->GetOneGravity(_rig);
			}
		}
	}
}