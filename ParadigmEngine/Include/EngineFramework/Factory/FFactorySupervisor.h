#ifndef _FFACTORYSUPERVISOR_H_
#define _FFACTORYSUPERVISOR_H_
#include <unordered_map>
#include <TArray.h>
#include <TKeyTable.h>
#include <TStaticKeyTable.h>
#include <Core/Dispach/FMultiCast.h>
#include <FParadigmEngine.h>


namespace ParadigmEngine
{
	namespace GameFramework
	{
		namespace GameEntity
		{
			class GEntity;
		}
	}

	namespace EngineFramework
	{
		namespace Factory
		{
			/** UFactory is the entity which manage all of the game entities and gears. */
			class FFactorySupervisor
			{
				public:
					////////////////////////////////////////////////
					// CONSTRUCTOR - DESTRUCTOR
					//____________________________________			
					FFactorySupervisor() { m_MetaData.Reserve(PARADIGM_LIMITATION_MAX_ENTITY); };
					~FFactorySupervisor() = default; // Do not forget to call Clear()
					public:
					// Pipeline Method
					void Initialize();
					void Terminate();

				public:
					////////////////////////////////////////////////
					// FUNCTIONALITY
					//____________________________________	
					/** Create a metaEntity and return an handler. */
					UKeyHandler<UMetaEntity>  CreateMetaEntity();

					/** Create gear and return KeyRegister. Copy the data, if pass as argument but _original IS NOT REFERENCING the created gear !!!*/
					template<typename T>
					UKeyHandler<T> CreateGear(UMetaEntity* _entityToGear);

					template<typename T>
					void CreateGearFromArchive(UMetaEntity* _entityToGear, T* _original);

					/** Reflection phase on waiting archive gears of type T.  */
					template<typename T>
					void ReflectGearsOfType();

					/** Add reflector's metagears callback. */
					template<typename T>
					void AddMetaGearReflector(UDynamicJob* _callback);

					/** Reflection phase on all available types of meta gear. */
					inline void MetaGearsReflection();

					/** Destroy the specified gear. */
					template<typename T>
					bool DestroyGear(UMetaEntity* _gearedEntity, T* _original);

					/** Destroy the gear that match with the key. */
					template<typename T>
					bool DestroyGear(UMetaEntity* _entityToGear, UKeyRegister _original);

					/** Destroy the MetaEntity that match with the key. */
					bool DestroyEntity(UKeyRegister _original);

					/** Add some description. */
					//bool DestroyEntity(UMetaEntity* _original);

					/** Destroy everything*/
					void Clear();

				public:
					////////////////////////////////////////////////
					// ELEMENTS ACCESS
					//____________________________________	
					/** Returns a pointer to the MetaEntity that match with the key. */
					UMetaEntity* GetMetaEntity(UKeyRegister _register);

					/** Returns a pointer to the Entity that match with the key. */
					ParadigmEngine::GameFramework::GameEntity::GEntity GetEntity(UKeyRegister _register);

					/** Give a reference to the gear that match with the key in out_value and returns true . */
					template<typename T>
					bool GetGear(UKeyRegister _register, T& out_value);

					/** Returns a pointer to the gear that match with the key. */
					template<typename T>
					T* GetGear(UKeyRegister _register);

					/** Returns a pointer to the Table of one type of gear. */
					template<typename T>
					TStaticKeyTable<T>* GetGearTable();

					/** Return an array of all metaEntity geared of T gear type. Multiple type verification is too heavy with classic data structure.
					* So please, prefer check gears when get one of different type from this entities. */
					template<typename T>
					TArray<UMetaEntity*>* GetGearedEntities();

				private:
					////////////////////////////////////////////////
					// DATA
					//____________________________________				
					/** this is where all the MetaEntity are stored*/
					TStaticKeyTable<UMetaEntity> m_MetaData;
					/** This is where all the gears are stored by type (using the GearID for key)*/
					std::unordered_map<GearID, IKeyTable*> m_Gears;
					/** This is a map that store all entities that are geared by a type of gear*/
					std::unordered_map<GearID, TArray<UMetaEntity*>*> m_GearedEntities;

					
					/** Multicast to callback reflector's metagears. */
					FMultiCast m_ReflectorCallback;
					/** Store the partially reflected gears. */
					std::unordered_map<GearID, std::vector<std::pair<IArchivable*, UMetaEntity*>>> m_PartialReflectedGears;
			};
		}
	}
}

typedef ParadigmEngine::EngineFramework::Factory::FFactorySupervisor FFactorySupervisor;

#include "FFactorySupervisor.inl"

#endif // !_FFACTORYSUPERVISOR_H_
