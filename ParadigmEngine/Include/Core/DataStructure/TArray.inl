////////////////////////////////////////////////////////////////////////////////////////////////
// _TARRAY_H_'s inline file
//________________________________________________________________________

#include <ParadigmException.h>

namespace ParadigmEngine
{
	namespace Core
	{
		namespace DataStructure
		{
			////////////////////////////////////////////////////////////////////////////////////////////////
			// ITERATOR
			//________________________________________________________________________
			template<typename T>
			TArray<T>::Iterator::Iterator(T* _begin)
			{
				m_DataPtr = _begin;
			}

			template<typename T>
			T& TArray<T>::Iterator::operator++()
			{
				T* buff = m_DataPtr;
				
				if (++m_DataPtr == nullptr)
					m_DataPtr = buff;

				return *m_DataPtr;
			}
			
			template<typename T>
			T& TArray<T>::Iterator::operator*()
			{
				return *m_DataPtr;
			}
			
			template<typename T> 
			void TArray<T>::Iterator::operator=(T* _begin)
			{
				if(!_begin)
					THROW_PARADIGM_EXCEPTION_ARGUMENT("");
				m_DataPtr = _begin;
			}

			template<typename T>
			bool TArray<T>::Iterator::operator==(const Iterator& _otherIt) const
			{
				return m_DataPtr == _otherIt.m_DataPtr;
			}

			template<typename T>
			bool TArray<T>::Iterator::operator!=(const Iterator& _otherIt) const
			{
				return m_DataPtr != _otherIt.m_DataPtr;
			}


			template<typename T>
			TArray<T>::Const_Iterator::Const_Iterator(const T* _begin)
			{
				m_DataPtr = _begin;
			}

			template<typename T>
			const T& TArray<T>::Const_Iterator::operator++()
			{
				const T* buff = m_DataPtr;

				if (++m_DataPtr == nullptr)
					m_DataPtr = buff;

				return *m_DataPtr;
			}

			template<typename T>
			const T& TArray<T>::Const_Iterator::operator*()
			{
				return *m_DataPtr;
			}

			template<typename T>
			void TArray<T>::Const_Iterator::operator=(const T* _begin)
			{
				if (!_begin)
					THROW_PARADIGM_EXCEPTION_ARGUMENT("");
				m_DataPtr = _begin;
			}

			template<typename T>
			bool TArray<T>::Const_Iterator::operator==(const Const_Iterator& _otherIt) const
			{
				return m_DataPtr == _otherIt.m_DataPtr;
			}

			template<typename T>
			bool TArray<T>::Const_Iterator::operator!=(const Const_Iterator& _otherIt) const
			{
				return m_DataPtr != _otherIt.m_DataPtr;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////
			// TArray
			//________________________________________________________________________

			template<typename T>
			TArray<T>::TArray(std::initializer_list<T> _list) : m_Data{_list}
			{
				
			}

			template<typename T>
			uint TArray<T>::Capacity() const
			{
				return (uint)m_Data.capacity();
			}
			
			template<typename T>
			uint TArray<T>::Count() const
			{
				return (uint)m_Data.size();
			}

			template<typename T>
			bool TArray<T>::IsEmpty() const
			{
				return m_Data.empty();
			}

			template<typename T>
			void TArray<T>::Reserve(size_t _size)
			{
				if(m_Data.capacity() < _size)
					m_Data.reserve(_size);
			}

			template<typename T>
			void TArray<T>::Resize(size_t _size)
			{
				m_Data.resize(_size);
			}
			
			/** Shrink to fit. */
			template<typename T>
			void TArray<T>::Compact()
			{
				m_Data.shrink_to_fit();
			}


			template<typename T>
			T& TArray<T>::Get(uint _index)
			{
				if (_index < m_Data.size())
					return m_Data[_index];
				THROW_PARADIGM_EXCEPTION_ARGUMENT("");
			}

			template<typename T>
			const T& TArray<T>::Get(uint _index) const
			{
				if (_index < m_Data.size())
					return m_Data[_index];
				THROW_PARADIGM_EXCEPTION_ARGUMENT("");
			}

			template<typename T>
			T& TArray<T>::operator[](uint _index)
			{
				if (_index < m_Data.size())
					return m_Data[_index];
				THROW_PARADIGM_EXCEPTION_OUT_OF_RANGE("");
			}

			template<typename T>
			const T& TArray<T>::operator[](uint _index) const
			{
				if (_index < m_Data.size())
					return m_Data[_index];
				THROW_PARADIGM_EXCEPTION_OUT_OF_RANGE("");
			}

			template<typename T>
			T* TArray<T>::GetData() noexcept
			{
				return m_Data.data();
			}

			template<typename T>
			const T* TArray<T>::GetData() const noexcept
			{
				return m_Data.data();
			}

			template<typename T>
			T& TArray<T>::Front()
			{
				if (!m_Data.size())
					THROW_PARADIGM_EXCEPTION_OUT_OF_RANGE("");
				return m_Data.front();
			}

			template<typename T>
			T& TArray<T>::Back()
			{
				if (!m_Data.size())
					THROW_PARADIGM_EXCEPTION_OUT_OF_RANGE("");
				return m_Data.back();
			}

			template<typename T>
			bool TArray<T>::Contains(const T& _original) const
			{
				int i{ 0 };
				for (Const_Iterator it = Const_Begin(); it != Const_End(); ++it)
				{
					if (*it == _original)
						return true;
					++i;
				}
				return false;
			}

			template <typename T>
			bool TArray<T>::Contains(const T* _original)
			{
				bool fst = _original - (m_Data.data() + m_Data.size()/* * sizeof(T)*/) < 0;
				bool snd = _original - m_Data.data() >= 0;
				return fst && snd;
			//	return ((unsigned long)_original - (&m_Data[0] + sizeof(T) * m_Data.size())) > 0;
			}

			template<typename T>
			void TArray<T>::AddCopy(const T _value)
			{
				m_Data.push_back(_value);
			}

			template<typename T>
			void TArray<T>::Add(T _value)
			{
				m_Data.push_back(_value);
			}

			template<typename T>
			void TArray<T>::Remove(uint _index)
			{
				if (_index < m_Data.size())
					m_Data.erase(m_Data.begin() + _index);
			}

			template<typename T>
			void TArray<T>::Remove(uint _indexBegin, uint _indexEnd)
			{
				m_Data.erase(m_Data.begin() + _indexBegin, m_Data.begin() + _indexEnd);
			}

			template<typename T>
			bool TArray<T>::Remove(const T& _original)
			{
				int i{ 0 };
				for (Iterator it = Begin(); it != End(); ++it, ++i)
				{
					if (*it == _original)
					{
						Remove(i);
						return true;
					}
				}
				return false;
			}

			template<typename T>
			bool TArray<T>::Replace(uint _index, const T& _data)
			{
				if (_index < m_Data.size())
				{
					m_Data[_index] = _data;
					return true;
				}
				return false;
			}

			template<typename T>
			bool TArray<T>::Replace(const T& _orginal, const T& _data)
			{
				auto iterator = Find(_orginal);
				if (iterator != End())
				{
					(*iterator) = _data;
					return true;
				}
				return false;
			}

			template<typename T>
			void TArray<T>::Clear()
			{
				m_Data.clear();
			}

			template<typename T>
			void TArray<T>::Insert(uint _index, const T& _value)
			{
				if (_index >= m_Data.size())
					m_Data.push_back(_value);
				else
					m_Data.insert(m_Data.begin() + _index, _value);
			}

			template<typename T>
			TArray<const T*> ArrayToPointerArray(const TArray<T>& _array)
			{
				TArray<const T*> outArray;
				for (TArray<T>::Const_Iterator it = _array.Const_Begin(); it != _array.Const_End(); ++it)
					outArray.AddCopy(&(*it));
				return outArray;
			}

			template<typename T>
			TArray<T> PointerArrayToArray(const TArray<T*>& _array)
			{
				TArray<T> outArray;
				for (TArray<T*>::Const_Iterator it = _array.Const_Begin(); it != _array.Const_End(); ++it)
					outArray.Add(*(*it));
				return outArray;
			}
		}
	}
}