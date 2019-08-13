#ifndef _FMETAENTITY_H_
#define _FMETAENTITY_H_

#include <EngineFramework/Factory/UMetaEntity.h>
#include <FParadigmEngine.h>
#include <EngineFramework/Factory/FFactorySupervisor.h>

namespace ParadigmEngine
{
	using namespace Core::DataStructure;
	using namespace Physics::Collision;

	namespace EngineFramework
	{
		namespace Factory
		{
			/** Logic part of UMetaEntity. Manage methods to manage it.*/
			class FMetaEntity
			{
				FMetaEntity() = default;
				public:
				// Constructor - Destructor
				~FMetaEntity() = default;

				public:
				// Methods
				static void CreateMetaEntity(UKeyHandler<UMetaEntity>& out_metaEntity);
				//		static void DestroyMetaEntity(UKeyHandler<UMetaEntity>& out_metaEntity);

				/** Attach a gear <T> to the UMetaEntity.*/
				template<typename T>
				static UKeyHandler<T> AddGear(UMetaEntity* _metaEntity, T* _original = nullptr);

				/** Attach a gear <T> to the UMetaEntity.*/
				template<typename T>
				static void AddGearFromArchive(UMetaEntity* _metaEntity, T* _original );

				template<typename T>
				static T* GetGear(UMetaEntity* _metaEntity);

				template<typename T>
				static TArray<T*> GetGears(UMetaEntity* _metaEntity);

				static bool AddChild(UMetaEntity* _metaEntity, UMetaEntity*);

				/** Change the parent entity if nullptr set to Root*/
				static void SetParent(UMetaEntity* _metaEntity, UMetaEntity* _value);

				/** Called when Position changed to update children*/
				static void OnPositionChanged(UMetaEntity* _metaEntity);

				/** Called when Rotation changed to update children*/
				static void OnRotationChanged(UMetaEntity* _metaEntity);

				/** Called when Scale changed to update children*/
				static void OnScaleChanged(UMetaEntity* _metaEntity);

				/** Destroy a gear <T> of the UMetaEntity.*/
				template<typename T>
				static bool DestroyGear(UMetaEntity* _metaEntity, const T& _original);

				/** Destroy evry gears <T> of the UMetaEntity.*/
				template<typename T>
				static bool DestroyGears(UMetaEntity* _metaEntity);

				/** Destroy evry gears of the UMetaEntity.*/
				static void DestroyGears(UMetaEntity* _metaEntity);
			};
		}
	}
}
typedef ParadigmEngine::EngineFramework::Factory::FMetaEntity FMetaEntity;
#include "FMetaEntity.inl"

#endif