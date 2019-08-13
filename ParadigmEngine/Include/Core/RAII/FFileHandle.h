#ifndef _FFILEHANDLE_H_
#define _FFILEHANDLE_H_

#include <ParadigmException.h>
#include <fstream>

namespace ParadigmEngine
{
	namespace Core
	{
		namespace RAII
		{
			enum EFileOpenMode
			{
				/** Open file for input operations. The file must exist. */
				Read = 0x1,

				/** Create an empty file for output operations. If a file with the same Name already exists, 
				its contents are discarded and the file is treated as a new empty file.*/
				Write = 0x2,

				/** Open file for output at the end of a file. Output operations always write data at the end of the file, expanding it.
				Repositioning operations (fseek, fsetpos, rewind) are ignored. The file is created if it does not exist.*/
				Append = 0x3,

				/** Open a file for update (both for input and output). The file must exist. */ 
				Read_Update = 0x4,

				/** Create an empty file and open it for update (both for input and output). 
				If a file with the same Name already exists its contents are discarded and the file is treated as a new empty file.*/
				Write_Update = 0x5,

				/** Open a file for update (both for input and output) with all output operations writing data at the end of the file. 
				Repositioning operations (fseek, fsetpos, rewind) affects the next input operations, but output operations move the position back to the end of file. 
				The file is created if it does not exist.*/
				Append_Update = 0x6,
			};

			static FString EnumFileOpenModeToString(EFileOpenMode _mode)
			{
				switch (_mode)
				{
				case ParadigmEngine::Core::RAII::Read:
					return "r";
				case ParadigmEngine::Core::RAII::Write:
					return "w";
				case ParadigmEngine::Core::RAII::Append:
					return "a";
				case ParadigmEngine::Core::RAII::Read_Update:
					return "r+";
				case ParadigmEngine::Core::RAII::Write_Update:
					return "w+";
				case ParadigmEngine::Core::RAII::Append_Update:
					return "a+";					
				default:
					THROW_PARADIGM_EXCEPTION_DOMAIN("Invalid or corrupted @EFileOpenMode pass as argument.");
				}
			}

			struct FFileHandle
			{				
					FFileHandle(const FString& _path, EFileOpenMode _openMode)
					{
#pragma warning(suppress : 4996)
						Data = fopen(_path, EnumFileOpenModeToString(_openMode));
						if (!Data)
							THROW_PARADIGM_EXCEPTION_RAII_ERROR("Failed to open " + _path);					
					}
					FFileHandle(const FString& _path, EFileOpenMode _openMode, bool& _success)
					{
#pragma warning(suppress : 4996)
						Data = fopen(_path, EnumFileOpenModeToString(_openMode));
						if (!Data)
							_success = false;
						else
							_success = true;
					}

					FString ToString()
					{
						FString ret{""};
						char c;
						do 
						{
							c = fgetc(Data);
							ret += c;
						} while (c != EOF);
						return ret;
					}

					~FFileHandle()
					{
						if (Data)
							fclose(Data);
					}
				
					FILE* Data;
			};
		}
	}
}

typedef ParadigmEngine::Core::RAII::EFileOpenMode EFileOpenMode;
typedef ParadigmEngine::Core::RAII::FFileHandle FFileHandle;

#endif