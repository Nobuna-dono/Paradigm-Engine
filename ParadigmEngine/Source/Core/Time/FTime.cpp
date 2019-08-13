#include <Core/Time/FTime.h>

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Time
		{
			FTime::FTime()
			{
				gameStart = lastFixed = lastUpdate = NOW;
			}

			bool FTime::FixedTimeExeeded()
			{
				if (m_fixedTimeExeeded)
				{
					m_fixedTimeExeeded = false;
					return true;
				}

				return false;
			}

			void FTime::Update()
			{
				m_deltaTime = m_timeScale * std::chrono::duration<float, std::milli>(NOW - lastUpdate).count()/ 1000;
				lastUpdate = NOW;
				if (std::chrono::duration<float, std::milli>(NOW - lastFixed).count() >= m_timeScale * m_fixedDeltaTime)
				{
					lastFixed = NOW;
					m_fixedTimeExeeded = true;
				}
			}
		}
	}
}