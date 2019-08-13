#ifndef _UVECTORFIELD_H_
#define _UVECTORFIELD_H_

#include "UVariableField.h"

namespace ParadigmEditor
{
	class UVectorField : public UVariableField
	{
		Q_OBJECT
		public:
			UVectorField(QWidget* _parent, QString _name, float _valueX, float _valueY, float _valueZ);
			UVectorField(QWidget* _parent, QString _name, UVector3 _vec);
			UVectorField(QWidget* _parent, QString _name, float _valueX, float _valueY, float _valueZ, float _valueW);
			UVectorField(QWidget* _parent, QString _name, UQuaternion _quat);
			~UVectorField();
			virtual void OnValueUpdated() override;
		public Q_SLOTS:
			void OnValueUpdated(double);

		private:
			QFormLayout* m_XLayout { nullptr };
			QFormLayout* m_YLayout { nullptr };
			QFormLayout* m_ZLayout{ nullptr };
			QFormLayout* m_WLayout {nullptr};

			QLabel* m_XField {nullptr};
			QLabel* m_YField {nullptr};
			QLabel* m_ZField{ nullptr };
			QLabel* m_WField {nullptr};

			QDoubleSpinBox* m_XVal {nullptr};
			QDoubleSpinBox* m_YVal {nullptr};
			QDoubleSpinBox* m_ZVal{ nullptr };
			QDoubleSpinBox* m_WVal {nullptr};
			bool m_IsQuaternion{false};
	};
}

#endif