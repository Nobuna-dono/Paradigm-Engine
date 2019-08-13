#include <Resource/FModel.h>
#include <ParadigmCore.h>

namespace ParadigmEngine
{
	namespace Resource
	{
		////////////////////////////////////////////////
		// INTRA-FUNCTIONALITY CLASS
		//____________________________________	
#pragma region INTRA-FUNCTIONALITY CLASS
		void UModel::FNativeSynchronizer::Synchronize(UModel& _model)
		{
			if (_model.m_bSynchronized)
				return;

			// For each uv ...
				PARADIGM_GRAPHICS->CreateElementAndVertexBuffers(_model.m_NativeModelBuffers.kElementBuffer, 
					_model.m_NativeModelBuffers.kVerticesBuffer,
					_model.m_Triangles, _model.m_Vertices[0]);
				_model.m_bSynchronized = true;
		}

		void UModel::FNativeModelEntry::Build(UModel& out_mesh, TArray<TArray<UVertex>>& _vertices, TArray<uint>& _indices)
		{
			out_mesh.m_Vertices = std::move(_vertices);
			out_mesh.m_Triangles = std::move(_indices);
			out_mesh.m_TriangleCount = out_mesh.m_Triangles.Count();
		}

		void UModel::FNativeModelEntry::Build(UModel& out_mesh, TArray<TArray<UVertex>>& _vertices, uint _indices)
		{
			out_mesh.m_Vertices = std::move(_vertices);
			out_mesh.m_TriangleCount = _indices;
		}

		void UModel::FCleaner::Clear(UModel& _mesh)
		{
			_mesh.m_Triangles.Clear();
			for (TArray<TArray<UVertex>>::Iterator it = _mesh.m_Vertices.Begin(); it != _mesh.m_Vertices.End(); ++it)
				(*it).Clear();
			_mesh.m_Vertices.Clear();
		}
#pragma endregion 


		////////////////////////////////////////////////
		// FUNCTIONALITY CLASS
		//____________________________________	
#pragma region FUNCTIONALITY CLASS
		KModel FModel::CreateModelFromMemory(TArray<TArray<UVertex>> _vertex, TArray<uint> _triangles)
		{
			UModel model;
			UModel::FNativeModelEntry::Build(model, _vertex, _triangles);
			return PARADIGM_RESOURCE->LoadModelFromMemory(model);
		}
		
		KModel FModel::CreateModelFromMemory(TArray<TArray<UVertex>> _vertex, uint _trianglesCount)
		{
			UModel model;
			UModel::FNativeModelEntry::Build(model, _vertex, _trianglesCount);
			return PARADIGM_RESOURCE->LoadModelFromMemory(model);
		}

		void FModel::SyncResource(UModel& _model, bool _clearResource)
		{
			UModel::FNativeSynchronizer::Synchronize(_model);
			if (_clearResource)
				UModel::FCleaner::Clear(_model);
		}

		void FModel::CleanResourceData(UModel& _model)
		{
			UModel::FCleaner::Clear(_model);
		}
#pragma endregion 

	}
}