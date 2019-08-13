#ifndef _TSTATICKEYTABLE_H_
#define _TSTATICKEYTABLE_H_

#include <IKeyTable.h>

namespace ParadigmEngine
{
	namespace Core
	{
		namespace DataStructure
		{
			//template <typename T>
			//using TKeyTable = ParadigmEngine::Core::DataStructure::TKeyTable<T>;

			template<typename T>
			class TStaticKeyTable : public IKeyTable
			{
				/*private:
					////////////////////////////////////////////////
					// PRIVATE MEMBER STRUCT
					//____________________________________	
					template<typename T>
					struct TKeyData
					{
						public:
								// Constructor
							TKeyData() = default;

						public:
								// Methods
							void Initialize(short _nextFreeKey);

						public:
								// Data
							T Data;
							bits32 SumBuffer : 13; // 17
							bits32 NextFreeKey : 16; // 2
							bits32 bActive : 1; // 1
							bits32 bCurrentFirst : 1; // 0
							bits32 bCurrentLast : 1; // 0
					};*/


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
							//const T& operator++();
							T& operator--();
							//const T& operator--();
							T& operator*();
							//const T& operator*();
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
					TStaticKeyTable();
					~TStaticKeyTable() = default;

				public:
					////////////////////////////////////////////////
					// CAPACITY
					//____________________________________		
					/** Return the total number of elements the internal data structure can hold without resizing. */
					uint Capacity() const;

					/** Clear content.*/
					void Clear() override;

					/** Return the number of elements contained in the data structure. */
					uint Count() const;


					/** Request a change of the total number of elements the internal data structure can hold. */
					void Reserve(uint _size = 0xFF) override;


				public:
					////////////////////////////////////////////////
					// ELEMENT ACCESS
					//____________________________________					
					/** Determines whether an element is in the array. */
					bool Contains(UKeyRegister _register) const;

					/** Fill the value via reference according to the register. If invalid Register, the value is not altered. For C-purist. */
					bool Get(UKeyRegister _register, T& out_value);
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
					* [Recommend] : bool Find(UKeyRegister _register, T& out_value). */
					T& operator[](UKeyRegister _register);



				public:
					////////////////////////////////////////////////
					// ITERATORS
					//____________________________________					
					/** Return iterator to beginning. */
					inline Iterator Begin()
					{
						return Iterator(m_Keys);
					}

					/** Return iterator to end. */
					inline Iterator End()
					{
						if (m_ActiveKeyCount > 0)
							return Iterator(&m_Keys[m_LastActiveKeyIndex]);
						return Iterator(m_Keys);
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
										
					/** Create a TStaticKeyTable which refer to the data of a TKeyTable. 
					* Be careful to use it only for local purposes, the pointer and references are volatile if they are referenced from a dynamic instance. */
					void GetRef(IKeyTable& _table);

					/** Copy the value of the TKeyTable. */
					void Copy(const IKeyTable& _table);


				private:
					////////////////////////////////////////////////
					// DATA
					//____________________________________
					TKeyData<T>* m_Keys = nullptr;
					uint m_ArraySize : 16;
					uint m_ActiveKeyCount : 16;
					uint m_FirstFreeKeyIndex : 16;
					uint m_LastActiveKeyIndex : 16; // Just allow to avoid the entire size of the array
			};
		}
	}
}
#include <TStaticKeyTable.inl>

template <typename T>
using TStaticKeyTable = ParadigmEngine::Core::DataStructure::TStaticKeyTable<T>;

#endif