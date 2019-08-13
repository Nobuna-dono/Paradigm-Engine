#include <NativeInterface/Physics/BulletMotionState.h>
#include <Physics/FTransform.h>
#include <EngineFramework/Factory/UMetaEntity.h>

namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Physics
		{
			ParadigmBulletMotionState::ParadigmBulletMotionState(ParadigmEngine::Physics::Force::UMetaRigidbody* _ptr, const btTransform& startTrans, const btTransform& centerOfMassOffset)
				: btDefaultMotionState(startTrans, centerOfMassOffset)
			{
				m_userPointer = _ptr;
			}

			void ParadigmBulletMotionState::setWorldTransform(const btTransform& centerOfMassWorldTrans)
			{
				btDefaultMotionState::setWorldTransform(centerOfMassWorldTrans);
				ParadigmEngine::Physics::Force::UMetaRigidbody* paradigmPtr = static_cast<ParadigmEngine::Physics::Force::UMetaRigidbody*>(m_userPointer);
				if (paradigmPtr)
				{
					ParadigmEngine::Physics::UMetaTransform* transPtr = paradigmPtr->GearedUnit->GetTransform();
					if (transPtr)
					{
						ParadigmEngine::Physics::UMetaTransform before = *transPtr;
						btVector3 origin = centerOfMassWorldTrans.getOrigin();
						btQuaternion rotation = centerOfMassWorldTrans.getRotation();
						transPtr->Position = { origin.getX(), origin.getY(), origin.getZ() };
						transPtr->Rotation = { rotation.getW(), rotation.getX(), rotation.getY(), rotation.getZ() };

						transPtr->Updated();
						if (before != *transPtr)
							paradigmPtr->MovingState = ParadigmEngine::Physics::Force::UMetaRigidbody::MOVING;
						else
							paradigmPtr->MovingState = ParadigmEngine::Physics::Force::UMetaRigidbody::IDLE;
					}
				}
			}
		}
	}
}