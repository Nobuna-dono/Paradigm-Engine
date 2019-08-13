#include <Core/Serialization/FArchiveSupervisor.h>
#include <EngineFramework/MetaGear/UMetaGear.h>

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Serialization
		{

			////////////////////////////////////////////////
			// FUNCTIONALITY
			//_____________________
			void FArchiveSupervisor::AddClassReplica(IArchivable* _newClass)
			{
				if (m_Replicas.find(typeid(*_newClass).hash_code()) == m_Replicas.end())
					m_Replicas.emplace(typeid(*_newClass).hash_code(), _newClass);
			}

			void FArchiveSupervisor::AddGearReplica(IArchivable* _newClass, FString _name)
			{
				if (m_GearReplicas.find(typeid(*_newClass).hash_code()) == m_GearReplicas.end())
					m_GearReplicas.emplace(typeid(*_newClass).hash_code(), UArchivableData(_name, _newClass));
			}

			void FArchiveSupervisor::AddAssetReplica(IArchivable* _newClass, FString _name)
			{
				if (m_AssetReplicas.find(typeid(*_newClass).hash_code()) == m_AssetReplicas.end())
					m_AssetReplicas.emplace(typeid(*_newClass).hash_code(), UArchivableData(_name, _newClass));
			}

			TArray<const UArchivableData*> FArchiveSupervisor::GetAvailableGears()
			{
				TArray<const UArchivableData*> ret;
				for (auto it = m_GearReplicas.begin(); it != m_GearReplicas.end(); ++it)
					ret.Add(&(*it).second);
				return ret;
			}

			TArray<const UArchivableData*> FArchiveSupervisor::GetAvailableAssets()
			{
				TArray<const UArchivableData*> ret;
				for (auto it = m_AssetReplicas.begin(); it != m_AssetReplicas.end(); ++it)
					ret.Add(&(*it).second);
				return ret;
			}

			IArchivable* FArchiveSupervisor::ReplicateFromID(ClassID _info)
			{
				if (m_GearReplicas.find(_info) != m_GearReplicas.end())
					return m_GearReplicas[_info].Replica->Replicate();
				else if (m_AssetReplicas.find(_info) != m_AssetReplicas.end())
					return m_AssetReplicas[_info].Replica->Replicate();
				else if (m_Replicas.find(_info) != m_Replicas.end())
					return m_Replicas[_info]->Replicate();
				return nullptr;
			}

			////////////////////////////////////////////////
			// FUNCTIONALITY - ENUMS
			//_____________________
			bool FArchiveSupervisor::IsEnum(ClassID _htype)
			{
				if (m_Enums.find(_htype) == m_Enums.end())
					return false;
				return true;
			}

			TArray<FString> FArchiveSupervisor::GetEnumValues(ClassID _htype)
			{
				if (m_Enums.find(_htype) != m_Enums.end())
					return m_Enums[_htype];
				return {};
			}

			////////////////////////////////////////////////
			// FUNCTIONALITY
			//_____________________
			void FArchiveSupervisor::Serialize(UArchive& out_archive, const FString& _str)
			{
				Serialize<uint>(out_archive, _str.Count());
				for (FString::Const_Iterator it = _str.Const_Begin(); it != _str.Const_End(); ++it)
					Serialize<char>(out_archive, *it);
			}

			bool FArchiveSupervisor::Deserialize(UArchive& _archive, FString& out_str)
			{
				int buff = 0;
				if (!Deserialize<int>(_archive, buff))
					return false;
				out_str.Clear();
				out_str.Reserve(buff);
				char c;
				for (int i = 0; i < buff; i++)
				{
					if (!Deserialize<char>(_archive, c))
						return false;
					out_str.PushBack(c);
				}
				return true;
			}

			void FArchiveSupervisor::SkipBytes(UArchive& out_archive, uint _bytes)
			{
				out_archive.Index += _bytes;
			}

			void FArchiveSupervisor::SkipCode(UArchive& out_archive)
			{
				Skip<size_t>(out_archive);
			}

			void FArchiveSupervisor::SkipString(UArchive& out_archive)
			{
				uint size;
				Deserialize<uint>(out_archive, size);
				SkipBytes(out_archive, size);
			}		
		}	
	}
}