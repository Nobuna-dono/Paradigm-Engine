#ifndef _NATIVEINPUTENUMS_H_
#define _NATIVEINPUTENUMS_H_

#include<Core/Serialization/FEnumerator.h>

namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Input
		{
			PARADIGM_ENUM(ENativeCursorCaptureMode,			
				/** The cursor will be able to move freely. */
				MouseCaptureMode_Free,
				/** The cursor will be lock in the center of the screen. */
				MouseCaptureMode_Locked,
				/** The cursor will be able to move freely inside of the context. Get out of the frame sends to the other side. */
				MouseCaptureMode_FreeBorder,
				/** The cursor will be able to move freely but it won't be able to reach the frame. */
				MouseCaptureMode_LockedBorder
			);

			/** Type of available device type. You can combine multiple device with the operator '|' (bitwize purpose). */
			enum ENativeInputDeviceType
			{
				/** Active mouse capture. */
				InputDeviceType_Mouse = 0x1,
				/** Active keyboard capture. */
				InputDeviceType_Keyboard = 0x2,

				/** Active gamepad1 capture. */
				InputDeviceType_Gamepad1 = 0x4,
				/** Active gamepad2 capture. */
				InputDeviceType_Gamepad2 = 0x8,
				/** Active gamepad3 capture. */
				InputDeviceType_Gamepad3 = 0x10,
				/** Active gamepad4 capture. */
				InputDeviceType_Gamepad4 = 0x20,
				/** Active any gamepad capture. */
				InputDeviceType_Gamepads = 0x40,
			};
			
			PARADIGM_ENUM(ENativeAxis,			
				Mouse,

				Gamepad1_LeftStick,
				Gamepad1_RightStick,
				Gamepad1_Trigger,

				Gamepad2_LeftStick,
				Gamepad2_RightStick,
				Gamepad2_Trigger,

				Gamepad3_LeftStick,
				Gamepad3_RightStick,
				Gamepad3_Trigger,

				Gamepad4_LeftStick,
				Gamepad4_RightStick,
				Gamepad4_Trigger,

				/** Any gamepad.  */
				Gamepad_LeftStick,
				/** Any gamepad.  */
				Gamepad_RightStick,
				/** Any gamepad.  */
				Gamepad_Trigger,
			);

			PARADIGM_ENUM(ENativeKeyCode,
				None,
				Escape,
				Return,
				Space,
				Backspace,
				Tab,

				Alpha0, /** The '0' key on the top of the alphanumeric keyboard. */
				Alpha1, /** The '1' key on the top of the alphanumeric keyboard. */
				Alpha2,	/** The '2' key on the top of the alphanumeric keyboard. */
				Alpha3,	/** The '3' key on the top of the alphanumeric keyboard. */
				Alpha4,	/** The '4' key on the top of the alphanumeric keyboard. */
				Alpha5,	/** The '5' key on the top of the alphanumeric keyboard. */
				Alpha6,	/** The '6' key on the top of the alphanumeric keyboard. */
				Alpha7,	/** The '7' key on the top of the alphanumeric keyboard. */
				Alpha8,	/** The '8' key on the top of the alphanumeric keyboard. */
				Alpha9,	/** The '9' key on the top of the alphanumeric keyboard. */

				Keypad0,
				Keypad1,
				Keypad2,
				Keypad3,
				Keypad4,
				Keypad5,
				Keypad6,
				Keypad7,
				Keypad8,
				Keypad9,

				KeypadPeriod,	/** Numeric keypad '.'.*/
				KeypadDivide,	/** Numeric keypad '/'.*/
				KeypadSlash,	/** Numeric keypad '/'.*/
				KeypadMultiply, /** Numeric keypad '*'.*/
				KeypadMinus,	/** Numeric keypad '-'.*/
				KeypadAdd,		/** Numeric keypad '+'.*/
				KeypadEnter,	/** Numeric keypad enter.*/
				KeypadDecimal,	/** Numeric keypad '.'.*/
				KeypadNumLock,

				Up,
				Down,
				Left,
				Right,

				F1,
				F2,
				F3,
				F4,
				F5,
				F6,
				F7,
				F8,
				F9,
				F10,
				F11,
				F12,

				A,
				B,
				C,
				D,
				E,
				F,
				G,
				H,
				I,
				J,
				K,
				L,
				M,
				N,
				O,
				P,
				Q,
				R,
				S,
				T,
				U,
				V,
				W,
				X,
				Y,
				Z,

				CapsLock,
				LeftAlt,
				RightAlt,
				LeftShift,
				RightShift,
				LeftControl,
				RightControl,
				LeftBracket,
				RightBracket,
				LeftWindows,
				RightWindows,

				Add,
				Minus,
				Equals,

				Insert,
				Delete,
				Home,
				End,

				Power, /** The system power button. */
					
				Mouse_LeftClick,
				Mouse_RightClick,
				Mouse_WheelClick,
				Mouse_WheelUp,
				Mouse_WheelDown,

				Gamepad_ButtonA,
				Gamepad_ButtonX,
				Gamepad_ButtonY,
				Gamepad_ButtonB,
				Gamepad_ButtonLB,
				Gamepad_ButtonRB,
				Gamepad_ButtonBack,
				Gamepad_ButtonStart,
				Gamepad_ButtonL3,
				Gamepad_ButtonR3,
				Gamepad_CrossLeft,
				Gamepad_CrossRight,
				Gamepad_CrossUp,
				Gamepad_CrossDown,

				Gamepad1_ButtonA,
				Gamepad1_ButtonX,
				Gamepad1_ButtonY,
				Gamepad1_ButtonB,
				Gamepad1_ButtonLB,
				Gamepad1_ButtonRB,
				Gamepad1_ButtonBack,
				Gamepad1_ButtonStart,
				Gamepad1_ButtonL3,
				Gamepad1_ButtonR3,
				Gamepad1_CrossLeft,
				Gamepad1_CrossRight,
				Gamepad1_CrossUp,
				Gamepad1_CrossDown,

				Gamepad2_ButtonA,
				Gamepad2_ButtonX,
				Gamepad2_ButtonY,
				Gamepad2_ButtonB,
				Gamepad2_ButtonLB,
				Gamepad2_ButtonRB,
				Gamepad2_ButtonBack,
				Gamepad2_ButtonStart,
				Gamepad2_ButtonL3,
				Gamepad2_ButtonR3,
				Gamepad2_CrossLeft,
				Gamepad2_CrossRight,
				Gamepad2_CrossUp,
				Gamepad2_CrossDown,

				Gamepad3_ButtonA,
				Gamepad3_ButtonX,
				Gamepad3_ButtonY,
				Gamepad3_ButtonB,
				Gamepad3_ButtonLB,
				Gamepad3_ButtonRB,
				Gamepad3_ButtonBack,
				Gamepad3_ButtonStart,
				Gamepad3_ButtonL3,
				Gamepad3_ButtonR3,
				Gamepad3_CrossLeft,
				Gamepad3_CrossRight,
				Gamepad3_CrossUp,
				Gamepad3_CrossDown,

				Gamepad4_ButtonA,
				Gamepad4_ButtonX,
				Gamepad4_ButtonY,
				Gamepad4_ButtonB,
				Gamepad4_ButtonLB,
				Gamepad4_ButtonRB,
				Gamepad4_ButtonBack,
				Gamepad4_ButtonStart,
				Gamepad4_ButtonL3,
				Gamepad4_ButtonR3,
				Gamepad4_CrossLeft,
				Gamepad4_CrossRight,
				Gamepad4_CrossUp,
				Gamepad4_CrossDown,
			);

		}
	}
}

typedef ParadigmEngine::NativeInterface::Input::ENativeAxis ENativeAxis;
typedef ENativeAxis EAxisCode;
typedef ParadigmEngine::NativeInterface::Input::ENativeKeyCode ENativeKeyCode;
typedef ENativeKeyCode EKeyCode;
typedef ParadigmEngine::NativeInterface::Input::ENativeCursorCaptureMode ENativeCursorCaptureMode;
typedef ENativeCursorCaptureMode ECursorCaptureMode;
typedef ParadigmEngine::NativeInterface::Input::ENativeInputDeviceType ENativeInputDeviceType;
typedef ENativeInputDeviceType EInputDeviceType;

#endif