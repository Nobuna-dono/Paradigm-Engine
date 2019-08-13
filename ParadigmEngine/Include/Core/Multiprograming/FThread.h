#ifndef _THREADMANAGER_H_
#define _THREADMANAGER_H_

#include <mutex>
#include <queue>
#include <thread>
#include <utility>
#include <vector>
#include "UThread.h"
#include "../Dispach/UJob.h"

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Multiprograming
		{
			/** Multiprograming service that manage threads and tasks*/
			class FThread
			{
				public:
				struct UJobInfo
				{
					void Join()
					{
						std::unique_lock<std::mutex> locker(mut);
						consume.wait(locker);
					}

					protected:
					std::mutex mut;
					std::condition_variable consume;
				};

				private:
				struct UJobWrap : UJobInfo
				{
					UJobWrap(UDynamicJob* _j) : m_job{ _j } {}
					~UJobWrap() { delete m_job; };

					void Joined()
					{
						consume.notify_all();
					}

					const UDynamicJob* m_job;
				};

				public:
				FThread(unsigned int _numThread = 0u);
				~FThread();

				template<class Func, class... Params>
				/** Add a task to the queue that will be executed by another thread. Defaults value are ignored please specify them*/
				UJobInfo* AddJob(Func&& _func, Params&&... _param)
				{
					m_numWaitingJobs++;

					UJobWrap* JW = new UJobWrap(new UJob<Params...>(_func, _param...));
					m_jobsLock.lock();
					m_jobs.push(JW);
					m_jobsLock.unlock();
					consume.notify_one();
					return JW;
				};

				template<class Func, class Owner, class... Params>
				/** Add a task to the queue that will be executed by another thread. Defaults value are ignored please specify them*/
				UJobInfo* AddMemberJob(Func&& _func, Owner& _owner, Params&&... _param)  // approx 2 micro-sec (0.000002s)
				{
					m_numWaitingJobs++;

					UJobWrap* JW = new UJobWrap(new UMemberJob<Owner, Params...>(_func, _owner, _param...));
					m_jobsLock.lock();
					m_jobs.push(JW);
					m_jobsLock.unlock();
					consume.notify_one();
					return JW;
				};

				/** Returns the count of task that are awaiting or not finished yet*/
				unsigned int JobsRemaining();

				/** Force to finish all tasks*/
				void FinishJobs();

				//#define ADDSIMPLEJOB(x, y) AddJob(new Job<>(std::bind(&x, y)))
				private:
				// Variables
				std::mutex m_jobsLock;
				std::mutex m_waitLock;

				std::condition_variable consume;

				std::atomic_bool m_stop{ true };
				std::atomic_uint_least8_t m_numThreads{ 0 };
				std::atomic_uint_least16_t m_numWaitingJobs{ 0 };
				std::atomic_uint_least16_t m_numWorkingJobs{ 0 };

				std::vector<UThread*> m_workers;
				std::queue<UJobWrap*> m_jobs;

				private:
				//Methods

				/** Returns a job that was waiting in the queue. If queue was empty returns nullptr.*/
				UJobWrap* GetJob();

				/** Function that execute jobs until m_stop is true.*/
				void JobWraper(UThread*);
			};
		}
	}
}
#endif
