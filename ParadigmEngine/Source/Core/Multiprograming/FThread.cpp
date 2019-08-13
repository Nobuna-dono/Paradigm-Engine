#include "Include/Core/Multiprograming/FThread.h"

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Multiprograming
		{
			FThread::FThread(unsigned int threads) : m_numThreads(threads)
			{
				if (threads == 0u)
					m_numThreads = std::thread::hardware_concurrency() - 1;

				m_numWaitingJobs = m_numWorkingJobs = 0u;
				m_stop = false;

				for (int i = 0; i < m_numThreads; ++i)
				{
					m_workers.push_back(new UThread(i));
					m_workers[i]->thread = std::thread(&FThread::JobWraper, this, m_workers[i]);
				}
			}

			FThread::~FThread()
			{
				m_stop = true;
				consume.notify_all();
				for (int i = 0; i < m_numThreads; ++i)
				{
					if (m_workers[i]->thread.joinable())
					{
						m_workers[i]->thread.join();
						delete m_workers[i];
					}
				}
			}

			unsigned int FThread::JobsRemaining()
			{
				m_jobsLock.lock();
				unsigned int out = (m_numWaitingJobs + m_numWorkingJobs);
				m_jobsLock.unlock();
				return out;
			}

			void FThread::FinishJobs()
			{
				UJobWrap* job = nullptr;
				while (JobsRemaining() != 0)
				{
					job = GetJob();
					if (job == nullptr)
						break;

					m_numWaitingJobs--;
					m_numWorkingJobs++;

					job->m_job->work();

					m_numWorkingJobs--;

					delete job;
					job = nullptr;
				}

				while (JobsRemaining() != 0) {};
			}

			FThread::UJobWrap* FThread::GetJob()
			{
				UJobWrap* j = nullptr;
				m_jobsLock.lock();
				if (!m_jobs.empty())
				{
					j = m_jobs.front();
					m_jobs.pop();
				}
				m_jobsLock.unlock();

				return j;
			}

			void FThread::JobWraper(UThread* _currentThread)
			{
				UJobWrap* jobWrap = nullptr;

				while (!m_stop)
				{
					while (jobWrap == nullptr && !m_stop)
					{
						jobWrap = GetJob();
						if (jobWrap == nullptr && !m_stop)
						{
							_currentThread->working = false;
							std::unique_lock<std::mutex> locker(m_waitLock);
							consume.wait(locker);
						}
					}

					if (m_stop)
						break;

					m_numWaitingJobs--;
					m_numWorkingJobs++;

					_currentThread->working = true;

					jobWrap->m_job->work();

					jobWrap->Joined();
					m_numWorkingJobs--;

					delete jobWrap;
					jobWrap = nullptr;
				}
			}
		}
	}
}