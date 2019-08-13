#include <Resource/FTexture.h>

namespace ParadigmEngine
{
	namespace Resource
	{
		void FTexture::SyncResource(UTexture& _texture)
		{
			UTexture::FNativeSynchronizer::Synchronize(_texture);
		}
	}
}