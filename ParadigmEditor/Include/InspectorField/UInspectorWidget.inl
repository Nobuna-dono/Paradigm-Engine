#include "FParadigmEngine.h"
#include "EngineFramework/Factory/FFactorySupervisor.h"

namespace ParadigmEditor
{
	template <typename T>
	void UInspectorWidget::SetGearValueFromName(UGearWidget* _gearWidget, FString _name, bool _MustBeDearchive, T _value)
	{
		UMetaEntity* entity = PARADIGM_FACTORY->GetMetaEntity(m_key);
		if (_MustBeDearchive)
		{
			bool result = entity->ReplaceValueInGear(_gearWidget->GetArchive(), _name, _value);
		}
		else
			entity->SetGearValueFromName(_gearWidget->typeCode, _gearWidget->index, _name, _value);
	}

}