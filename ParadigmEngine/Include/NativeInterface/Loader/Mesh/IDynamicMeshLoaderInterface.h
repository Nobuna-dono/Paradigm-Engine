#ifndef _IDYNAMICMESHLOADERINTERFACE_H_
#define _IDYNAMICMESHLOADERINTERFACE_H_

#include <ParadigmException.h>
#include <Resource/FResourceSupervisor.h>

namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Loader
		{
			namespace Mesh
			{				
				
				class IDynamicMeshLoaderInterface
				{
					public:
						////////////////////////////////////////////////
						// CONSTRUCTOR - DESTRUCTOR
						//____________________________________	
						IDynamicMeshLoaderInterface() = default;
						~IDynamicMeshLoaderInterface() = default;
				

					public:
						////////////////////////////////////////////////
						// FUNCTIONALITY
						//____________________________________	
						/** Initialize a mesh loader interface from the mesh _filename. */
						virtual bool Initialize(const FString& _filename, void* _desc = nullptr) = 0;

						/** Terminate the mesh loader interface process and free resources. */
						virtual void Terminate() = 0;

						/** Return the number of meshes in the mesh scene. */
						virtual uint GetMeshCount() = 0;
						/** Return the number of texture in the mesh scene. */
						virtual uint GetTextureCount() = 0;

						/** Browse the scene and return all the models found. 
						(If supported) You can pass a TArray of uint to try to get material indices to rebuild the mesh. */
						virtual TArray<UModel> BuildModels(TArray<uint>* _materialIndices = nullptr) = 0;

						/** Browse the scene and return all the models found.
						(If supported) You can pass a TArray of uint to try to get material indices to rebuild the mesh. */
						virtual void BuildModels(TArray<UModel*>* out_models = nullptr, TArray<uint>* _materialIndices = nullptr) = 0;

						/** Browse the scene and return all the texture found. 
						(if supported) You can pass a TArray of uint to try to get uv indices to rebuild the mesh. */
						virtual TArray<UTexture> BuildTextures(TArray<uint>* _uvsIndex = nullptr) = 0;

						/** Browse the scene and return all the texture found.
						(if supported) You can pass a TArray of uint to try to get uv indices to rebuild the mesh. */
						virtual void BuildTextures(TArray<UTexture*>* out_textures, TArray<uint>* _uvsIndex = nullptr) = 0;
				};
			}
		}
	}
}

#endif // _FDYNAMICMESHLOADERINTERFACE_H_

