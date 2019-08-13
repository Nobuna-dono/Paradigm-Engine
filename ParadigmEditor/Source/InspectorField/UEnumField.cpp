#include "Include/InspectorField/UEnumField.h"

namespace ParadigmEditor
{
	UEnumField::UEnumField(QWidget* _parent, QString _name, std::vector<QString> _value, uint _currentindex) : UVariableField(_parent, _name)
	{
		m_Enum = new QComboBox(m_Widget);
		//m_Enum->setMaximumWidth(100);
		m_Enum->setMinimumHeight(20);
		m_Enum->setStyleSheet("color: #FFB712; background-color: #131414;");
		for(unsigned int i = 0; i < _value.size(); ++i)
			m_Enum->addItem(_value[i]);
		m_Layout->addWidget(m_Enum);
		m_Enum->setCurrentIndex(_currentindex);
		QObject::connect(m_Enum, &QComboBox::currentTextChanged, this, &UEnumField::OnValueUpdated);
	};

	UEnumField::~UEnumField()
	{
		if (m_Enum)
			delete m_Enum;
		m_Enum = { nullptr };
	}

	void UEnumField::OnValueUpdated()
	{
		m_OwnerGear->m_Inspector->SetGearValueFromName(m_OwnerGear, FString(m_Name.toStdString()), m_bMustBeDearchive, m_Enum->currentData().toInt());
	}
}