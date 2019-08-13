#ifndef _UMODEL_H_
#define _UMODEL_H_

#include <Resource/UResource.h>

namespace ParadigmEngine
{
	namespace Resource
	{
		struct UModel : public UResource
		{
			public:
				////////////////////////////////////////////////
				// CONSTRUCTOR - DESTRUCTOR
				//____________________________________	
				ASSET_ATTRIBUTES(UModel);
				UModel(const FString& _resourcePath);


			public:
				////////////////////////////////////////////////
				// FUNCTIONALITY - ARCHIVAGE
				//____________________________________	
				void Archive(UArchive& out_archive)  override 
				{
					ARCHIVE_MEMBER(UModel, out_archive, 1);
					SERIALIZE_MEMBER(out_archive, m_ResourcePath);
				};
				bool Dearchive(UArchive& out_archive)  override 
				{ 
					SKIP_ARCHIVE_INFO(out_archive);
					DESERIALIZE_MEMBER(out_archive, m_ResourcePath);					
					return true; 
				};

			public:
				////////////////////////////////////////////////
				// ELEMENT ACCESS
				//____________________________________
				/** Return the number of model's vertices. */
				uint GetVertexCount(uint _index = 0) const;

				/** Return the native resource handle (underlying graphics API) to the element(index) buffer. */
				KNativeResource GetElementBufferHandle() const;

				/** Return the native resource handle (underlying graphics API) to the vertex buffer. */
				KNativeResource GetVertexBufferHandle() const;
			
				/** Return the number or subMeshes. */
				uint GetSubMeshCount() const;

				/** Return the number of uvs. */
				uint GetUvsCount() const;

				/** Get the vertex array of the indexed subMesh. */
				TArray<UVertex>& GetSubMeshVertices(uint _index);
				/** Get the vertex array of the indexed subMesh. */
				const TArray<UVertex>& GetSubMeshVertices(uint _index) const;
		

			public:
				////////////////////////////////////////////////
				// ELEMENT ACCESS
				//____________________________________	
				CUSTOM_GETTER_PROPERTY(UNativeModelBuffer, NativeBuffers, { return m_NativeModelBuffers; });
				CUSTOM_GETTER_PROPERTY(uint, TriangleCount, { return m_TriangleCount; });
				/** An array containing all triangles in the Mesh. */
				RESOURCE_PROPERTY(TArray<uint>, Triangles);


			private:
				////////////////////////////////////////////////
				// DATA
				//____________________________________	
				/** Index and Vertices buffer's NativeResourceHandle. */
				UNativeModelBuffer m_NativeModelBuffers; //KNativeResource
				/** Vertex array which contains normals, positons, tangents and uvs of the model. */
				TArray<TArray<UVertex>> m_Vertices;
			
				uint m_TriangleCount;


			public:
				////////////////////////////////////////////////
				// INTRA-FUNCTIONALITY CLASS
				// An Intra-class is a class which allow to manage private data of utilities. (Usefull for native functionnality)
				//____________________________________	
				/** An intra-class which manage the native buffer syncrhonization. */
				class FNativeSynchronizer
				{
					public:
						FNativeSynchronizer() = delete;
						/** Native synchronization of model's resources. */
						static void Synchronize(UModel& _model);
				};

				/** An intra-class which help to manage the native model building. */
				class FNativeModelEntry
				{
					public:
						FNativeModelEntry() = delete;
						/** Move constructor of Mesh from the NativeMeshEntry. */
						static void Build(UModel& out_mesh, TArray<TArray<UVertex>>& _vertices, TArray<uint>& _triangles);
						/** Move constructor of Mesh from the NativeMeshEntry. */
						static void Build(UModel& out_mesh, TArray<TArray<UVertex>>& _vertices, uint _trianglesCount);
				};

				/** An intra-class which help to manage the mesh loading. */
				class FCleaner
				{
					public:
						FCleaner() = delete;
						/** Clear the resources of the model. */
						static void Clear(UModel& _mesh);
				};
		};
		SERIALIZABLE_INSTANCE(UModel)
	}
}
typedef ParadigmEngine::Resource::UModel UModel;
typedef KResource KModel;

#endif