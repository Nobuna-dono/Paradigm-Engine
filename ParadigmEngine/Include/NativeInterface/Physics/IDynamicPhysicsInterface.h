#ifndef _IDYNAMICPHYSICSINTERFACE_H_
#define _IDYNAMICPHYSICSINTERFACE_H_
#include <Physics/Collision/URayCastHit.h>
//#include <Physics/Force/FRigidbody.h>
#include <Physics/Collision/UCollision.h>

namespace ParadigmEngine
{
	namespace Physics
	{
		namespace Collision
		{
			class UMetaCollider;
		}
		namespace Force
		{
			class UMetaRigidbody;
		}
		class UMetaTransform;
	}
	using namespace Physics;
	using namespace Physics::Force;
	using namespace Physics::Collision;

	namespace NativeInterface
	{
		namespace Physics
		{

			class IDynamicPhysicsInterface
			{
				public:
				///Constructor
				IDynamicPhysicsInterface() { Layers.AddLayer(std::string("Default")); };
				public:
				///destructor
				~IDynamicPhysicsInterface() = default;
				public:
				///Methods
				virtual void LinkCollider(UMetaCollider*) = 0;

				virtual void LinkRigidbody(UMetaRigidbody*) = 0;
				virtual void SetActivationStateRigidbody(UMetaRigidbody*) = 0;
				virtual void DestroyRigidbody(UMetaRigidbody*) = 0;
				virtual void DestroyCollider(UMetaCollider*) = 0;
				virtual void PresetRigidbody(UMetaRigidbody*) = 0;
				virtual void UpdateRigidbody(UMetaRigidbody*) = 0;

				virtual UVector3	GetTotalTorque(UMetaRigidbody&) =0;
				virtual void		ApplyTorque(UMetaRigidbody&, const UVector3 _torque) =0;
				virtual UVector3	GetTotalForce(UMetaRigidbody&) =0;
				virtual void		ApplyForce(UMetaRigidbody&, const UVector3 _force, const UVector3 _applicationPosition = {0,0,0}) =0;
				
				virtual void ClearForces(UMetaRigidbody&) =0;
				
				virtual UVector3	GetLinearVelocity(UMetaRigidbody&) =0;
				virtual UVector3	GetAngularVelocity(UMetaRigidbody&) =0;
				
				virtual void SetLinearVelocity(UMetaRigidbody&, const UVector3&) =0;
				virtual void SetAngularVelocity(UMetaRigidbody&, const UVector3&) =0;
				
				virtual UVector3	GetCenterOfMass(UMetaRigidbody&) =0;
				virtual void		SetCenterOfMass(UMetaRigidbody&, const UVector3&) =0;

				virtual void SetOneGravity(const UMetaRigidbody&, UVector3)=0;
				virtual UVector3 GetOneGravity(const UMetaRigidbody&)=0;

				virtual void SetGravity(const FVector3&) = 0;
				inline void SetEarthGravity() { SetGravity({ 0, -9.81f, 0 });};
				inline void SetMoonGravity() { SetGravity({ 0, -1.62f, 0 }); };
				inline void SetMarsGravity() { SetGravity({ 0, -3.71f, 0 }); };

				virtual void Initialize() =0;
				virtual void Step() =0;

				virtual TArray<URayCastHit> Raycast(UVector3& _from, UVector3& _to, bool _stopToFirstCollision = true) const = 0;
				virtual bool Raycast(UVector3& _from, UVector3& _to, URayCastReport& hit, bool _stopToFirstCollision = true) const = 0;

				FLayerSupervisor Layers;
			};
		}
	}
}


#endif // !_FDYNAMICPHYSICSINTERFACE_H_
