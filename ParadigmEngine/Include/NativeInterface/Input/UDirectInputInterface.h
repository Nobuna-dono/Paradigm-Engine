#ifndef _UDIRECTECTINPUTINTERFACE_H_
#define _UDIRECTECTINPUTINTERFACE_H_

#include <TArray.h>
#include <IKeyTable.h>

#include <NativeInterface/Input/NativeInputAttributes.h>
#include <NativeInterface/Input/NativeInputAttributes_DirectInput.h>

namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Input
		{
			struct UDirectInputInterface
			{
				IDirectInput8* DirectInput;
				ETargetViewport TargetViewport;
				uint InputDeviceMask;

				UMouseDevice Mouse;
				UKeyboardDevice Keyboard;
				TArray<UGamepadDevice> Gamepads;
			};
		}
	}
}

#endif