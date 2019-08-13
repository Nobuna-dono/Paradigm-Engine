#ifndef _TARRAYDATAPROCESSOR_H_
#define _TARRAYDATAPROCESSOR_H_
#include "./IDataProcessor.h"
#include <vector>

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace NativeProcessor
		{
			template<typename T>
			class TArrayDataProcessor : public IDataProcessor<T>
			{
				public:
				// Virtual Methods				
				virtual void Initialize() override;
				virtual void Update() override;
				virtual void FixedUpdate() override;
				virtual void LateUpdate() override;
				virtual void Pause() override;
				virtual void Terminate() override;

				protected:
				// Data
				std::vector<T>* m_Data{ nullptr };
			};
		}
	}
}
#include "./TArrayDataProcessor.inl"
#endif // !_TARRAYDATAPROCESSOR_H_