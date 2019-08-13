#ifndef _FPROCESSORSUPERVISOR_H_
#define _FPROCESSORSUPERVISOR_H_
#include "./UProcessor.h"
#include <EngineFramework/MetaGear/UMetaGear.h>
#include <EngineFramework/MetaGear/UCustomBehaviourGear.h>
#include <EngineFramework/Processor/TGearProcessor.h>
#include <EngineFramework/Processor/FCustomBehaviourProcessor.h>
#include <TArray.h>
#include <unordered_map>

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace NativeProcessor
		{
			class FProcessorSupervisor : public UProcessor
			{
				public:
				//Constructor - Destructor
				FProcessorSupervisor() = default;
				~FProcessorSupervisor() = default;

				public:
				// Virtual Pipeline Methods
				void Initialize() override;

				void FixedUpdate() override;

				void Update() override;

				void LateUpdate() override;

				void Pause() override;

				void Terminate() override;

				void Draw() override;

				void PostDraw() override;

				void PrePhysics() override;

				void PostPhysics() override;

				template <typename T>
				struct FNativeAdder
				{
					template <bool = std::is_base_of<UCustomBehaviourGear, T>::value>
					static void AddProcessor(FProcessorSupervisor& _sup) {};

					template <>
					static void AddProcessor<false>(FProcessorSupervisor& _sup)
					{
						_sup.AddProcessor<T>();
					}

					template <>
					static void AddProcessor<true>(FProcessorSupervisor& _sup)
					{
						_sup.AddCustomProcessor<T>();
					}
				};

				template <typename T>
				void AddProcessor()
				{
					GearID id = GEAR_ID(T);
					if (m_Processors.find(id) == m_Processors.end())
					{
						if (std::is_base_of<UCustomBehaviourGear, T>::value)
						{
							//AddCustomProcessor<T>();
							THROW_PARADIGM_EXCEPTION_ARGUMENT("Uses bad fonction,for custom processors use \"AddCustomProcessor<T>()\" instead.");
						}
						else if (std::is_base_of<UMetaGear, T>::value && Processor::TGearProcessor<T>::BaseEnabledPipelines != NONE)
						{
							m_Processors.emplace(id, new Processor::TGearProcessor<T>());
							m_Processors[id]->enabledPiplines = Processor::TGearProcessor<T>::BaseEnabledPipelines;
						}
					}
				}

				template <typename T>
				void AddCustomProcessor()
				{
					GearID id = GEAR_ID(T);
					if (m_Processors.find(id) == m_Processors.end())
					{
						if (std::is_base_of<UCustomBehaviourGear, T>::value && FOverridableCustomProcessor<T>::BaseEnabledPipelines != NONE)
						{
							m_Processors.emplace(id, new FOverridableCustomProcessor<T>());
							m_Processors[id]->enabledPiplines = FOverridableCustomProcessor<T>::BaseEnabledPipelines;
						}
						else
							AddProcessor<T>();
					}
				}

				void CaptureData() {};

				private:
					// Data
					std::unordered_map<GearID, UProcessor*> m_Processors;
			};
		}
	}
}

//typedef ParadigmEngine::EngineFramework::NativeProcessor::FProcessorSupervisor FProcessorSupervisor;
#endif // !_FPROCESSORSUPERVISOR_H_