////////////////////////////////////////////////////////////////////////////////////////////////
// _TKEYTABLE_H_'s inline file
//________________________________________________________________________
#include <ParadigmException.h>
#include <FPrint.h>

namespace ParadigmEngine
{
	namespace Core
	{
		namespace DataStructure
		{

			////////////////////////////////////////////////////////////////////////////////////////////////
			// TKeyData
			//________________________________________________________________________
			/*template<typename A> template<typename T>
			void TKeyTable<A>::TKeyData<T>::Initialize(short _nextFreeKey)
			{
				SumBuffer = 0;
				NextFreeKey = _nextFreeKey;
				if (_nextFreeKey == 1)				
					bCurrentFirst = true;				
				bActive = false;
			}*/

			////////////////////////////////////////////////////////////////////////////////////////////////
			// Iterator
			//________________________________________________________________________
			template<typename T>
			TKeyTable<T>::Iterator::Iterator(TKeyData<T>* _begin)
			{
				m_DataPtr = _begin;
			}

			template<typename T>
			T& TKeyTable<T>::Iterator::operator++()
			{
				++m_DataPtr;

				while (!m_DataPtr->bActive)
				{
					if (!m_DataPtr->SumBuffer)
						break;
					++m_DataPtr;
				}
				return m_DataPtr->Data;
			}

			template<typename T>
			T& TKeyTable<T>::Iterator::operator--()
			{
				--m_DataPtr;

				while (!m_DataPtr->bActive)
				{
					if (m_DataPtr->bCurrentFirst)
						break;
					--m_DataPtr;
				}
				return m_DataPtr->Data;
			}

			template<typename T>
			T& TKeyTable<T>::Iterator::operator*()
			{
				if (!m_DataPtr->bActive)
					operator++();
				return m_DataPtr->Data;
			}

			template<typename T>
			void TKeyTable<T>::Iterator::operator=(TKeyData<T>* _begin)
			{
				if (!_begin)
					THROW_PARADIGM_EXCEPTION_ARGUMENT("");
				m_DataPtr = _begin;
			}

			template<typename T>
			bool TKeyTable<T>::Iterator::operator==(const Iterator& _otherIt) const
			{
				return m_DataPtr == _otherIt.m_DataPtr;
			}

			template<typename T>
			bool TKeyTable<T>::Iterator::operator!=(const Iterator& _otherIt) const
			{
				return m_DataPtr != _otherIt.m_DataPtr;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////
			// TKeyTable
			//________________________________________________________________________
			template<typename T>
			TKeyTable<T>::TKeyTable()			
				: m_FirstFreeKeyIndex{0}, m_LastActiveKeyIndex{0}
			{
				//Add({});
				//m_Keys[0].bActive = false;
				//m_FirstFreeKeyIndex = 0 ;
				//Remove({ 0,1 });
				/*m_Keys.push_back({});
				m_Keys.back().Initialize(1);
				m_Keys.back().bActive = true;
				m_FirstFreeKeyIndex = 1;*/
			}

			template<typename T>
			TKeyTable<T>::~TKeyTable()
			{
				Clear();
			}
			
			template<typename T>
			void TKeyTable<T>::Reserve(uint _arraySize)
			{
				try
				{
					if (_arraySize > MAX_KEYTABLE_SIZE)
						THROW_PARADIGM_EXCEPTION_DOMAIN("Maximum array size reached.");
				}
				catch (const ParadigmException& paradigmException)
				{
					FPrint::Print(paradigmException.SumUp(), EParadigmDebugLevel::CAUGHT_EXCEPTION);
					_arraySize = MAX_KEYTABLE_SIZE;
				}
				m_Keys.reserve(_arraySize);
			}

			template<typename T>
			void TKeyTable<T>::Clear()
			{
				m_Keys.clear();
				m_ActiveKeyCount = m_FirstFreeKeyIndex = 0;
			}

			template<typename T>
			UKeyRegister TKeyTable<T>::Add(T _data)
			{
				uint index = m_FirstFreeKeyIndex;
				uint size = m_Keys.size() ? (uint)m_Keys.size() - 1 : (uint)m_Keys.size();

				try
				{
					if (index >= MAX_KEYTABLE_SIZE)
						THROW_PARADIGM_EXCEPTION_RANGE("Maximum table size of @MAX_KEYTABLE_SIZE element reached.");
					
					if (index >= size)
					{ 
						if (!index) // if non initialize array, add the last bloc for iterator						
							m_Keys.push_back({});
						
						m_Keys.push_back({});
						m_Keys[index].Initialize((short)m_Keys.size() - 1);
						m_Keys.back().bCurrentLast = true;
						m_Keys[index].bCurrentLast = false;
					}

					if (m_Keys[index].bActive == true)
						THROW_PARADIGM_EXCEPTION_BAD_IMPLEMENTATION(PARADIGM_DEV_SIGNATURE_ARUMA);

					if (m_Keys[index].SumBuffer == MAX_KEY_DATA_SUM_BUFFER)
						m_Keys[index].SumBuffer = 0;
					++m_Keys[index].SumBuffer;
					m_Keys[index].bActive = true;
					m_Keys[index].Data = _data;
					m_FirstFreeKeyIndex = m_Keys[index].NextFreeKey;

					if (m_LastActiveKeyIndex < index)
						m_LastActiveKeyIndex = index;

					++m_ActiveKeyCount;
				}
				catch (const ParadigmException& except)
				{
					FPrint::Print(except.SumUp(), EParadigmDebugLevel::CAUGHT_EXCEPTION);
					return INVALID_KEY_REGISTER;
				}

				return UKeyRegister(index, m_Keys[index].SumBuffer);
			}

			template<typename T>
			bool TKeyTable<T>::Replace(UKeyRegister _register, T _newData)
			{
				uint index = _register.Index;
				if (index >= (uint)m_Keys.size())
					THROW_PARADIGM_EXCEPTION_OUT_OF_RANGE("");

				if (m_Keys[index].SumBuffer == _register.SumBuffer && m_Keys[index].bActive)
				{
					m_Keys[index].Data = _newData;
					return true;
				}
				return false;
			}

			template<typename T>
			bool TKeyTable<T>::Remove(UKeyRegister _register)
			{
				uint index = _register.Index;
				if (index >= (uint)m_Keys.size())
					THROW_PARADIGM_EXCEPTION_OUT_OF_RANGE("");

				if (m_Keys[index].SumBuffer == _register.SumBuffer && m_Keys[index].bActive)
				{
					// Update search pattern free key
					m_Keys[index].NextFreeKey = m_FirstFreeKeyIndex;
					m_Keys[index].bActive = false;

					m_FirstFreeKeyIndex = index;
					--m_ActiveKeyCount;

					return true;
				}
				return false;
			}

			//template<typename T>
			//bool TKeyTable<T>::Remove(T* _register)
			//{
			//	for (auto it = Begin(); it != End(); ++it)
			//	{
			//		if ((*it) == _ptr)
			//		{
			//			if ((*it).bActive)
			//			{
			//				// Update search pattern free key
			//				(*it).NextFreeKey = m_FirstFreeKey;
			//				(*it).bActive = false;

			//				m_FirstFreeKey = index;
			//				--m_ActiveKeyCount;

			//				return true;
			//			}
			//		}
			//	}
			//	return false;
			//}

			template<typename T>
			T& TKeyTable<T>::Front()
			{
				if (!m_Keys.size())
					THROW_PARADIGM_EXCEPTION_OUT_OF_RANGE("");
				return m_Keys.front().Data;
			}

			template<typename T>
			T& TKeyTable<T>::Back()
			{
				if (!m_Keys.size())
					THROW_PARADIGM_EXCEPTION_OUT_OF_RANGE("");

				Iterator it = End();
				return --it;
			}

			template<typename T>
			bool TKeyTable<T>::Contains(UKeyRegister _register) const
			{
				uint index = _register.Index;
				if (index >= (uint)m_Keys.size())
					return false;

				if (m_Keys[index].SumBuffer == _register.SumBuffer && m_Keys[index].bActive)
					return true;
				return false;
			}

			template<typename T>
			bool TKeyTable<T>::Contains(T* _original) const
			{
				for (auto it = Begin(); it != End(); ++it)
					if ((*it).Pointer == _ptr)
						return true;

				return false;
			}

			template<typename T>
			bool TKeyTable<T>::Get(UKeyRegister _register, T& out_value)
			{
				uint index = _register.Index;
				if (index >= (uint)m_Keys.size())
					THROW_PARADIGM_EXCEPTION_OUT_OF_RANGE("");

				if (m_Keys[index].SumBuffer == _register.SumBuffer && m_Keys[index].bActive)
				{
					out_value = m_Keys[index].Data;
					return true;
				}
				return false;
			}

			template<typename T>
			bool TKeyTable<T>::Get(UKeyRegister _register, T* out_value)
			{
				uint index = _register.Index;
				if (index >= (uint)m_Keys.size())
					THROW_PARADIGM_EXCEPTION_OUT_OF_RANGE("");

				if (m_Keys[index].SumBuffer == _register.SumBuffer && m_Keys[index].bActive)
				{
					out_value = &m_Keys[index].Data;
					return true;
				}
				return false;
			}

			template<typename T>
			bool TKeyTable<T>::GetRegister(uint _index, UKeyRegister& out_value) const
			{
				if (_index >= (uint)m_Keys.size())
					THROW_PARADIGM_EXCEPTION_OUT_OF_RANGE("Out of range of _index{" + FString::ToString(_index) + "} while the table is of size{" + FString::ToString((uint)m_Keys.size()) + "}");

				if (m_Keys[_index].bActive)
				{
					out_value.Index = _index;
					out_value.SumBuffer = m_Keys[_index].SumBuffer;
					return true;
				}
				return false;
			}

			template<typename T>
			T& TKeyTable<T>::Get(UKeyRegister _register)
			{
				uint index = _register.Index;
				if (index >= (uint)m_Keys.size())
					THROW_PARADIGM_EXCEPTION_OUT_OF_RANGE("Invalid or corrupted key register.");

				if (m_Keys[index].SumBuffer == _register.SumBuffer && m_Keys[index].bActive)
					return m_Keys[index].Data;

				THROW_PARADIGM_EXCEPTION_ARGUMENT("Invalid or corrupted key register.");
			}

			template<typename T>
			const T& TKeyTable<T>::Get(UKeyRegister _register) const
			{
				uint index = _register.Index;
				if (index >= (uint)m_Keys.size())
					THROW_PARADIGM_EXCEPTION_OUT_OF_RANGE("");

				if (m_Keys[index].SumBuffer == _register.SumBuffer && m_Keys[index].bActive)
					return m_Keys[index].Data;

				THROW_PARADIGM_EXCEPTION_ARGUMENT("");
			}

			template<typename T>
			uint TKeyTable<T>::GetFirstAvailableRegisterIndex() const
			{
				return m_FirstFreeKeyIndex;
			}

			template<typename T>
			uint TKeyTable<T>::GetLastAvailableRegisterIndex() const
			{
				return m_LastActiveKeyIndex;
			}

			template<typename T>
			uint TKeyTable<T>::Capacity() const
			{
				return (uint)m_Keys.capacity();
			}

			template<typename T>
			uint TKeyTable<T>::Count() const
			{
				return m_ActiveKeyCount;
			}

			template<typename T>
			T& TKeyTable<T>::operator[](UKeyRegister _register)
			{
				uint index = _register.Index;
				if (index >= (uint)m_Keys.size())
					THROW_PARADIGM_EXCEPTION_OUT_OF_RANGE("");

				if (m_Keys[index].SumBuffer == _register.SumBuffer && m_Keys[index].bActive)
					return m_Keys[index].Data;

				THROW_PARADIGM_EXCEPTION_ARGUMENT("");
			}

			template<typename T>
			const T& TKeyTable<T>::operator[](UKeyRegister _register) const
			{
				uint index = _register.Index;
				if (index >= (uint)m_Keys.size())
					THROW_PARADIGM_EXCEPTION_OUT_OF_RANGE("");

				if (m_Keys[index].SumBuffer == _register.SumBuffer && m_Keys[index].bActive)
					return m_Keys[index].Data;

				THROW_PARADIGM_EXCEPTION_ARGUMENT("");
			}

			template<typename T>
			void* TKeyTable<T>::GetData()
			{
				return (void*)m_Keys.data();
			}

			template<typename T>
			const void* TKeyTable<T>::GetData() const
			{
				return (void*)m_Keys.data();
			}
		}
	}
}