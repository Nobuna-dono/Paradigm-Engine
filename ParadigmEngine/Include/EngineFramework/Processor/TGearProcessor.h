#ifndef _TGEARPROCESSOR_H_
#define _TGEARPROCESSOR_H_
#include <EngineFramework\NativeProcessor\TDataProcessor.h>
#include <ParadigmDebug.h>

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace Processor
		{
			template <class T>
			class TGearProcessor : public NativeProcessor::TDataProcessor<T>
			{
				public:
					//static data
					static const uint BaseEnabledPipelines{ NONE };
				
				public : 
					TGearProcessor() 
					{ FPrint::Print("Gear type specified as no specific processor.\n", EParadigmDebugLevel::WARNING_LEVEL); }
			};
		}
	}
}
#define GEAR_PROCESSOR_CLASS(NAME, METATYPE)			\
		typedef TGearProcessor<METATYPE> NAME;			\
		template <>										\
		class TGearProcessor<METATYPE> : public NativeProcessor::TDataProcessor<METATYPE>

#endif