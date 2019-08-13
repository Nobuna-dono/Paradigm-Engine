#include <FConsoleUtility.h>
#include <windows.h>
#include <Core/Time/FTime.h>

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Debug
		{
			void FConsoleUtility::SetPrintColor(EConsolePrintColor _color)
			{
				HANDLE hConsole;				
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, _color);
			}

		}
	}
}