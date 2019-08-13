#ifndef _TKEYTABLEDATAPROCESSOR_H_
#define _TKEYTABLEDATAPROCESSOR_H_
#include "./IDataProcessor.h"
#include <Core/DataStructure/TKeyTable.h>

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace NativeProcessor
		{
			template<typename T>
			class TKeyTableDataProcessor : public IDataProcessor<T>
			{
				public:
				// Methods
				virtual void Initialize() override;
				virtual void Update() override;
				virtual void FixedUpdate() override;
				virtual void LateUpdate() override;
				virtual void PrePhysics() override;
				virtual void PostPhysics() override;
				virtual void Pause() override;
				virtual void Terminate() override;

				TKeyTable<T>* m_Data{ nullptr };
				protected:
				// Data
			};
		}
	}
}

#include "./TKeyTableDataProcessor.inl"
#endif // !_TKEYTABLEDATAPROCESSOR_H_

