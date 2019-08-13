#ifndef _FCAMERAPROCESSOR_H_
#define _FCAMERAPROCESSOR_H_

#include <EngineFramework/Processor/TGearProcessor.h>
#include <EngineFramework/MetaGear/LowRenderer/FMetaCamera.h>
#include <EngineFramework/MetaGear/LowRenderer/UMetaMeshRender.h>

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace Processor
		{
			GEAR_PROCESSOR_CLASS(FCameraProcessor, MetaGear::LowRenderer::UMetaCamera)
			{
				public:
					////////////////////////////////////////////////
					// STATIC DATA
					//_____________________
					static const uint BaseEnabledPipelines{ DRAW | LATEUPDATE };

				public:
					////////////////////////////////////////////////
					// CONSTRUCTOR - DESTRUCTOR
					//_____________________
					//TGearProcessor() = default;
					//~TGearProcessor() = default;
					
				public:
					////////////////////////////////////////////////
					// PIPELINE
					//_____________________
					void LateUpdate() override;
					void Draw() override;
					void DrawOne(MetaGear::LowRenderer::UMetaCamera& _data) override;


				private:
					////////////////////////////////////////////////
					// FUNCTIONALITY
					//_____________________
					void RendererQueueBinding();

				private:
					////////////////////////////////////////////////
					// STRUCT
					//_____________________
					struct URendererInfo
					{
						UKeyRegister kNativeShader, kElementBuffer, kVerticesBuffer;
						uint TriangleCount : 23;
						uint RenderQueue : 8;
						ENativePrimitiveTopology Topology;
						uint LayerMask;
						UMatrix4 ModelMatrix;
						UMetaMaterial Material;
					};

				private:
					////////////////////////////////////////////////
					// DATA
					//_____________________
					TArray<URendererInfo> m_RendererInfo;
					//std::map<uint, TArray<URendererInfo>> m_RendererInfo;
			};
		}
	}
}

#endif