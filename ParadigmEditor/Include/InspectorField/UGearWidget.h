#ifndef _UGEARWIDGET_H_
#define _UGEARWIDGET_H_

#include "Core/DataStructure/TArray.h"
#include <unordered_map>
#include <Serialization/UArchive.h>
#include "../QtIncludes.h"
	
namespace ParadigmEditor
{
	class UInspectorWidget;

	class UGearWidget
	{
		public:
			UGearWidget(QWidget* _parent, UArchive& _name);

		private:
			void CreateVariableField(UArchive& str);
		public :
			UInspectorWidget * m_Inspector{ nullptr };
			size_t typeCode;
			uint index{0u};
			UArchive& GetArchive();

		private:
			QGroupBox* m_Box{ nullptr };
			QFormLayout* m_Layout = new QFormLayout(m_Box);
			std::pair<size_t, QString> m_GearInfo;
			UArchive m_GearArchive;
			//TArray<UVariableField> m_VariableField;
	};
}

#endif