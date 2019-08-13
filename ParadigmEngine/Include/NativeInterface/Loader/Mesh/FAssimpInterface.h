#ifndef _FASSIMPINTERFACE_H_
#define _FASSIMPINTERFACE_H_

#include <NativeInterface/Loader/Mesh/IDynamicMeshLoaderInterface.h>

#include <Extern/Include/assimp/scene.h>
#include <Extern/Include/assimp/mesh.h>
#include <Extern/Include/assimp/Importer.hpp>
#include <Extern/Include/assimp/postprocess.h>

namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Loader
		{
			namespace Mesh
			{
				class FAssimpInterface : public IDynamicMeshLoaderInterface
				{
					public:
						////////////////////////////////////////////////
						// CONSTRUCTOR - DESTRUCTOR
						//____________________________________	
						FAssimpInterface() = default;
						~FAssimpInterface();

					public:
						////////////////////////////////////////////////
						// FUNCTIONALITY
						//____________________________________	
						/** Initialize a mesh loader interface from the mesh _filename. */
						bool Initialize(const FString& _filename, void* _desc = nullptr) override;

						/** Terminate the mesh loader interface process and free resources. */
						void Terminate() override;
						
						/** Return the number of meshes in the mesh scene. */
						uint GetMeshCount() override;
						/** Return the number of texture in the mesh scene. */
						uint GetTextureCount() override;


						/** Browse the scene and return all the models found.
						(If supported) You can pass a TArray of uint to try to get material indices to rebuild the mesh. */
						TArray<UModel> BuildModels(TArray<uint>* _materialIndices = nullptr) override;
						
						/** Browse the scene and return all the models found.
						(If supported) You can pass a TArray of uint to try to get material indices to rebuild the mesh. */
						void BuildModels(TArray<UModel*>* out_models, TArray<uint>* _materialIndices = nullptr) override;

						/** Browse the scene and return all the texture found.
						(if supported) You can pass a TArray of uint to try to get uv indices to rebuild the mesh. */
						TArray<UTexture> BuildTextures(TArray<uint>* _uvsIndex = nullptr) override;
						
						/** Browse the scene and return all the texture found.
						(if supported) You can pass a TArray of uint to try to get uv indices to rebuild the mesh. */
						void BuildTextures(TArray<UTexture*>* out_textures, TArray<uint>* _uvsIndex = nullptr) override;


					private:
						////////////////////////////////////////////////
						// FUNCTIONALITY
						//____________________________________	
						//bool InitFromScene(const aiScene* pScene, const FString& Filename);
						bool InitModel(const aiMesh* paiMesh, UModel& out_mesh);
						void InitTextures(const aiMaterial* _material, aiTextureType _type, TArray<UTexture>& out_textures, TArray<uint>* _uvsIndex = nullptr);
						

					private:
						////////////////////////////////////////////////
						// DATA
						//____________________________________	
						Assimp::Importer m_aiImporter;
						const aiScene* m_aiScene = nullptr;
						FString m_CurrentFilename;
						TArray<Resource::UModel::FNativeModelEntry> m_MeshEntries;
						TArray<Resource::UTexture> m_Textures;
				};
			}
		}
	}
}
#endif
