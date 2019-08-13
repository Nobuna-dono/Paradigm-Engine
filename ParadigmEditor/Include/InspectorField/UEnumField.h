#ifndef _UENUMFIELD_H_
#define _UENUMFIELD_H_

#include "UVariableField.h"

namespace ParadigmEditor
{
	class UEnumField : public UVariableField
	{
		public:
			UEnumField(QWidget* _parent, QString _name, std::vector<QString> _value, uint _currentindex);
			~UEnumField();
			virtual void OnValueUpdated() override;

		private:
			QComboBox* m_Enum {nullptr};
	};
}

#endif