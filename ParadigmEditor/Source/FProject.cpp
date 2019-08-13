#include "../Include/ParadigmEditor.h"

namespace ParadigmEditor
{
	/* Project Dock Creation */	
	QDockWidget* FParadigmEditor::CreateProjectDock()
	{
		QDockWidget* projectDock = new QDockWidget(tr("Hierarchy"), this);
		projectDock->setStyleSheet("background-color: #2E2E2F;");
		projectDock->setWidget(new QWidget);
		QVBoxLayout* layout = new QVBoxLayout(projectDock->widget());
		projectDock->widget()->resize(200, 500);
		//QTreeWidget* hierarchyTree = CreateTreeHierarchy();
		//layout->addWidget(hierarchyTree);

		m_Hierarchy = new UHierarchyWidget(projectDock->widget());

		/*connect(m_HierarchyTree, &QTreeWidget::itemChanged, this, [=](QTreeWidgetItem* _Item, int column)
		{
			m_ClassEdit->setText(m_HierarchyTree->currentItem()->text(0));
			UCustomTreeItem* Item = static_cast<UCustomTreeItem*>(_Item);
			Item->entity->Name = _Item->text(0).toStdString();
		});*/

		connect(m_Hierarchy->GetTreeWidget(), &QTreeWidget::itemSelectionChanged, m_Hierarchy, [=]() { 
			UCustomTreeItem* item = static_cast<UCustomTreeItem*>(m_Hierarchy->GetTreeWidget()->selectedItems()[0]);
			m_Hierarchy->SetSelectedItem(item); });

		return projectDock;
	}
}