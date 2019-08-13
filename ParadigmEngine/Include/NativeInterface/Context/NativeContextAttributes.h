#ifndef _NATIVECONTEXTATTRIBUTES_H_
#define _NATIVECONTEXTATTRIBUTES_H_

#include <IKeyTable.h>
#include <NativeInterface/Context/NativeContextEnums.h>
#include <ParadigmKeyword.h>

namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Context
		{
			struct UNativeContextDimension
			{
				uint Width, Height;
			};

			struct UDynamicContextAttributes
			{
				/** The name of the window. */
				FString Name{ PARADIGM_APPLICATION_NAME };
				/** The icon pathname for this window. */
				//FString Icon;
				uint bForeground : 1;
				uint bGuestHandle : 1;
				uint : 30;

				/** The window frame mode. (see @ENativeResolutionMode) */
				ENativeResolutionMode ResolutionMode{ NAT_BORDER };
				/** Resolution (in pixel) of the context. Can differ from the @Dimension. (see @ENativeResolution) */
				ENativeResolution Resolution{ NAT_1280x720 };
				
				/** Size of the window. Same as the @Resolution if 0 or null values. */
				UNativeContextDimension Dimension;
				/** Initial position of the window. Negative value will set to center of the screen. */
				int PositionX{ -1 }, PositionY{ -1 };
				
				void* Handle;
				
			};			
		}
	}
}

typedef ParadigmEngine::NativeInterface::Context::UDynamicContextAttributes UDynamicContextAttributes;
typedef UDynamicContextAttributes UContextAttributes;
typedef ParadigmEngine::NativeInterface::Context::UNativeContextDimension UNativeContextDimension;
typedef UNativeContextDimension UContextDimension;

#endif
