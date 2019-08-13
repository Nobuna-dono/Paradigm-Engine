#include <EngineFramework/Factory/UMetaEntity.h>
#include <Physics/FTransform.h>

#include <EngineFramework/Factory/FFactorySupervisor.h>
#include <Serialization/FArchive.h>
#include <FParadigmEngine.h>


namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace Factory
		{
			FLayerSupervisor UMetaEntity::EntityLayers;


			UMetaGear* UMetaEntity::GetGearFromID(GearID _gearID, uint _index)
			{
				if (Gears.find(_gearID) != Gears.end())
				{
					if(_index < Gears[_gearID].Count())
						return (Gears[_gearID])[_index].Pointer;
				}
				return nullptr;
			}

			UArchive UMetaEntity::GetArchived()
			{				
				UArchive archive;
				UArchive archiveBuff;
				uint gearCount{0};

				for (auto it = Gears.begin(); it != Gears.end(); ++it)
				{
					for (auto itMetaGear = (*it).second.Begin(); itMetaGear != (*it).second.End(); ++itMetaGear)
					{
						++gearCount;
						(*itMetaGear).Pointer->Archive(archiveBuff);
					}
				}

				FArchive::Serialize<uint>(archive, gearCount);
				archive.Data += archiveBuff.Data.Substring(1,archiveBuff.Data.Count());
				archive.ResetIndex();
				
				// Convert this engine archive in Editor archive
				return archive;
			}
			
			Physics::UMetaTransform* UMetaEntity::GetTransform()
			{
				return GetGear<Physics::UMetaTransform>();
			}

			UMetaEntity* UMetaEntity::GetChild(FString _name)
			{
				for (uint i = 0; i < m_Children.Count(); ++i)
					if (m_Children[i]->Name == _name)
						return m_Children[i];

				return nullptr;
			}

			UMetaEntity* UMetaEntity::GetChild(uint _index)
			{
				return m_Children[_index];
			}

			TArray<UMetaEntity*>& UMetaEntity::GetChildrens()
			{
				return m_Children;
			}

			UMetaEntity*  UMetaEntity::GetParent()
			{
				return m_Parent;
			}

		}
	}
}