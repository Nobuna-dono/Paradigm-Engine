#include <GameFramework\GameGear\Physics\GRigidbody.h>


namespace ParadigmEngine
{
	namespace GameFramework
	{
		namespace GameGear
		{
			namespace Physics
			{
				UVector3 GRigidbody::GetTotalTorque()
				{
					return FRigidbody::GetTotalTorque(*m_MetaGear);
				}

				void GRigidbody::ApplyTorque(const UVector3 _torque)
				{
					return FRigidbody::ApplyTorque(*m_MetaGear, _torque);
				}

				UVector3 GRigidbody::GetTotalForce()
				{
					return FRigidbody::GetTotalForce(*m_MetaGear);
				}

				void GRigidbody::ApplyForce(const UVector3 _force, const UVector3 _applicationPosition)
				{
					return FRigidbody::ApplyForce(*m_MetaGear, _force, _applicationPosition);
				}

				void GRigidbody::ClearForces()
				{
					return FRigidbody::ClearForces(*m_MetaGear);
				}

				UVector3 GRigidbody::GetLinearVelocity()
				{
					return FRigidbody::GetLinearVelocity(*m_MetaGear);
				}

				UVector3 GRigidbody::GetAngularVelocity()
				{
					return FRigidbody::GetAngularVelocity(*m_MetaGear);
				}

				void GRigidbody::SetLinearVelocity(const UVector3& _newLinVelo)
				{
					return FRigidbody::SetLinearVelocity(*m_MetaGear, _newLinVelo);
				}
				void GRigidbody::SetAngularVelocity(const UVector3& _newAngVelo)
				{
					return FRigidbody::SetAngularVelocity(*m_MetaGear, _newAngVelo);
				}

				UVector3 GRigidbody::GetCenterOfMass()
				{
					return FRigidbody::GetCenterOfMass(*m_MetaGear);
				}
				void GRigidbody::SetCenterOfMass(const UVector3& _newCenter)
				{
					return FRigidbody::SetCenterOfMass(*m_MetaGear, _newCenter);
				}

				void GRigidbody::SetGravity(UVector3 _vec)
				{
					return FRigidbody::SetGravity(*m_MetaGear, _vec);
				}

				UVector3 GRigidbody::GetGravity()
				{
					return FRigidbody::GetGravity(*m_MetaGear);
				}
			}
		}
	}
}