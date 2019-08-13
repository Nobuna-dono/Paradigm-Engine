#ifndef _FARCHIVE_H_
#define _FARCHIVE_H_

#include <TArray.h>
#include <ParadigmMath.h>

#include <Core/Serialization/UArchive.h>

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Serialization
		{
			class FArchive
			{
				public:
					////////////////////////////////////////////////
					// CONSTRUCTOR
					//_____________________
					FArchive() = delete;

				public:
					////////////////////////////////////////////////
					// FUNCTIONALITY - SERIALIZATION
					//_____________________
					/** Serialize the data ._. .*/
					template<typename T>
					static void Serialize(UArchive& out_archive, const T& _data);
					
					/** Serialization of TArray. */
					template<typename T>
					static void Serialize(UArchive& out_archive, const TArray<T>& _archivable);

					/** Serialization of TArray of pointer value. */
					template<typename T>
					static void Serialize(UArchive& out_archive, const TArray<T*>& _archivable);					

					/** Serialization for strings. */					
					static void Serialize(UArchive& out_archive, const FString& _str);


					////////////////////////////////////////////////
					// FUNCTIONALITY - DESERIALIZATION
					//_____________________
					/** Deserialization for any simple type */
					template<typename T>
					static bool Deserialize(UArchive& _archive, T& out_data);

					template<>
					static bool Deserialize<char>(UArchive& _archive, char& out_data);
					
					/** Deserialization for array type */
					template<typename T>
					static bool Deserialize(UArchive& _archive, TArray<T>& out_data);
					
					/** Serialization of TArray of pointer value. */
					template<typename T>
					static bool Deserialize(UArchive& _archive, TArray<T*>& out_data);

					/** Deserialization for strings. */
					static bool Deserialize(UArchive& _archive, FString& out_str);
				

				public:
					////////////////////////////////////////////////
					// FUNCTIONALITY - HELPERS
					//_____________________
					/** Reads data without making the index progressing */
					template<typename T>
					static void ReadOnly(const UArchive& _archive, T& out_data);

					/** Move forward the index according to the type weight. */
					template<typename T>
					static void Skip(UArchive& out_archive);

					/** Skip data code (= Skip<size_t>(...)). */					
					static void SkipCode(UArchive& out_archive);

					/** Move forward the index of the _bytes unit. */
					static void SkipBytes(UArchive& out_archive, uint _bytes);

					/** Consider the next data as a string and skip it.*/
					static void SkipString(UArchive& out_archive);

					/** Browse the archive and stop the index at the given name. Always reset the index and return false if not found.*/
					static bool FindNameValueFromGear(UArchive& out_archive, const FString& _name);
					
					template<typename T>
					static bool ReplaceValueInGear(UArchive& out_gearArchive, const FString& _name, T _value);

			};
		}
	}
}
#include "FArchive.inl"
typedef ParadigmEngine::Core::Serialization::FArchive FArchive;

#endif


/** Serialization for unordered map type */
//template<typename T, typename U>
//static void Serialize(UArchive& out_archive, std::unordered_map<T, U>& _umap);

/** Deserialization for unordered map type */
//template<typename T, typename U>
//static bool Deserialize(UArchive& out_archive, std::unordered_map<T, U>& out_umap);

