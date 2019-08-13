
namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace Factory
		{

			template<typename T>
			bool UMetaEntity::SetGearValueFromName(GearID _metaGearCode, uint _index, FString _valueName, T _value)
			{
				if (Gears.find(_metaGearCode) != Gears.end() && _index < Gears[_metaGearCode].Count())
					return Gears[_metaGearCode][_index].Pointer->SetValueFromName(_valueName, _value);
				return false;
			}

			template<typename T>
			bool UMetaEntity::ReplaceValueInGear(UArchive& out_gearArchive, const FString& _name, T _value)
			{
				if (!FArchive::ReplaceValueInGear(out_gearArchive, _name, _value))
					return false;

				size_t gearId;
				FArchive::Deserialize<size_t>(out_gearArchive, gearId); // get gear id 
				//FArchive::SkipString(out_gearArchive); // skip gear name
				out_gearArchive.ResetIndex();

				auto gear = GetGearFromID(gearId);
				if (!gear)
					return false;
				try { gear->Dearchive(out_gearArchive); }
				catch (const ParadigmException&)
				{
					FPrint::Print("Failed to dearchive gear.", EParadigmDebugLevel::CAUGHT_EXCEPTION);
					return false;
				}

				return true;
			}


			template<typename T>
			T* UMetaEntity::GetGear()
			{
				if (Gears.find(GEAR_ID(T)) != Gears.end())
					return static_cast<T*>(Gears[GEAR_ID(T)][0].Pointer);
				return nullptr;
			}

			template<typename T>
			TArray<T*> UMetaEntity::GetGears()
			{
				TArray<T*> outArray;
				if (Gears.find(GEAR_ID(T)) != Gears.end())
				{
					uint size = Gears[GEAR_ID(T)].Count();
					for (uint i = 0; i < size; ++i)
						outArray.Add((T*)(Gears[GEAR_ID(T)][i].Pointer));
				}
				return outArray;
			}

			template<typename T>
			UKeyRegister UMetaEntity::GetGearRegister(T* _ptr)
			{

				if (Gears.find(GEAR_ID(T)) != Gears.end())
				{
					if (_ptr)
					{
						for (auto it = Gears[GEAR_ID(T)].Begin(); it != Gears[GEAR_ID(T)].End(); ++it)
							if ((*it).Pointer == _ptr)
								return (*it).Register;
					}
					else
						return Gears[GEAR_ID(T)][0].Register;
				}
				return INVALID_KEY_REGISTER;
			}

			template<typename T>
			UKeyHandler<T> UMetaEntity::GetGearHandle(T* _ptr)
			{
				if (Gears.find(GEAR_ID(T)) != Gears.end())
				{
					if (_ptr)
					{
						for (auto it = Gears[GEAR_ID(T)].Begin(); it != Gears[GEAR_ID(T)].End(); ++it)
							if ((*it).Pointer == _ptr)
								return (*it);
					}
					else
						return Gears[GEAR_ID(T)][0];
				}
				return { nullptr,{} };
			}

			template<typename GearT>
			UMetaEntity* UMetaEntity::GetChild()
			{
				UMetaEntity* out = nullptr;
				for (uint i = 0; i < m_Children.Count(); ++i)
					if (m_Children[i]->GetGear<GearT>())
						return m_Children[i];
				return nullptr;
			}
		}
	}
}