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
			void TKeyTableDataProcessor<T>::Initialize()
			{
				for (TKeyTable<T>::Iterator it = m_Data->Begin(); it != m_Data->End(); ++it)
				{
					InitializeOne(*it);
				}
			}

			template<typename T>
			void TKeyTableDataProcessor<T>::Update()
			{
				for (TKeyTable<T>::Iterator it = m_Data->Begin(); it != m_Data->End(); ++it)
				{
					UpdateOne(*it);
				}
			}

			template<typename T>
			void TKeyTableDataProcessor<T>::FixedUpdate()
			{
				for (TKeyTable<T>::Iterator it = m_Data->Begin(); it != m_Data->End(); ++it)
				{
					FixedUpdateOne(*it);
				}
			}

			template<typename T>
			void TKeyTableDataProcessor<T>::PrePhysics()
			{
				for (TKeyTable<T>::Iterator it = m_Data->Begin(); it != m_Data->End(); ++it)
				{
					PrePhysicsOne(*it);
				}
			}

			template<typename T>
			void TKeyTableDataProcessor<T>::PostPhysics()
			{
				for (TKeyTable<T>::Iterator it = m_Data->Begin(); it != m_Data->End(); ++it)
				{
					PostPhysicsOne(*it);
				}
			}

			template<typename T>
			void TKeyTableDataProcessor<T>::LateUpdate()
			{
				for (TKeyTable<T>::Iterator it = m_Data->Begin(); it != m_Data->End(); ++it)
				{
					LateUpdateOne(*it);
				}
			}

			template<typename T>
			void TKeyTableDataProcessor<T>::Pause()
			{
				for (TKeyTable<T>::Iterator it = m_Data->Begin(); it != m_Data->End(); ++it)
				{
					PauseOne(*it);
				}
			}

			template<typename T>
			void TKeyTableDataProcessor<T>::Terminate()
			{
				for (TKeyTable<T>::Iterator it = m_Data->Begin(); it != m_Data->End(); ++it)
				{
					TerminateOne(*it);
				}
			}
		}
	}
}