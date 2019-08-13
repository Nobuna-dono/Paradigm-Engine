#ifndef _FMESHLOADERINTERFACE_H_
#define _FMESHLOADERINTERFACE_H_

#include <NativeInterface/Loader/Mesh/FAssimpInterface.h>

namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Loader
		{
			namespace Mesh
			{				
				static IDynamicMeshLoaderInterface* GetNativeLoader()
				{
					// if (PARADIGM.Config.NativeMeshLoader == "ASSIMP")
					return new FAssimpInterface();
					// else exception;
				}
			}
		}
	}
}

#define PARADIGM_NATIVE_MESH_LOADER ParadigmEngine::NativeInterface::Loader::Mesh::GetNativeLoader()
typedef ParadigmEngine::NativeInterface::Loader::Mesh::IDynamicMeshLoaderInterface* FMeshLoaderInterface;

#endif