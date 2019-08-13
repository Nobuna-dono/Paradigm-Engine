#ifndef _PARADIGMDEBUGENUM_H_
#define _PARADIGMDEBUGENUM_H_

namespace ParadigmEngine
{
	namespace Core
	{
		namespace Debug
		{
			enum EParadigmDebugLevel
			{
				NORMAL_LEVEL,
				WARNING_LEVEL,
				ERROR_LEVEL,
				ASSERTION_LEVEL,

				CAUGHT_EXCEPTION,
				EXCEPTION_CAUGHT,
			};
		}
	}
}
typedef ParadigmEngine::Core::Debug::EParadigmDebugLevel EParadigmDebugLevel;
#endif