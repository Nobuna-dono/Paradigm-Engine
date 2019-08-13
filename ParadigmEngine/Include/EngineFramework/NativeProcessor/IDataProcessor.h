#ifndef _IDATAPROCESSOR_H_
#define _IDATAPROCESSOR_H_
#include "./UProcessor.h"

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace NativeProcessor
		{
			template<typename T>
			class IDataProcessor : public UProcessor
			{
				public:
					////////////////////////////////////////////////
					// PIPELINE
					//_____________________
					virtual void InitializeOne(T& _data) {};
				
					virtual void UpdateOne(T& _data) {};
					virtual void FixedUpdateOne(T& _data) {};
					virtual void LateUpdateOne(T& _data) {};
				
					virtual void DrawOne(T& _data) {};
				
					virtual void PrePhysicsOne(T& _data) {};
					virtual void PostPhysicsOne(T& _data) {};
				
					virtual void PauseOne(T& _data) {};
					virtual void TerminateOne(T& _data) {};
			};
		}
	}
}

#endif // _IDATAPROCESSOR_H_