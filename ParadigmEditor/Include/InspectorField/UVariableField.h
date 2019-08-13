#ifndef _UVARIABLEFIELD_H_
#define _UVARIABLEFIELD_H_

#define DOUBLE_MAX std::numeric_limits<double>::max()
#define DOUBLE_MIN -DOUBLE_MAX

#define INTEGER_MAX std::numeric_limits<int>::max()
#define INTEGER_MIN std::numeric_limits<int>::min()

#include "Include/QtIncludes.h"
#include <Core/Serialization/UArchive.h>
#include "UInspectorWidget.h"
#include "UGearWidget.h"

namespace ParadigmEditor
{
	enum EVariableFieldType
	{
		VariableField_Bool = 0x0,
		VariableField_Integer,
		VariableField_UnsignedInteger,
		VariableField_Float,
		VariableField_String,
		VariableField_Enum,
	};

	struct UVariableFieldBuffer
	{
		QString Name;
		EVariableFieldType FieldType;
	};

	class UVariableField : public QObject
	{
		Q_OBJECT
		public:
			void AddToLayout(QLayout* _gearLayout);
			void SetMustBeDearchived(bool _value);
			virtual void OnValueUpdated() = 0;

		//signals:
			UGearWidget* m_OwnerGear{nullptr};
		protected:
			UVariableField(QWidget* _parent, QString _name);
			~UVariableField();
			
			QWidget* m_Widget {nullptr};
			QHBoxLayout* m_Layout{ nullptr };
			QString m_Name;
			uint Type;
			bool m_bMustBeDearchive{ true };
	};
}

#endif