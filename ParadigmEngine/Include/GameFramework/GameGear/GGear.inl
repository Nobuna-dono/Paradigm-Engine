
namespace ParadigmEngine
{
	namespace GameFramework
	{
		namespace GameGear
		{
			template <class MetaType, class derive>
			GGear<MetaType, derive>::GGear(MetaType* _metaData) : m_MetaGear{ _metaData }
			{}

			template <class MetaType, class derive>
			GGear<MetaType, derive>::GGear(UMetaEntity* _metaData) : m_MetaGear{ _metaData->GetGear<MetaType>() }
			{}

			template <class MetaType, class derive>
			MetaType* GGear<MetaType, derive>::GetMetaData() const
			{
				return m_MetaGear;
			}

			template <class MetaType, class derive>
			GEntity GGear<MetaType, derive>::GetEntity() const
			{
				return GEntity(m_MetaGear->GearedUnit);
			}

			template <class MetaType, class derive>
			void  GGear<MetaType, derive>::operator=(MetaType* _metaGear)
			{
				m_MetaGear = _metaGear;
			}

			template <class MetaType, class derive>
			GGear<MetaType, derive>:: operator MetaType*()
			{
				return m_MetaGear;
			}

			template <class MetaType, class derive>
			GGear<MetaType, derive>:: operator bool()
			{
				return m_MetaGear;
			}

		}
	}
}