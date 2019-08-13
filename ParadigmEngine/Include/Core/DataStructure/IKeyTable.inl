////////////////////////////////////////////////////////////////////////////////////////////////
// _IKEYTABLE_H_'s inline file
//________________________________________________________________________

namespace ParadigmEngine
{
	namespace Core
	{
		namespace DataStructure
		{
			template<typename T>
			void TKeyData<T>::Initialize(short _nextFreeKey)
			{
				SumBuffer = 0;
				NextFreeKey = _nextFreeKey;
				if (_nextFreeKey == 1)
					bCurrentFirst = true;
				bActive = false;
			}
		}
	}
}