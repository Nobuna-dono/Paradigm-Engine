#ifndef _NATIVECONTEXTENUMS_H_
#define _NATIVECONTEXTENUMS_H_

#include <NativeInterface/NativeInterfaceEnums.h>

namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Context
		{
			enum ENativeResolutionMode
			{
				NAT_BORDER = 0,
				NAT_BORDERLESS = 1,
				NAT_FULLSCREEN = 2,
			};

			enum ENativeResolution
			{
				NAT_640x480 = 0x028001E0,
				NAT_800x600 = 0x03200258,
				NAT_1024x768 = 0x04000300,
				NAT_1280x720 = 0x050002D0,
				NAT_1366x768 = 0x05560300,
				NAT_1440x900 = 0x05A00384,
				NAT_1920x1080 = 0x07800438,
				NAT_2560x1440 = 0x0A0005A0,
				NAT_3840x2160 = 0x0F000870,
			};
		}
	}
}

typedef ParadigmEngine::NativeInterface::Context::ENativeResolutionMode ENativeResolutionMode;
typedef ParadigmEngine::NativeInterface::Context::ENativeResolution ENativeResolution;

#endif