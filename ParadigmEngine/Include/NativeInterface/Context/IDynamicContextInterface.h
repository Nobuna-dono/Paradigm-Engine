#ifndef _IDYNAMICWINDOWHANDLERINTERFACE_H_
#define _IDYNAMICWINDOWHANDLERINTERFACE_H_

#include <ParadigmException.h>
#include <NativeInterface/Context/NativeContextAttributes.h>

namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Context
		{
			class IDynamicContextInterface
			{
				public:
					////////////////////////////////////////////////
					// CONSTRUCTOR - DESTRUCTOR
					//____________________________________	

					IDynamicContextInterface() = default;
					virtual ~IDynamicContextInterface() = default;

				public:
					////////////////////////////////////////////////
					// PIPELINE MODULES
					//____________________________________	
					/** Initialize window handler (render window). */
					virtual void Initialize() = 0;
					/** [Engine purpose] */
					virtual bool Update() = 0;
					/** Close the context and free the resources. */
					virtual void Terminate() = 0;

				public:
					////////////////////////////////////////////////
					// FUNCTIONALITY
					//____________________________________
					/** Set link between viewport and existing handle. (Don't use this if you don't know what you do!) */
					virtual void LinkContext(ETargetViewport _target, void* _handle) { THROW_PARADIGM_EXCEPTION_NOT_IMPLEMENTED_ERROR(""); };

					/** Create a window according to attributes. */
					virtual void CreateContext(ETargetViewport _target, UDynamicContextAttributes _contextDescriptor = {}) = 0;
					/** Create a window according to attributes. (Shortcut) */
					virtual void CreateContext(ETargetViewport _target, ENativeResolutionMode _resolutionMode, ENativeResolution _resolution) = 0;
					/** Destroy the registered's context. Do nothing if invalid key. */
					virtual void DestroyContext(ETargetViewport _target) = 0;
					
					/** Fill @out_attribute with the first native context. Primaly usefull for the engine initialization. */
					//virtual void GetNativeContextAttributes(UDynamicContextAttributes& out_attribute) = 0;
					/** Get a context information from the register key. An invalid regist will throw an exception. */
					virtual const UContextAttributes& GetContextAttributes(ETargetViewport _target = VIEWPORT_0) = 0;

					/** Allow to set foreground and focus on the targeted viewport. */
					virtual void SetFocusOn(ETargetViewport _target) {};
					/** Is _target the current focus on ? */
					virtual bool IsFocusOn(ETargetViewport _target) { return true; };
					/** Return the current focused viewport. Also return VIEWPORT_0 if no focus found. */
					virtual ETargetViewport GetCurrentFocusOn() { return ETargetViewport (1); };
					
					/** Return if the viewport is active (and enable to render or to receive input). */
					virtual bool IsViewportActive(ETargetViewport _target) = 0;

					/** Return an integer between 0 and 8 (corresponding to VIEWPORT_0 to VIEWPORT_EDITOR).
					If no one is available, return -1. */
					virtual int AvailableViewport() = 0;
			};
		}
	}
}

#endif //_FDYNAMICWINDOWHANDLERINTERFACE_H_