#include <TArray.h>
#include <EngineFramework\MetaGear\UCustomBehaviourGear.h>
namespace ParadigmEngine
{
	namespace GameFramework
	{
		namespace GameEntity
		{
			template <typename GearT>
			GearT GEntity::AddGear(GearT* _original)
			{
				//if (std::is_base_of<UCustomBehaviourGear, GearT>::value)
				//	return FMetaEntity::AddGear<GearT>(m_MetaEntity.Pointer, _original ? _original->GetMetaData() : nullptr).Pointer;
				return FMetaEntity::AddGear<GearT::MetaType>(m_MetaEntity.Pointer, _original ? _original->GetMetaData() : nullptr).Pointer;
			}

			template <typename GearT>
			GearT GEntity::GetGear() const
			{
				return {m_MetaEntity.Pointer->GetGear<GearT::MetaType>()};
			}

			template <typename GearT>
			TArray<GearT> GEntity::GetGears() const
			{
				GearT temp;
				TArray<GearT::MetaType*> metaArray = m_MetaEntity.Pointer->GetGears<GearT::MetaType>();
				TArray<GearT> Garray;
				for (uint i = 0; i < metaArray.Count(); ++i)
				{
					Garray.Add({ metaArray[i]});
				}
				return Garray;
			}

			template <typename GearT>
			bool GEntity::RemoveGear(GearT* _original)
			{
				return FMetaEntity::DestroyGear(m_MetaEntity.Pointer, _original->GetMetaData())
			}

			template<typename GearT>
			GEntity GEntity::GetChild()
			{
				return m_MetaEntity.Pointer->GetChild<GearT::MetaType>();
			}
		}
	}
}