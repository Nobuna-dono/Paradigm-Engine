#include <Core/Serialization/FArchive.h>

#include <FParadigmEngine.h>

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Serialization
		{
			UArchive::UArchive()
			{
				Clear();
			}

			UArchive::UArchive(const UArchive& _other)
			{
				Data = _other.Data;
				m_Index = _other.m_Index;
			}

			UArchive::UArchive(UArchive&& _other)
			{
				Data = std::move(_other.Data);
				m_Index = std::move(_other.m_Index);
			}

			void UArchive::Clear()
			{
				m_Index = 1;
				Data.Clear();
				/** Secure the target machine import-export. */
#ifdef  _x86
				Data += 86;
#elif _x64
				Data += 64;
#endif //  _x86 || _x64			
			}

			UArchive UArchive::operator=(const UArchive& _other)
			{
				Data = _other.Data;
				m_Index = _other.m_Index;
				return *this;
			}

			void UArchive::ResetIndex()
			{
				Index = 0;
			}

			bool UArchive::IsValid()
			{
				if (Data.Count())
				{
#ifdef _x86
					if (Data[0u] == 86)
						return true;
#elif _x64
					if (Data[0u] == 64)
						return true;
#endif 
				}
				return false;
			}


			void FArchive::Serialize(UArchive& out_archive, const FString& _str)
			{
				/** Easy to optimize. */
				Serialize<uint>(out_archive, _str.Count());
				if (!_str.Count())
					return;
				for (FString::Const_Iterator it = _str.Const_Begin(); it != _str.Const_End(); ++it)
					Serialize<char>(out_archive, *it);
			}

			bool FArchive::Deserialize(UArchive& _archive, FString& out_str)
			{
				uint buff = 0;
				if (!Deserialize(_archive, buff))
					return false;
				out_str.Clear();
				out_str.Reserve(buff);
				char c;
				for (uint i = 0; i < buff; i++)
				{
					if (!Deserialize<char>(_archive, c))
						return false;
					out_str.PushBack(c);
				}
				return true;
			}

			void FArchive::SkipBytes(UArchive& out_archive, uint _bytes)
			{
				out_archive.Index = out_archive.Index + _bytes;
			}

			void FArchive::SkipCode(UArchive& out_archive)
			{
				Skip<size_t>(out_archive);
			}

			void FArchive::SkipString(UArchive& out_archive)
			{
				uint size;
				Deserialize<uint>(out_archive, size);
				SkipBytes(out_archive, size);
			}


			bool FArchive::FindNameValueFromGear(UArchive& out_archive, const FString& _name)
			{
				size_t gearId;
				FString gearName;
				uint countValues;

				FArchive::Deserialize<size_t>(out_archive, gearId); //Skip #type
				FArchive::Deserialize<FString>(out_archive, gearName);
				FArchive::Deserialize<uint>(out_archive, countValues);

				// VALUES CONSTRUCTION
				for (uint i = 0; i < countValues; ++i)
				{
					bool bMustBeDearchived;
					size_t typeCode;
					size_t typeField;
					FString valueName;

					FArchive::Deserialize<bool>(out_archive, bMustBeDearchived); // Store this value to know if the value can be set from name!
					FArchive::Deserialize<size_t>(out_archive, typeField); // ONLY FOR ENGINE ARCHIVE else uint field
					FArchive::Deserialize<FString>(out_archive, valueName);
					FArchive::Deserialize<size_t>(out_archive, typeCode); // In case of Iarchivable value (none fundamental type)
					if (valueName == _name)
						return true;

					if (typeCode == _BOOL_HASH_CODE)
						FArchive::Skip<bool>(out_archive);
					else if (typeCode == _string_hash_code)
						FArchive::SkipString(out_archive);
					else if (typeCode == typeid(short).hash_code())
						FArchive::Skip<short>(out_archive);
					else if (typeCode == typeid(uint).hash_code() || typeCode == typeid(int).hash_code() 
						|| typeCode == typeid(float).hash_code() || PARADIGM_ARCHIVE.IsEnum(typeCode))
						FArchive::Skip<uint>(out_archive);
					else if (typeCode == typeid(long).hash_code() || typeCode == typeid(double).hash_code())
						FArchive::Skip<double>(out_archive);
					else if (typeCode == typeid(UVector3).hash_code())
						FArchive::Skip<UVector3>(out_archive);
					else if (typeCode == typeid(UQuaternion).hash_code())
						FArchive::Skip<UQuaternion>(out_archive);
				}

				return false;
			}

		}
	}
}