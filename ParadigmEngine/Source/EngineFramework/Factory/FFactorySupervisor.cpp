#include <EngineFramework/Factory/FFactorySupervisor.h>
#include<GameFramework/GameEntity/GEntity.h>
#include <EngineFramework/Factory/FMetaEntity.h>

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace Factory
		{
			// Pipeline Method
			void FFactorySupervisor::Initialize()
			{
			}

			void FFactorySupervisor::Terminate()
			{
				m_MetaData.Clear();

				for (std::unordered_map<GearID, IKeyTable*>::iterator it = m_Gears.begin(); it != m_Gears.end(); it++)
				{
					if (it->second)
					{
						it->second->Clear();
						delete(it->second);
					}
					else
						THROW_PARADIGM_EXCEPTION("");
				}
				m_Gears.clear();

				for (std::unordered_map<GearID, TArray<UMetaEntity*>*>::iterator it = m_GearedEntities.begin(); it != m_GearedEntities.end(); it++)
				{
					if (it->second)
					{
						it->second->Clear();
						delete(it->second);
					}
					else
						THROW_PARADIGM_EXCEPTION("");
				}
				m_GearedEntities.clear();

				/** partial. */
				//for (auto it = m_PartialReflectedGears.begin; it != m_PartialReflectedGears.end(); ++it)
					//(*it).clear;
				m_PartialReflectedGears.clear();
				m_ReflectorCallback.Clear();
			};

			// Methods
			UKeyHandler<UMetaEntity> FFactorySupervisor::CreateMetaEntity()
			{
				UKeyHandler<UMetaEntity> handler;
				handler.Register = m_MetaData.Add(UMetaEntity());
				handler.Pointer = GetMetaEntity(handler.Register);
				FMetaEntity::SetParent(handler.Pointer, nullptr);

				return handler;
			}

			bool FFactorySupervisor::DestroyEntity(UKeyRegister _original)
			{
				FMetaEntity::DestroyGears(&m_MetaData[_original]);
				return m_MetaData.Remove(_original);
			}

			//bool FFactorySupervisor::DestroyEntity(UMetaEntity* _original)
			//{
			//	return m_MetaEntity.Remove(_original);
			//}

			void FFactorySupervisor::Clear()
			{
				for (auto it = m_MetaData.Begin(); it != m_MetaData.End(); ++it)
					FMetaEntity::DestroyGears(&*it);
				m_MetaData.Clear();
			}

			// Getter
			UMetaEntity* FFactorySupervisor::GetMetaEntity(UKeyRegister _register)
			{
				return &m_MetaData[_register];
			}
			GEntity FFactorySupervisor::GetEntity(UKeyRegister _register)
			{
				return GEntity(&m_MetaData[_register]);
			}
		}
	}
}