#ifndef _FTEXTURE_H_
#define _FTEXTURE_H_

#include <Resource/UTexture.h>

namespace ParadigmEngine
{
	namespace Resource
	{
		/** The @UTexture's functionality class. */
		class FTexture
		{
			public:
				////////////////////////////////////////////////
				// FUNCTIONALITY
				//____________________________________	
				/** Creates or reupload buffer according with the resources. (Must be call manually until that we can use good enought TProperty)*/
				static void SyncResource(UTexture& _texture);
		};
	
	}
}

typedef ParadigmEngine::Resource::FTexture FTexture;

#endif //_FTEXTURE_H_