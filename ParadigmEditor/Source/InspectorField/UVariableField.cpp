#include "Include/InspectorField/UVariableField.h"

namespace ParadigmEditor
{
	UVariableField::UVariableField(QWidget* _parent, QString _name)
	{
		m_Widget = new QWidget(_parent);
		m_Widget->setMinimumHeight(20);
		m_Name = _name;
		m_Layout = new QHBoxLayout(m_Widget);


		//m_Widget->setGeometry(QRect(QPoint(0, 0), QSize(100, 20)));
		//m_layout = new QFormLayout{ _parent };
		//m_Name = new QLabel(_name + ": ", m_Widget);
		//m_Name->setStyleSheet("color: #FFB712;");

		//m_layout = new QHBoxLayout(m_Widget);
		//m_layout->addWidget(m_Name);
	};

	void UVariableField::AddToLayout(QLayout* _gearLayout)
	{
		QFormLayout* layout = static_cast<QFormLayout*>(_gearLayout);
		if (layout)
			layout->addRow(m_Name, m_Widget);
		else
			_gearLayout->addWidget(m_Widget);
	}

	void UVariableField::SetMustBeDearchived(bool _value)
	{
		m_bMustBeDearchive = _value;
	}

	UVariableField::~UVariableField()
	{
		if (m_Widget)
		{
			delete m_Widget;
			m_Widget = { nullptr };
		}

		if (m_Layout)
		{
			delete m_Layout;
			m_Layout = { nullptr };
		}
	}
}