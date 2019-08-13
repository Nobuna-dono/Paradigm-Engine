#ifndef _USTRINGFIELD_H_
#define _USTRINGFIELD_H_

#include "UVariableField.h"

namespace ParadigmEditor
{
	class UStringField : public UVariableField
	{
		public:
			UStringField(QWidget* _parent, QString _name, QString _value);
			~UStringField();
			virtual void OnValueUpdated() override;

		private:
			//QTextEdit * m_String{ nullptr };
			QLineEdit * m_String {nullptr};
	};
}

#endif