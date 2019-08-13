#include "../Include/ParadigmEditor.h"

namespace ParadigmEditor
{
	void FParadigmEditor::InspectorInfo(/*QTreeWidgetItem* _item, int _column*/)
	{
		m_Inspector->Destroy();

		UCustomTreeItem* temp = static_cast<UCustomTreeItem*>(m_Hierarchy->GetTreeWidget()->selectedItems()[0]);

		m_Inspector->Construct(m_InspectorDock->widget(), temp->key);

		//if (m_InspectorScrolling)
		//	delete m_InspectorScrolling;

		//m_InspectorScrolling = new QScrollArea(m_InspectorDock->widget());
		//m_InspectorScrolling->setMinimumWidth(425);
		//m_InspectorScrolling->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		//m_InspectorScrolling->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		//m_InspectorDock->widget()->layout()->addWidget(m_InspectorScrolling);
		//QWidget* content = new QWidget(m_InspectorDock->widget());
		//QFormLayout* entity = new QFormLayout(content);
		//content->setLayout(entity);
		//content->setStyleSheet("background-color: #2F2E2F;");

		//for (int i = 0; i < 6; ++i)
		//{

		//	std::string str = "Gear " + std::to_string(i);
		//	UGearWidget* gear = new UGearWidget(content, str.c_str());
		//}
		//m_InspectorScrolling->setWidget(content);
	}
}