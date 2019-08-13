#ifndef _FVARIABLETREE_H_
#define _FVARIABLETREE_H_

#include <functional>

template<typename Type>
class TProperty
{
	public:
		__declspec(property(get = CallGetData, put = CallSetData)) Type Data;
	
		void CallSetData(const Type& _data)
		{
			SetDataptr(_data);
		}
	
		const Type& CallGetData() const
		{
			return GetDataptr();
		}
	
		void SwapBuffers()
		{
			hotBuffer1 = !hotBuffer1;
		}
	
	protected:
		std::function<void(TProperty&, const Type&)> SetDataptr = &TProperty::SetData;
		std::function<const Type&(const TProperty&)> GetDataptr = &TProperty::GetData;
	
		void SetData(const Type& _data)
		{
			if (hotBuffer1)
				m_Data2 = _data;
			else
				m_Data1 = _data;
		}
	
		const Type& GetData() const
		{
			return hotBuffer1? m_Data1 : m_Data2;
		}
		bool hotBuffer1 = true;
		Type m_Data1;
		Type m_Data2;
};

#endif