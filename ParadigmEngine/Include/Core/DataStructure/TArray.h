#ifndef _TARRAY_H_
#define _TARRAY_H_

#include <ParadigmException.h>
#include <ParadigmTypedef.h>
#include <vector>
#include <initializer_list>
namespace ParadigmEngine
{
	namespace Core
	{
		namespace DataStructure
		{
			template<typename T>
			struct TArray
			{
				public:
					////////////////////////////////////////////////
					// MEMBER STRUCT
					//____________________________________			
					struct Iterator
					{
						public:
							// Constructor - Destructor
							Iterator(T* _begin);

						public:
							// Operators
							T& operator++();
							T& operator*();							
							void operator=(T* _begin);
							bool operator==(const Iterator& _otherIt) const;
							bool operator!=(const Iterator&_otherIt) const;

						private:
							//  Data
							T* m_DataPtr;
					};


					struct Const_Iterator
					{
						public:
							// Constructor - Destructor
							Const_Iterator(const T* _begin);

						public:
							// Operators
							const T& operator++();
							const T& operator*();
							void operator=(const T* _begin);
							bool operator==(const Const_Iterator& _otherIt) const;
							bool operator!=(const Const_Iterator&_otherIt) const;

						private:
							//  Data
							const T* m_DataPtr;
					};


				public:	
					////////////////////////////////////////////////
					// CONSTRUCTOR - DESTRUCTOR
					//____________________________________		
					TArray(std::initializer_list<T>);
					TArray() = default;
					~TArray() = default;


				public:
					////////////////////////////////////////////////
					// CAPACITY
					//____________________________________
					/** Return the total number of elements the internal data structure can hold without resizing. */
					inline uint Capacity() const;
					
					/** Clear content.*/
					void Clear();
					
					/** Return the number of elements contained in the data structure. */
					inline uint Count() const;

					/** Test whether array is empty. */
					inline bool IsEmpty() const;

					/** Request a change of the total number of elements the internal data structure can hold. */
					void Reserve(size_t _size);

					/** Request a change of the number of elements the internal data structure can hold. */
					void Resize(size_t _size);
					
					/** Shrink to fit. */
					void Compact();

				public:
					////////////////////////////////////////////////
					// ELEMENT ACCESS
					//____________________________________
					/** Return the first element in the array. */
					T& Front();

					/** Return the last element in the array. */
					T& Back();

					/** Determines whether an element is in the array. */
					bool Contains(const T& _original) const;

					/** Determines whether an element is in the array and return an iterator. Return @End() if not found. */
					Iterator Find(const T& _original)
					{
						int i{ 0 };
						TArray<T>::Iterator it = Begin();
						for (; it != End(); ++it)
						{
							if (*it == _original)
								break;
						}
						return it;
					}

					/** Determines whether an element is in the array. */
					bool Contains(const T* _original);

					/** Access element in the range of @Count. */
					T& Get(uint _index);
					/** Access element in the range of @Count. */
					const T& Get(uint _index) const;

					/** Access element in the range of @Count. */
					T& operator[](uint _index);					
					/** Access element in the range of @Count. */
					const T& operator[](uint _index) const;

					/** Returns a direct pointer to the memory array used internally by the array. */
					T* GetData() noexcept;
					/** Returns a direct pointer to the memory array used internally by the array. */
					const T* GetData() const noexcept;

				public:
					////////////////////////////////////////////////
					// ITERATORS
					//____________________________________
					/** Return iterator to beginning. */
					inline Iterator Begin()
					{						
						return Iterator(m_Data.data());
					}

					/** Return iterator to end. */
					inline Iterator End() 
					{
						if (m_Data.size() > 0)
						{
							Iterator it = Iterator(&m_Data[m_Data.size() - 1]);
							++it;
							return it;
						}
						return Iterator(m_Data.data());
					}

					inline const Const_Iterator Const_Begin() const
					{
						return Const_Iterator(m_Data.data());
					}

					inline const Const_Iterator Const_End() const
					{
						if (m_Data.size() > 0)
						{
							Const_Iterator it = Const_Iterator(&m_Data[m_Data.size() - 1]);
							++it;
							return it;
						}
						return Const_Iterator(m_Data.data());
					}
				

				public:
					////////////////////////////////////////////////
					// MODIFIERS
					//____________________________________
					/** Copy an object in the array. */
					void AddCopy(const T _value);
					/** Adds an object in the array. */
					void Add(T _value);

					/** Removes indexed elements. */
					void Remove(uint _index);
					/** Removes indexed elements. */
					void Remove(uint _indexBegin, uint _indexEnd);
					/** Removes the first occurrence of a specific object. */
					bool Remove(const T& _orginal);

					/** Replace the specific object from a specific index. */
					bool Replace(uint _index, const T& _data);

					/** Replace the specific object from a specific index. */
					bool Replace(const T& _orginal, const T& _data);

					/** Insert new elements before the element at the specified index. */
					void Insert(uint _index, const T& _value);


				private:
					////////////////////////////////////////////////
					// DATA
					//____________________________________
					std::vector<T> m_Data;
			};
			
			////////////////////////////////////////////////
			// FUNCTIONALITY
			//____________________________________
			template<typename T>
			static TArray<const T*> ArrayToPointerArray(const TArray<T>& _array);
			
			template<typename T>
			static TArray<T> PointerArrayToArray(const TArray<T*>& _array);
		}
	}
}
#include <TArray.inl>

template <typename T>
using TArray = ParadigmEngine::Core::DataStructure::TArray<T>;

#endif