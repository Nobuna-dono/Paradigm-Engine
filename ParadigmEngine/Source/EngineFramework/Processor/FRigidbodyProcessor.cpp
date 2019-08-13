#include <EngineFramework/Processor/FRigidbodyProcessor.h>
#include <NativeInterface/Physics/IDynamicPhysicsInterface.h>
#include <EngineFramework/Factory/UMetaEntity.h>
#include <Physics/FTransform.h>
#include <FParadigmEngine.h>

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace Processor
		{
			void TGearProcessor<UMetaRigidbody>::InitializeOne(UMetaRigidbody& _data)
			{
				PARADIGM_PHYSICS.Interface->LinkRigidbody(&_data);
			}

			void TGearProcessor<UMetaRigidbody>::UpdateOne(UMetaRigidbody& _data)
			{
				THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR("FRigidbody Updatisation");
			}

			void TGearProcessor<UMetaRigidbody>::PrePhysicsOne(UMetaRigidbody& _data)
			{
				if (_data.GearedUnit->GetTransform()->bOutdated || _data.outdated)
				{
					PARADIGM_PHYSICS.Interface->PresetRigidbody(&_data);
				}
			}

			void TGearProcessor<UMetaRigidbody>::PostPhysicsOne(UMetaRigidbody& _data)
			{

			}

			void TGearProcessor<UMetaRigidbody>::TerminateOne(UMetaRigidbody& _data)
			{
				THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR("FRigidbody termination");
			}
		}
	}
}