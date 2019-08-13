#ifndef _FINPUTINTERFACE_H_
#define _FINPUTINTERFACE_H_

#include <ParadigmKeyword.h>
#include <NativeInterface/Input/FDirectInputInterface.h>

#ifdef PARADIGM_NATIVE_INPUT_DIRECTINPUT
#include <NativeInterface/Input/FDirectInputInterface.h>
#endif

namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Input
		{
			static IDynamicInputInterface* GetNativeInputInterface(FString _config)
			{
				if (_config == "DIRECTINPUT")
					return new FDirectInputInterface();
				else
					return nullptr;
			}
		}
	}
}

#define PARADIGM_NATIVE_INPUT(Config) ParadigmEngine::NativeInterface::Input::GetNativeInputInterface(Config)
typedef ParadigmEngine::NativeInterface::Input::IDynamicInputInterface* FInputInterface;

#endif