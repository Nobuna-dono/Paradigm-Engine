#include <NativeInterface\Physics\FPhysicsInterface.h>



namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Physics
		{
			void FPhysicsInterface::Initialize()
			{
				Interface->Initialize();
			}

			void FPhysicsInterface::Step()
			{
				Interface->Step();
			}

			TArray<URayCastHit> FPhysicsInterface::Raycast(UVector3& _from, UVector3& _to, bool _stopToFirstCollision) const
			{
				return Interface->Raycast(_from, _to, _stopToFirstCollision);
			}

			bool FPhysicsInterface::Raycast(UVector3& _from, UVector3& _to, URayCastReport& hit, bool _stopToFirstCollision) const
			{
				return Interface->Raycast(_from, _to, hit, _stopToFirstCollision);
			}

			void FPhysicsInterface::SetGravity(const FVector3& _force) const
			{
				Interface->SetGravity(_force);
			}

			void FPhysicsInterface::SetEarthGravity()
			{ 
				SetGravity({ 0, -9.81f, 0 }); 
			};

			void FPhysicsInterface::SetMoonGravity()
			{ 
				SetGravity({ 0, -1.62f, 0 }); 
			};

			void FPhysicsInterface::SetMarsGravity()
			{ 
				SetGravity({ 0, -3.71f, 0 }); 
			};
		}
	}
}