#include <FString.h>
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
			FString::Iterator::Iterator(char* _begin)
			{
				m_DataPtr = _begin;
			}

			char& FString::Iterator::operator++()
			{
				char* buff = m_DataPtr;

				if (++m_DataPtr == nullptr)
					m_DataPtr = buff;

				return *m_DataPtr;
			}

			char& FString::Iterator::operator*()
			{
				return *m_DataPtr;
			}

			void FString::Iterator::operator=(char* _begin)
			{
				if (!_begin)
					THROW_PARADIGM_EXCEPTION_ARGUMENT("");
				m_DataPtr = _begin;
			}

			bool FString::Iterator::operator==(const Iterator& _otherIt) const
			{
				return m_DataPtr == _otherIt.m_DataPtr;
			}

			bool FString::Iterator::operator!=(const Iterator& _otherIt) const
			{
				return m_DataPtr != _otherIt.m_DataPtr;
			}

			FString::Const_Iterator::Const_Iterator(const char* _begin)
			{
				m_DataPtr = _begin;
			}

			const char& FString::Const_Iterator::operator++()
			{
				const char* buff = m_DataPtr;

				if (++m_DataPtr == nullptr)
					m_DataPtr = buff;

				return *m_DataPtr;
			}

			const char& FString::Const_Iterator::operator*()
			{
				return *m_DataPtr;
			}

			void FString::Const_Iterator::operator=(char* _begin)
			{
				if (!_begin)
					THROW_PARADIGM_EXCEPTION_ARGUMENT("");
				m_DataPtr = _begin;
			}

			bool FString::Const_Iterator::operator==(const Const_Iterator& _otherIt) const
			{
				return m_DataPtr == _otherIt.m_DataPtr;
			}

			bool FString::Const_Iterator::operator!=(const Const_Iterator& _otherIt) const
			{
				return m_DataPtr != _otherIt.m_DataPtr;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////
			// FSTRING
			//________________________________________________________________________
			FString::FString(FString&& _movestr)
			{
				m_Data = std::move(_movestr);
			}			

			FString::FString(const std::string& _string)
			{
				m_Data = _string;
			}

			FString::FString(char _char)
			{
				m_Data = _char;
			}

			FString::FString(const char* _string)
			{
				m_Data = { _string };
			}

			FString::FString(const char* _string, size_t _numberOfChar)
			{
				m_Data = { _string, _numberOfChar };
			}

			uint FString::Capacity()
			{
				return (uint)m_Data.capacity();
			}

			void FString::Clear()
			{
				if(m_Data.size())
					m_Data.clear();
			}

			uint FString::Count() const
			{
				return (uint)m_Data.size();
			}

			void FString::Reserve(size_t _size)
			{
				m_Data.reserve(_size);
			}

			char& FString::Back()
			{
				return m_Data.back();
			}
			const char& FString::Back() const
			{
				return m_Data.back();
			}

			char& FString::Front()
			{
				return m_Data.front();
			}
			const char& FString::Front() const
			{
				return m_Data.front();
			}

			char& FString::Get(uint _index)
			{
				if (_index >= m_Data.size())
					THROW_PARADIGM_EXCEPTION_OUT_OF_RANGE("");
				return m_Data.at(_index);
			}
			const char& FString::Get(uint _index) const
			{
				if (_index >= m_Data.size())
					THROW_PARADIGM_EXCEPTION_OUT_OF_RANGE("");
				return m_Data.at(_index);
			}

			char& FString::operator[](uint _index)
			{
				if (_index >= m_Data.size())
					THROW_PARADIGM_EXCEPTION_OUT_OF_RANGE("");
				return m_Data[_index];
			}
			const char& FString::operator[](uint _index) const
			{
				if (_index >= m_Data.size())
					THROW_PARADIGM_EXCEPTION_OUT_OF_RANGE("");
				return m_Data[_index];
			}

			void FString::operator+=(const FString& _string)
			{
				m_Data += _string.m_Data;
			}
			void FString::operator+=(const char* _string)
			{
				if (_string)
					m_Data += _string;
			}
			void FString::operator+=(char _char)
			{
				m_Data += _char;
			}

			void FString::Insert(uint _index, const FString& _string)
			{
				m_Data.insert(_index, _string.m_Data);
			}
			void FString::Insert(uint _index, const char* _string)
			{
				if (!_string)
					THROW_PARADIGM_EXCEPTION_ARGUMENT("");
				m_Data.insert(_index, _string);
			}
			void FString::Insert(uint _index, const char* _string, size_t _numberOfChar)
			{
				if (!_string)
					THROW_PARADIGM_EXCEPTION_ARGUMENT("");
				m_Data.insert(_index, _string, _numberOfChar);
			}

			void FString::Remove(uint _index, size_t _lenght)
			{
				m_Data.erase(_index, _lenght);				
			}

			bool FString::Remove(const FString& _toRemove)
			{
				uint index = Find(_toRemove, 0);				

				if (index != (uint(0) - 1))
				{
					Remove(index, _toRemove.Count());
					return true;
				}
				return false;
			}

			void FString::PushBack(char c)
			{
				m_Data.push_back(c);
			}
			void FString::PopBack()
			{
				m_Data.pop_back();
			}


			const char* FString::ToConstChar() const noexcept
			{
				return m_Data.c_str();
			}

			std::wstring FString::ToConstWideString() const noexcept
			{
				std::wstring wstr{ m_Data.begin(), m_Data.end() };
				return wstr;
			}

			const char* FString::GetData() const noexcept
			{
				return m_Data.data();
			}
						
			uint FString::Find(const FString& _str, uint _beginIndex) const
			{
				if (_beginIndex >= m_Data.size())
					return uint(0) - 1;
				return (uint)m_Data.find(_str, _beginIndex);
			}
			uint FString::Find(const char* _str, uint _beginIndex) const
			{
				if (_beginIndex >= m_Data.size())
					THROW_PARADIGM_EXCEPTION_OUT_OF_RANGE("");
				return (uint)m_Data.find(_str, _beginIndex);

			}
			uint FString::Find(char _char, uint _beginIndex) const
			{
				if (_beginIndex >= m_Data.size())
					THROW_PARADIGM_EXCEPTION_OUT_OF_RANGE("");
				return (uint)m_Data.find(_char, _beginIndex);
			}

			FString FString::Substring(uint64 _beginOffset, uint64 _endOffset)
			{
				if (m_Data.size() > _beginOffset && m_Data.size() >= _endOffset)
				{
					return m_Data.substr(_beginOffset, _endOffset - _beginOffset);
				}
				return "";
			}

			FString::operator const char*() const
			{
				return m_Data.c_str();
			}

			FString FString::operator+(const FString& _str) const
			{
				return FString(m_Data + _str.m_Data);
			}

			FString FString::operator+(const char* _str) const
			{
				if (!_str)
					THROW_PARADIGM_EXCEPTION_ARGUMENT("");
				return FString((m_Data + _str));
			}

			FString FString::operator+(char _char) const
			{
				return FString((m_Data + _char));
			}

			bool FString::operator==(const FString& _str) const
			{
				return m_Data == _str.m_Data;
			}

			bool FString::operator!=(const FString& _str) const
			{
				return m_Data != _str.m_Data;
			}

			bool FString::operator==(const char* _str) const
			{
				return m_Data == _str;
			}

			bool FString::operator!=(const char* _str) const
			{
				return m_Data != _str;
			}

			std::ostream& FString::operator<<(std::ostream& _os) const
			{
				for (std::string::const_iterator it = m_Data.cbegin(); it != m_Data.cend(); ++it)
					_os << *it;
				return _os;
			}

			////////////////////////////////////////////////
			// INTRA FUNCTIONALITY CLASS
			//____________________________________
			FString FString::FPathSlicer::Path(const FString& _path)
			{
				uint size = (uint)_path.m_Data.size();
				FString ret = "";
				for (std::string::const_iterator it = _path.m_Data.cend(); it != _path.m_Data.cbegin(); --size)
				{
					--it;
					if (*it == '/')
						break;
				}

				if (!size)
					return ret;

				ret.Reserve(size);
				for (uint i = 0; i < size; i++)
					ret.PushBack(_path.m_Data[i]);
				ret.Remove("./");
				return ret;
			}

			FString FString::FPathSlicer::Name(const FString& _path, const FString& _from)
			{
				uint index = 0;
				index = _path.Find(_from, 0);
				if (index != (uint()-1))
					return FString(_path.GetData() + index + _from.Count());

				uint size = (uint)_path.m_Data.size();
				FString ret = "";
				for (std::string::const_iterator it = _path.m_Data.cend(); it != _path.m_Data.cbegin(); --size)
				{
					--it;
					if ((*it) == '/')
						break;
				}

				if (size < 1)
					return _path;

				ret.Reserve(size);

				for (uint i = size; i < _path.m_Data.size(); ++i)
					ret.PushBack(_path.m_Data[i]);
				ret.Remove("./");
				return ret;
			}

			FString FString::FPathSlicer::Extension(const FString& _path, bool _returnExtension)
			{
				uint size = (uint)_path.m_Data.size();
				FString ret = "";
				for (std::string::const_iterator it = _path.m_Data.cend(); it != _path.m_Data.cbegin(); --size)
				{
					--it;
					if (*it == '.')
					{
						--size;
						break;
					}
				}

				if (!size)
					return _path;

				if (!_returnExtension)
				{
					ret.Reserve(size);
					for (uint i = 0; i < size; i++)
						ret.PushBack(_path.m_Data[i]);
				}
				else
				{
					ret.Reserve(_path.m_Data.size() - size);
					for (uint i = size; i < _path.m_Data.size(); i++)
						ret.PushBack(_path.m_Data[i]);
				}
				return ret;
			}

			////////////////////////////////////////////////
			// NON-MEMBER FUNCTION OVERLOAD : operator+
			//____________________________________	
			
			FString operator+(const FString& _left, FString&& _right)
			{
				return _left.operator+(_right);
			}

			FString operator+(const char* _left, FString&& _right)
			{
				return FString(_left).operator+(_right);
			}
			FString operator+(const char* _left, const FString& _right)
			{
				return FString(_left).operator+(_right);
			}

			FString operator+(char _left, FString&& _right)
			{
				return FString(_left).operator+(_right);
			}
			FString operator+(char _left, const FString& _right)
			{
				return FString(_left).operator+(_right);
			}

			////////////////////////////////////////////////
			// NON-MEMBER FUNCTION OVERLOAD : operator>>
			//____________________________________		
			std::ostream& operator<<(std::ostream& _os, const FString& _str)
			{
				return _str.operator<<(_os);
			}

		}
	}
}

