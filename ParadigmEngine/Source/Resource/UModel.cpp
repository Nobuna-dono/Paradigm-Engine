#include <Resource/UModel.h>


namespace ParadigmEngine
{
	namespace Resource
	{
		////////////////////////////////////////////////
		// CONSTRUCTOR - DESTRUCTOR
		//____________________________________	
#pragma region CONSTRUCTOR - DESTRUCTOR
		UModel::UModel(const FString& _resourcePath)
			: UResource(_resourcePath)
		{}
#pragma endregion 


		////////////////////////////////////////////////
		// ELEMENT ACCESS
		//____________________________________	
#pragma region ELEMENT ACCESS
		uint UModel::GetVertexCount(uint _index) const
		{
			if (m_Vertices.Count() < _index)
				return m_Vertices[_index].Count();
			THROW_PARADIGM_EXCEPTION_OUT_OF_RANGE("");
		}

		KNativeResource UModel::GetElementBufferHandle() const
		{
			return m_NativeModelBuffers.kElementBuffer;
		}

		KNativeResource UModel::GetVertexBufferHandle() const
		{
			return m_NativeModelBuffers.kVerticesBuffer;
		}

		uint UModel::GetSubMeshCount() const
		{
			return m_Vertices.Count();
		}

		uint UModel::GetUvsCount() const
		{
			return m_Vertices.Count();
		}

		TArray<UVertex>& UModel::GetSubMeshVertices(uint _index)
		{
			if (m_Vertices.Count() < _index)
			{
				m_bSynchronized = false;
				return m_Vertices[_index];
			}
			THROW_PARADIGM_EXCEPTION_OUT_OF_RANGE("");
		}

		const TArray<UVertex>& UModel::GetSubMeshVertices(uint _index) const
		{
			if (m_Vertices.Count() < _index)
				return m_Vertices[_index];
			THROW_PARADIGM_EXCEPTION_OUT_OF_RANGE("");
		}				
#pragma endregion		
	}
}