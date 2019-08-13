#ifndef _UNUMBERFIELD_H_
#define _UNUMBERFIELD_H_

#include "UVariableField.h"

namespace ParadigmEditor
{
	class UNumberField : public UVariableField
	{
		Q_OBJECT
		public:
			UNumberField(QWidget* _parent, QString _Name, double _value);
			UNumberField(QWidget* _parent, QString _Name, int _value);
			UNumberField(QWidget* _parent, QString _Name, unsigned int _value);
			~UNumberField();
			virtual void OnValueUpdated() override;
		public Q_SLOTS:
			void OnValueUpdated(double);
			void OnValueUpdated(int);
			void OnValueUpdated(const QString&);

		private:
			QAbstractSpinBox* m_Number {nullptr};
			bool m_floating{ false };
			bool m_signed{ true };
	};
}

#endif