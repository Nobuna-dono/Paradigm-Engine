namespace ParadigmEngine
{
	namespace Core
	{
		namespace DataStructure
		{

			Layer FLayerSupervisor::GetLayer(const LayerName& _tag)
			{
				return m_strMap[_tag];
			}

			LayerMask FLayerSupervisor::GetLayerMask(const LayerName& _tag)
			{
				return m_binMap[m_strMap[_tag]];
			}

			void FLayerSupervisor::InternSetTagRelation(const LayerName& _tag, const LayerName& _tag2, bool _newValue)
			{
				if (_newValue)
				{
					m_binMap[m_strMap[_tag]] = m_binMap[m_strMap[_tag]] | m_strMap[_tag2];
					m_binMap[m_strMap[_tag2]] = m_binMap[m_strMap[_tag2]] | m_strMap[_tag];
				}
				else
				{
					m_binMap[m_strMap[_tag]] = m_binMap[m_strMap[_tag]] & (m_strMap[_tag2] ^ INT_MAX);
					m_binMap[m_strMap[_tag2]] = m_binMap[m_strMap[_tag2]] & (m_strMap[_tag] ^ INT_MAX);
				}
			}
		}
	}
}