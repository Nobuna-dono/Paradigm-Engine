#ifndef _FMULTICAST_H_
#define _FMULTICAST_H_

#include <vector>
#include <functional>
#include <iostream>

#include "UJob.h"


class FMultiCast
{
	std::vector<UDynamicJob*> linkedJobs;
	std::vector<UDynamicJob*> trash;
	public:
		void Clear()
		{
			linkedJobs.clear();
		}
	
		bool IsObserved()
		{
			return (linkedJobs.size() > 0);
		}
	
	public:
			//Operators
		void operator+=(UDynamicJob* _job)
		{
			linkedJobs.push_back(_job);
		}

		template<class type>
		void operator+=(std::function<type> _func)
		{
			UJob<>* j = new UJob<>(_func);
			linkedJobs.push_back(j);
		}
	
		void operator-=(UDynamicJob* _job)
		{
			if (linkedJobs.size() > 0)
			{
				std::vector<UDynamicJob*> temp;
				for (UDynamicJob* var : linkedJobs)
				{
					if (var != _job)
						temp.push_back(var);
					else
						trash.push_back(var);
				}
				linkedJobs.erase(linkedJobs.begin(), linkedJobs.end());
				linkedJobs = temp;
			}
		}
	
		void operator()()
		{
			Invoke();
		}
	

	public:
			//Methods
		void Invoke()
		{
			std::vector<UDynamicJob*> templist = linkedJobs;
			for (unsigned int i = 0; i< templist.size(); i++)
			{
				templist.at(i)->work();
			}
	
			for (unsigned int i = 0; i< trash.size(); i++)
			{
				delete trash[i];
			}
			trash.clear();
		}
};

#endif