#include <EngineFramework/Processor/FMaterialViewverProcessor.h>
#include <EngineFramework/MetaGear/LowRenderer/FMetaMeshShape.h>

#include <GameFramework/GameGear/LowRenderer/GCamera.h>
#include <GameFramework/GameGear/LowRenderer/GMaterialViewver.h>
#include <GameFramework/GameGear/Physics/GTransform.h>
#include <GameFramework/GameEntity/GEntity.h>
#include <EngineFramework/Factory/UMetaEntity.h>
#include <ParadigmCore.h>


namespace ParadigmEngine
{
	namespace EngineFramework
	{
		using namespace MetaGear::LowRenderer;

		namespace Processor
		{
			////////////////////////////////////////////////
			// PIPELINE
			//_____________________

			void FMaterialViewverProcessor::FixedUpdateOne(UMetaMaterialViewver& _data)
			{
				if (m_bContexBuild && !PARADIGM_CONTEXT->IsViewportActive(ETargetViewport(m_Viewport)))
					m_bContexBuild = false;

				bool bResync = false;
				if (m_bContexBuild)
				{		
					//////////////////////////////////////////////////////////////////////
					// INIT
					//_____________________________________________
					if (!m_Camera)
					{	
						m_Camera = new GEntity(GEntity::Instanciate());
						m_Camera->GetMetaEntity()->GetTransform()->Position = {0,0,0};
						
						GTransform cameraTransform = m_Camera->GetGear<GTransform>();
						cameraTransform.Position = { 0.f, 0.f, -1.5f };

						GCamera cameraCamera = m_Camera->AddGear<GCamera>();						
						cameraCamera.Data.CullingMask = RENDER_LAYERS.AddLayer("MaterialViewver");
						cameraCamera.Data.DisplayTarget = ETargetViewport(m_Viewport);
						cameraCamera.Data.ClearColor = UColor::Silver;
					}
					if (!m_Mesh)
					{
						m_Mesh = new GEntity(GEntity::Instanciate());
						m_Mesh->GetMetaEntity()->GetTransform()->Position = { 0,0,0 };

						m_Mesh->GetMetaEntity()->Tag = RENDER_LAYERS.AddLayer("MaterialViewver");
					}
					
					if(_data.bOutdated)
					{
						GMeshShape shape = m_Mesh->AddGear<GMeshShape>();
						shape.Data.Topology = _data.Topology;
						m_Mesh->GetGear<GMeshShape>().SetModel(PARADIGM_RESOURCE->Model(_data.kModel));
						m_Mesh->AddGear<GMeshRender>();
						m_Mesh->AddGear<GMeshRender>();
					}
					
					//////////////////////////////////////////////////////////////////////
					// FILES STATS CHECKING
					//_____________________________________________
					{
						struct stat shardStat;
						if (_data.VertexFilename.Count())
						{
							stat(_data.VertexFilename.ToConstChar(), &shardStat);
							if (m_ShardsStat[0].st_mtime != shardStat.st_mtime)
							{
								m_ShardsStat[0] = shardStat;
								bResync = true;
							}
						}

						if (_data.GeometryFilename.Count())
						{
							stat(_data.GeometryFilename.ToConstChar(), &shardStat);
							if (m_ShardsStat[1].st_mtime != shardStat.st_mtime)
							{
								m_ShardsStat[1] = shardStat;
								bResync = true;
							}
						}

						if (_data.PixelFilename.Count())
						{
							stat(_data.PixelFilename.ToConstChar(), &shardStat);
							if (m_ShardsStat[2].st_mtime != shardStat.st_mtime)
							{
								m_ShardsStat[2] = shardStat;
								bResync = true;
							}
						}

						if (_data.ComputeFilename.Count())
						{
							stat(_data.ComputeFilename.ToConstChar(), &shardStat);
							if (m_ShardsStat[3].st_mtime != shardStat.st_mtime)
							{
								m_ShardsStat[3] = shardStat;
								bResync = true;
							}
						}

						if (m_bOpenShard)
						{
							FString directory = PARADIGM.ApplicationDirectory() + "/";

							if (_data.VertexFilename.Count())
								ShellExecute(0, 0, (directory + _data.VertexFilename).ToConstChar(), 0, 0, SW_SHOW);
							if (_data.GeometryFilename.Count())
								ShellExecute(0, 0, (directory + _data.GeometryFilename).ToConstChar(), 0, 0, SW_SHOW);
							if (_data.PixelFilename.Count())
								ShellExecute(0, 0, (directory + _data.PixelFilename).ToConstChar(), 0, 0, SW_SHOW);
							if (_data.ComputeFilename.Count())
								ShellExecute(0, 0, (directory + _data.ComputeFilename).ToConstChar(), 0, 0, SW_SHOW);
							m_bOpenShard = false;
						}
					}

					//////////////////////////////////////////////////////////////////////
					// RESYNC
					//_____________________________________________
					if (bResync || _data.bOutdated)
					{
						// Hot reload shader
						UShader& shader = PARADIGM_RESOURCE->Shader("MaterialViewver.shader");
						if (_data.VertexFilename.Count())
							FShader::SetShard(shader, PARADIGM_RESOURCE->ShardShader(_data.VertexFilename, _data.VertexEntry));
						if (_data.GeometryFilename.Count())
							FShader::SetShard(shader, PARADIGM_RESOURCE->ShardShader(_data.GeometryFilename, _data.GeometryEntry));
						if (_data.PixelFilename.Count())
							FShader::SetShard(shader, PARADIGM_RESOURCE->ShardShader(_data.PixelFilename, _data.PixelEntry));
						if (_data.ComputeFilename.Count())
							FShader::SetShard(shader, PARADIGM_RESOURCE->ShardShader(_data.ComputeFilename, _data.ComputeEntry));
						
						GMeshRender render = m_Mesh->GetGear<GMeshRender>();
						render.SetMaterial({ shader });
						
						FMetaMaterial::SetResourcesData(render.GetMaterial().GetMetaData(), _data.MaterialData);

						m_Mesh->GetGear<GMeshRender>().GetMaterial().Resync();
					}
					_data.bOutdated = false;
				}
			}

			void FMaterialViewverProcessor::Draw()
			{
				if (PARADIGM_INPUT->IsKeyDown(EKeyCode::F6))
				{
					if (!m_bLock)
					{
						if (!m_bContexBuild)
						{
							m_bContexBuild = true;
							int viewport = PARADIGM_CONTEXT->AvailableViewport();
							if (viewport > 0)
								m_Viewport = viewport;
							UContextAttributes context;
							context.Name = "Paradigm Material Viewver";
							context.Dimension = { 800, 600 };
							context.Resolution = ENativeResolution::NAT_800x600;
							context.bForeground = true;
							PARADIGM_GRAPHICS->CreateViewport(ETargetViewport::VIEWPORT_2, context, false, true);
							PARADIGM_INPUT->CreateInputSystem(ETargetViewport::VIEWPORT_2, { EInputDeviceType::InputDeviceType_Mouse | EInputDeviceType::InputDeviceType_Keyboard });
						}
					}
					m_bLock = true;
				}				
				else if(m_bContexBuild && PARADIGM_INPUT->IsKeyDown(ETargetViewport(m_Viewport), EKeyCode::F7))
				{
					if(!m_bLock)
						m_bOpenShard = true;
					m_bLock = true;
				}
				else
					m_bLock = false;
			}

		}		
	}
}