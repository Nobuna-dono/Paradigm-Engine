#ifndef _IDYNAMICINPUTINTERFACE_H_
#define _IDYNAMICINPUTINTERFACE_H_

#include <ParadigmException.h>
#include <NativeInterface/Input/NativeInputAttributes.h>
#include <NativeInterface/Graphics/NativeGraphicsEnums.h>

namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Input
		{
			class IDynamicInputInterface
			{
				public:
					////////////////////////////////////////////////
					// PIPELINE
					//____________________________________	
					virtual void Initialize() = 0;
					/** Create an input event system for the targeted context according with the devices' mask. (see @EInputDeviceType) */
					virtual void CreateInputSystem(uint _inputDeviceMask = { InputDeviceType_Mouse | InputDeviceType_Keyboard }) = 0;
					/** Create an input event system for the targeted context according with the devices' mask. (see @EInputDeviceType) */
					virtual void CreateInputSystem(ETargetViewport _target, uint _inputDeviceMask = { InputDeviceType_Mouse | InputDeviceType_Keyboard }) = 0;
					virtual void Update(ETargetViewport _target = VIEWPORT_0) = 0;
					virtual void Terminate() = 0;

				public:
					////////////////////////////////////////////////
					// FUNCTIONALITY - MOUSE
					//____________________________________	
					/** Display the cursor ? */
					virtual void SetActiveCursor(bool _value)
					{ THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); }
					/** Set type of available device type. You can combine multiple device with the operator '|' (bitwize purpose). */
					virtual void SetCursorCaptureMode(ECursorCaptureMode _mode)
					{ /** Do nothing if no API implementation. */ }
					/** Set type of available device type. You can combine multiple device with the operator '|' (bitwize purpose). */
					virtual void SetCursorCaptureMode(ETargetViewport _target, ECursorCaptureMode _mode)
					{ /** Do nothing if no API implementation. */ }					

					/** Return the last position of the mouse in pixel. */
					virtual UAxis GetMousePosition() = 0;
					/** Return the axis value of a given axis. (see @EAxisCode) */
					virtual UAxis GetAxis(EAxisCode _axis) = 0;
					/** Return the axis value of a given axis. (see @EAxisCode)
					Return{ 0,0 } if the context has no binded input system. */
					virtual UAxis GetAxis(ETargetViewport _target, EAxisCode _axis, bool _bnormalize = true) = 0;

				public:
					////////////////////////////////////////////////
					// FUNCTIONALITY - Keyboard
					//____________________________________	
					virtual bool IsKeyDown(EKeyCode _value) = 0;
					virtual bool IsKeyDown(ETargetViewport _target, EKeyCode _value) = 0;
					virtual bool IsAnyKeyPressed() = 0;
					virtual bool IsEscapePressed() = 0;
			};

		}
	}
}

#endif