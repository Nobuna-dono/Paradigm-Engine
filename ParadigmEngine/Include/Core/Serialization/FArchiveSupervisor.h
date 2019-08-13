#ifndef _FARCHIVESUPERVISOR_H_
#define _FARCHIVESUPERVISOR_H_

#include <Serialization/FTransfer.h>

typedef size_t ClassID;

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Serialization
		{
			class FArchiveSupervisor
			{
				public:
					struct UArchivableData
					{
						UArchivableData(FString _name = "", IArchivable* _replica = nullptr) 
							: Name{ _name }, Replica{ _replica }
						{}
						FString Name;
						IArchivable* Replica;
					};

				public:
					////////////////////////////////////////////////
					// FUNCTIONALITY - REPLICA
					//_____________________
					/** Add a clone of the class to the supervisor. Needed to allow the replication.
					You can use @SERIALIZABLE_INSTANCE() to automaticly added your serializable class to the supervisor. */
					void AddClassReplica(IArchivable* _newClass);
					void AddGearReplica(IArchivable* _newGear, FString _name);
					void AddAssetReplica(IArchivable* _newAsset, FString _name);

					/** Return all archived gears.*/
					TArray<const UArchivableData*> GetAvailableGears();
					/** Return all archived assets.*/
					TArray<const UArchivableData*> GetAvailableAssets();

					/** Recreate the original archivable class from it's ID. */
					IArchivable* ReplicateFromID(ClassID _info);


					////////////////////////////////////////////////
					// FUNCTIONALITY - REPLICA
					//_____________________
					template<typename T>
					void AddEnum(TArray<FString> _values);

					bool IsEnum(ClassID _htype);

					TArray<FString> GetEnumValues(ClassID _htype);


					template<typename T>
					static ClassID GetClassID(const T& value);
					template<typename T>
					static ClassID GetClassID(const TArray<T>& value);
					template<typename T>
					static ClassID GetClassID(const TArray<T*>& value);


				public:
					////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					// NOTE:
					// For the moment all Archivage methods are same of FArchive, but later, they will become member 
					// and will call FArchive static method with the multithreading feature!
					//_____________________________________________________________________________________________________________________

					////////////////////////////////////////////////
					// FUNCTIONALITY - ARCHIVAGE
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


				public:
					////////////////////////////////////////////////
					// FUNCTIONALITY - DEARCHIVAGE
					//_____________________
					/** Deserialization for any simple type */
					template<typename T>
					static bool Deserialize(UArchive& _archive, T& out_data);

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

				

				private:
					////////////////////////////////////////////////
					// DATA
					//_____________________
					std::unordered_map<ClassID, IArchivable*> m_Replicas;
					std::unordered_map<ClassID, UArchivableData> m_GearReplicas;
					std::unordered_map<ClassID, UArchivableData> m_AssetReplicas;
					std::unordered_map<ClassID, TArray<FString>> m_Enums;
			};
		}
	}
}
typedef ParadigmEngine::Core::Serialization::FArchiveSupervisor FArchiveSupervisor;
typedef ParadigmEngine::Core::Serialization::FArchiveSupervisor::UArchivableData UArchivableData;
#include <Core/Serialization/FArchiveSupervisor.inl>
#endif