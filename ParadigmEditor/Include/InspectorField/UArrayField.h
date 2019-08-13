#ifndef _UARRAYFIELD_H_
#define _UARRAYFIELD_H_

#include "UVariableField.h"

namespace ParadigmEditor
{
	class UArrayField : public UVariableField
	{
		public:
			UArrayField(QWidget* _parent, QString _name/*, FString? _value*/);

		private:
			//TArray<UVariableField*> m_Variables;
	};
}

#endif