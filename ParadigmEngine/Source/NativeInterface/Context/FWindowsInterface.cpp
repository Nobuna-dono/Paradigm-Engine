#include <NativeInterface/Context/FWindowsInterface.h>
#include <ParadigmDebug.h>

namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Context
		{
			////////////////////////////////////////////////
			// PIPELINE MODULES
			//____________________________________	
			void FWindowsInterface::Initialize()
			{
				m_Contexts.Reserve(VIEWPORT_EDITOR +1);
				for (uint i = 0; i < (uint)VIEWPORT_EDITOR + 1; ++i)
				{
					m_AvailableViewports[i] = true;
					m_Contexts.Add({});
				}
			}

			bool FWindowsInterface::Update()
			{
				MSG msg;
				if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}

				for (auto it = m_Contexts.Begin(); it != m_Contexts.End(); ++it)
				{
					if ((*it).Handle && (*it).bForeground)
						ShowWindow((HWND)(*it).Handle, SW_SHOWNA);
				}

				// if a window is close, check all context and update the handle
				if (msg.message == WM_QUIT)
				{
					m_ActiveContext = 0;
					for (uint i = 0; i < m_Contexts.Count(); ++i)
					{
						if (IsWindow((HWND)m_Contexts[i].Handle))
							++m_ActiveContext;
						else
						{
							m_AvailableViewports[i] = true;
							m_Contexts[i].Handle = nullptr;
						}
					}
				}

				if (m_ActiveContext == 0)
					return false;

				return true;
			}


			void FWindowsInterface::Terminate()
			{
				for (TArray<UDynamicContextAttributes>::Iterator it = m_Contexts.Begin(); it != m_Contexts.End(); ++it)
					DestroyContext(*it);

				m_Instance = nullptr;

				m_Contexts.Clear();
			}

			////////////////////////////////////////////////
			// FUNCTIONALITY
			//____________________________________			
			void FWindowsInterface::LinkContext(ETargetViewport _target, void* _handle)
			{
				if (!_handle)
					return;

				uint target = (uint)_target < ENativeTargetViewport::VIEWPORT_EDITOR + 1 ? (uint)_target : 0;
				
				if (m_Contexts[target].Handle)
					DestroyContext(m_Contexts[target]);
				UDynamicContextAttributes& windowInterfaceDesc = m_Contexts[target];
				windowInterfaceDesc.Handle = _handle;
				windowInterfaceDesc.bGuestHandle = true;

				++m_ActiveContext;
				m_AvailableViewports[target] = false;
			}


			void FWindowsInterface::CreateContext(ETargetViewport _target, UDynamicContextAttributes _contextDescriptor)
			{
				uint target = (uint)_target < ENativeTargetViewport::VIEWPORT_EDITOR + 1 ? (uint)_target : 0;

				WNDCLASSEX wc;
				DEVMODE dmScreenSettings;
				FString className = "PARADIGM_CONTEXT" + FString::ToString(_target);
				//int windowInterface.PositionX, windowInterface.PositionY;

				ZeroMemory(&wc, sizeof(WNDCLASSEX));

				UDynamicContextAttributes& windowInterfaceDesc = m_Contexts[target];

				if (windowInterfaceDesc.Handle)
					DestroyContext(windowInterfaceDesc);

				// Get some application informations from WidowsUser service
				m_Instance = GetModuleHandle(0);
				UContextDimension systemMetrics = { (uint)GetSystemMetrics(SM_CXSCREEN), (uint)GetSystemMetrics(SM_CYSCREEN) };

				// Window class configuration
				// https://msdn.microsoft.com/en-us/library/windows/desktop/ms632600(v=vs.85).aspx
				windowInterfaceDesc.Name = _contextDescriptor.Name;
				wc.style = 0;
				wc.lpfnWndProc = WindowsProcedure;
				wc.cbClsExtra = 0;
				wc.cbWndExtra = 0;
				wc.hInstance = m_Instance;
				wc.hIcon = LoadIcon(m_Instance, PARADIGM_WINDOW_ICON); //static_cast<HICON>(LoadImage(windowInterface.Instance, PARADIGM_WINDOW_ICON, IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_SHARED | LR_DEFAULTSIZE)); 
				wc.hIconSm = wc.hIcon;
				wc.hCursor = LoadCursor(0, IDC_ARROW);
				wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH + target);
				wc.lpszMenuName = 0;
				wc.lpszClassName = className;
				wc.cbSize = sizeof(WNDCLASSEX);

				RegisterClassEx(&wc);

				if (_contextDescriptor.ResolutionMode == ENativeResolutionMode::NAT_FULLSCREEN)
				{
					windowInterfaceDesc.Dimension = systemMetrics;
					windowInterfaceDesc.Resolution = _contextDescriptor.Resolution;

					memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
					dmScreenSettings.dmSize = sizeof(dmScreenSettings);
					dmScreenSettings.dmPelsWidth = windowInterfaceDesc.Dimension.Width;
					dmScreenSettings.dmPelsHeight = windowInterfaceDesc.Dimension.Height;
					dmScreenSettings.dmBitsPerPel = 32;
					dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

					ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

					// Set the Initial position of the window
					windowInterfaceDesc.PositionX = windowInterfaceDesc.PositionY = 0;

					// Create the window in fullscreen mode					
					windowInterfaceDesc.Handle = CreateWindowEx(WS_EX_APPWINDOW, wc.lpszClassName, windowInterfaceDesc.Name,
						WS_POPUPWINDOW, windowInterfaceDesc.PositionX, windowInterfaceDesc.PositionY,
						windowInterfaceDesc.Dimension.Width, windowInterfaceDesc.Dimension.Height,
						0, 0, m_Instance, 0);
				}
				else
				{
					// Dimension Settings
					windowInterfaceDesc.Dimension = _contextDescriptor.Dimension;

					if (!windowInterfaceDesc.Dimension.Width && !windowInterfaceDesc.Dimension.Height)
						windowInterfaceDesc.Dimension = { (uint)(_contextDescriptor.Resolution & 0xFFFF0000) >> 16, (uint)_contextDescriptor.Resolution & 0xFFFF };

					if (windowInterfaceDesc.Dimension.Width > systemMetrics.Width)
						windowInterfaceDesc.Dimension.Width = systemMetrics.Width;
					if (windowInterfaceDesc.Dimension.Height > systemMetrics.Height)
						windowInterfaceDesc.Dimension.Height = systemMetrics.Height;

					// Set the Initial position of the window					
					windowInterfaceDesc.PositionX = _contextDescriptor.PositionX < 0 ? (GetSystemMetrics(SM_CXSCREEN) - windowInterfaceDesc.Dimension.Width) / 2 : _contextDescriptor.PositionX;
					windowInterfaceDesc.PositionY = _contextDescriptor.PositionY < 0 ? (GetSystemMetrics(SM_CYSCREEN) - windowInterfaceDesc.Dimension.Height) / 2 : _contextDescriptor.PositionY;

					if (_contextDescriptor.ResolutionMode == ENativeResolutionMode::NAT_BORDER)
					{
						// Create the window in border mode
						windowInterfaceDesc.Handle = CreateWindowEx(WS_EX_APPWINDOW, wc.lpszClassName, windowInterfaceDesc.Name.ToConstChar(),
							WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
							windowInterfaceDesc.PositionX, windowInterfaceDesc.PositionY,
							windowInterfaceDesc.Dimension.Width, windowInterfaceDesc.Dimension.Height,
							0, 0, wc.hInstance, 0);
					}
					else if (_contextDescriptor.ResolutionMode == ENativeResolutionMode::NAT_BORDERLESS)
					{

						// Create the window in borderless mode
						windowInterfaceDesc.Handle = CreateWindowEx(WS_EX_APPWINDOW, wc.lpszClassName, windowInterfaceDesc.Name,
							WS_POPUPWINDOW, windowInterfaceDesc.PositionX, windowInterfaceDesc.PositionY,
							windowInterfaceDesc.Dimension.Width, windowInterfaceDesc.Dimension.Height,
							0, 0, m_Instance, 0);
					}
				}

				if (!windowInterfaceDesc.Handle)
					THROW_PARADIGM_EXCEPTION_NATIVE_IMPLEMENTATION_ERROR("CreateWindowEx failed, GetLastError{" + FString::ToString(GetLastError()) + "}");

				// Display the window and focus on it.
				ShowWindow((HWND)windowInterfaceDesc.Handle, SW_SHOW);
				SetForegroundWindow((HWND)windowInterfaceDesc.Handle);
				SetFocus((HWND)windowInterfaceDesc.Handle);

				// Add new context count
				++m_ActiveContext;
				m_AvailableViewports[target] = false;
				
				windowInterfaceDesc.bForeground = _contextDescriptor.bForeground;
			}



			void FWindowsInterface::CreateContext(ETargetViewport _target, ENativeResolutionMode _resolutionMode, ENativeResolution _resolution)
			{
				UDynamicContextAttributes tmp;
				tmp.Resolution = _resolution;
				tmp.ResolutionMode = _resolutionMode;
				CreateContext(_target);
			}

			void FWindowsInterface::DestroyContext(ETargetViewport _target)
			{
				uint target = (uint)_target < ETargetViewport::VIEWPORT_EDITOR + 1 ? (uint)_target : 0;
				
				if (!m_Contexts[target].bGuestHandle)
				{
					m_AvailableViewports[target] = true;
					DestroyContext(m_Contexts[target]);
				}			
			}

			void FWindowsInterface::DestroyContext(UDynamicContextAttributes& _contextDesc)
			{
				if (_contextDesc.bGuestHandle)
					return;

				SetFocus((HWND)_contextDesc.Handle);

				// Cancel fullscreen stance
				if (_contextDesc.ResolutionMode == ENativeResolutionMode::NAT_FULLSCREEN)
					ChangeDisplaySettings(0, 0);

				// Destroy window
				if(_contextDesc.Handle)
					DestroyWindow((HWND)_contextDesc.Handle);
				_contextDesc.Handle = nullptr;

				// Destroy the instance
				UnregisterClass(_contextDesc.Name, m_Instance);

				m_ActiveContext--;
			}

			const UContextAttributes& FWindowsInterface::GetContextAttributes(ETargetViewport _target)
			{
				uint target = (uint)_target < ETargetViewport::VIEWPORT_EDITOR + 1 ? (uint)_target : 0;

				// Update position
				RECT rect;
				if (GetWindowRect((HWND)m_Contexts[target].Handle, &rect))
				{
					m_Contexts[target].PositionX = rect.left;
					m_Contexts[target].PositionY = rect.top;
					m_Contexts[target].Dimension.Width = rect.right - rect.left;
					m_Contexts[target].Dimension.Height = rect.bottom - rect.top;
				}

				return m_Contexts[target];
			}

			void FWindowsInterface::SetFocusOn(ETargetViewport _target)
			{
				uint target = (uint)_target < ETargetViewport::VIEWPORT_EDITOR + 1 ? (uint)_target : 0;

				SetForegroundWindow((HWND)m_Contexts[target].Handle);
				SetFocus((HWND)m_Contexts[target].Handle);
			}

			bool FWindowsInterface::IsFocusOn(ETargetViewport _target)
			{
				uint target = (uint)_target < ETargetViewport::VIEWPORT_EDITOR + 1 ? (uint)_target : 0;

				if (!m_Contexts[target].Handle)
					return false;

				HWND focus = GetFocus();
				return m_Contexts[target].Handle == focus;
			}

			ETargetViewport FWindowsInterface::GetCurrentFocusOn()
			{
				if (IsFocusOn(m_LastFocusContext))
					return m_LastFocusContext;

				if (!GetFocus())
					return m_LastFocusContext;

				for (uint i = 0; i < VIEWPORT_EDITOR + 1; ++i)
				{
					if (m_Contexts[i].Handle == GetFocus())
						return m_LastFocusContext = ETargetViewport(i);
				}

				return VIEWPORT_0;
			}

			bool FWindowsInterface::IsViewportActive(ETargetViewport _target)
			{
				uint target = (uint)_target;
				if (target > VIEWPORT_EDITOR + 1)
					return false;
				return m_Contexts[target].Handle;
			}

			int FWindowsInterface::AvailableViewport()
			{
				for (uint i = 0; i < ETargetViewport::VIEWPORT_EDITOR + 1; ++i)
				{
					if (m_AvailableViewports[i])
						return i;
				}
				return -1;
			}


			LRESULT CALLBACK WindowsProcedure(HWND _hwnd, UINT _umessage, WPARAM _wparam, LPARAM _lparam)
			{
				switch (_umessage)
				{
					// Check if window must be destroy
					case WM_DESTROY:		
						PostQuitMessage(0);
						return 0;
					// Check if window is close
					case WM_CLOSE:								
						DestroyWindow(_hwnd);
						return 0;
					// Other message from system
					default:					
						return DefWindowProc(_hwnd, _umessage, _wparam, _lparam);
				}
			}

		}
	}
}