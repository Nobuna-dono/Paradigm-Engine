#ifndef _GRIGIDBODY_H_
#define _GRIGIDBODY_H_

#include <EngineFramework/Processor/FRigidbodyProcessor.h>
#include <GameFramework/GameGear/GGear.h>
#include <GameFramework/GameEntity/GEntity.h>
#include <Physics/Force/FRigidbody.h>
#include <Property.h>

namespace ParadigmEngine
{
	namespace GameFramework
	{
		namespace GameGear
		{
			namespace Physics
			{
				GEAR_CLASS(GRigidbody, UMetaRigidbody)
				{
					GEAR_CLASS_CONSTRUCTOR(GRigidbody, UMetaRigidbody);

				public:
					//Methods
					UVector3 GetTotalTorque();
					void ApplyTorque(const UVector3 _torque);
					UVector3 GetTotalForce();
					void ApplyForce(const UVector3 _force, const UVector3 _applicationPosition = { 0,0,0 });

					void ClearForces();

					UVector3 GetLinearVelocity();
					UVector3 GetAngularVelocity();

					void SetLinearVelocity(const UVector3&);
					void SetAngularVelocity(const UVector3&);

					UVector3 GetCenterOfMass();
					void SetCenterOfMass(const UVector3&);



					UVector3 GetGravity();
					void SetGravity(UVector3 _vec);
				public:
					//data
					CUSTOM_PROPERTY(float, Mass, { return m_MetaGear->Mass; }, { m_MetaGear->Mass = _value; });
					CUSTOM_PROPERTY(PhysicsLayer, Layer, { return m_MetaGear->PhysicsTag; }, { m_MetaGear->PhysicsTag = _value; });
					CUSTOM_PROPERTY(UMetaRigidbody::EMovingState, MovingState, { return m_MetaGear->MovingState; }, { m_MetaGear->MovingState = _value; });
					CUSTOM_PROPERTY(bool, IsKinematic, {return m_MetaGear-> isKinematic;}, {m_MetaGear->isKinematic = _value;});

					CUSTOM_PROPERTY(bool, FreezePositionX, { return m_MetaGear->freezePositionX; }, { return m_MetaGear->freezePositionX = _value; });
					CUSTOM_PROPERTY(bool, FreezePositionY, { return m_MetaGear->freezePositionY; }, { return m_MetaGear->freezePositionY = _value; });
					CUSTOM_PROPERTY(bool, FreezePositionZ, { return m_MetaGear->freezePositionZ; }, { return m_MetaGear->freezePositionZ = _value; });
					CUSTOM_PROPERTY(bool, FreezeRotationX, { return m_MetaGear->freezeRotationX; }, { return m_MetaGear->freezeRotationX = _value; });
					CUSTOM_PROPERTY(bool, FreezeRotationY, { return m_MetaGear->freezeRotationY; }, { return m_MetaGear->freezeRotationY = _value; });
					CUSTOM_PROPERTY(bool, FreezeRotationZ, { return m_MetaGear->freezeRotationZ; }, { return m_MetaGear->freezeRotationZ = _value; });
					CUSTOM_PROPERTY(bool, useGravity, { return m_MetaGear->useGravity; }, { m_MetaGear->useGravity = _value; });
				};

			}
		}
	}
}
typedef ParadigmEngine::GameFramework::GameGear::Physics::GRigidbody GRigidbody;
#endif // !_GRIGIDBODY_H_
