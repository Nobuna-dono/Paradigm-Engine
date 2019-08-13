#include "../Include/ParadigmEditor.h"
#include "../Include/HierarchyTree/CustomTreeItem.h"

namespace ParadigmEditor
{
	/* Hierarchy Tree for the Project Tab*/
	QTreeWidget* FParadigmEditor::CreateTreeHierarchy()
	{
		m_HierarchyTree = CreateTreeWidget("color: #E2E2E2; background-color: #131414; selection-color: #2F2E2F; selection-background-color: #FFB712");
		m_HierarchyTree->setColumnCount(1);
		QStringList hierarchyLabel;
		hierarchyLabel << "Hierarchy";

		m_HierarchyTree->setHeaderLabels(hierarchyLabel);
		m_HierarchyTree->setSelectionMode(QAbstractItemView::SingleSelection);
		m_HierarchyTree->setDragEnabled(true);
		m_HierarchyTree->viewport()->setAcceptDrops(true);
		m_HierarchyTree->setDropIndicatorShown(true);
		m_HierarchyTree->setDragDropMode(QAbstractItemView::InternalMove);
	//	UCustomTreeItem
		for (uint i = 0; i < 10; ++i)
		{
			QTreeWidgetItem* playerItem = new QTreeWidgetItem(m_HierarchyTree, QStringList(QObject::tr("Player(1)")));
			playerItem->setFlags(playerItem->flags() | Qt::ItemIsEditable);

			QTreeWidgetItem* sidekickItem = new QTreeWidgetItem(m_HierarchyTree, QStringList(QObject::tr("Sidekick")));
			sidekickItem->setFlags(sidekickItem->flags() | Qt::ItemIsEditable);

			QTreeWidgetItem* luguas = new QTreeWidgetItem(sidekickItem, QStringList(QObject::tr("Luguas")));
			luguas->setFlags(luguas->flags() | Qt::ItemIsEditable);
			//	sidekickItem->addChild(luguas);

			QTreeWidgetItem* arma = new QTreeWidgetItem(sidekickItem, QStringList(QObject::tr("Arma")));
			arma->setFlags(arma->flags() | Qt::ItemIsEditable);
			//sidekickItem->addChild(arma);

			QTreeWidgetItem* khrome = new QTreeWidgetItem(sidekickItem, QStringList(QObject::tr("Khrome")));
			khrome->setFlags(khrome->flags() | Qt::ItemIsEditable);
			//sidekickItem->addChild(khrome);

			QTreeWidgetItem* chocobo = new QTreeWidgetItem(QStringList(QObject::tr("Chocobo")));
			chocobo->setFlags(chocobo->flags() | Qt::ItemIsEditable);
			arma->addChild(chocobo);

			m_HierarchyTree->expandItem(playerItem);
			m_HierarchyTree->expandItem(sidekickItem);
		}
		return m_HierarchyTree;
	}
}