#ifndef _UTHREAD_H_
#define _UTHREAD_H_

#include <atomic>
#include <thread>

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Multiprograming
		{
			/** Struct that wrap a thread and also contain his id*/
			struct UThread
			{
				template<class _Fn, class... _Args>
				UThread(int _id, _Fn&& _func, _Args&&... _args) : threadId(_id), working(false), thread{ std::thread(_func, _args...) } {}
				UThread(int _id) : threadId(_id), working(false) {}

				const int threadId;
				std::atomic_bool working;
				std::thread thread;
			};
		}
	}
}

#endif