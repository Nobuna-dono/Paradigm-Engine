#ifndef _UHIERARCHYWIDGET_H_
#define _UHIERARCHYWIDGET_H_
#include "Include/QtIncludes.h"
#include "EngineFramework/Factory/UMetaEntity.h"
#include  "Include/HierarchyTree/CustomTreeItem.h"
#include "Physics/Collision/UColliderShape.h"

namespace ParadigmEditor
{
	class UHierarchyWidget : public QObject
	{
	public:
		UHierarchyWidget(QWidget* _parent);
		QTreeWidget* GetTreeWidget() { return m_Tree; }

		void AddItem(UCustomTreeItem* itemParent = NULL);
		void AddShape(ParadigmEngine::Physics::Collision::EColliderShape _shape, UCustomTreeItem* _itemParent = NULL);
		void AddVoidEntity(UCustomTreeItem* _itemParent = NULL);
		void SetSelectedItem(UCustomTreeItem* _newSelection);
	private:
		QTreeWidget * m_Tree;
		QScrollArea * m_InspectorScrolling{ nullptr };
		QWidget* content{ nullptr };
		QFormLayout* entity{ nullptr };
		UCustomTreeItem* m_SelectedItem{ nullptr };
	};
}

#endif // !_UHIERARCHYWIDGET_H_
