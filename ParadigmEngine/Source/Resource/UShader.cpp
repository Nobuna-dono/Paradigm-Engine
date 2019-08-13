#include <Resource/UShader.h>
#include <Resource/FResourceSupervisor.h>

namespace ParadigmEngine
{
	namespace Resource
	{
		////////////////////////////////////////////////
		// CONSTRUCTOR - DESTRUCTOR
		//____________________________________	
		UShader::UShader(const FString& _resourcePath) 
			: UResource(_resourcePath)
		{
			kShardComputeShader = INVALID_KEY_REGISTER;
			kShardControlShader = INVALID_KEY_REGISTER; 
			kShardEvaluationShader = INVALID_KEY_REGISTER;
			kShardPixelShader = INVALID_KEY_REGISTER;
			kShardGeometryShader = INVALID_KEY_REGISTER;
			kShardVertexShader = INVALID_KEY_REGISTER;
		}

		void UShader::Archive(UArchive& out_archive) 
		{
			UShardShader shard;
			FString str;

			ARCHIVE_MEMBER(UShader, out_archive, 4);

			if (FParadigmEngine::GetInstance().Resource->GetShardShader(m_kShardVertexShader, shard))
				str = shard.ResourcePath;
			SERIALIZE_DATA(out_archive, FString("VertexShader"), str);
			str = "";
			if (PARADIGM_RESOURCE->GetShardShader(m_kShardPixelShader, shard))
				str = shard.ResourcePath;
			SERIALIZE_DATA(out_archive, FString("PixelShader"), str);
			str = "";
			if (PARADIGM_RESOURCE->GetShardShader(m_kShardGeometryShader, shard))
				str = shard.ResourcePath;
			SERIALIZE_DATA(out_archive, FString("GeometryShader"), str);
			str = "";
			if (PARADIGM_RESOURCE->GetShardShader(m_kShardComputeShader, shard))
				str = shard.ResourcePath;
			SERIALIZE_DATA(out_archive, FString("ComputeShader"), str);
		}

		bool UShader::Dearchive(UArchive& out_archive) 
		{
			FString str;
			SKIP_ARCHIVE_INFO(out_archive);
			DESERIALIZE_DATA(out_archive, str);
			m_kShardVertexShader = PARADIGM_RESOURCE->ShardShaderKey(str);
			DESERIALIZE_DATA(out_archive, str);
			m_kShardPixelShader = PARADIGM_RESOURCE->ShardShaderKey(str);
			DESERIALIZE_DATA(out_archive, str);
			m_kShardGeometryShader = PARADIGM_RESOURCE->ShardShaderKey(str);
			DESERIALIZE_DATA(out_archive, str);
			m_kShardComputeShader = PARADIGM_RESOURCE->ShardShaderKey(str);
			return true;
		}
	}
}
