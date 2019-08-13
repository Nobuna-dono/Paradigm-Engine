
namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace Factory
		{
			template<typename T>
			UKeyHandler<T> FMetaEntity::AddGear(UMetaEntity* _metaEntity, T* _original)
			{
				if (!std::is_base_of<UMetaGear, T>::value || GEAR_ID(T) == GEAR_ID(UMetaGear))
					THROW_PARADIGM_EXCEPTION_ARGUMENT("The parameter _original type is not a UGear derived class.");

				if (!_metaEntity)
				{
					THROW_PARADIGM_EXCEPTION_ARGUMENT("Invalid UMetaEntity* passed to FMetaEntity::AddGear, call ignored.");
					return {};
				}

				if (_metaEntity->Gears.find(GEAR_ID(T)) == _metaEntity->Gears.end())
				{
						_metaEntity->Gears.emplace(std::pair<GearID, TArray<UKeyHandler<UMetaGear>>>(GEAR_ID(T), TArray<UKeyHandler<UMetaGear>>()));
				}
				
				UKeyHandler<T> tempHand;
				//if(_original)
				//	tempHand = PARADIGM_FACTORY->CreateGear<T>(_metaEntity, *_original);
				//else
					tempHand = PARADIGM_FACTORY->CreateGear<T>(_metaEntity);

				UKeyHandler<UMetaGear> hand;
				hand.Register = tempHand.Register;
				hand.Pointer = static_cast<UMetaGear*>(tempHand.Pointer);
				_metaEntity->Gears[GEAR_ID(T)].Add(hand);
				return tempHand;
			}

			template<typename T>
			void FMetaEntity::AddGearFromArchive(UMetaEntity* _metaEntity, T* _original)
			{
				if (!_metaEntity)
				{
					THROW_PARADIGM_EXCEPTION_ARGUMENT("Invalid UMetaEntity* passed to FMetaEntity::AddGear, call ignored.");
				}


			//	size_t acode = typeid(*a).hash_code();
				//size_t metacode = typeid(UMetaGear).hash_code();
				//if (_metaEntity->Gears.find(acode) == _metaEntity->Gears.end())
					//_metaEntity->Gears.emplace(std::pair<GearID, TArray<UKeyHandler<UMetaGear>>>(acode, TArray<UKeyHandler<UMetaGear>>()));
				
				PARADIGM_FACTORY->CreateGearFromArchive(_metaEntity, _original);

				PARADIGM_FACTORY->MetaGearsReflection();
				/*UKeyHandler<UMetaGear> hand;
				acode = typeid(*tempHand.Pointer).hash_code();

				hand.Register = tempHand.Register;
				hand.Pointer = dynamic_cast<UMetaGear*>(tempHand.Pointer);
				_metaEntity->Gears[acode].Add(hand);*/
				//return tempHand;
			}

			template<typename T>
			T* FMetaEntity::GetGear(UMetaEntity* _metaEntity)
			{
				return _metaEntity->GetGear<T>();
			}

			template<typename T>
			TArray<T*> FMetaEntity::GetGears(UMetaEntity* _metaEntity)
			{
				return _metaEntity->GetGears<T>();
			}

			template<typename T>
			bool FMetaEntity::DestroyGear(UMetaEntity* _metaEntity, const T& _original)
			{
				if (_metaEntity->Gears.find(GEAR_ID(T)) == m_Gears.end())
				{
					FPrint::Print("Invalid argument to DestroyGear : this entity don't have this type of gear, call ignored.", Core::Debug::WARNING);
					return false;
				}

				if (!PARADIGM.Factory.DestroyGear<T>(_original))
					FPrint::Print("wtf this gear was not find in the factory ! But ok well, I erased it from this entity.");

				_metaEntity->Gears[GEAR_ID(T)].Remove(_original);

				if (_metaEntity->Gears[GEAR_ID(T)].Count() == 0u)
					_metaEntity->Gears.erase(GEAR_ID(T));
				return true;
			}

			template<typename T>
			bool FMetaEntity::DestroyGears(UMetaEntity* _metaEntity)
			{
				if (_metaEntity->Gears.find(GEAR_ID(T)) == m_Gears.end())
				{
					FPrint::Print("Invalid argument to DestroyGear : this entity don't have this type of gear, call ignored.");
					return false;
				}

				for (auto var = (_metaEntity->Gears[GEAR_ID(T)]).Begin(); var != _metaEntity->Gears[GEAR_ID(T)].End(); var++)
				{
					if (!PARADIGM.Factory.DestroyGear<T>(_metaEntity, *var.Register))
						FPrint::Print("wtf this gear was not find in the factory ! But ok well, I erased it from this entity.");
				}
				_metaEntity->Gears.erase(GEAR_ID(T));
				return true;
			}
		}
	}
}