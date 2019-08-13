#ifndef _FCONSOLEPRINT_H_
#define _FCONSOLEPRINT_H_

#include <iostream>

#include <FString.h>
#include <ParadigmDebugEnum.h>
#include <FConsoleUtility.h>


/** Define me if you want to print in file all print call. */
//#define PARADIGM_LOG_FILE

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Debug
		{
			class FPrint
			{
				public:
					/** Print sentence in console. */
					static void Print(const FString& _sentence, EParadigmDebugLevel _debugLevel = EParadigmDebugLevel::NORMAL_LEVEL);
					/** Print sentence in console. */
					//static void Print(const FString& _sentence, EConsolePrintColor _color = WHITE);					

					/** Print sentence in file. */
					static void PrintFile(const FString& _sentence, EParadigmDebugLevel _debugLevel = NORMAL_LEVEL, const FString& _logFile = "Log.txt");
			};
		}
	}
}

typedef ParadigmEngine::Core::Debug::FPrint FPrint;

#endif