#include <EngineFramework/Processor/FCameraProcessor.h>

#include <EngineFramework/Factory/FMetaEntity.h>
#include <EngineFramework/MetaGear/LowRenderer/FMetaMeshShape.h>
#include <Physics/FTransform.h>
#include <FParadigmEngine.h>
#include <Time/FTime.h>


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
			void TGearProcessor<UMetaCamera>::LateUpdate()
			{
				
				//AUTOCHRONO("RendererQueueBinding time: ");
				RendererQueueBinding();
			}

			void TGearProcessor<UMetaCamera>::Draw()
			{
				//AUTOCHRONO("Draw time: ");
				for (TStaticKeyTable<UMetaCamera>::Iterator it = m_Data->Begin(); it != m_Data->End(); ++it)
				{
					try
					{
						if ((*it).bActive)
						{

#ifndef _PARADIGM_EDITOR
							if (PARADIGM_CONTEXT->IsViewportActive((*it).DisplayTarget))
#endif
							{
								PARADIGM_GRAPHICS->BeginScene((*it).DisplayTarget, (*it).ClearColor);
								DrawOne(*it);
								PARADIGM_GRAPHICS->EndScene((*it).DisplayTarget);
							}
						}
					}
					PARADIGM_CATCH_EXCEPTION;
				}
			}

			void TGearProcessor<MetaGear::LowRenderer::UMetaCamera>::DrawOne(UMetaCamera& _camera)
			{
				//AUTOCHRONO("DrawOne Camera time: ");
				UMatrix4 view = FMetaCamera::ComputeView(_camera);
				UMatrix4 proj = FMetaCamera::ComputeProjection(_camera);
				UVector4 position = *((UVector4*)&FVector4(_camera.GearedUnit->GetTransform()->Position, 0));
				UKeyRegister kshader;
				UNativeModelBuffer kinputAssembly;
				bool bOptimize = false;

				for (TArray<URendererInfo>::Iterator it2 = m_RendererInfo.Begin(); it2 != m_RendererInfo.End(); ++it2)
				{
					if (_camera.CullingMask == (*it2).LayerMask)
					{
						if (kshader != (*it2).Material.kNativeShader)
						{
							float dtime = PARADIGM.Time.GetDeltaTime();
							FMetaMaterial::SetData((*it2).Material, "DeltaTime", dtime);
							FMetaMaterial::SetData((*it2).Material, "ViewMatrix", view);
							FMetaMaterial::SetData((*it2).Material, "ProjectionMatrix", proj);
							FMetaMaterial::SetData((*it2).Material, "CameraPosition", position);
							kshader = (*it2).Material.kNativeShader;
							PARADIGM_GRAPHICS->BindShader(kshader);
							bOptimize = false;
						}
						if ((kinputAssembly.kElementBuffer != (*it2).kElementBuffer || kinputAssembly.kVerticesBuffer != (*it2).kVerticesBuffer))
						{							
							kinputAssembly = { (*it2).kElementBuffer, (*it2).kVerticesBuffer };
							PARADIGM_GRAPHICS->BindInputAssembly(kinputAssembly.kElementBuffer, kinputAssembly.kVerticesBuffer);							
						}

						FMetaMaterial::SetData((*it2).Material, "WorldMatrix", (*it2).ModelMatrix);
						PARADIGM_GRAPHICS->BindShaderResources(kshader, bOptimize);
						PARADIGM_GRAPHICS->SetPrimitiveDrawingMode((*it2).Topology);
						PARADIGM_GRAPHICS->DrawCall((*it2).TriangleCount);
						bOptimize = true;
					}
				}
			}


			////////////////////////////////////////////////
			// FUNCTIONALITY
			//_____________________
			void TGearProcessor<UMetaCamera>::RendererQueueBinding()
			{
				m_RendererInfo.Clear();
				URendererInfo rendererInfo;
				TArray<UMetaEntity*>* metaEntityArray = PARADIGM_FACTORY->GetGearedEntities<UMetaMeshShape>();
				
				if (!metaEntityArray)
					return;

				TArray<std::pair<uint, uint>> tmpRenderQueue;
				for (TArray<UMetaEntity*>::Iterator it = metaEntityArray->Begin(); it != metaEntityArray->End(); ++it)
				{
					UMetaMeshRender* meshRenderTmp = (*it)->GetGear<UMetaMeshRender>();
					if (!meshRenderTmp->Materials.Count())
						continue;
					rendererInfo.kNativeShader = meshRenderTmp->Materials[0];
					rendererInfo.Material = meshRenderTmp->Materials[0].GetMetaData();
					rendererInfo.RenderQueue = (meshRenderTmp->Materials[0].GetMetaData().RenderQueue);

					UMetaMeshShape* meshShapeTmp = (*it)->GetGear<UMetaMeshShape>();
					rendererInfo.kElementBuffer = meshShapeTmp->kNativeModelBuffer.kElementBuffer;
					rendererInfo.kVerticesBuffer = meshShapeTmp->kNativeModelBuffer.kVerticesBuffer;
					rendererInfo.TriangleCount = meshShapeTmp->TriangleCount;
					rendererInfo.Topology = meshShapeTmp->Topology;

					if (!rendererInfo.TriangleCount || !(rendererInfo.kElementBuffer != INVALID_KEY_REGISTER && rendererInfo.kElementBuffer != NULL_KEY_REGISTER))
						continue;

					rendererInfo.ModelMatrix = (*it)->GetTransform()->ToMatrix();
					rendererInfo.LayerMask = (*it)->Tag;


					if (m_RendererInfo.Count())
					{
						uint i;
						for (i = 0; i < tmpRenderQueue.Count(); ++i)
						{
							if (rendererInfo.RenderQueue < tmpRenderQueue[i].second)
							{
								m_RendererInfo.Insert(tmpRenderQueue[i].first, rendererInfo);
								tmpRenderQueue.Insert(0, std::pair<uint, uint>(tmpRenderQueue[i].first, rendererInfo.RenderQueue));

								// Update all index
								for (uint j = i; j < tmpRenderQueue.Count(); ++j)
									tmpRenderQueue[j].first++;

								break;
							}
						}
						if (i == tmpRenderQueue.Count())
						{
							if (tmpRenderQueue[i - 1].second != rendererInfo.RenderQueue)
								tmpRenderQueue.Add(std::pair<uint, uint>(tmpRenderQueue.Count() - 1, rendererInfo.RenderQueue));
							m_RendererInfo.Add(rendererInfo);
						}
					}
					else
					{
						tmpRenderQueue.Add(std::pair<uint, uint>(0, rendererInfo.RenderQueue));
						m_RendererInfo.Add(rendererInfo);
					}

				}
			}

		}
	}
}