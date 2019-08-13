#ifndef _UBOOLEANFIELD_H_
#define _UBOOLEANFIELD_H_

#include "UVariableField.h"

namespace ParadigmEditor
{
	class UBooleanField : public UVariableField
	{
		public:
			UBooleanField(QWidget* _parent, QString _Name, bool _value);
			~UBooleanField();
			virtual void OnValueUpdated() override;

		//private:
			QCheckBox* m_Boolean{nullptr};
	};
}

#endif