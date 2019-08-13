
namespace ParadigmEngine
{
	namespace Core
	{
		namespace Dispatch
		{

#pragma region ToolClasses
			template <class... Params>
			template<typename Owner>
			FEvent<Params...>::MemberFuncWrapper<Owner>::MemberFuncWrapper(Owner* _owner, void(Owner::*_func)(Params...)) : m_owner{ _owner }, m_func{ _func }
			{};

			template <class... Params>
			template<typename Owner>
			void FEvent<Params...>::MemberFuncWrapper<Owner>::operator()(Params... _params) const
			{
				(m_owner->*m_func)(_params...);
			};

			template <class... Params>
			template<typename Owner>
			bool FEvent<Params...>::MemberFuncWrapper<Owner>::operator==(Owner* _owner) const
			{
				return _owner == m_owner;
			};

			template <class... Params>
			template<typename Owner>
			bool FEvent<Params...>::MemberFuncWrapper<Owner>::operator==(void(Owner::*_func)(Params...)) const
			{
				return _func == m_func;
			};

			template <class... Params>
			FEvent<Params...>::GlobalFuncWrapper::GlobalFuncWrapper(void(*_func)(Params...)) : m_func{ _func }
			{
			};

			template <class... Params>
			void FEvent<Params...>::GlobalFuncWrapper::operator()(Params... _params) const
			{
				m_func(_params...);
			};

			template <class... Params>
			bool FEvent<Params...>::GlobalFuncWrapper::operator==(void(*_func)(Params...)) const
			{
				return _func == m_func;
			};
#pragma endregion

			template <class... Params>
			void FEvent<Params...>::Subscribe(void(*_func)(Params...))
			{
				globalListeners.Add(GlobalFuncWrapper(_func));
			};

			template <class... Params>
			template <typename Owner>
			void FEvent<Params...>::Subscribe(void(Owner::*_func)(Params...), Owner* _owner)
			{
				MemberListeners.Add(new MemberFuncWrapper<Owner>(_owner, _func));
			};

			template <class... Params>
			void FEvent<Params...>::Unsubscribe(void(*_func)(Params...))
			{
				for (int i = 0; i < globalListeners.Count(); ++i)
					if (globalListeners[i] == _func)
					{
						globalListeners.Remove(globalListeners[i]);
						--i;
					}
			};

			template <class... Params>
			template <typename Owner>
			void FEvent<Params...>::Unsubscribe(void(Owner::*_func)(Params...), Owner* _owner)
			{
				MemberFuncWrapper<Owner>* ptr;
				for (uint i = 0; i < MemberListeners.Count(); ++i)
				{
					ptr = static_cast<MemberFuncWrapper<Owner>*>(MemberListeners[i]);
					if (ptr && *ptr == _func && (!_owner || *ptr == _owner))
					{
						delete MemberListeners[i];
						MemberListeners.Remove(MemberListeners[i]);
						--i;
					}
				}
			}

			template <class... Params>
			void FEvent<Params...>::Clear()
			{
				globalListeners.clear();
				for (auto iterator = MemberListeners.Begin(); iterator != MemberListeners.End(); ++iterator)
				{
					delete *iterator;
				}
				MemberListeners.clear();
			};

			template <class... Params>
			uint FEvent<Params...>::ListenerCount() const
			{
				return globalListeners.Count() + MemberListeners.Count();
			}

			template <class... Params>
			void FEvent<Params...>::Invoke(Params... _params) //const
			{
				for (TArray<GlobalFuncWrapper>::Iterator iterator = globalListeners.Begin(); iterator != globalListeners.End(); ++iterator)
				{
					(*iterator)(_params...);
				}
				for (auto iterator = MemberListeners.Begin(); iterator != MemberListeners.End(); ++iterator)
				{
					(**iterator)(_params...);
				}
			};

			template <class... Params>
			void FEvent<Params...>::operator()(Params... _params) //const
			{
				Invoke(_params...);
			};
		};
	};
};