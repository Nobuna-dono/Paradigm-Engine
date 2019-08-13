#ifndef _FENUMERATOR_H_
#define _FENUMERATOR_H_

#include <array>
#include <string>
#include <sstream>
#include <stdexcept>

#include <TArray.h>

#define _SERIALIZABLE_ENUM(Name,...)\
	\
	enum Name { __VA_ARGS__ }; \
	\
	struct __##Name##Enumerator\
	{\
		static constexpr int EnumCount()\
		{\
			\
				enum Name { __VA_ARGS__ }; \
				Name enumArray[]{ __VA_ARGS__ }; \
				return sizeof(enumArray) / sizeof(enumArray[0]); \
		}\
		\
		static std::string StringValues() { return #__VA_ARGS__; } \
	}; \

/** Serializable enum. Only available for "vanilla"s enum (You can't attributes any value). */
#define SERIALIZABLE_ENUM(Name,...) _SERIALIZABLE_ENUM(Name, __VA_ARGS__)

/** Serializable enum. Only available for "vanilla"s enum (You can't attributes any value). */
#define PARADIGM_ENUM(Name,...) SERIALIZABLE_ENUM(Name, __VA_ARGS__)

/** Return the EnumeratorType of the Enum. */
#define ENUMERATOR_TYPE(EnumName) __##EnumName##Enumerator

#define FENUMERATOR(EnumName) FEnumerator<EnumName,ENUMERATOR_TYPE(EnumName)>

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Utility
		{
			template<typename E>
			using IsEnum = typename std::enable_if<std::is_enum<E>::value>::type;

			/** Experiemental helper to serialize enums. You can use it as FEnumerator<EFoo, ENUMERATOR_TYPE<FieldA::FieldB::EFoo>>::ToString(EFoo::Value_A); */
			template<typename EnumType, typename EnumeratorType, IsEnum<EnumType>* = nullptr>
			class FEnumerator
			{
				public:
					FEnumerator() = delete; /* prevents instantiation */

				public:
					constexpr static int Count()
					{
						return EnumeratorType::EnumCount();
					}

					/* List all enum values to string */
					static TArray<FString> ValuesToString()
					{
						TArray<FString> strVals;
						static std::array<std::string, Count()> values;
						if (values[0].empty())
						{
							uint i = 0;
							std::string valuesStr = EnumeratorType::StringValues();
							std::stringstream ss(valuesStr);
							for (auto& value : values) // iterator
							{
								std::getline(ss, value, ',');
								strVals.Add(values[i]);
								++i;
							}
						}						
						return strVals;
					};

					/* List all enum values. */
					static auto const& Values()
					{
						static TArray<EnumType> values{ MakeIndexArray(index_sequence_for<Count()>()) };
						return values;
					};

					/* Convert enum value to string. */
					constexpr static FString ToString(EnumType arg)
					{
						FString str{ ValuesToString()[static_cast<unsigned>(arg)] };
						str.Remove(" ");
						return str;
					}

					/* Convert string to enum value. */
					static EnumType FromString(std::string const& val)
					{
						/* Attempt at converting from string value */
						auto const& strValues = ValuesToString();

						for (unsigned int i = 0; i < strValues.Count(); i++)
						{
							if (val == strValues[i])
							{
								return static_cast<EnumType>(i);
							}
						}
						throw std::runtime_error("No matching enum value found for token: " + val);
					}

				private:
					template<std::size_t...Idx>
					static auto MakeIndexArray(std::index_sequence<Idx...>)
					{
						return TArray<EnumType>{ { static_cast<EnumType>(Idx)... } };;
					}
			};

		}
	}
}

template<typename EnumType, typename EnumeratorType>
using FEnumerator = ParadigmEngine::Core::Utility::FEnumerator<EnumType, EnumeratorType>;

#endif