#ifndef _TSTATICKEYTABLEDATAPROCESSOR_H_
#define _TSTATICKEYTABLEDATAPROCESSOR_H_
#include "./IDataProcessor.h"
#include <Core/DataStructure/TStaticKeyTable.h>

namespace ParadigmEngine
{
	namespace EngineFramework
	{
		namespace NativeProcessor
		{
			template<typename T>
			class TStaticKeyTableDataProcessor : public IDataProcessor<T>
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

				TStaticKeyTable<T>* m_Data{ nullptr };
				protected:
				// Data
			};
		}
	}
}

#include "./TStaticKeyTableDataProcessor.inl"
#endif // !_TSTATICKEYTABLEDATAPROCESSOR_H_

