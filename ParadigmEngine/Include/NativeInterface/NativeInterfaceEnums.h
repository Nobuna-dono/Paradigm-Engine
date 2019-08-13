#ifndef _NATIVEINTERFACEENUMS_H_
#define _NATIVEINTERFACEENUMS_H_

#include <Core/Serialization/FEnumerator.h>

namespace ParadigmEngine
{
	namespace NativeInterface
	{
#ifdef _PARADIGM_EDITOR		
		SERIALIZABLE_ENUM(ENativeTargetViewport,		
			VIEWPORT_0,
			VIEWPORT_1,
			VIEWPORT_2,
			VIEWPORT_3,
			VIEWPORT_4,
			VIEWPORT_5,
			VIEWPORT_6,
			VIEWPORT_7,
			VIEWPORT_EDITOR
		);
#else
		SERIALIZABLE_ENUM(ENativeTargetViewport,
			VIEWPORT_0,
			VIEWPORT_1,
			VIEWPORT_2,
			VIEWPORT_3,
			VIEWPORT_4,
			VIEWPORT_5,
			VIEWPORT_6,
			VIEWPORT_7,
			VIEWPORT_EDITOR
		);
#endif
	}
}
typedef ParadigmEngine::NativeInterface::__ENativeTargetViewportEnumerator __ENativeTargetViewportEnumerator;
typedef __ENativeTargetViewportEnumerator __ETargetViewportEnumerator;
typedef ParadigmEngine::NativeInterface::ENativeTargetViewport ENativeTargetViewport;
typedef ENativeTargetViewport ETargetViewport;

#endif