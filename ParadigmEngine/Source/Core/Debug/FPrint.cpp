#include <FPrint.h>
#include <fstream>
#include <windows.h>

#include <ParadigmKeyword.h>

#ifdef PARADIGM_NATIVE_GRAPHICS_DIRECT3D11
#define PARADIGM_DEBUG_OUTPUT(TEXT) OutputDebugString(TEXT)
#else
#define PARADIGM_DEBUG_OUTPUT(TEXT) std::cout << TEXT << "\n";
#endif

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Debug
		{
			void FPrint::Print(const FString& _sentence, EParadigmDebugLevel _debugLevel)
			{				
				#ifdef PARADIGM_LOG_FILE
				PrintFile(_sentence, _debugLevel, FString("Log/" + FString(PARADIGM_DATE) + "ParadigmEngine.log"));
				#endif

				FString str;
				switch (_debugLevel)
				{
					case WARNING_LEVEL:
						str += "[WARNING] : ";
						#ifndef PARADIGM_NATIVE_GRAPHICS_DIRECT3D11
						FConsoleUtility::SetPrintColor(EConsolePrintColor::ORANGE);
						#endif
						break;
					case ERROR_LEVEL:
						str += "[ERROR] : ";
						#ifndef PARADIGM_NATIVE_GRAPHICS_DIRECT3D11
						FConsoleUtility::SetPrintColor(EConsolePrintColor::RED);
						#endif
						break;
					case ASSERTION_LEVEL:
						#ifndef PARADIGM_NATIVE_GRAPHICS_DIRECT3D11
						FConsoleUtility::SetPrintColor(EConsolePrintColor::MAGENTA);
						#endif
						str += "[ASSERTION] : ";
						break;
					case CAUGHT_EXCEPTION:
						#ifndef PARADIGM_NATIVE_GRAPHICS_DIRECT3D11
						FConsoleUtility::SetPrintColor((EConsolePrintColor::LIGHT_RED));
						#endif
						str += "\n[CAUGHT EXCEPTION] : ";
						break;
					case EXCEPTION_CAUGHT:
						#ifndef PARADIGM_NATIVE_GRAPHICS_DIRECT3D11
						FConsoleUtility::SetPrintColor((EConsolePrintColor::LIGHT_RED));
						#endif
						str += "\n[EXCEPTION CAUGHT] : ";
						break;
					default:
						break;
				}
				str += _sentence + '\n';				

				PARADIGM_DEBUG_OUTPUT(str);
				
				#ifndef PARADIGM_NATIVE_GRAPHICS_DIRECT3D11
				FConsoleUtility::SetPrintColor(EConsolePrintColor::WHITE);
				#endif
			}

			/*void FPrint::Print(const FString& _sentence, EConsolePrintColor _color)
			{
				#ifndef PARADIGM_NATIVE_GRAPHICS_DIRECT3D11
				FConsoleUtility::SetPrintColor(_color);
				#endif

				#ifdef PARADIGM_LOG_FILE
				PrintFile(_sentence, EParadigmDebugLevel::NORMAL_LEVEL, FString(PARADIGM_DATE + "ParadigmEngine.log"));
				#endif

				PARADIGM_DEBUG_OUTPUT(_sentence);
				
				#ifndef PARADIGM_NATIVE_GRAPHICS_DIRECT3D11
				FConsoleUtility::SetPrintColor(EConsolePrintColor::WHITE);
				#endif
			}*/

			void FPrint::PrintFile(const FString& _sentence, EParadigmDebugLevel _debugLevel, const FString& _logFile)
			{
				FString str = PARADIGM_DATE + PARADIGM_TIME;

				switch (_debugLevel)
				{
					case WARNING_LEVEL:
						str += "[WARNING] - ";
						break;
					case ERROR_LEVEL:
						str += "[ERROR] - ";
						break;
					case ASSERTION_LEVEL:
						str += "[ASSERTION] - ";
						break;
					case EXCEPTION_CAUGHT:
						str += "[EXCEPTION] - ";
						break;
					case CAUGHT_EXCEPTION:
						str += "[EXCEPTION] - ";
						break;
					default:
						break;
				}
				str += _sentence;
				
				// RAII
				std::ofstream file(_logFile, std::ios::app);
				if (file)
				{
					file << str;
					file.close();
				}
			}

		}
	}
}