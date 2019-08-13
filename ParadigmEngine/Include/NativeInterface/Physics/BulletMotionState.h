#ifndef _BULLETMOTIONSTATE_H_
#define _BULLETMOTIONSTATE_H_


#include "btBulletDynamicsCommon.h"
#include <Physics/Force/FRigidbody.h>

namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Physics
		{
			///The btDefaultMotionState provides a common implementation to synchronize world transforms with offsets.
			struct	ParadigmBulletMotionState : public btDefaultMotionState
			{

				ParadigmBulletMotionState(ParadigmEngine::Physics::Force::UMetaRigidbody*, const btTransform& startTrans = btTransform::getIdentity(), const btTransform& centerOfMassOffset = btTransform::getIdentity());

				///synchronizes world transform from physics to user
				///Bullet only calls the update of worldtransform for active objects
				virtual void	setWorldTransform(const btTransform& centerOfMassWorldTrans);
			};
		}
	}
}

#endif // !_BULLETMOTIONSTATE_H_
