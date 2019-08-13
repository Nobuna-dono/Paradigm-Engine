#ifndef _FRIGIDBODYPROCESSOR_H_
#define _FRIGIDBODYPROCESSOR_H_

#include <EngineFramework/Processor/TGearProcessor.h>
#include <Physics/Force/URigidbody.h>

namespace ParadigmEngine
{
	using namespace Physics::Force;
	namespace EngineFramework
	{
		namespace Processor
		{
			GEAR_PROCESSOR_CLASS(FRigidBodyProcessor, UMetaRigidbody)
			{
				public:
					//static data
					static const uint BaseEnabledPipelines{ INITIALIZE | PREPHYSICS };

				public:
					TGearProcessor() = default;
					~TGearProcessor() = default;

					void InitializeOne(UMetaRigidbody& _data) override;
					void UpdateOne(UMetaRigidbody& _data) override;
					void PrePhysicsOne(UMetaRigidbody& _data) override;
					void PostPhysicsOne(UMetaRigidbody& _data) override;
					void TerminateOne(UMetaRigidbody& _data) override;

			};

		}
	}
}

#endif // !_FRIGIDBODYPROCESSOR_H_
