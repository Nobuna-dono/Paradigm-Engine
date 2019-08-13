#ifndef _TKEYTABLE_H_
#define _TKEYTABLE_H_

#include <vector>

#include <IKeyTable.h>

namespace ParadigmEngine
{
	namespace Core
	{
		namespace DataStructure
		{		
			/** An efficient datastructure base on a "key register - value" concept. 
			T must have a default constructor. */
			template<typename T>
			class TKeyTable : public IKeyTable
			{
				public:
					////////////////////////////////////////////////
					// MEMBER STRUCT
					//____________________________________	
					struct Iterator
					{
						public:
								// Constructor - Destructor
							Iterator(TKeyData<T>* _begin);

						public:
								// Operators
							T& operator++();							
							T& operator--();							
							T& operator*();							
							void operator=(TKeyData<T>* _begin);
							bool operator==(const Iterator& _otherIt) const;
							bool operator!=(const Iterator&_otherIt) const;

						private:
								//  Data
							TKeyData<T>* m_DataPtr;
					};
					

				public:
					////////////////////////////////////////////////
					// CONSTRUCTOR - DESTRUCTOR
					//____________________________________		
					TKeyTable();
					~TKeyTable();


				public:
					////////////////////////////////////////////////
					// CAPACITY
					//____________________________________					
					/** Return the total number of elements the internal data structure can hold without resizing. */
					inline uint Capacity() const;

					/** Clear content.*/
					void Clear() override;

					/** Return the number of elements contained in the data structure. */
					inline uint Count() const;


					/** Request a change of the total number of elements the internal data structure can hold. */
					void Reserve(uint _size = 0x0) override;


				public:
					////////////////////////////////////////////////
					// ELEMENT ACCESS
					//____________________________________
					/** Return the first element in the array. */
					T& Front();
					
					/** Return the last element in the array. */
					T& Back();

					/** Determines whether an element is in the array. */
					bool Contains(UKeyRegister _register) const;

					/** Determines whether an element is in the array. */
					bool Contains(T* _original) const;
										
					/** Fill the value via reference according to the register. If invalid Register, the value is not altered. For C-purists.*/
					bool Get(UKeyRegister _register, T& out_value);
					/** Fill the value via reference according to the register. If invalid Register, the value is not altered. For C-purists.*/
					bool Get(UKeyRegister _register, T* out_value);
					/** Return the value adress according to the register. */
					T& Get(UKeyRegister _register);
					/** Return the value adress according to the register. */
					const T& Get(UKeyRegister _register) const;

					/** Return the first available register. */
					uint GetFirstAvailableRegisterIndex() const override;

					/** Return the first available register. */
					uint GetLastAvailableRegisterIndex() const override;

					/** Get table data. */
					void* GetData() override;
					/** Get table data. */
					const void* GetData() const override;

					/** Allow to get the value of the keytable from an index. */
					bool GetRegister(uint _index, UKeyRegister& out_register) const;

					/** Return the value corresponding of they register. If invalid Register, return a default value of type <T>.
					* [Recommend] : bool Get(UKeyRegister _register, T& out_value). */
					T& operator[](UKeyRegister _register);
					/** Return the value corresponding of they register. If invalid Register, return a default value of type <T>.
					* [Recommend] : bool Get(UKeyRegister _register, T& out_value). */
					const T& operator[](UKeyRegister _register) const;


				public:
					////////////////////////////////////////////////
					// ITERATORS
					//____________________________________
					/** Return iterator to beginning. */
					Iterator Begin()
					{
						return Iterator(m_Keys.data());
					}

					const Iterator Begin() const
					{
						return Iterator(m_Keys.data());
					}

					/** Return iterator to end. */
					Iterator End()
					{
						if (m_ActiveKeyCount > 0)
						{
							Iterator it = Iterator(&m_Keys[m_Keys.size() - 1]);
							return it;
						}
						return Iterator(m_Keys.data());
					}

					const Iterator End() const
					{
						if (m_ActiveKeyCount > 0)
						{
							Iterator it = Iterator(&m_Keys[m_Keys.size() - 1]);
							return it;
						}
						return Iterator(m_Keys.data());
					}

				public:
					////////////////////////////////////////////////
					// MODIFIERS
					//____________________________________
					/** Adds a new object to the data structure. Return a key register to access it. */
					UKeyRegister Add(T _data);
										
					/** Supply the data, according to the register, with the new. Do nothing if invalid data. */
					bool Replace(UKeyRegister _register, T _newData);

					/** Remove the data according to the register. Do nothing if invalid data. */
					bool Remove(UKeyRegister _register);

					/** Remove the data according to the register. Do nothing if invalid data. */
				//	bool Remove(T* _original);
				
				
				private:
					////////////////////////////////////////////////
					// DATA
					//____________________________________
					std::vector<TKeyData<T>> m_Keys;				
					uint m_ActiveKeyCount{0};
					uint m_FirstFreeKeyIndex : 16;
					uint m_LastActiveKeyIndex : 16;
			};		
		}
	}
}
#include <TKeyTable.inl>			


template <typename T>
using TKeyTable = ParadigmEngine::Core::DataStructure::TKeyTable<T>;

#endif
