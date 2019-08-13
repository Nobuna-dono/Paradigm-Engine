#include "Include/InspectorField/UNumberField.h"

#undef max
#undef min

namespace ParadigmEditor
{
	UNumberField::UNumberField(QWidget* _parent, QString _name, double _value) : UVariableField(_parent, _name)
	{
		m_Number = new QDoubleSpinBox(m_Widget);
		QDoubleSpinBox* number = static_cast<QDoubleSpinBox*>(m_Number);
		//number->setMaximumWidth(100);
		number->setMinimumHeight(20);
		number->setStyleSheet("color: #FFB712; background-color: #131414;");
		number->setValue(_value);
		number->setMinimum(-DOUBLE_MAX);
		number->setMaximum(DOUBLE_MAX);
		m_Layout->addWidget(number);
		m_floating =  true;
		connect(m_Number, SIGNAL(valueChanged(const QString&)),
							this, SLOT(OnValueUpdated(const QString&)));
	};

	UNumberField::UNumberField(QWidget* _parent, QString _name, int _value) : UVariableField(_parent, _name)
	{
		m_Number = new QSpinBox(m_Widget);
		QSpinBox* number = static_cast<QSpinBox*>(m_Number);
		//m_Number->setMaximumWidth(100);
		number->setMinimumHeight(20);
		number->setStyleSheet("color: #FFB712; background-color: #131414;");
		number->setValue(_value);
		number->setMinimum(INTEGER_MIN);
		number->setMaximum(INTEGER_MAX);
		m_Layout->addWidget(number);
		connect(m_Number, SIGNAL(valueChanged(const QString&)),
			this, SLOT(OnValueUpdated(const QString&)));
	}

	UNumberField::UNumberField(QWidget* _parent, QString _name, unsigned int _value) : UVariableField(_parent, _name)
	{
		m_Number = new QSpinBox(m_Widget);
		QSpinBox* number = static_cast<QSpinBox*>(m_Number);
		//m_Number->setMaximumWidth(100);
		number->setMinimumHeight(20);
		number->setStyleSheet("color: #FFB712; background-color: #131414;");
		number->setValue(_value);
		number->setMinimum(0);
		number->setMaximum(std::numeric_limits<unsigned int>::max());
		m_Layout->addWidget(number);
		m_signed = false;
		connect(m_Number, SIGNAL(valueChanged(const QString&)),
			this, SLOT(OnValueUpdated(const QString&)));
	}

	UNumberField::~UNumberField()
	{
		if (m_Number)
			delete m_Number;
		m_Number = { nullptr };
	}

	void UNumberField::OnValueUpdated()
	{
		if (m_floating)
		{
			float number = static_cast<QDoubleSpinBox*>(m_Number)->value();
			m_OwnerGear->m_Inspector->SetGearValueFromName(m_OwnerGear, FString(m_Name.toStdString()), m_bMustBeDearchive, number);
		}
		else if (m_signed)
		{
			int number = static_cast<QSpinBox*>(m_Number)->value();
			m_OwnerGear->m_Inspector->SetGearValueFromName(m_OwnerGear, FString(m_Name.toStdString()), m_bMustBeDearchive, number);
		}
		else
		{
			unsigned int number = static_cast<QSpinBox*>(m_Number)->value();
			m_OwnerGear->m_Inspector->SetGearValueFromName(m_OwnerGear, FString(m_Name.toStdString()), m_bMustBeDearchive, number);
		}
	}
	void UNumberField::OnValueUpdated(double _value) { OnValueUpdated(); };
	void UNumberField::OnValueUpdated(int _value) { OnValueUpdated(); };
	void UNumberField::OnValueUpdated(const QString&) { OnValueUpdated(); };

}