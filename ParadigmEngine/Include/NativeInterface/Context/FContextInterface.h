#ifndef _FCONTEXTITNERFACE_H_
#define _FCONTEXTITNERFACE_H_

#include <ParadigmKeyword.h>
#include <FString.h>

#ifdef PARADIGM_NATIVE_CONTEXT_WINDOWS
#include <NativeInterface/Context/FWindowsInterface.h>
#endif

namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Context
		{
			static IDynamicContextInterface* GetNativeContext(FString _config)
			{
				if (_config == "WINDOWS")
					return new FWindowsInterface();
				else
					return nullptr;
			}
		}
	}
}

#define PARADIGM_NATIVE_CONTEXT(Config) ParadigmEngine::NativeInterface::Context::GetNativeContext(Config)
typedef ParadigmEngine::NativeInterface::Context::IDynamicContextInterface* FContextInterface;

#endif