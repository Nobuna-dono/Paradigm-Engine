#ifndef _TYPEINFO_H_
#define _TYPEINFO_H_

namespace Core
{
	namespace Logic
	{
		class UTypeInfo
		{
			public:
				template<typename T, typename S>
				static bool CompareType()
				{
					T* typeT = new T();
					S* TypeS = typeT;
					const type_info &type1 = typeid(*typeT);	// type1 consider *T type
					const type_info &type2 = typeid(*TypeS);	// type2 consider *S type
					delete typeT;
					return (type1 == type2);
				}

				template<typename T, typename S>
				static bool CompareType(T* _t, S* _s)
				{
					const type_info &type1 = typeid(*_t);	// type1 consider *T type
					const type_info &type2 = typeid(*_s);	// type2 consider *S type
					return (type1 == type2);
				}

				template<typename T, typename S>
				static bool CompareType(S* TypeS)
				{
					T* typeT = new T();
					const type_info &type1 = typeid(*typeT);	// type1 consider *T type
					const type_info &type2 = typeid(*TypeS);	// type2 consider *S type
					delete typeT;
					return (type1 == type2);
				}
		};
	}
}

#endif