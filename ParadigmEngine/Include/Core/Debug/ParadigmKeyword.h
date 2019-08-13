#ifndef _PARADIGMKEYWORD_H_
#define _PARADIGMKEYWORD_H_

#include <FString.h>

#define PARADIGM_PAUSE system("Pause")
#define PARADIGM_TIME " : " + FString(__TIME__) + " : "
#define PARADIGM_DATE "[" + FString(__DATE__) + "]"
#define PARADIGM_LOCATION (FString(__FILE__) + " func<") + FString(__func__) + FString("> at Line ") + FString::ToString<unsigned int>(__LINE__)
#define PARADIGM_TEMPORALITY_LOCATION_DETAILS PARADIGM_DATE + PARADIGM_TIME + "\n| #Location : " + PARADIGM_LOCATION + "\n| #Details : "

#define PARADIGM_DEV_SIGNATURE_ARUMA FString("Aruma, +336 95 47 12 90 | m.hoarau@student.isartdigital.com")
#define PARADIGM_DEV_SIGNATURE_KUROMU FString("Kuromu, add some comment !")
#define PARADIGM_DEV_SIGNATURE_LUCAS FString("Please Lucas add some comment")

#define PARADIGM_PATCH_VER FString(" ver.0.1.0")
#define PARADIGM_APPLICATION_NAME FString("Paradigm Engine") + PARADIGM_PATCH_VER
#define PARADIGM_WINDOW_ICON FString("")

#define PARADIGM_NATIVE_GRAPHICS_DIRECT3D11
#define PARADIGM_NATIVE_CONTEXT_WINDOWS

#define PARADIGM_NATIVE_PHYSICS_BULLET

#ifdef PARADIGM_NATIVE_GRAPHICS_DIRECT3D11
#define PARADIGM_CRITICAL_MESSAGE(Handler, Text, Caption) MessageBox(Handler, Text, Caption, MB_OK)
#else
#define PARADIGM_CRITICAL_MESSAGE(Text) FPrint::PrintFile(Text);
#endif

#endif