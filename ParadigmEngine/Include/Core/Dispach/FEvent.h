#pragma once
#include <TArray.h>

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Dispatch
		{

			template <class... Params>
			class FEvent
			{
#pragma region ToolClasses
				class DynamicFuncWrapper
				{
					public:
					virtual void operator()(Params... _params) const = 0;
				};

				template<typename Owner>
				class MemberFuncWrapper : public DynamicFuncWrapper
				{
					public:
					MemberFuncWrapper(Owner*, void(Owner::*)(Params...));
					void operator()(Params... _params) const override;
					bool operator==(Owner*) const;
					bool operator==(void(Owner::*)(Params...)) const;
					private:
					Owner* m_owner;
					void(Owner::*m_func)(Params...);
				};

				class GlobalFuncWrapper : public DynamicFuncWrapper
				{
					public:
					GlobalFuncWrapper(void(*)(Params...));
					void operator()(Params... _params) const override;
					bool operator==(void(*)(Params...)) const;
					private:
					void(*m_func)(Params...);
				};
#pragma endregion

				public:
				FEvent() = default;
				~FEvent() = default;

				/** Subscribe a new listener with the specified global fonction.*/
				void Subscribe(void(*_func)(Params...));

				template <typename Owner>
				/** Subscribe a new listener with the specified class and member fonction.*/
				void Subscribe(void(Owner::*_func)(Params...), Owner* _owner);

				/** Unsubscribe all the listeners coresponding to the specified parameters.*/
				void Unsubscribe(void(*_func)(Params...));

				template <typename Owner>
				/** Unsubscribe all the listeners coresponding to the specified parameters.
					If _owner is nullptr unsibscirbe all the listeners with corresponding function pointer*/
				void Unsubscribe(void(Owner::*_func)(Params...), Owner* _owner = nullptr);

				/** Unsubscribe all the listeners.*/
				void Clear();

				inline uint ListenerCount() const;

				/** Invoke all the listeners with the specified Parameters.*/
				void Invoke(Params... _params) ;//const;

				/** Invoke all the listeners with the specified Parameters.*/
				inline void operator()(Params... _params) ;//const;

				private:
				TArray<GlobalFuncWrapper> globalListeners;
				TArray<DynamicFuncWrapper*> MemberListeners;
			};

		}
	}
}

template <class... Params>
using FEvent = ParadigmEngine::Core::Dispatch::FEvent<Params...>;

#include "FEvent.inl"