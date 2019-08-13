#include <Resource/FShader.h>
#include <NativeInterface/Graphics/Shader/ShaderInterfaceAttributes.h>
#include <ParadigmCore.h>

namespace ParadigmEngine
{
	namespace Resource
	{
		////////////////////////////////////////////////
		// INTRA-FUNCTIONALITY CLASS
		//____________________________________	
		void UShader::FNativeSynchronizer::Synchronize(UShader& out_shader, bool _brefresh)
		{
			if (_brefresh || !out_shader.m_bSynchronized)
			{
				out_shader.m_bSynchronized = true;
				TArray<UShardShaderDescriptor> shardsDesc;

				if (out_shader.kShardVertexShader != INVALID_KEY_REGISTER)
				{
					UShardShader& shard = PARADIGM_RESOURCE->ShardShader(out_shader.kShardVertexShader);
					shardsDesc.Add({ (ENativeShaderType)shard.Type, shard.ResourcePath, shard.EntryPoint });
				}
				if (out_shader.kShardPixelShader != INVALID_KEY_REGISTER)
				{
					UShardShader& shard = PARADIGM_RESOURCE->ShardShader(out_shader.kShardPixelShader);
					shardsDesc.Add({ (ENativeShaderType)shard.Type, shard.ResourcePath, shard.EntryPoint });
				}
				if (out_shader.kShardGeometryShader != INVALID_KEY_REGISTER)
				{
					UShardShader& shard = PARADIGM_RESOURCE->ShardShader(out_shader.kShardGeometryShader);
					shardsDesc.Add({ (ENativeShaderType)shard.Type, shard.ResourcePath, shard.EntryPoint });
				}
				if (out_shader.kShardControlShader != INVALID_KEY_REGISTER)
				{
					UShardShader& shard = PARADIGM_RESOURCE->ShardShader(out_shader.kShardControlShader);
					shardsDesc.Add({ (ENativeShaderType)shard.Type, shard.ResourcePath, shard.EntryPoint });

				}
				if (out_shader.kShardEvaluationShader != INVALID_KEY_REGISTER)
				{
					UShardShader& shard = PARADIGM_RESOURCE->ShardShader(out_shader.kShardEvaluationShader);
					shardsDesc.Add({ (ENativeShaderType)shard.Type, shard.ResourcePath, shard.EntryPoint });
				}
				if (out_shader.kShardComputeShader != INVALID_KEY_REGISTER)
				{
					UShardShader& shard = PARADIGM_RESOURCE->ShardShader(out_shader.kShardComputeShader);
					shardsDesc.Add({ (ENativeShaderType)shard.Type, shard.ResourcePath, shard.EntryPoint });
				}
				/** Can be optimize with recycling of native shader and remove not referenced. */
				PARADIGM_GRAPHICS->CreateShader(out_shader.m_kNativeShaderResources, shardsDesc, _brefresh);
			}
		}

		void FShader::SyncResource(UShader& out_shader, bool _brefresh)
		{
			UShader::FNativeSynchronizer::Synchronize(out_shader, _brefresh);
		}

		void FShader::SetShard(UShader& out_shader, EShaderType _shardType, KShardShader _kShard)
		{
			switch (_shardType)
			{
			case EShaderType::EShaderType_Vertex:
				out_shader.kShardVertexShader = _kShard;
				break;
			case EShaderType::EShaderType_Pixel:
				out_shader.kShardPixelShader = _kShard;
				break;
			case EShaderType::EShaderType_Geometry:
				out_shader.kShardGeometryShader = _kShard;
				break;
			case EShaderType::EShaderType_TessellationControl:
				out_shader.kShardControlShader = _kShard;
				break;
			case EShaderType::EShaderType_TessellationEvaluation:
				out_shader.kShardEvaluationShader = _kShard;
				break;
			case EShaderType::EShaderType_Compute:
				out_shader.kShardComputeShader = _kShard;
				break;
			default:
				break;
			}
		}

		void FShader::SetShard(UShader& out_shader, const UShardShader& _kShard)
		{
			SetShard(out_shader, _kShard.Type, PARADIGM_RESOURCE->ShardShaderKey(_kShard.ResourceName));
		}

		void FShader::RemoveShard(UShader& out_shader, const UShardShader& _shard)
		{
			SetShard(out_shader, _shard.Type, INVALID_KEY_REGISTER);
		}
	}
}