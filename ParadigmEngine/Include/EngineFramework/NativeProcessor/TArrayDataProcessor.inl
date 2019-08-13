namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace NativeProcessor
		{
			template<typename T>
			void TArrayDataProcessor<T>::Initialize()
			{
				for (std::vector<T>::iterator it = m_Data.begin(); it != m_Data.end(); it++)
				{
					if (it) InitializeOne(*it);
				}
			}

			template<typename T>
			void TArrayDataProcessor<T>::Update()
			{
				for (std::vector<T>::iterator it = m_Data.begin(); it != m_Data.end(); it++)
				{
					if (it) UpdateOne(*it);
				}
			}
			
			template<typename T>
			void TArrayDataProcessor<T>::FixedUpdate()
			{
				for (std::vector<T>::iterator it = m_Data.begin(); it != m_Data.end(); it++)
				{
					if (it) FixedUpdateOne(*it);
				}
			}

			template<typename T>
			void TArrayDataProcessor<T>::LateUpdate()
			{
				for (std::vector<T>::iterator it = m_Data.begin(); it != m_Data.end(); it++)
				{
					if (it) LateUpdateOne(*it);
				}
			}

			template<typename T>
			void TArrayDataProcessor<T>::Pause()
			{
				for (std::vector<T>::iterator it = m_Data.begin(); it != m_Data.end(); it++)
				{
					if (it) PauseOne(*it);
				}
			}

			template<typename T>
			void TArrayDataProcessor<T>::Terminate()
			{
				for (std::vector<T>::iterator it = m_Data.begin(); it != m_Data.end(); it++)
				{
					if (it) TerminateOne(*it);
				}
			}
		}
	}
}