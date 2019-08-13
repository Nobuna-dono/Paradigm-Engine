#include <Physics\Force\FRigidbody.h>

namespace ParadigmEngine
{
	namespace Physics
	{
		namespace Force
		{

			bool UMetaRigidbody::_GetuseGravity() const
			{ 
				return m_useGravity;
			}
			
			void UMetaRigidbody::_SetuseGravity(const bool& _value)
			{ 
				if (m_useGravity != _value) { m_useGravity = _value; m_useGravityoutdated = true; }
			}
		}
	}
}
