#ifndef _NATIVEINPUTATTRIBUTES_H_
#define _NATIVEINPUTATTRIBUTES_H_

#include <ParadigmTypedef.h>
#include <NativeInterface/Input/NativeInputEnums.h>

namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Input
		{
			struct UAxis
			{
				float X{ 0 }, Y{ 0 };
			};
		}
	}
}

typedef ParadigmEngine::NativeInterface::Input::UAxis UAxis;

#endif