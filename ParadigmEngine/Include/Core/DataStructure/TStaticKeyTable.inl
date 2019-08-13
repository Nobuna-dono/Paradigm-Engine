////////////////////////////////////////////////////////////////////////////////////////////////
// _TSTATICKEYTABLE_H_'s inline file
//________________________________________________________________________

#include <ParadigmException.h>

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
			void TStaticKeyTable<A>::TKeyData<T>::Initialize(short _nextFreeKey)
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
			TStaticKeyTable<T>::Iterator::Iterator(TKeyData<T>* _begin)
			{
				m_DataPtr = _begin;
			}

			template<typename T>
			T& TStaticKeyTable<T>::Iterator::operator++()
			{
				++m_DataPtr;

				while (!m_DataPtr->bActive)
				{
					if (m_DataPtr->bCurrentLast)
						break;
					++m_DataPtr;
				}
				return m_DataPtr->Data;
			}

			template<typename T>
			T& TStaticKeyTable<T>::Iterator::operator--()
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
			T& TStaticKeyTable<T>::Iterator::operator*()
			{
				if (!m_DataPtr->bActive)
					operator++();
				return m_DataPtr->Data;
			}

			template<typename T>
			void TStaticKeyTable<T>::Iterator::operator=(TKeyData<T>* _begin)
			{
				if (!_begin)
					THROW_PARADIGM_EXCEPTION_ARGUMENT("");
				m_DataPtr = _begin;
			}

			template<typename T>
			bool TStaticKeyTable<T>::Iterator::operator==(const Iterator& _otherIt) const
			{
				return m_DataPtr == _otherIt.m_DataPtr;
			}

			template<typename T>
			bool TStaticKeyTable<T>::Iterator::operator!=(const Iterator& _otherIt) const
			{
				return m_DataPtr != _otherIt.m_DataPtr;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////
			// TStaticKeyTable
			//________________________________________________________________________
			template<typename T>
			TStaticKeyTable<T>::TStaticKeyTable()				
			{
				Reserve();
			}

			/*template<typename T>
			TStaticKeyTable<T>::TStaticKeyTable(const TKeyTable<T>& _table)
			{
				Clear();
				m_Keys = (TKeyData<T>*)_table.GetData();
			}*/

			template<typename T>
			void TStaticKeyTable<T>::Reserve(uint _arraySize)
			{
				if (_arraySize + 1 >= MAX_KEYTABLE_SIZE)
				{
					FPrint::Print("Maximum table size of @MAX_KEYTABLE_SIZE element reached.", EParadigmDebugLevel::ERROR_LEVEL);
					m_ArraySize = MAX_KEYTABLE_SIZE + 1;
				}
				else
					m_ArraySize = _arraySize + 1;
				m_ActiveKeyCount = m_FirstFreeKeyIndex = m_LastActiveKeyIndex = 0;

				m_Keys = new TKeyData<T>[m_ArraySize]();

				// Initialize first entry for iterator purpose
				m_Keys[0].Initialize(1);

				for (uint i = 1; i < m_ArraySize; ++i)
					m_Keys[i].Initialize(i + 1);

				m_Keys[m_ArraySize - 1].bCurrentLast = true;
			}

			template<typename T>
			void TStaticKeyTable<T>::Clear()
			{
				if (m_Keys)
					delete[] m_Keys;

				m_ActiveKeyCount = 0;
				m_ArraySize = 0;
			}

			template<typename T>
			UKeyRegister TStaticKeyTable<T>::Add(T _data)
			{
				size_t index = m_FirstFreeKeyIndex;

				try
				{
					if (index >= MAX_KEYTABLE_SIZE)
						THROW_PARADIGM_EXCEPTION_RANGE("Maximum table size of @MAX_KEYTABLE_SIZE element reached.");

					if (!m_Keys || m_ActiveKeyCount >= m_ArraySize || m_Keys[index].bActive)
						THROW_PARADIGM_EXCEPTION_BAD_IMPLEMENTATION(PARADIGM_DEV_SIGNATURE_ARUMA);

					if (m_Keys[index].SumBuffer == MAX_KEY_DATA_SUM_BUFFER)
						m_Keys[index].SumBuffer = 0;
					++m_Keys[index].SumBuffer;
					m_Keys[index].bActive = true;
					m_Keys[index].bCurrentLast = false;
					m_Keys[index].Data = _data;
					m_FirstFreeKeyIndex = m_Keys[index].NextFreeKey;

					// For iterator purpose.
					if (index >= m_LastActiveKeyIndex)
					{
						m_LastActiveKeyIndex = index + 1;
						if (m_LastActiveKeyIndex < m_ArraySize)
							m_Keys[m_LastActiveKeyIndex].bCurrentLast = true;
					}
					++m_ActiveKeyCount;
				}
				catch (const ParadigmException& except)
				{
					FPrint::Print(except.SumUp(), EParadigmDebugLevel::CAUGHT_EXCEPTION);
					return INVALID_KEY_REGISTER;
				}

				return UKeyRegister((uint)index, m_Keys[index].SumBuffer);
			}

			template<typename T>
			bool TStaticKeyTable<T>::Replace(UKeyRegister _register, T _newData)
			{
				int index = _register.Index;
				if (m_Keys[index].SumBuffer == _register.SumBuffer && m_Keys[index].bActive)
				{
					m_Keys[index].Data = _newData;
					return true;
				}
				return false;
			}

			template<typename T>
			bool TStaticKeyTable<T>::Remove(UKeyRegister _register)
			{
				int index = _register.Index;
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

			template<typename T>
			void TStaticKeyTable<T>::GetRef(IKeyTable& _table)
			{
				Clear();
				m_Keys = (TKeyData<T>*)_table.GetData();
				m_ActiveKeyCount = _table.Count();
				m_ArraySize = _table.Capacity();				
				m_FirstFreeKeyIndex = _table.GetFirstAvailableRegisterIndex();
				m_LastActiveKeyIndex = _table.GetLastAvailableRegisterIndex();
			}
			
			template<typename T>
			void TStaticKeyTable<T>::Copy(const IKeyTable& _table)
			{
				Clear();
				Reserve(_table.Count());
				for (uint i = 0; i < _table.Count(); ++i)
					m_Keys[i] = ((TKeyData<T>*)_table.GetData())[i];
				m_ActiveKeyCount = _table.Count();
				m_FirstFreeKeyIndex = _table.GetFirstAvailableRegisterIndex();
				m_LastActiveKeyIndex = _table.GetLastAvailableRegisterIndex();
			}

			template<typename T>
			bool TStaticKeyTable<T>::Contains(UKeyRegister _register) const
			{
				int index = _register.Index;
				if (m_Keys[index].SumBuffer == _register.SumBuffer && m_Keys[index].bActive)
					return true;
				return false;
			}

			template<typename T>
			bool TStaticKeyTable<T>::Get(UKeyRegister _register, T& out_value)
			{
				int index = _register.Index;
				if (m_Keys[index].SumBuffer == _register.SumBuffer && m_Keys[index].bActive)
				{
					out_value = m_Keys[index].Data;
					return true;
				}
				return false;
			}

			template<typename T>
			T& TStaticKeyTable<T>::Get(UKeyRegister _register)
			{
				int index = _register.Index;
				if (m_Keys[index].SumBuffer == _register.SumBuffer && m_Keys[index].bActive)
					return m_Keys[index].Data;

				THROW_PARADIGM_EXCEPTION_ARGUMENT("");
			}

			template<typename T>
			const T& TStaticKeyTable<T>::Get(UKeyRegister _register) const
			{
				int index = _register.Index;
				if (m_Keys[index].SumBuffer == _register.SumBuffer && m_Keys[index].bActive)
					return m_Keys[index].Data;

				THROW_PARADIGM_EXCEPTION_ARGUMENT("");
			}

			template<typename T>
			bool TStaticKeyTable<T>::GetRegister(uint _index, UKeyRegister& out_value) const
			{
				if (_index >= m_ArraySize)
					THROW_PARADIGM_EXCEPTION_OUT_OF_RANGE("Out of range of _index{" + FString::ToString(_index) + "} while the table is of size{" + FString::ToString(m_ArraySize) + "}");

				if (m_Keys[_index].bActive)
				{
					out_value.Index = _index;
					out_value.SumBuffer = m_Keys[_index].SumBuffer;
					return true;
				}
				return false;
			}

			template<typename T>
			uint TStaticKeyTable<T>::Capacity() const
			{
				return m_ArraySize;
			}

			template<typename T>
			uint TStaticKeyTable<T>::Count() const
			{
				return m_FirstFreeKeyIndex;
			}

			template<typename T>
			uint TStaticKeyTable<T>::GetFirstAvailableRegisterIndex() const
			{
				return m_FirstFreeKeyIndex;
			}

			template<typename T>
			uint TStaticKeyTable<T>::GetLastAvailableRegisterIndex() const
			{
				return m_LastActiveKeyIndex;
			}

			template<typename T>
			void* TStaticKeyTable<T>::GetData()
			{
				return (void*)m_Keys;
			}

			template<typename T>
			const void* TStaticKeyTable<T>::GetData() const
			{
				return (void*)m_Keys;
			}

			template<typename T>
			T& TStaticKeyTable<T>::operator[](UKeyRegister _register)
			{
				int index = _register.Index;
				if (m_Keys[index].SumBuffer == _register.SumBuffer && m_Keys[index].bActive)
					return m_Keys[index].Data;

				THROW_PARADIGM_EXCEPTION_ARGUMENT("Invalid or corrupted key register.");
			}
		}
	}
}