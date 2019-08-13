////////////////////////////////////////////////////////////////////////////////////////////////
// _TKEYTABLEDATAPROCESSOR_H_'s inline file
//________________________________________________________________________

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace NativeProcessor
		{
			template<typename T>
			void TStaticKeyTableDataProcessor<T>::Initialize()
			{
				for (TStaticKeyTable<T>::Iterator it = m_Data->Begin(); it != m_Data->End(); ++it)
				{
					InitializeOne(*it);
				}
			}

			template<typename T>
			void TStaticKeyTableDataProcessor<T>::Update()
			{
				for (TStaticKeyTable<T>::Iterator it = m_Data->Begin(); it != m_Data->End(); ++it)
				{
					UpdateOne(*it);
				}
			}

			template<typename T>
			void TStaticKeyTableDataProcessor<T>::FixedUpdate()
			{
				for (TStaticKeyTable<T>::Iterator it = m_Data->Begin(); it != m_Data->End(); ++it)
				{
					FixedUpdateOne(*it);
				}
			}

			template<typename T>
			void TStaticKeyTableDataProcessor<T>::PrePhysics()
			{
				for (TStaticKeyTable<T>::Iterator it = m_Data->Begin(); it != m_Data->End(); ++it)
				{
					PrePhysicsOne(*it);
				}
			}

			template<typename T>
			void TStaticKeyTableDataProcessor<T>::PostPhysics()
			{
				for (TStaticKeyTable<T>::Iterator it = m_Data->Begin(); it != m_Data->End(); ++it)
				{
					PostPhysicsOne(*it);
				}
			}

			template<typename T>
			void TStaticKeyTableDataProcessor<T>::LateUpdate()
			{
				for (TStaticKeyTable<T>::Iterator it = m_Data->Begin(); it != m_Data->End(); ++it)
				{
					LateUpdateOne(*it);
				}
			}

			template<typename T>
			void TStaticKeyTableDataProcessor<T>::Pause()
			{
				for (TStaticKeyTable<T>::Iterator it = m_Data->Begin(); it != m_Data->End(); ++it)
				{
					PauseOne(*it);
				}
			}

			template<typename T>
			void TStaticKeyTableDataProcessor<T>::Terminate()
			{
				for (TStaticKeyTable<T>::Iterator it = m_Data->Begin(); it != m_Data->End(); ++it)
				{
					TerminateOne(*it);
				}
			}
		}
	}
}