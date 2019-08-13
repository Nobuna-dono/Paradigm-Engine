#include "Include/InspectorField/UVectorField.h"
#include "ParadigmMath.h"

#undef max
#undef min
namespace ParadigmEditor
{
	UVectorField::UVectorField(QWidget* _parent, QString _name, float _valueX, float _valueY, float _valueZ) 
		: UVariableField(_parent, _name)
	{
		m_XVal = new QDoubleSpinBox(m_Widget);
		m_XVal->setFixedSize(75, 20);
		m_XVal->setStyleSheet("color: #FFB712; background-color: #131414;");
		m_XVal->setRange(DOUBLE_MIN,DOUBLE_MAX);
		m_XVal->setValue(_valueX);
		m_XLayout = new QFormLayout(/*m_Widget*/);
		m_XLayout->addRow("X: ", m_XVal);
		m_Layout->addLayout(m_XLayout);
		QObject::connect(m_XVal, SIGNAL(valueChanged(double)),
			this, SLOT(OnValueUpdated(double)));


		m_YVal = new QDoubleSpinBox(m_Widget);
		m_YVal->setFixedSize(75, 20);
		m_YVal->setStyleSheet("color: #FFB712; background-color: #131414;");
		m_YVal->setRange(DOUBLE_MIN,DOUBLE_MAX);
		m_YVal->setValue(_valueY);
		m_YLayout = new QFormLayout(/*m_Widget*/);
		m_YLayout->addRow("Y: ", m_YVal);
		m_Layout->addLayout(m_YLayout);
		QObject::connect(m_YVal, SIGNAL(valueChanged(double)),
			this, SLOT(OnValueUpdated(double)));

		m_ZVal = new QDoubleSpinBox(m_Widget);
		m_ZVal->setFixedSize(75, 20);
		m_ZVal->setStyleSheet("color: #FFB712; background-color: #131414;");
		m_ZVal->setRange(DOUBLE_MIN,DOUBLE_MAX);
		m_ZVal->setValue(_valueZ);
		m_ZLayout = new QFormLayout(/*m_Widget*/);
		m_ZLayout->addRow("Z: ", m_ZVal);
		m_Layout->addLayout(m_ZLayout);
		QObject::connect(m_ZVal, SIGNAL(valueChanged(double)),
			this, SLOT(OnValueUpdated(double)));
	};

	UVectorField::UVectorField(QWidget* _parent, QString _name, UVector3 _vec) : UVectorField(_parent, _name, _vec.x, _vec.y, _vec.z )
	{

	}

	UVectorField::UVectorField(QWidget* _parent, QString _name, float _valueX, float _valueY, float _valueZ, float _valueW)	: UVariableField(_parent, _name)
	{
		m_XVal = new QDoubleSpinBox(m_Widget);
		m_XVal->setFixedSize(55, 20);
		m_XVal->setStyleSheet("color: #FFB712; background-color: #131414;");
		m_XVal->setRange(DOUBLE_MIN,DOUBLE_MAX);
		m_XVal->setValue(_valueX);
		m_XLayout = new QFormLayout(/*m_Widget*/);
		m_XLayout->addRow("X: ", m_XVal);
		m_Layout->addLayout(m_XLayout);
		QObject::connect(m_XVal, SIGNAL(valueChanged(double)),
			this, SLOT(OnValueUpdated(double)));


		m_YVal = new QDoubleSpinBox(m_Widget);
		m_YVal->setFixedSize(50, 20);
		m_YVal->setStyleSheet("color: #FFB712; background-color: #131414;");
		m_YVal->setRange(DOUBLE_MIN,DOUBLE_MAX);
		m_YVal->setValue(_valueY);
		m_YLayout = new QFormLayout(/*m_Widget*/);
		m_YLayout->addRow("Y: ", m_YVal);
		m_Layout->addLayout(m_YLayout);
		QObject::connect(m_YVal, SIGNAL(valueChanged(double)),
			this, SLOT(OnValueUpdated(double)));

		m_ZVal = new QDoubleSpinBox(m_Widget);
		m_ZVal->setFixedSize(50, 20);
		m_ZVal->setStyleSheet("color: #FFB712; background-color: #131414;");
		m_ZVal->setRange(DOUBLE_MIN,DOUBLE_MAX);
		m_ZVal->setValue(_valueZ);
		m_ZLayout = new QFormLayout(/*m_Widget*/);
		m_ZLayout->addRow("Z: ", m_ZVal);
		m_Layout->addLayout(m_ZLayout);
		QObject::connect(m_ZVal, SIGNAL(valueChanged(double)),
			this, SLOT(OnValueUpdated(double)));

		m_WVal = new QDoubleSpinBox(m_Widget);
		m_WVal->setFixedSize(50, 20);
		m_WVal->setStyleSheet("color: #FFB712; background-color: #131414;");
		m_WVal->setRange(DOUBLE_MIN,DOUBLE_MAX);
		m_WVal->setValue(_valueW);
		m_WLayout = new QFormLayout(/*m_Widget*/);
		m_WLayout->addRow("W: ", m_WVal);
		m_Layout->addLayout(m_WLayout);

		QObject::connect(m_WVal, SIGNAL(valueChanged(double)),
							this, SLOT(OnValueUpdated(double)));
	}

	UVectorField::UVectorField(QWidget* _parent, QString _name, UQuaternion _quat) : UVectorField(_parent, _name, ((FQuaternion)_quat).ToEulerAngles())
	{
		m_XVal->setSingleStep(5.0);
		m_YVal->setSingleStep(5.0);
		m_ZVal->setSingleStep(5.0);
		m_IsQuaternion = true;
	}

	UVectorField::~UVectorField()
	{
		if (m_XField)
		{
			delete m_XField;
			m_XField = { nullptr };
		}
		if (m_YField)
		{
			delete m_YField;
			m_YField = { nullptr };
		}
		if (m_ZField)
		{
			delete m_ZField;
			m_ZField = { nullptr };
		}
		if (m_WField)
		{
			delete m_WField;
			m_ZField = { nullptr };
		}

		if (m_WVal)
		{
			delete m_XVal;
			m_XVal = { nullptr };
		}
		if (m_YVal)
		{
			delete m_YVal;
			m_YVal = { nullptr };
		}
		if (m_ZVal)
		{
			delete m_ZVal;
			m_ZVal = { nullptr };
		}
		if (m_WVal)
		{
			delete m_WVal;
			m_WVal = { nullptr };
		}
	}

	void UVectorField::OnValueUpdated()
	{
		if (m_WVal)
		{
			UVector4 vec = { m_XVal->value(), m_YVal->value(), m_ZVal->value(), m_WVal->value() };
			m_OwnerGear->m_Inspector->SetGearValueFromName(m_OwnerGear, FString(m_Name.toStdString()), m_bMustBeDearchive, vec);
		}
		else if (m_IsQuaternion)
		{
			UVector3 vec = { m_XVal->value(), m_YVal->value(), m_ZVal->value() };
			m_OwnerGear->m_Inspector->SetGearValueFromName(m_OwnerGear, FString(m_Name.toStdString()), m_bMustBeDearchive, FQuaternion::FromEulerAngles(vec));
		}
		else
		{
			UVector3 vec = { m_XVal->value(), m_YVal->value(), m_ZVal->value() };
			m_OwnerGear->m_Inspector->SetGearValueFromName(m_OwnerGear, FString(m_Name.toStdString()), m_bMustBeDearchive, vec);
		}
	}

	void UVectorField::OnValueUpdated(double) { OnValueUpdated(); };
}