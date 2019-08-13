#ifndef _UJOB_H_
#define _UJOB_H_

#include <functional>

class UDynamicJob 
{
	public:
		virtual void work() const {};
};

template<class... Params>
class UJob : public UDynamicJob
{		
	public:
			//Constructor
		UJob() = default;
	
			//Destructor
		~UJob() = default;

			//Job(Func& func, Params&... params) : m_task{ func }, m_p{ params... }
		UJob(std::function<void(Params...)> func, Params... params) : m_task{ func }, m_p{params...}
		{}
	
		void work() const override
		{
			m_task(std::get<Params>(m_p)...);
		}

	private:
			//Variables
		std::function<void(Params...)> m_task;
		std::tuple<Params...> m_p;
};

template<class Class,class... Params>
class UMemberJob : public UDynamicJob
{
	public:
			//Constructor
		UMemberJob() = default;
	
			//Job(Func& func, Params&... params) : m_task{ func }, m_p{ params... }
		UMemberJob(void(Class::* func)(Params...), Class& _owner, Params... params) : m_task{ func }, m_p{ params... }, m_owner{&_owner}
		{}
	
			//Destructor
		virtual ~UMemberJob() = default;
	
		void work() const override
		{
			m_task(*m_owner,std::get<Params>(m_p)...);
		}

	private:
			//Variables
		//std::function<void(Params...)> m_task;
		void(Class::* m_task)(Params...);
		std::tuple<Params...> m_p;
		Class* m_owner;
};

#endif