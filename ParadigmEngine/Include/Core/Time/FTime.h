#ifndef _FTIME_H_
#define _FTIME_H_

#include <chrono>
#include <FPrint.h>

//#include <ctime>

#define NOW std::chrono::high_resolution_clock::now() //save current time 
#define AUTOCHRONO(X) ParadigmEngine::Core::Time::ScopeChronometer chrono(X); //log the difference of time between now and the end aof the scope
typedef std::chrono::time_point<std::chrono::steady_clock> TimePoint;
#define TIMELAG(X) std::chrono::duration<float, std::milli>(NOW - X).count() //return the difference betwen X and now

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Time
		{
			class ScopeChronometer
			{
			public:
				ScopeChronometer(std::string _in = "Scope duration : ") { prev = NOW; text = _in; }
				~ScopeChronometer() 
				{
					float timeInSecond = std::chrono::duration<float, std::milli>(NOW - prev).count();
					FPrint::Print(text + "[" + FString::ToString((int)(1000.f / timeInSecond)) + " fps] - " +FString::ToString(timeInSecond) + "ms\n");
				}

			private:
				TimePoint prev;
				std::string text;
			};

			class FTime
			{
			public:
				FTime();
				~FTime() = default;

				bool FixedTimeExeeded();
				void Update();
				float GetTimeScale() { return m_timeScale; };
				void SetTimeScale(float _val) { m_timeScale = _val; };

				/** Returns the deltatime from the previous frame in seconds*/
				float GetDeltaTime() { return m_deltaTime; };
				float GetGameTime() { return TIMELAG(gameStart); };
				float GetFixedDeltaTime() { return m_fixedDeltaTime; };

			private:
				float m_deltaTime{ 0 }, m_fixedDeltaTime{ 16 }, m_timeScale{ 1 };
				TimePoint gameStart, lastFixed, lastUpdate;
				bool m_fixedTimeExeeded{ true };
			};
		}
	}
}

#endif