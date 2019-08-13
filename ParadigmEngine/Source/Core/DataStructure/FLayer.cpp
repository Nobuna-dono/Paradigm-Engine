#include <FLayer.h>
#include <ParadigmMath.h>
#include<ParadigmException.h>

namespace ParadigmEngine
{
	namespace Core
	{
		namespace DataStructure
		{
			Layer FLayerSupervisor::AddLayer(const LayerName& _tag)
			{
				if (m_strMap.find(_tag) == m_strMap.end())
				{
					Layer id = 1 << m_strMap.size();
					m_strMap.insert({ _tag, id });
					m_binMap.insert({ id, INT_MAX });				
				}

				return m_strMap[_tag];
			}

			bool FLayerSupervisor::GetLayerMaskValue(const LayerName& _tag, const LayerName& _tag2)
			{
				if ((m_strMap.find(_tag2) != m_strMap.end() && m_strMap.find(_tag) != m_strMap.end()))
					return (m_binMap[m_strMap[_tag]] & m_strMap[_tag2]) > 0u;
				else
					THROW_PARADIGM_EXCEPTION_ARGUMENT("One or both of the arguments (\"" + _tag + "\" & \"" + _tag2 + "\") couldn't be found in the structure.");
				return false;
			}


			void FLayerSupervisor::SetLayerMaskValue(const LayerName& _tag, const LayerName& _tag2, bool _newValue)
			{
				if ((m_strMap.find(_tag2) != m_strMap.end() && m_strMap.find(_tag) != m_strMap.end()))
				{
					InternSetTagRelation(_tag, _tag2, _newValue);
				}
				else
					THROW_PARADIGM_EXCEPTION_ARGUMENT("One or both of the arguments (\"" +_tag +"\" & \"" + _tag2 +"\") couldn't be found in the structure.");
			}

			void FLayerSupervisor::SetLayerMask(const LayerName& _tag, TArray<LayerName>& _tags, bool _newValue)
			{
				if (m_strMap.find(_tag) == m_strMap.end()) 
					THROW_PARADIGM_EXCEPTION_ARGUMENT(_tag + " couldn't be found in the structure.");

				for (unsigned int i = 0; i < _tags.Count(); ++i)
				{
					try
					{
						if (m_strMap.find(_tags[i]) != m_strMap.end())
						{
							InternSetTagRelation(_tag, _tags[i], _newValue);
						}
						else
							THROW_PARADIGM_EXCEPTION_ARGUMENT(_tags[i] + " couldn't be found in the structure.");
					}
					catch (ParadigmException _ecxept) {	}
				}
			}
		}
	}
}