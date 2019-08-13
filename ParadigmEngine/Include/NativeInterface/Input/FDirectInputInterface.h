#ifndef _FDIRECTECTINPUTINTERFACE_H_
#define _FDIRECTECTINPUTINTERFACE_H_

#include <Property.h>
#include <IKeyTable.h>

// INPUT
#include <NativeInterface/Input/IDynamicInputInterface.h>
#include <NativeInterface/Input/UDirectInputInterface.h>
// CONTEXT
#include <NativeInterface/Context/NativeContextAttributes.h>

#include <unordered_map>
#include <map>

namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Input
		{	
			class FDirectInputInterface : public IDynamicInputInterface
			{
				public:
					////////////////////////////////////////////////
					// PIPELINE
					//____________________________________	
					void Initialize() override;
					/** Create an input event system for the targeted context according with the devices' mask. (see @EInputDeviceType) */
					void CreateInputSystem(uint _inputDeviceMask = { InputDeviceType_Mouse | InputDeviceType_Keyboard }) override;
					/** Create an input event system for the targeted context according with the devices' mask. (see @EInputDeviceType) */
					void CreateInputSystem(ETargetViewport _target, uint _inputDeviceMask = { InputDeviceType_Mouse | InputDeviceType_Keyboard }) override;
					void Update(ETargetViewport _target = VIEWPORT_0) override;
					void Terminate() override;
					
				public:
					////////////////////////////////////////////////
					// FUNCTIONALITY - MOUSE / GAMEPAD
					//____________________________________	
					void SetActiveCursor(bool _value) override;					
					void SetCursorCaptureMode(ENativeCursorCaptureMode _mode) override;
					void SetCursorCaptureMode(ETargetViewport _target, ENativeCursorCaptureMode _mode) override;

					/** Return the last position of the mouse in pixel. */
					UAxis GetMousePosition() override;
					/** Return the axis value of a given axis. (see @EAxisCode) */
					UAxis GetAxis(EAxisCode _axis) override;
					/** Return the last position of the mouse in pixel. (ReadOnly) */
					UAxis GetAxis(ETargetViewport _target, EAxisCode _value, bool _bnormalize = true) override;
				
				private:
					////////////////////////////////////////////////
					// FUNCTIONALITY - MOUSE
					//____________________________________	
					void ProcessCapture(UDirectInputInterface& out_interface);

				public:
					////////////////////////////////////////////////
					// FUNCTIONALITY - Keyboard
					//____________________________________	
					bool IsKeyDown(EKeyCode _value) override;
					bool IsKeyDown(ETargetViewport _target, EKeyCode _value) override;
					bool IsAnyKeyPressed() override;
					bool IsEscapePressed() override;

				private:
					////////////////////////////////////////////////
					// FUNCTIONALITY - Keyboard
					//____________________________________	
					bool IsGamepadKeyDown(uint _target, uint _gamepad, uint _button);

				private:
					////////////////////////////////////////////////
					// FUNCTIONALITY - DEVICE STATE 
					//____________________________________	
					void TryCoupleMouse(UDirectInputInterface& out_interface, const UContextAttributes& _context);
					void TryCoupleKeyboard(UDirectInputInterface& out_interface, const UContextAttributes& _context);
					void TryCoupleGamepads(UDirectInputInterface& out_interface, const UContextAttributes& _context);
					
					void ScanMouse(UDirectInputInterface& out_interface);
					void ScanKeyboard(UDirectInputInterface& out_interface);
					void ScanGamepads(UDirectInputInterface& out_interface);

				private :
					////////////////////////////////////////////////
					// DATA
					//____________________________________	
					TArray<UDirectInputInterface> m_InterfaceDatas;
					uint m_lastFocusViewport : 31;
					uint m_bCursorActive : 1;
			};
		}
	}
}

#endif