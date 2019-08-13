#ifndef _FBULLETINTERFACE_H_
#define _FBULLETINTERFACE_H_

#include <Core/Time/FTime.h>
#include "btBulletDynamicsCommon.h"
#include "IDynamicPhysicsInterface.h"
#include <Core/DataStructure/TKeyTable.h>
//#include <Physics/Collision/UCollision.h>
//#include <Physics/FTransform.h>

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
	using namespace Physics::Collision;
	using namespace Physics::Force;

	namespace NativeInterface
	{
		namespace Physics
		{
			class FBulletInterface : public IDynamicPhysicsInterface
			{
				public:
					//Constructor
					FBulletInterface();
				public:
					//destructor
					~FBulletInterface();
				public:
					//Methods

					void Initialize() override;
					void Step() override;

					TArray<URayCastHit> Raycast(UVector3& _from, UVector3& _to, bool _stopToFirstCollision = true) const override;
					bool Raycast(UVector3& _from, UVector3& _to, URayCastReport& hit, bool _stopToFirstCollision = true) const override;

					static bool EnterCollisionCallback(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1);
					static bool DestroyCollisionCallback(void* usrPtr);

					//Link Methods
					void LinkCollider(UMetaCollider*) override;
					void LinkRigidbody(UMetaRigidbody*) override;
					void GetChildrensColliders(btCompoundShape* _shape, UMetaEntity* _currentEntity, UMetaTransform* _rgidbody, UVector3& out_centerofmass);

					//RigidBody Methods
					void SetActivationStateRigidbody(UMetaRigidbody*) override;
					void DestroyRigidbody(UMetaRigidbody*) override;
					void PresetRigidbody(UMetaRigidbody*) override;
					void UpdateRigidbody(UMetaRigidbody*) override {};
					UVector3	GetTotalTorque(UMetaRigidbody&) override;
					void		ApplyTorque(UMetaRigidbody&, const UVector3 _torque) override;
					UVector3	GetTotalForce(UMetaRigidbody&) override;
					void		ApplyForce(UMetaRigidbody&, const UVector3 _force, const UVector3 _applicationPosition = {0,0,0}) override;
					void ClearForces(UMetaRigidbody&) override;
					UVector3	GetLinearVelocity(UMetaRigidbody&) override;
					UVector3	GetAngularVelocity(UMetaRigidbody&) override;
					void SetLinearVelocity(UMetaRigidbody&, const UVector3&) override;
					void SetAngularVelocity(UMetaRigidbody&, const UVector3&) override;
					UVector3	GetCenterOfMass(UMetaRigidbody&) override;
					void		SetCenterOfMass(UMetaRigidbody&, const UVector3&) override;

					void SetOneGravity(const UMetaRigidbody&, UVector3) override;
					UVector3 GetOneGravity(const UMetaRigidbody&) override;

					void SetGravity(const FVector3&) override;

					void DestroyCollider(UMetaCollider*) override;

				private:
					struct FNativeConvertor
					{
						static btTransform ToBulletData(const UMetaTransform& _nimportequoi);
						static btVector3 ToBulletData(const FVector3& _nimportequoi);
						static btQuaternion ToBulletData(const FQuaternion& _nimportequoi);
						static btManifoldPoint ToBulletData(const UCollision& _nimportequoi);
						 		
						static UMetaTransform ToParadigmData(const btTransform& _nimportequoi);
						static UVector3 ToParadigmData(const btVector3& _nimportequoi);
						static FQuaternion ToParadigmData(const btQuaternion& _nimportequoi);
						static UCollision ToParadigmData(const btManifoldPoint& _nimportequoi);
					};

				private:
					//Data
					///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
					btDefaultCollisionConfiguration* m_collisionConfiguration;
					///use the default collision dispatcher.
					btCollisionDispatcher* m_dispatcher;
					///btDbvtBroadphase is a good general purpose broadphase.
					btBroadphaseInterface* m_overlappingPairCache;
					///the default constraint solver.
					btSequentialImpulseConstraintSolver* m_solver;
					btDiscreteDynamicsWorld* m_dynamicsWorld;

					TKeyTable<btCollisionShape*> m_colliderTable;
					TKeyTable<btRigidBody*> m_rigidbodyTable;

					TimePoint m_previousUpdate;
			};
		}
	}
}
#endif // !_FBULLETINTERFACE_H_