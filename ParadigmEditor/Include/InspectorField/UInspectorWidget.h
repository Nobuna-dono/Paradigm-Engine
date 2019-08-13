#ifndef _UINSPECTORWIDGET_H_
#define _UINSPECTORWIDGET_H_

#include "IKeyTable.h"
#include "../QtIncludes.h"
#include "FString.h"
#include "UGearWidget.h"
#include <FParadigmEngine.h>

namespace ParadigmEditor
{
	enum EBasicGear { COLLIDER, RIGIDBODY, CAMERA, MESHRENDER, MESHSHAPE, MATERIALVIEWVER };
	

	class UInspectorWidget
	{
	public:
		void Construct(QWidget* _parent, UKeyRegister _key);
		void Destroy();
		void AddGear(EBasicGear _gear);
		void AddGear(const UArchivableData* _data);

		template <typename T>
		void SetGearValueFromName(UGearWidget* _gearWidget, FString _name, bool _MustBeDearchive, T _value);

	private:
		QWidget * m_parent;
		QScrollArea * m_InspectorScrolling{ nullptr };
		QWidget* m_content { nullptr };
		QFormLayout* m_entity{ nullptr };
		UKeyRegister m_key{ INVALID_KEY_REGISTER };
	};
}

#include "UInspectorWidget.inl"
#endif