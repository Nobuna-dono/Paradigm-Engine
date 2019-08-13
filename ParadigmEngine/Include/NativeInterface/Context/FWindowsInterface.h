#ifndef _FWINDOWSINTERFACE_H_
#define _FWINDOWSINTERFACE_H_

#include <windows.h>

#include <TArray.h>
#include <NativeInterface/Context/IDynamicContextInterface.h>

#ifdef PARADIGM_WINDOW_ICON 
#undef PARADIGM_WINDOW_ICON
#define PARADIGM_WINDOW_ICON MAKEINTRESOURCE(104)
#endif

namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Context
		{	
			class FWindowsInterface : public IDynamicContextInterface
			{
				public:
					////////////////////////////////////////////////
					// CONSTRUCTOR - DESTRUCTOR
					//____________________________________	

					FWindowsInterface() = default;
					~FWindowsInterface() = default;

				public:
					////////////////////////////////////////////////
					// PIPELINE MODULES
					//____________________________________	
					/** Initialize window handler (render window). */
					void Initialize() override;
					/** Close the context and free the resources. */
					bool Update() override;
					/** Close the context and free the resources. */
					void Terminate() override;

				public:
					////////////////////////////////////////////////
					// FUNCTIONALITY
					//____________________________________				
					/** Set link between viewport and existing handle. (Don't use this if you don't know what you do!) */
					void LinkContext(ETargetViewport _target, void* _handle) override;

					/** Create a window according to attributes. If the targeted viewport already exist, override it.*/
					void CreateContext(ETargetViewport _target, UDynamicContextAttributes _contextDescriptor = {}) override;
					/** Create a window according to attributes. If the targeted viewport already exist, override it.(Shortcut) */
					void CreateContext(ETargetViewport _target, ENativeResolutionMode _resolutionMode, ENativeResolution _resolution) override;
					/** Destroy the registered's context. Do nothing if invalid key. */
					void DestroyContext(ETargetViewport _target) override;					
					
					/** Fill @out_attribute with the first native context. Primaly usefull for the engine initialization. */
					//void GetNativeContextAttributes(UDynamicContextAttributes& out_attribute) override;
					/** Get a context information from the register key. An invalid regist will throw an exception. */
					const UContextAttributes& GetContextAttributes(ETargetViewport _target = VIEWPORT_0) override;
					
					/** Allow to set foreground and focus on the targeted viewport. */
					void SetFocusOn(ETargetViewport _target) override;
					/** Is _target the current focus on ? */
					bool IsFocusOn(ETargetViewport _target) override;					
					/** Return the current focused viewport. */
					ETargetViewport GetCurrentFocusOn() override;

					/** Return if the viewport is active (and enable to render or to receive input). */
					bool IsViewportActive(ETargetViewport _target) override;

					/** Return an integer between 0 and 8 (corresponding to VIEWPORT_0 to VIEWPORT_EDITOR). 
					If no one is available, return -1. */
					int AvailableViewport() override;

				private:
					/** Destroy the context. */
					void DestroyContext(UDynamicContextAttributes& _context);

				private:
					////////////////////////////////////////////////
					// DATA
					//____________________________________						
					TArray<UDynamicContextAttributes> m_Contexts;
					HINSTANCE m_Instance;
					ETargetViewport m_LastFocusContext;
					uint m_ActiveContext : 31;
					uint m_bOutadatedContext : 1;					
					bool m_AvailableViewports[8];
			};
			static LRESULT CALLBACK WindowsProcedure(HWND, UINT, WPARAM, LPARAM);
		}
	}
}
typedef ParadigmEngine::NativeInterface::Context::FWindowsInterface FWindowsInterface;

#endif //_FWINDOWSINTERFACE_H_