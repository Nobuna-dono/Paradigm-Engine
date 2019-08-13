#ifndef _FSTRING_H_
#define _FSTRING_H_

#include <iostream>
#include <istream>
#include <string>
#include <ParadigmTypedef.h>

namespace ParadigmEngine
{
	namespace Core
	{
		namespace DataStructure
		{
			class FString
			{
				public:
					////////////////////////////////////////////////
					// MEMBER STRUCT
					//____________________________________			
					struct Iterator
					{
						public:
							// Constructor - Destructor
							Iterator(char* _begin);

						public:
							// Operators
							char& operator++();
							char& operator*();
							void operator=(char* _begin);
							bool operator==(const Iterator& _otherIt) const;
							bool operator!=(const Iterator&_otherIt) const;

						private:
							//  Data
							char* m_DataPtr;
					};

					struct Const_Iterator
					{
						public:
							// Constructor - Destructor
							Const_Iterator(const char* _begin);

						public:
							// Operators
							const char& operator++();
							const char& operator*();
							void operator=(char* _begin);
							bool operator==(const Const_Iterator& _otherIt) const;
							bool operator!=(const Const_Iterator&_otherIt) const;

						private:
							//  Data
							const char* m_DataPtr;
					};



				public:
					////////////////////////////////////////////////
					// CONSTRUCTOR - DESTRUCTOR
					//____________________________________		
					FString() = default;
					FString(FString&&);
					FString(const std::string& _string);
					FString(char _char);
					FString(const char* _string);
					FString(const char* _string, size_t _numberOfChar);
					~FString() = default;

				public:
					////////////////////////////////////////////////
					// CAPACITY
					//____________________________________
					/** Return the total number of elements the internal data structure can hold without resizing. */
					uint Capacity();
					
					/** Clear content.*/
					void Clear();

					/** Return the number of elements contained in the data structure. */
					inline uint Count() const;

					/** Request a change of the total number of elements the internal data structure can hold. */
					void Reserve(size_t _size);

				public:
					////////////////////////////////////////////////
					// GETTERS
					//____________________________________
					/** Access last character. */
					char& Back();
					/** Access last character. */
					const char& Back() const;

					/** Access first character. */
					char& Front();
					/** Access first character. */
					const char& Front() const;

					/** Access character. */
					char& Get(uint _index);
					/** Access character. */
					const char& Get(uint _index) const;

					/** Access character. */
					char& operator[](uint _index);
					/** Access character. */
					const char& operator[](uint _index) const;


				public:
					////////////////////////////////////////////////
					// ITERATORS
					//____________________________________
					inline std::string::iterator NativeBegin()
					{
						return m_Data.begin();
					}
					
					/** Return iterator to beginning. */					
					inline Iterator Begin()
					{						
						return Iterator(&m_Data.front());
					}
					
					/** Return iterator to end. */
					inline Iterator End()
					{
						if (m_Data.size() > 0)
						{
							Iterator it{ &m_Data[m_Data.size() - 1] };
							++it;
							return it;
						}
						return Iterator(&m_Data.front());
					}
					
					/** Return iterator to beginning. */
					inline Const_Iterator Const_Begin() const
					{
						return Const_Iterator(&m_Data.front());
					}

					/** Return iterator to end. */
					inline Const_Iterator Const_End() const
					{
						if (m_Data.size() > 0)
						{
							Const_Iterator it{ &m_Data[m_Data.size() - 1] };
							++it;
							return it;
						}
						return Const_Iterator(&m_Data.front());
					}


				public:
					////////////////////////////////////////////////
					// MODIFIERS
					//____________________________________
					/** Append to string. */
					void operator+=(const FString& _string);
					/** Append to string. */
					void operator+=(const char* _string);
					/** Append to string. */
					void operator+=(char _char);

					/** Insert into string. */
					void Insert(uint _index, const FString& _string);
					/** Insert into string. */
					void Insert(uint _index, const char* _string);
					/** Insert into string. */
					void Insert(uint _index, const char* _string, size_t _numberOfChar);

					/** Erase character from string. */
					void Remove(uint _index, size_t _lenght = 0);
					/** Erase the given string from string. */			
					bool Remove(const FString& _toRemove);

					/** Append character to string.*/
					void PushBack(char c);
					/** Erases the last character of the string. */
					void PopBack();


				public:
					////////////////////////////////////////////////
					// FUNCTIONNALITY
					//____________________________________
					/** Get string data. */
					const char* GetData() const noexcept;

					/** Searches the string for the first occurrence of the sequence specified by its arguments. Return (uint(0) -1) if no found. */
					uint Find(const FString& str, uint _beginIndex) const;
					/** Searches the string for the first occurrence of the sequence specified by its arguments. Return (uint(0) -1) if no found. */
					uint Find(const char* str, uint _beginIndex) const;
					/** Searches the string for the first occurrence of the sequence specified by its arguments. Return (uint(0) -1) if no found.*/
					uint Find(char str, uint _beginIndex) const;

					FString Substring(uint64 _beginOffset, uint64 _endOffset);

					/** Returns a pointer to an array that contains a null-terminated sequence of characters. */
					operator const char*() const;
										
					/** Return concatenated string. */
					FString operator+(const FString& _str) const;
					/** Return concatenated string. */
					FString operator+(const char* _str) const;
					/** Return concatenated string. */
					FString operator+(char _char) const;
					

					FString(const FString&) = default;
					FString& operator=(const FString& _str) = default;

					/** Determines whether string are same. */
					bool operator==(const FString& _str) const;
					/** Determines whether string are same. */
					bool operator==(const char* _str) const;
					/** Determines whether string are same. */
					bool operator!=(const FString& _str) const;
					/** Determines whether string are same. */
					bool operator!=(const char* _str) const;

					std::ostream& operator<<(std::ostream&) const;

					/** Returns a pointer to an array that contains a null-terminated sequence of characters. */					
					const char* ToConstChar() const noexcept;
					std::wstring ToConstWideString() const noexcept;

					/** Convert a basic type(int, float, double, long, ...) and return it as string. */
					template<typename T>
					static FString ToString(const T& _value)
					{
						return FString(std::to_string(_value));
					}


				private:
					////////////////////////////////////////////////
					// DATA
					//____________________________________
					std::string m_Data;


				public:
					////////////////////////////////////////////////
					// INTRA FUNCTIONALITY CLASS
					//____________________________________
					class FPathSlicer
					{
						public:
							////////////////////////////////////////////////
							// FUNCTIONNALITY
							//____________________________________							
							/** Slice the string and return the string before the last '/' ('/' included). */
							static FString Path(const FString& _path);
							/** Slice the string and return the string after the last '/'. If @_from is specified, return the Name after it's value if found. */
							static FString Name(const FString& _path, const FString& _from = "");
							/** Slice the extension and return the string or the extension. Return @_path if no extension found. */
							static FString Extension(const FString& _path, bool _returnExtension = false);
					};
			};	

			FString operator+(const FString& _left, FString&& _right);

			FString operator+(const char* _left, FString&& _right);
			FString operator+(const char* _left, const FString& _right);

			FString operator+(char _left, FString&& _right);
			FString operator+(char _left, const FString& _right);
	
			std::ostream& operator<<(std::ostream& _is, const FString& _str);

		}
	}
}
typedef ParadigmEngine::Core::DataStructure::FString FString;

#endif