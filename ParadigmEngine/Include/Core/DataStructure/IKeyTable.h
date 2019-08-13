#ifndef _ITABLE_H_
#define _ITABLE_H_

#include <ParadigmTypedef.h>

#define MAX_KEYTABLE_SIZE (0xFFFF - 2)
#define MAX_KEY_DATA_SUM_BUFFER 0x1FFF
#define INVALID_KEY_REGISTER UKeyRegister(-1, MAX_KEY_DATA_SUM_BUFFER + 1)
#define NULL_KEY_REGISTER UKeyRegister(0, 0)

namespace ParadigmEngine
{
	namespace Core
	{
		namespace DataStructure
		{
			struct UKeyRegister
			{
				public:
						// Constructor
					UKeyRegister()
						: Index(0), SumBuffer(0)
					{}
					UKeyRegister(bits32 _index, bits32 _buffer)
						: Index(_index), SumBuffer(_buffer)
					{}

				public:
						// Processor
					operator bits32() const
					{
						return SumBuffer << 16 | Index;
					}

				public:
						// Data
					bits32 Index : 16;
					bits32 SumBuffer : 16;
			};

			template<typename T>
			struct TKeyData
			{				
				public:
					////////////////////////////////////////////////
					// METHODS
					//____________________________________	
					void Initialize(short _nextFreeKey);

				public:
					////////////////////////////////////////////////
					// DATA
					//____________________________________	
					T Data;
					bits32 SumBuffer : 13; // 17
					bits32 NextFreeKey : 16; // 2
					bits32 bActive : 1; // 1
					bits32 bCurrentFirst : 1; // 0
					bits32 bCurrentLast : 1; // 0
			};

			template<typename T>
			struct UKeyHandler
			{
				T* Pointer;
				UKeyRegister Register;
			};

			class IKeyTable
			{
				public:
					////////////////////////////////////////////////
					// ABSTRACT METHODS
					//____________________________________						
					/** Return the total number of elements the internal data structure can hold without resizing. */
					virtual uint Capacity() const = 0;
					/** Return the number of elements contained in the data structure. */
					virtual uint Count() const = 0;
					/** Clear content.*/
					virtual void Clear() = 0;
					/** Determines whether an element is in the data structure. */
					virtual bool Contains(UKeyRegister _register) const = 0;
					/** Removes indexed elements. */
					virtual bool Remove(UKeyRegister _register) = 0;
					/** Request a change of the total number of elements the internal data structure can hold. */
					virtual void Reserve(uint _size = 0xFF) = 0;

					/** Return the first available register. */
					virtual uint GetFirstAvailableRegisterIndex() const = 0;
					/** Return the first available register. */
					virtual uint GetLastAvailableRegisterIndex() const = 0;

					/** Get table data. */
					virtual void* GetData() = 0;

					/** Get table data. */
					virtual const void* GetData() const = 0;
			};
		}
	}
}
#include <IKeyTable.inl>

typedef ParadigmEngine::Core::DataStructure::UKeyRegister UKeyRegister;

#endif