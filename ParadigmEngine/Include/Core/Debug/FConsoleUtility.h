#ifndef _FCONSOLEUTILITY_H_
#define _FCONSOLEUTILITY_H_

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Debug
		{
			enum EConsolePrintColor
			{
				BLACK = 0x0,
				BLUE = 0x0001,
				GREEN = 0x0002,
				RED = 0x0004,
				
				ORANGE = GREEN | RED,
				MAGENTA = BLUE | RED,
				CYAN = BLUE | GREEN,

				INTENSITY = 0x0008,

				WHITE = BLUE | GREEN | RED | INTENSITY,

				LIGHT_BLUE = BLUE | INTENSITY,
				LIGHT_GREEN = GREEN | INTENSITY,
				LIGHT_RED = RED | INTENSITY,
				LIGHT_ORANGE = GREEN | RED | INTENSITY,
				LIGHT_MAGENTA = BLUE | RED | INTENSITY,
				LIGHT_CYAN = BLUE | GREEN | INTENSITY,

				BACK_BLUE = 0x0010,
				BACK_GREEN = 0x0020,
				BACK_RED = 0x0040,
				BACK_INTENSITY = 0x0080,

				BACK_WHITE = BACK_BLUE | BACK_GREEN | BACK_RED | BACK_INTENSITY,

				NORMAL = WHITE,
				WARNING = RED,
			};

			class FConsoleUtility
			{
				public:
					/** Allow to set the channel color of the console. */
					static void SetPrintColor(EConsolePrintColor _color);
			};
		}
	}
}
typedef ParadigmEngine::Core::Debug::EConsolePrintColor EConsolePrintColor;
#endif