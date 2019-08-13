#include <EngineFramework/NativeProcessor/FProcessorSupervisor.h>

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace Factory
		{

			template<typename T>
			UKeyHandler<T> FFactorySupervisor::CreateGear(UMetaEntity* _entityToGear)
			{
				if (!std::is_base_of<UMetaGear, T>::value)
					THROW_PARADIGM_EXCEPTION_ARGUMENT("The parameter _original type is not a gear.");

				//This add a processor if there is not already one of this type 
				NativeProcessor::FProcessorSupervisor::FNativeAdder<T>::AddProcessor(*PARADIGM_PROCESSOR);
				UKeyHandler<T> handle;
				handle.Pointer = nullptr;
				handle.Register = UKeyRegister();

				if (_entityToGear == nullptr)
					return handle;

				
				if (m_GearedEntities.find(GEAR_ID(T)) == m_GearedEntities.end())
				{
					TArray<UMetaEntity*>* newArray = new TArray<UMetaEntity*>();
					newArray->Add(_entityToGear);
					m_GearedEntities.emplace(std::pair<GearID, TArray<UMetaEntity*>*>(GEAR_ID(T), newArray));
				}
				else
					m_GearedEntities[GEAR_ID(T)]->Add(_entityToGear);


				if (m_Gears.find(GEAR_ID(T)) == m_Gears.end())
				{
					TStaticKeyTable<T>* newTable = new TStaticKeyTable<T>();
					newTable->Reserve(PARADIGM_LIMITATION_MAX_ENTITY);
					m_Gears.emplace(std::pair<GearID, TStaticKeyTable<T>*>(GEAR_ID(T), newTable));
				}

				TStaticKeyTable<T>* Table = static_cast<TStaticKeyTable<T>*>(m_Gears[GEAR_ID(T)]);
				handle.Register = Table->Add(T());


				handle.Pointer = &(Table->Get(handle.Register));
				((UMetaGear*)handle.Pointer)->GearedUnit = _entityToGear;

				return handle;
			}


			template<typename T>
			void FFactorySupervisor::ReflectGearsOfType()
			{
				if (!std::is_base_of<UMetaGear, T>::value)
					THROW_PARADIGM_EXCEPTION_ARGUMENT("The parameter _original type is not a gear.");

				GearID hcode = typeid(T).hash_code();
				if (m_PartialReflectedGears.find(hcode) != m_PartialReflectedGears.end())
				{

					//This add a processor if there is not already one of this type 
					NativeProcessor::FProcessorSupervisor::FNativeAdder<T>::AddProcessor(*PARADIGM_PROCESSOR);

					for (auto it = m_PartialReflectedGears[hcode].begin(); it != m_PartialReflectedGears[hcode].end(); ++it)
					{
						if (m_GearedEntities.find(GEAR_ID(T)) == m_GearedEntities.end())
						{
							TArray<UMetaEntity*>* newArray = new TArray<UMetaEntity*>();
							newArray->Add((*it).second);
							m_GearedEntities.emplace(std::pair<GearID, TArray<UMetaEntity*>*>(GEAR_ID(T), newArray));
						}
						else
							m_GearedEntities[GEAR_ID(T)]->Add((*it).second);
						
						if (m_Gears.find(GEAR_ID(T)) == m_Gears.end())
						{
							TStaticKeyTable<T>* newTable = new TStaticKeyTable<T>();
							newTable->Reserve(PARADIGM_LIMITATION_MAX_ENTITY);
							m_Gears.emplace(std::pair<GearID, TStaticKeyTable<T>*>(GEAR_ID(T), newTable));
						}

						TStaticKeyTable<T>* table = static_cast<TStaticKeyTable<T>*>(m_Gears[GEAR_ID(T)]);
						
						if ((*it).second->Gears.find(hcode) == (*it).second->Gears.end())
							(*it).second->Gears.emplace(std::pair<GearID, TArray<UKeyHandler<UMetaGear>>>(GEAR_ID(T), {}));
						
						UKeyHandler<UMetaGear> handle;
						handle.Register = table->Add(*(dynamic_cast<T*>((*it).first)));
						handle.Pointer = &(table->Get(handle.Register));
						
						(*it).second->Gears[hcode].Add(handle);
						((UMetaGear*)handle.Pointer)->GearedUnit = (*it).second;
					}

					m_PartialReflectedGears[hcode].clear();
				}
			}

			template<typename T>
			void FFactorySupervisor::AddMetaGearReflector(UDynamicJob* _callback)
			{
				if (m_PartialReflectedGears.find(typeid(T).hash_code()) == m_PartialReflectedGears.end())
				{
					FParadigmEngine::GetInstance().Factory->m_ReflectorCallback += _callback;
					m_PartialReflectedGears.emplace(std::pair<GearID, std::vector<std::pair<IArchivable*, UMetaEntity*>>>(typeid(T).hash_code(), {}));
				}
			}
			
			void FFactorySupervisor::MetaGearsReflection()
			{
				m_ReflectorCallback();
			}

			template<typename T>
			void FFactorySupervisor::CreateGearFromArchive(UMetaEntity* _entityToGear, T* _original)
			{				
				//This add a processor if there is not already one of this type 
				GearID hcode = typeid(*_original).hash_code();

				if (m_PartialReflectedGears.find(hcode) == m_PartialReflectedGears.end())
					m_PartialReflectedGears.emplace(std::pair<GearID, std::vector<std::pair<IArchivable*, UMetaEntity*>>>(hcode, {}));

				m_PartialReflectedGears[hcode].push_back(std::pair<IArchivable*, UMetaEntity*>(_original, _entityToGear));
			}

			template<typename T>
			bool FFactorySupervisor::DestroyGear(UMetaEntity* _gearedEntity, T* _original)
			{
				if (m_Gears.find(GEAR_ID(T)) != m_Gears.cend())
				{
					//delete m_Gears[GEAR_ID(T)][_gearedEntity->GetGearRegister(_original)];
					return m_Gears[GEAR_ID(T)]->Remove(_gearedEntity->GetGearRegister(_original));
				}
				return false;
			}

			template<typename T>
			bool FFactorySupervisor::DestroyGear(UMetaEntity* _gearedEntity, UKeyRegister _original)
			{
				//delete m_Gears[GEAR_ID(T)][_original];
				return m_Gears[GEAR_ID(T)]->Remove(_original);
			}

			template<typename T>
			bool FFactorySupervisor::GetGear(UKeyRegister _register, T& out_value)
			{
				if (m_Gears.find(GEAR_ID(T)) != m_Gears.cend())
				{
					TStaticKeyTable<T>* Table = static_cast<TStaticKeyTable<T>*>(m_Gears[T::GearID]);

					if (!Table)
						THROW_PARADIGM_EXCEPTION("");
					return Table->Get(_register, out_value);
				}
				return false;
			}

			template<typename T>
			T* FFactorySupervisor::GetGear(UKeyRegister _register)
			{
				if (m_Gears.find(GEAR_ID(T)) != m_Gears.cend() && m_Gears[GEAR_ID(T)]->Find(_register))
				{
					TStaticKeyTable<T>* Table = static_cast<TStaticKeyTable<T>*>(m_Gears[GEAR_ID(T)]);

					if (!Table)
						THROW_PARADIGM_EXCEPTION("");
					return Table->Get(_register);
				}
				return nullptr;
			}

			template<typename T>
			TStaticKeyTable<T>* FFactorySupervisor::GetGearTable()
			{
				if (m_Gears.find(GEAR_ID(T)) != m_Gears.cend())
				{
					TStaticKeyTable<T>* Table = static_cast<TStaticKeyTable<T>*>(m_Gears[GEAR_ID(T)]);

					if(!Table)
						THROW_PARADIGM_EXCEPTION("");
					return Table;
				}
				else
					return nullptr;
			}

			template<typename T>
			TArray<UMetaEntity*>* FFactorySupervisor::GetGearedEntities()
			{
				if (m_GearedEntities.find(GEAR_ID(T)) != m_GearedEntities.end())
					return m_GearedEntities[GEAR_ID(T)];
				else return nullptr;
			}
		}
	}
}