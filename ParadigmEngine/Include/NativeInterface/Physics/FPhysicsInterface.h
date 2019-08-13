#ifndef _PHYSICSITNERFACE_H_
#define _PHYSICSITNERFACE_H_

#include <ParadigmKeyword.h>
#include <FString.h>

#ifdef PARADIGM_NATIVE_PHYSICS_BULLET
#include <NativeInterface/Physics/FBulletInterface.h>
#endif

typedef ParadigmEngine::NativeInterface::Physics::IDynamicPhysicsInterface* IPhysicsInterface;
namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Physics
		{
			static IDynamicPhysicsInterface* GetNativePhysics(FString _config)
			{
				if (_config == "BULLET")
					return new FBulletInterface();
				else
					return nullptr;
			}


			struct FPhysicsInterface
			{
	//			FPhysicsInterface(ParadigmEngine::NativeInterface::Physics::IDynamicPhysicsInterface*);

				//Interface Methods
				void Initialize();
				void Step();

				TArray<URayCastHit> Raycast(UVector3& _from, UVector3& _to, bool _stopToFirstCollision = true) const;
				bool Raycast(UVector3& _from, UVector3& _to, URayCastReport& hit, bool _stopToFirstCollision = true) const;
				void SetGravity(const FVector3&) const;
				void SetEarthGravity();
				void SetMoonGravity();
				void SetMarsGravity();

				//Data
				IPhysicsInterface Interface;
			};
		}
	}
}

typedef ParadigmEngine::NativeInterface::Physics::FPhysicsInterface FPhysicsInterface;
#define PARADIGM_NATIVE_PHYSICS(Config) {ParadigmEngine::NativeInterface::Physics::GetNativePhysics(Config)}

#endif