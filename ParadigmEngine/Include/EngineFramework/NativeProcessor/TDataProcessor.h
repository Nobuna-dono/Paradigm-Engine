#ifndef _TDATAPROCESSOR_H_
#define _TDATAPROCESSOR_H_

#include "./TStaticKeyTableDataProcessor.h"
#include <EngineFramework/MetaGear/UMetaGear.h>

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace NativeProcessor
		{

			template <class GearT, class = IfDeriveGear<GearT>>
			class TDataProcessor : public TStaticKeyTableDataProcessor<GearT>
			{	
				public:
					////////////////////////////////////////////////
					// PIPELINE
					//_____________________
					virtual void Initialize() override;
					virtual void Update() override;
					virtual void FixedUpdate() override;
					virtual void LateUpdate() override;
					virtual void PrePhysics() override;
					virtual void PostPhysics() override;
					virtual void Pause() override;
					virtual void Terminate() override;

				protected:
					////////////////////////////////////////////////
					// PIPELINE
					//_____________________
					virtual void CaptureData();
			};
		}
	}
}
#include "./TDataProcessor.inl"
#endif // !_TGEARPROCESSOR_H_
