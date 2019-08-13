#ifndef _FMATERIALVIEWVERPROCESSOR_H_
#define _FMATERIALVIEWVERPROCESSOR_H_

#include <EngineFramework/MetaGear/LowRenderer/UMetaMaterialViewver.h>
#include <EngineFramework/Processor/TGearProcessor.h>
#include <sys/stat.h>

namespace ParadigmEngine
{
	namespace GameFramework
	{
		namespace GameEntity
		{
			class GEntity;
		}
	}
	using namespace GameFramework::GameEntity;

	namespace EngineFramework
	{
		namespace Processor
		{
			GEAR_PROCESSOR_CLASS(FMaterialViewverProcessor, UMetaMaterialViewver)
			{
				public:
					////////////////////////////////////////////////
					// STATIC DATA
					//_____________________
					static const uint BaseEnabledPipelines{ FIXEDUPDATE | DRAW };

				public:
					////////////////////////////////////////////////
					// PIPELINE
					//_____________________
					void FixedUpdateOne(UMetaMaterialViewver& _data) override;
					void Draw() override;


				private:
					////////////////////////////////////////////////
					// FUNCTIONALITY
					//_____________________
					void Init(UMetaMaterialViewver& _data);

				private:
					////////////////////////////////////////////////
					// DATA
					//_____________________
					GEntity* m_Camera;
					GEntity* m_Mesh;				
					
					struct stat m_ShardsStat[4];
					uint m_Viewport : 28;
					uint m_bContexBuild : 1;
					uint m_bLock : 1;
					uint m_bOpenShard : 1;
					uint m_bLight : 1;
			};
		}
	}
}

#endif