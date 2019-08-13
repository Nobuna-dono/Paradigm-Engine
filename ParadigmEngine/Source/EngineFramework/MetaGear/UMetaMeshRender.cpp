#include <EngineFramework/MetaGear/LowRenderer/UMetaMeshRender.h>
#include <Resource/FResourceSupervisor.h>

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace MetaGear
		{
			namespace LowRenderer
			{
				////////////////////////////////////////////////
				// FUNCTIONALITY - ARCHIVAGE
				//____________________________________	
				void UMetaMeshRender::Archive(UArchive& out_archive)  
				{
					ARCHIVE_MEMBER(UMetaMeshRender, out_archive, 8);

					SERIALIZE_MEMBER(out_archive, bCastShadow);
					SERIALIZE_MEMBER(out_archive, bReceiveShadow);
					

					UShader shader;
					bool bMat = false;
					if (Materials.Count())
					{
						bMat = true;
						shader = Materials[0].GetShader();
					}

					// Vertex 
					FString str = "", entry = "";
					if (bMat && shader.kShardVertexShader != INVALID_KEY_REGISTER)
					{
						UShader& shader = Materials[0].GetShader();
						try
						{
							UShardShader& shard = PARADIGM_RESOURCE->ShardShader(shader.kShardVertexShader);
							str = shard.ResourceName;
							entry = shard.EntryPoint;
						}
						catch (const ParadigmException&) {}
					}
					SERIALIZE_DATA(out_archive, FString("VertexShard"), str);
					SERIALIZE_DATA(out_archive, FString("VertexEntry"), entry);

					// Geometry 
					str = "", entry = "";
					if (bMat && shader.kShardGeometryShader != INVALID_KEY_REGISTER)
					{
						try
						{
							UShardShader& shard = PARADIGM_RESOURCE->ShardShader(shader.kShardGeometryShader);
							str = shard.ResourceName;
							entry = shard.EntryPoint;
						}
						catch (const ParadigmException&) {}
					}
					SERIALIZE_DATA(out_archive, FString("GeometryShard"), str);
					SERIALIZE_DATA(out_archive, FString("GeometryEntry"), entry);

					// Pixel 
					str = "", entry = "";
					if (bMat && shader.kShardPixelShader != INVALID_KEY_REGISTER)
					{
						try
						{
							UShardShader& shard = PARADIGM_RESOURCE->ShardShader(shader.kShardPixelShader);
							str = shard.ResourceName;
							entry = shard.EntryPoint;
						}
						catch (const ParadigmException&) {}
					}
					SERIALIZE_DATA(out_archive, FString("PixelShard"), str);
					SERIALIZE_DATA(out_archive, FString("PixelEntry"), entry);
				}

				bool UMetaMeshRender::Dearchive(UArchive& out_archive)  
				{
					SKIP_ARCHIVE_INFO(out_archive);
					
					DESERIALIZE_MEMBER(out_archive, bCastShadow);
					DESERIALIZE_MEMBER(out_archive, bReceiveShadow);
					
					UShader& shader = PARADIGM_RESOURCE->Shader("TmpShader.shader");
					FString str, entry;
					for (uint i = 0; i < 3; ++i)
					{
						DESERIALIZE_DATA(out_archive, str);
						DESERIALIZE_DATA(out_archive, entry);
						UKeyRegister key = PARADIGM_RESOURCE->ShardShaderKey(str, entry);
						if (key != INVALID_KEY_REGISTER)
							FShader::SetShard(shader, PARADIGM_RESOURCE->ShardShader(key));
					}
					if (!Materials.Count())
						Materials.Add(shader);
					else
						Materials[0] = FMaterial(shader);
					
					return true;
				}
			}
		}
	}
}