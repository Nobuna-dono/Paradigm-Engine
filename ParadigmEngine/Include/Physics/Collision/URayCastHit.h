#ifndef _URAYCASTHIT_H_
#define _URAYCASTHIT_H_
#include <Core/DataStructure/TArray.h>
#include <EngineFramework/Factory/UMetaEntity.h>
#include <ParadigmMath.h>

namespace ParadigmEngine
{
	namespace Physics
	{
		namespace Collision
		{
			struct URayCastHit
			{
				EngineFramework::Factory::UMetaEntity*  entity;

				FVector3 contactNormal;
				FVector3 contactPosition;
				FVector3 contactFraction;
			};

			struct URayCastReport
			{
				bool hasHit {false};
				TArray<URayCastHit> hits;

				operator bool() { return hasHit; };
			};
		}
	}
}

#endif // !_URAYCASTHIT_H_
