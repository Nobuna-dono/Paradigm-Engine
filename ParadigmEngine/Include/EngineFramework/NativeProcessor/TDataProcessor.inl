////////////////////////////////////////////////////////////////////////////////////////////////
// _TGearsProcessor_H_'s inline file
//________________________________________________________________________
#include <ParadigmDebug.h>
#include <ParadigmException.h>
#include <EngineFramework/Factory/FFactorySupervisor.h>

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace NativeProcessor
		{
			template<class GearT, class derive>
			void TDataProcessor<GearT, derive>::Initialize()
			{
				if (!m_Data)
					return;
				for (TStaticKeyTable<GearT>::Iterator it = m_Data->Begin(); it != m_Data->End(); ++it)
				{
					try
					{
						InitializeOne(*it);
						(*it).bIsInitialized = 1;
					}
					catch (const ParadigmException& paradigmException)
					{
						FPrint::Print(paradigmException.SumUp(), EParadigmDebugLevel::CAUGHT_EXCEPTION);
						PARADIGM_PAUSE;
					}
				}
			}

			template<class GearT, class derive>
			void TDataProcessor<GearT, derive>::Update()
			{
				if (!m_Data)
					return;
				for (TStaticKeyTable<GearT>::Iterator it = m_Data->Begin(); it != m_Data->End(); ++it)
				{
					try
					{
						if (!(*it).bIsInitialized)
						{
							InitializeOne(*it);
							(*it).bIsInitialized = 1;
							//FPrint::Print((*it).GearedUnit->Name + typeid(GearT).Name() + " Inited\n");
						}
						if(enabledPiplines & UPDATE)
							UpdateOne(*it);
					}
					PARADIGM_CATCH_EXCEPTION;
				}
			}

			template<class GearT, class derive>
			void TDataProcessor<GearT, derive>::FixedUpdate()
			{
				if (!m_Data)
					return;
				for (TStaticKeyTable<GearT>::Iterator it = m_Data->Begin(); it != m_Data->End(); ++it)
				{
					try
					{
						FixedUpdateOne(*it);
					}
					PARADIGM_CATCH_EXCEPTION;
				}
			}

			template<class GearT, class derive>
			void TDataProcessor<GearT, derive>::PrePhysics()
			{
				if (!m_Data)
					return;
				for (TStaticKeyTable<GearT>::Iterator it = m_Data->Begin(); it != m_Data->End(); ++it)
				{
					try
					{
						PrePhysicsOne(*it);
					}
					PARADIGM_CATCH_EXCEPTION;
				}
			}

			template<class GearT, class derive>
			void TDataProcessor<GearT, derive>::PostPhysics()
			{
				if (!m_Data)
					return;
				for (TStaticKeyTable<GearT>::Iterator it = m_Data->Begin(); it != m_Data->End(); ++it)
				{
					try
					{
						PostPhysicsOne(*it);
					}
					PARADIGM_CATCH_EXCEPTION;
				}
			}

			template<class GearT, class derive>
			void TDataProcessor<GearT, derive>::LateUpdate()
			{
				if (!m_Data)
					return;
				for (TStaticKeyTable<GearT>::Iterator it = m_Data->Begin(); it != m_Data->End(); ++it)
				{
					try
					{
						LateUpdateOne(*it);
					}
					PARADIGM_CATCH_EXCEPTION;
				}
			}

			template<class GearT, class derive>
			void TDataProcessor<GearT, derive>::Pause()
			{
				if (!m_Data)
					return;
				for (TStaticKeyTable<GearT>::Iterator it = m_Data->Begin(); it != m_Data->End(); ++it)
				{
					try
					{
						PauseOne(*it);
					}
					PARADIGM_CATCH_EXCEPTION;
				}
			}

			template<class GearT, class derive>
			void TDataProcessor<GearT, derive>::Terminate()
			{
				if (!m_Data)
					return;
				for (TStaticKeyTable<GearT>::Iterator it = m_Data->Begin(); it != m_Data->End(); ++it)
				{
					try
					{
						TerminateOne(*it);
					}
					PARADIGM_CATCH_EXCEPTION;
				}
			}

			template<class GearT, class derive>
			void TDataProcessor<GearT, derive>::CaptureData()
			{
				m_Data = static_cast<TStaticKeyTable<GearT>*>(PARADIGM.Factory->GetGearTable<GearT>());

				//if (!(m_Data = static_cast<TStaticKeyTable<GearT>*>(PARADIGM.Factory->GetGearTable<GearT>())))
					//FPrint::Print("Fail to capture  processor's data");
					//THROW_PARADIGM_EXCEPTION("");
			}
		}
	}
}