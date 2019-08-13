#ifndef _NATIVEINPUTATTRIBUTES_DIRECTINPUT_H_
#define _NATIVEINPUTATTRIBUTES_DIRECTINPUT_H_

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
#include <NativeInterface/Input/NativeInputEnums_DirectInput.h>

namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Input
		{
			struct UInputDevice
			{
				ENativeInputDeviceType Type;
				IDirectInputDevice8* Device;
			};

			struct UKeyboardDevice : UInputDevice
			{
				uint8 State[256];
			};

			struct UMouseDevice : UInputDevice
			{
				DIMOUSESTATE State;
				ENativeCursorCaptureMode MouseCaptureMode { MouseCaptureMode_Free };
				UAxis Axis;
			};

			struct UGamepadDevice : UInputDevice
			{
				DIJOYSTATE2 State;
				UAxis LeftStick;
				UAxis RightStick;
				UAxis Cross;
				UAxis Trigger;
				uint64 A : 1;
				uint64 B : 1;
				uint64 X : 1;
				uint64 Y : 1;
				uint64 LB : 1;
				uint64 RB : 1;
				uint64 Back : 1;
				uint64 Start : 1;
				uint64 LJoyB : 1;
				uint64 RJoyB : 1;
			};
		}
	}
}

typedef ParadigmEngine::NativeInterface::Input::UAxis UAxis;

#endif