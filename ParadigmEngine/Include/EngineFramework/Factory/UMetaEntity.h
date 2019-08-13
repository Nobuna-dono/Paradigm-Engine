#ifndef _UMETAENTITY_H_
#define _UMETAENTITY_H_

#include <ParadigmException.h>

#include <unordered_map>
#include <IKeyTable.h>
#include <FString.h>
#include <FLayer.h>

#include <Core/Dispach/FEvent.h>
#include <EngineFramework/MetaGear/UMetaGear.h>
#include <Core/Serialization/UArchive.h>

namespace ParadigmEngine
{
	using namespace Core::DataStructure;
	namespace Physics
	{
		class UMetaTransform;
	}

	namespace EngineFramework
	{
		namespace Factory
		{
			/** Data part of UMetaEntity. Held the gears data. */
			struct UMetaEntity
			{
				static FLayerSupervisor EntityLayers;

				public:
					////////////////////////////////////////////////
					// FUNCTIONALITY - ARCHIVAGE
					//________________________________________
					UArchive GetArchived();

					UMetaGear* GetGearFromID(GearID _gearId, uint index = 0);

					template<typename T>
					bool SetGearValueFromName(GearID _metaGearCode, uint _indexGear, FString _valueName, T _value);

					template<typename T>
					bool ReplaceValueInGear(UArchive& out_gearArchive, const FString& _name, T _value);

				public:
					////////////////////////////////////////////////
					// ELEMENT ACCESS
					//________________________________________
					Physics::UMetaTransform* GetTransform();

					template<typename T>
					T* GetGear();

					template<typename T>
					TArray<T*> GetGears();

					template<typename T>
					UKeyRegister GetGearRegister(T* _ptr = nullptr);

					template<typename T>
					UKeyHandler<T> GetGearHandle(T* _ptr = nullptr);

					UMetaEntity* GetChild(FString _name);
					UMetaEntity* GetChild(uint _index);

					template<typename GearT>
					UMetaEntity* GetChild();
					TArray<UMetaEntity*>& GetChildrens();
					UMetaEntity* GetParent();
				
				public:
					////////////////////////////////////////////////
					// DATA
					//_____________________
					FString Name {"Entity"};
					/** The layer where the entity is in. */
					Layer Tag;

					UMetaEntity* m_Parent{ nullptr };
					TArray<UMetaEntity*> m_Children;

					std::unordered_map<GearID, TArray<UKeyHandler<UMetaGear>>> Gears;

			};

			std::ostream& operator<<(std::ostream& _os, const UMetaEntity& _entity);
		}
	}
}
#include "UMetaEntity.inl"

typedef ParadigmEngine::EngineFramework::Factory::UMetaEntity UMetaEntity;

#define RENDER_LAYERS ENTITY_LAYERS
#define ENTITY_LAYERS UMetaEntity::EntityLayers

#endif // !_METAENTITY_H_