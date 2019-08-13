#include "Include/InspectorField/UInspectorWidget.h"
#include "Include/InspectorField/UBooleanField.h"

namespace ParadigmEditor
{
	UBooleanField::UBooleanField(QWidget* _parent, QString _name, bool _value) : UVariableField(_parent, _name)
	{
		m_Boolean = new QCheckBox(m_Widget);
		m_Boolean->setMinimumHeight(13);

		m_Boolean->setStyleSheet("background-color: #131414;");
		m_Boolean->setChecked(_value);
		m_Boolean->setMaximumSize(13, 13);
		m_Boolean->move(10, 0);
		QObject::connect(m_Boolean, &QCheckBox::stateChanged, this, &UBooleanField::OnValueUpdated);
	};

	UBooleanField::~UBooleanField()
	{
		if (m_Boolean) 
			delete m_Boolean;
		m_Boolean = { nullptr };
	}

	void UBooleanField::OnValueUpdated()
	{
		m_OwnerGear->m_Inspector->SetGearValueFromName(m_OwnerGear, FString(m_Name.toStdString()), m_bMustBeDearchive, m_Boolean->isChecked());
	}
}