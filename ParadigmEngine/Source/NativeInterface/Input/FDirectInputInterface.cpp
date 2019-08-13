#include <NativeInterface/Input/FDirectInputInterface.h>
#include <Core/Serialization/FEnumerator.h>
#include <FParadigmEngine.h>


namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Input
		{

#define _NAT_KEYDOWN(name, key) (name[key] & 0x80)

			////////////////////////////////////////////////
			// CALLBACK
			//____________________________________	
			BOOL CALLBACK DIEnumDevicesCallback(LPCDIDEVICEINSTANCE _instance, LPVOID _refInterface)
			{
				if (_refInterface != nullptr)
				{
					UDirectInputInterface* DIInterface = static_cast<UDirectInputInterface*>(_refInterface);
					DIInterface->Gamepads.Add({});
					DIInterface->DirectInput->CreateDevice(_instance->guidInstance, &DIInterface->Gamepads.Back().Device, 0);
				}
				return DIENUM_CONTINUE;
			}

			////////////////////////////////////////////////
			// PIPELINE
			//____________________________________	
			void FDirectInputInterface::Initialize()
			{
				// Reserve for the number of viewport
				m_InterfaceDatas.Reserve(VIEWPORT_EDITOR + 1);
				for (uint i = 0; i < 8 + 1; ++i)
					m_InterfaceDatas.Add({});
				
				m_bCursorActive = true;
			}

			void FDirectInputInterface::CreateInputSystem(uint _inputDeviceMask)
			{
				/** Get the first context*/
				CreateInputSystem(ETargetViewport::VIEWPORT_0, _inputDeviceMask);
			}

			void FDirectInputInterface::CreateInputSystem(ETargetViewport _target, uint _inputDeviceMask)
			{				
				const UContextAttributes& context = PARADIGM_CONTEXT->GetContextAttributes(_target);
				
				uint target = (uint)_target < ETargetViewport::VIEWPORT_EDITOR + 1 ? (uint)_target : 0;				
				// DIRECTINPUT
				if (FAILED(DirectInput8Create(GetModuleHandle(0), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_InterfaceDatas[target].DirectInput, 0)))
				{
					THROW_PARADIGM_EXCEPTION("Failed to create direct input device.");
					PARADIGM_CRITICAL_MESSAGE((HWND)context.Handle, "Failed to init direct input device.", "ParadigmError");
				}

				m_InterfaceDatas[target].TargetViewport = ETargetViewport(target);
				m_InterfaceDatas[target].InputDeviceMask = _inputDeviceMask;
				TryCoupleMouse(m_InterfaceDatas[target], context);
				TryCoupleKeyboard(m_InterfaceDatas[target], context);
				TryCoupleGamepads(m_InterfaceDatas[target], context);
			}

			void FDirectInputInterface::Update(ETargetViewport _target)
			{
				m_lastFocusViewport = _target;
				
				if (!m_InterfaceDatas[_target].InputDeviceMask)
					return;

				if (m_InterfaceDatas[_target].InputDeviceMask & EInputDeviceType::InputDeviceType_Mouse)
				{
					ScanMouse(m_InterfaceDatas[_target]);
					ProcessCapture(m_InterfaceDatas[_target]);
				}
				if (m_InterfaceDatas[_target].InputDeviceMask & EInputDeviceType::InputDeviceType_Keyboard)
					ScanKeyboard(m_InterfaceDatas[_target]);
				ScanGamepads(m_InterfaceDatas[_target]);
			}
			

			void FDirectInputInterface::Terminate()
			{
				for (TArray<UDirectInputInterface>::Iterator it = m_InterfaceDatas.Begin(); it != m_InterfaceDatas.End(); ++it)
				{
					if ((*it).Mouse.Device)
					{
						(*it).Mouse.Device->Release();
						(*it).Mouse.Device = nullptr;
					}
					if ((*it).Keyboard.Device)
					{
						(*it).Keyboard.Device->Release();
						(*it).Keyboard.Device = nullptr;
					}
					for (TArray<UGamepadDevice>::Iterator itgamepad = (*it).Gamepads.Begin(); itgamepad != (*it).Gamepads.End(); ++itgamepad)
					{
						if ((*itgamepad).Device)
						{
							(*itgamepad).Device->Release();
							(*itgamepad).Device = nullptr;
						}
					}
				}
			}

			////////////////////////////////////////////////
			// FUNCTIONALITY - MOUSE / GAMEPAD
			//____________________________________	
			void FDirectInputInterface::SetActiveCursor(bool _value)
			{
				if (m_bCursorActive != _value)
				{
					m_bCursorActive = _value;
					ShowCursor(_value);
				}
			}

			void FDirectInputInterface::SetCursorCaptureMode(ENativeCursorCaptureMode _mode)
			{				
				m_InterfaceDatas[0].Mouse.MouseCaptureMode = _mode;
			}

			void FDirectInputInterface::SetCursorCaptureMode(ETargetViewport _target, ENativeCursorCaptureMode _mode)
			{
				if((uint)_target < m_InterfaceDatas.Count())
					m_InterfaceDatas[(uint)_target].Mouse.MouseCaptureMode = _mode;
			}

			void FDirectInputInterface::ProcessCapture(UDirectInputInterface& out_interface)
			{
				// Update the location of the mouse cursor based on the change of the mouse location during the frame
				out_interface.Mouse.Axis.X += out_interface.Mouse.State.lX;
				out_interface.Mouse.Axis.Y += out_interface.Mouse.State.lY;
			
				const UContextAttributes& context = PARADIGM_CONTEXT->GetContextAttributes(out_interface.TargetViewport);
				
				switch (out_interface.Mouse.MouseCaptureMode)
				{
				case ENativeCursorCaptureMode::MouseCaptureMode_Free:
					break;

					case MouseCaptureMode_Locked:
					SetCursorPos(context.PositionX + (context.Dimension.Width / 2), context.PositionY + (context.Dimension.Height / 2));
					break;

					case MouseCaptureMode_FreeBorder:
						if (out_interface.Mouse.Axis.X < 0)
							out_interface.Mouse.Axis.X = context.Dimension.Width;
						else if (out_interface.Mouse.Axis.X > context.Dimension.Width)
							out_interface.Mouse.Axis.X = 0;

						if (out_interface.Mouse.Axis.Y < 0)
							out_interface.Mouse.Axis.Y = context.Dimension.Height;
						else if (out_interface.Mouse.Axis.Y > context.Dimension.Height)
							out_interface.Mouse.Axis.Y = 0;
						SetCursorPos(out_interface.Mouse.Axis.X + context.PositionX, out_interface.Mouse.Axis.Y + context.PositionY);
						break;

					case MouseCaptureMode_LockedBorder:
						if (out_interface.Mouse.Axis.X < 0)
							out_interface.Mouse.Axis.X = 0;
						else if (out_interface.Mouse.Axis.X > context.Dimension.Width)
						out_interface.Mouse.Axis.X = context.Dimension.Width;

						if (out_interface.Mouse.Axis.Y < 0)
							out_interface.Mouse.Axis.Y = 0;
						else if (out_interface.Mouse.Axis.Y > context.Dimension.Height)
							out_interface.Mouse.Axis.Y = context.Dimension.Height;
						SetCursorPos(out_interface.Mouse.Axis.X + context.PositionX, out_interface.Mouse.Axis.Y + context.PositionY);
						break;

					default:
					break;
				}
			}

			UAxis FDirectInputInterface::GetMousePosition()
			{
				return m_InterfaceDatas[0].Mouse.Axis;
			}

			UAxis FDirectInputInterface::GetAxis(EAxisCode _value)
			{
				return GetAxis(ETargetViewport::VIEWPORT_0, _value);
			}

			/** Return the last position of the mouse in pixel. (ReadOnly) */
			UAxis FDirectInputInterface::GetAxis(ETargetViewport _target, EAxisCode _value, bool _bnormalize)
			{
				UAxis axis{ 0,0 };
				
				const UContextAttributes& attrib = PARADIGM_CONTEXT->GetContextAttributes(_target);
				
				/** From now, I'll only take care of the first context. */
				if ((uint)_target >= m_InterfaceDatas.Count())
					return axis;

				UDirectInputInterface& it = m_InterfaceDatas[(uint)_target];

				switch (_value)
				{
					case EAxisCode::Mouse:
						if (!_bnormalize)
							axis = it.Mouse.Axis;
						else
						{
							float x = (it.Mouse.Axis.X / attrib.Dimension.Width);
							axis.X = (x * 0.5f) + 0.5f;
							float y = (it.Mouse.Axis.Y / attrib.Dimension.Height);
							axis.Y = (y * 0.5f) + 0.5f;
						}
						break;

					case EAxisCode::Gamepad_LeftStick:
						for (uint i = 0; i < it.Gamepads.Count(); ++i)
						{
							axis = it.Gamepads[i].LeftStick;
							if (axis.X || axis.Y)
								break;
						}
						break;
					case EAxisCode::Gamepad_RightStick:
						for (uint i = 0; i < it.Gamepads.Count(); ++i)
						{
							axis = it.Gamepads[i].RightStick;
							if (axis.X || axis.Y)
								break;
						}
						break;
					case EAxisCode::Gamepad_Trigger:
						for (uint i = 0; i < it.Gamepads.Count(); ++i)
						{
							axis = it.Gamepads[i].Trigger;
							if (axis.X || axis.Y)
								break;
						}
						break;

					case EAxisCode::Gamepad1_LeftStick:
						if (it.Gamepads.Count())
							axis = it.Gamepads[0].LeftStick;
						break;
					case EAxisCode::Gamepad1_RightStick:
						if (it.Gamepads.Count())
							axis = it.Gamepads[0].RightStick;
						break;
					case EAxisCode::Gamepad1_Trigger:
						if (it.Gamepads.Count())
							axis = it.Gamepads[0].Trigger;
						break;

					case EAxisCode::Gamepad2_LeftStick:
						if (it.Gamepads.Count() >= 2)
							axis = it.Gamepads[1].LeftStick;
						break;
					case EAxisCode::Gamepad2_RightStick:
						if (it.Gamepads.Count() >= 2)
							axis = it.Gamepads[1].RightStick;
						break;
					case EAxisCode::Gamepad2_Trigger:
						if (it.Gamepads.Count() >= 2)
							axis = it.Gamepads[1].Trigger;
						break;

					case EAxisCode::Gamepad3_LeftStick:
						if (it.Gamepads.Count() >= 3)
							axis = it.Gamepads[2].LeftStick;
						break;
					case EAxisCode::Gamepad3_RightStick:
						if (it.Gamepads.Count() >= 3)
							axis = it.Gamepads[2].RightStick;
						break;
					case EAxisCode::Gamepad3_Trigger:
						if (it.Gamepads.Count() >= 3)
							axis = it.Gamepads[2].Trigger;
						break;

					case EAxisCode::Gamepad4_LeftStick:
						if (it.Gamepads.Count() >= 4)
							axis = it.Gamepads[3].LeftStick;
						break;
					case EAxisCode::Gamepad4_RightStick:
						if (it.Gamepads.Count() >= 4)
							axis = it.Gamepads[3].RightStick;
						break;
					case EAxisCode::Gamepad4_Trigger:
						if (it.Gamepads.Count() >= 4)
							axis = it.Gamepads[3].Trigger;
						break;

					default:
						break;
				}			
				return axis;
			}

			////////////////////////////////////////////////
			// FUNCTIONALITY - Keyboard
			//____________________________________	
			bool FDirectInputInterface::IsKeyDown(EKeyCode _value)
			{				
				ETargetViewport target = PARADIGM_CONTEXT->GetCurrentFocusOn();
				//if (target != m_lastFocusViewport)
					//Update(target);
				return IsKeyDown(target, _value);
			}
			
			bool FDirectInputInterface::IsKeyDown(ETargetViewport _target, EKeyCode _value)
			{
				uint target = (uint)_target < m_InterfaceDatas.Count() ? (uint)_target : 0;
				if (_value <= EKeyCode::Power)
				{
					/** From now, I'll only take care of the first context. */
					return _NAT_KEYDOWN(m_InterfaceDatas[target].Keyboard.State, ToDirectInputKeyCode(_value));
				}
				else
				{
					if (_value >= Mouse_LeftClick && _value < Gamepad_ButtonA)
					{
						switch (_value)
						{
							case Mouse_LeftClick:
								return m_InterfaceDatas[target].Mouse.State.rgbButtons[0];
							case Mouse_RightClick:
								return m_InterfaceDatas[target].Mouse.State.rgbButtons[1];
							case Mouse_WheelClick:
								return m_InterfaceDatas[target].Mouse.State.rgbButtons[2];
							default: 
								break;
						}						
					}
					else if (_value >= Gamepad_ButtonA && _value < Gamepad1_ButtonA)
					{
						// 4 is the maximum number of gamepad
						for (uint i = 0; i < 4; ++i)
						{
							uint button = (_value + 13) - (Gamepad_ButtonA + (i * 13));
							return IsGamepadKeyDown(ETargetViewport::VIEWPORT_0, i, button);
						}
					}
					else if (_value >= Gamepad1_ButtonA)
					{
						uint gamepad = (_value - Gamepad1_ButtonA) / 13; // get the entire part to know which gamepad get
						uint button = _value - (Gamepad1_ButtonA + (gamepad * 13));
						return IsGamepadKeyDown(target, gamepad, button);
					}
				}
				return false;
			}

			bool FDirectInputInterface::IsAnyKeyPressed()
			{
				for(uint i = 0; i < ENativeKeyCode::Power; ++i)
					if (m_InterfaceDatas[0].Keyboard.State[ToDirectInputKeyCode((ENativeKeyCode)i)])
					{						
						FPrint::Print("KeyDown : ["+ FEnumerator<ENativeKeyCode, ENUMERATOR_TYPE(ENativeKeyCode)>::ToString((ENativeKeyCode)i) +"]");
						return true;
					}
				return false;
			}

			bool FDirectInputInterface::IsEscapePressed()
			{				
				return _NAT_KEYDOWN(m_InterfaceDatas[0].Keyboard.State, ToDirectInputKeyCode(ENativeKeyCode::Escape));
			}

			bool FDirectInputInterface::IsGamepadKeyDown(uint _target, uint _gamepad, uint _button)
			{
				DIJOYSTATE2& state = m_InterfaceDatas[_target].Gamepads[_gamepad].State;
				switch (_button)
				{
				case 0: //A
					return state.rgbButtons[0];
				case 1: //X
					return state.rgbButtons[2];
				case 2: //Y
					return state.rgbButtons[3];
				case 3: //B
					return state.rgbButtons[1];
				case 4: //LB
					return state.rgbButtons[4];
				case 5: //RB
					return state.rgbButtons[5];
				case 6: //Back
					return state.rgbButtons[6];
				case 7: //Start
					return state.rgbButtons[7];
				case 8: //L3
					return state.rgbButtons[8];
				case 9: //R3
					return state.rgbButtons[9];
				case 10: //Crossleft
					return state.rgdwPOV[0] >= 22500;
				case 11: //CrossRight
					return state.rgdwPOV[0] >= 4500 && state.rgdwPOV[0] <= 13500;
				case 12: //CrossUp
					return state.rgdwPOV[0] >= 13500 && state.rgdwPOV[0] <= 22500;
				case 13: //CrossDown
					return state.rgdwPOV[0] == 0 || state.rgdwPOV[0] == 4500 || state.rgdwPOV[0] == 31500;
				default:
					break;
				}
				return false;
			}




			////////////////////////////////////////////////
			// FUNCTIONALITY - DEVICE STATE 
			//____________________________________	
			void FDirectInputInterface::TryCoupleKeyboard(UDirectInputInterface& out_interface, const UContextAttributes& _context)
			{
				out_interface.DirectInput->CreateDevice(GUID_SysKeyboard, &out_interface.Keyboard.Device, 0);
				out_interface.Keyboard.Device->SetDataFormat(&c_dfDIKeyboard);
				out_interface.Keyboard.Device->SetCooperativeLevel((HWND)_context.Handle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE /*| DISCL_NOWINKEY*/);
				out_interface.Keyboard.Device->Acquire();
			}

			void FDirectInputInterface::TryCoupleMouse(UDirectInputInterface& out_interface, const UContextAttributes& _context)
			{
				out_interface.DirectInput->CreateDevice(GUID_SysMouse, &out_interface.Mouse.Device, 0);
				out_interface.Mouse.Device->SetDataFormat(&c_dfDIMouse);
				out_interface.Mouse.Device->SetCooperativeLevel((HWND)_context.Handle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
				out_interface.Mouse.Device->Acquire();
			}
			void FDirectInputInterface::TryCoupleGamepads(UDirectInputInterface& out_interface, const UContextAttributes& _context)
			{
				out_interface.DirectInput->EnumDevices(DI8DEVCLASS_GAMECTRL, DIEnumDevicesCallback, (void*)&out_interface, DIEDFL_ALLDEVICES);
				for (TArray<UGamepadDevice>::Iterator it = out_interface.Gamepads.Begin(); it != out_interface.Gamepads.End(); ++it)
				{
					if ((*it).Device)
					{
						(*it).Device->SetDataFormat(&c_dfDIJoystick2);
						(*it).Device->Acquire();
					}
				}
			}

			void FDirectInputInterface::ScanKeyboard(UDirectInputInterface& out_interface)
			{
				HRESULT result;
				if (FAILED(result = out_interface.Keyboard.Device->GetDeviceState(sizeof(out_interface.Keyboard.State), (LPVOID)&out_interface.Keyboard.State)))
				{
					//if the keyboard lost focus or was not acquired then try to get control back
					if ((result == DIERR_INPUTLOST) || result == DIERR_NOTACQUIRED)
						out_interface.Keyboard.Device->Acquire();
					else
						TryCoupleKeyboard(out_interface, PARADIGM_CONTEXT->GetContextAttributes(out_interface.TargetViewport));
				}

			}
			void FDirectInputInterface::ScanMouse(UDirectInputInterface& out_interface)
			{
				HRESULT result;
				if (FAILED(result = out_interface.Mouse.Device->GetDeviceState(sizeof(out_interface.Mouse.State), (LPVOID)&out_interface.Mouse.State)))
				{
					//if the keyboard lost focus or was not acquired then try to get control back
					if ((result == DIERR_INPUTLOST) || result == DIERR_NOTACQUIRED)
						out_interface.Mouse.Device->Acquire();
					else
						TryCoupleMouse(out_interface, PARADIGM_CONTEXT->GetContextAttributes(out_interface.TargetViewport));
				}
			}
			void FDirectInputInterface::ScanGamepads(UDirectInputInterface& out_interface)
			{
				if (out_interface.InputDeviceMask >= EInputDeviceType::InputDeviceType_Gamepad1)
				{
					for (TArray<UGamepadDevice>::Iterator it = out_interface.Gamepads.Begin(); it != out_interface.Gamepads.End(); ++it)
					{
						if ((*it).Device)
						{
							HRESULT result = (*it).Device->GetDeviceState(sizeof((*it).State), (LPVOID)&(*it).State);
							if (FAILED(result))
								TryCoupleGamepads(out_interface, PARADIGM_CONTEXT->GetContextAttributes(out_interface.TargetViewport));
						}
						else
						{
							//GetControllerAxes
							(*it).RightStick.X = (*it).State.lX - 32767;
							(*it).RightStick.Y = (*it).State.lY - 32767;
						}
					}
				}
			}

		}
	}
}

//void InputClass::GetMouseLocation(int& _outMouseX, int& _outMouseY)
//{
//	_outMouseX = m_mouseX;
//	_outMouseY = m_mouseY;
//}

//void InputClass::GetXboxControllerState(InputsDataXboxController& _outData)
//{
//    /* XBoxController */
//if (!m_Controller)
//return;
//
//_outData.LeftStick.X = m_JoypadState.lX - 32767; // LeftJoystick X axis [-32727, 32727]
//if (abs(_outData.LeftStick.X) < 5000)
//	_outData.LeftStick.X = 0;
//_outData.LeftStick.Y = -(m_JoypadState.lY - 32767); // LeftJoystick Y axis [-32727, 32727]
//if (abs(_outData.LeftStick.Y) < 5000)
//	_outData.LeftStick.Y = 0;
//
//_outData.RightStick.X = m_JoypadState.lRx - 32767; // RightJoystick X axis [-32727, 32727]
//if (abs(_outData.RightStick.X) < 5000)
//	_outData.RightStick.X = 0;
//_outData.RightStick.Y = m_JoypadState.lRy - 32767; // RightJoystick Y axis [-32727, 32727]
//if (abs(_outData.RightStick.Y) < 5000)
//	_outData.RightStick.Y = 0;
//
//// if(+) : LeftTrigger [0,32727] | if(-) : RightTrigger [-32727,0]
//_outData.Trigger.X = m_JoypadState.lZ; //- 32767;	
//_outData.Trigger.Y = m_JoypadState.lRz; //- 32767;	
//
//_outData.A = m_JoypadState.rgbButtons[0]; //XboxController : A
//_outData.B = m_JoypadState.rgbButtons[1]; //XboxController : B
//_outData.X = m_JoypadState.rgbButtons[2]; //XboxController : X
//_outData.Y = m_JoypadState.rgbButtons[3]; //XboxController : Y
//_outData.LB = m_JoypadState.rgbButtons[4]; //XboxController : LB
//_outData.RB = m_JoypadState.rgbButtons[5]; //XboxController : RB
//_outData.Back = m_JoypadState.rgbButtons[6]; //XboxController : Back
//_outData.Start = m_JoypadState.rgbButtons[7]; //XboxController : Start
//_outData.LJoyB = m_JoypadState.rgbButtons[8]; //XboxController : LJoyB
//_outData.RJoyB = m_JoypadState.rgbButtons[9]; //XboxController : RJoyB
//
//switch (m_JoypadState.rgdwPOV[0])
//{
//case 0:		_outData.Cross.X = 0;	_outData.Cross.Y = -1; 	break;
//case 4500:	_outData.Cross.X = 1;	_outData.Cross.Y = -1; 	break;
//case 9000:	_outData.Cross.X = 1;	_outData.Cross.Y = 0;	break;
//case 13500:	_outData.Cross.X = 1;	_outData.Cross.Y = 1;	break;
//case 18000:	_outData.Cross.X = 0;	_outData.Cross.Y = 1;	break;
//case 22500:	_outData.Cross.X = -1;	_outData.Cross.Y = 1;	break;
//case 27000:	_outData.Cross.X = -1;	_outData.Cross.Y = 0;	break;
//case 31500:	_outData.Cross.X = -1;	_outData.Cross.Y = -1;	break;
//default:	_outData.Cross.X = 0;	_outData.Cross.Y = 0;	break;
//}
//
//}