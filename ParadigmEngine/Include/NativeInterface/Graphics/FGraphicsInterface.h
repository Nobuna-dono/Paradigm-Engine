#ifndef _FGRAPHICSINTERFACE_H_
#define _FGRAPHICSINTERFACE_H_

#include <ParadigmKeyword.h>

#ifdef PARADIGM_NATIVE_GRAPHICS_DIRECT3D11
#include <NativeInterface/Graphics/FD3D11Interface.h>
#endif

namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Graphics
		{
			static IDynamicGraphicsInterface* GetNativeGraphics(FString _config)
			{
				if (_config == "DIRECT3D11")
					return new FD3D11Interface();
				else
					return nullptr;
			}
		}
	}
}

#define PARADIGM_NATIVE_GRAPHICS(Config) ParadigmEngine::NativeInterface::Graphics::GetNativeGraphics(Config)
typedef ParadigmEngine::NativeInterface::Graphics::IDynamicGraphicsInterface* FGraphicsInterface;


#endif