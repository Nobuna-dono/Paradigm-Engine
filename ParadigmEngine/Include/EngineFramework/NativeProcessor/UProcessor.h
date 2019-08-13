#ifndef _UPROCESSOR_H_
#define _UPROCESSOR_H_
#include "../IPipelineHandle.h"

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace NativeProcessor
		{
			class UProcessor : public IPipelineHandle
			{
				public:
				// Struct
				struct UEventProcessor
				{
					public:
					// Enumeration
					enum EEventTag
					{
						EXECUTE_ONLY_OFF_PAUSE,
						EXECUTE_ON_PAUSE,
						EXECUTE_ONLY_ON_PAUSE,
					};

					public:
					//Processor
					//void operator+=(UMulticast _newEvent);

					public:
					// Data
					//UMulticast Event;
					EEventTag Tag;
				};

				enum EProcessorThreadTag
				{
					DEFAULT,
					MAIN_THREAD_ONLY,
					MULTITHREADABLE
				};

				public:
				virtual void CaptureData() = 0;

				public:
				// Data
				EProcessorThreadTag ThreadTag{ DEFAULT };
				/*UEventProcessor OnInitialize;
				UEventProcessor OnUpdate;
				UEventProcessor OnFixedUpdate;
				UEventProcessor OnLateUpdate;
				UEventProcessor OnTerminate;*/
				private:
			};

		}
	}
}


#endif // !_UPROCESSOR_H_
