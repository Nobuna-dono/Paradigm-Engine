#ifndef _UGEAR_H_
#define _UGEAR_H_

#include <TArray.h>
#include <ParadigmTypedef.h>
#include <type_traits>
#include <Core/Serialization/UArchive.h>

#define GEAR_ID(gear)  typeid(gear).hash_code()
typedef size_t GearID;


namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace Factory
		{
			struct UMetaEntity;
		}

		namespace MetaGear
		{			
			struct UMetaGear : public virtual IArchivable
			{
				protected:
					TArray<IArchivable::UMetaData> __metaData; 

				public:
					template<typename T>
					bool SetValueFromName(const FString& _name, const T& _value)
					{
						auto it = __metaData.Find({ _name });
						if (it != __metaData.End())
						{
							*static_cast<T*>((*it).Data) = _value;
							return true;
						}
						return false;
					}
				
				public:
					Factory::UMetaEntity* GearedUnit{ nullptr };

					union
					{
						struct 
						{
							bits32 bActive : 1;
							bits32 bIsEnabled : 1;
							bits32 bIsInitialized : 1;
							//bits32 : 30;
						};
						bits32 _bitsValue{ 0x3 };
				};				
			};
		}
	}
}
typedef ParadigmEngine::EngineFramework::MetaGear::UMetaGear UMetaGear;


template <class T>
using IfDeriveGear = std::enable_if_t<std::is_base_of<UMetaGear, T>::value>;

#endif // !_GEAR_H_

