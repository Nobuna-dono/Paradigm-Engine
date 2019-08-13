#include "Include/InspectorField/UStringField.h"

namespace ParadigmEditor
{
	UStringField::UStringField(QWidget* _parent, QString _name, QString _value) : UVariableField(_parent, _name)
	{
		m_String = new QLineEdit(m_Widget);
		//m_String->setMaximumWidth(250);
		m_String->setMinimumHeight(20);
		m_String->setStyleSheet("background-color: #131414;");
		m_String->setText(_value);
		m_Layout->addWidget(m_String);
		QObject::connect(m_String, &/*QTextEdit::selectionChanged*/QLineEdit::editingFinished,
			this, &UStringField::OnValueUpdated);
	};

	UStringField::~UStringField()
	{
		if (m_String)
			delete m_String;
		m_String = { nullptr };

	}

	void UStringField::OnValueUpdated()
	{
		m_OwnerGear->m_Inspector->SetGearValueFromName(m_OwnerGear, FString(m_Name.toStdString()), m_bMustBeDearchive, FString(m_String->text().toStdString()));
	}
}