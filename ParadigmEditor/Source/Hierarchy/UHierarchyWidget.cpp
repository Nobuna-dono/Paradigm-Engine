#include "Include/HierarchyTree/UHierarchyWidget.h"
#include "Include/HierarchyTree/CustomTreeItem.h"
#include "FParadigmEngine.h"
#include "GameFramework/GameEntity/GEntity.h"
#include "GameFramework/GameGear/LowRenderer/GMeshRender.h"
#include "GameFramework/GameGear/LowRenderer/GMeshShape.h"
#include "GameFramework/GameGear/Physics/GRigidbody.h"
#include "GameFramework/GameGear/Physics/GCollider.h"
#include <Resource\FResourceSupervisor.h>
#include <TKeyTable.h>

namespace ParadigmEditor
{
	UHierarchyWidget::UHierarchyWidget(QWidget* _parent)
	{
		m_Tree = new QTreeWidget(_parent);
		_parent->layout()->addWidget(m_Tree);
		m_Tree->setAutoFillBackground(true);
		m_Tree->setStyleSheet("color: #E2E2E2; background-color: #131414; selection-color: #2F2E2F; selection-background-color: #FFB712");
		m_Tree->setColumnCount(1);
		QStringList hierarchyLabel;
		hierarchyLabel << "Scene 1";

		m_Tree->setHeaderLabels(hierarchyLabel);
		m_Tree->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
		m_Tree->setDragEnabled(true);
		m_Tree->viewport()->setAcceptDrops(true);
		m_Tree->setDropIndicatorShown(true);
		
		m_Tree->setDragDropMode(QAbstractItemView::InternalMove);

		//QObject::connect(m_Tree, &QTreeWidget::chan)
	}

	void UHierarchyWidget::AddItem(UCustomTreeItem* itemParent)
	{
		GEntity entity = GEntity::Instanciate();
		if (!itemParent)
			new UCustomTreeItem(m_Tree, entity.GetMetaKey());
		else
			new UCustomTreeItem(itemParent, entity.GetMetaKey());

		//TArray<UMetaEntity*> children = entity.GetMetaEntity()->GetChildrens();
		//for (uint i = 0; i < children.Count(); ++i)
		//	AddHisChildren(children[i], nullptr);
	}

	void UHierarchyWidget::AddShape(ParadigmEngine::Physics::Collision::EColliderShape _shape, UCustomTreeItem* _itemParent)
	{
		GEntity entity = GEntity::Instanciate(_itemParent ? &GEntity(_itemParent->key) : nullptr);
		GMeshRender meshRender2 = entity.AddGear<GMeshRender>();
		GMeshShape meshShape2 = entity.AddGear<GMeshShape>();
		
		UShader& shader = PARADIGM_RESOURCE->Shader("Resource/Shader/Foo.shader");
		FShader::SetShard(shader, PARADIGM_RESOURCE->ShardShader("Resource/Shader/DebugNormals.vs", "VertexToPixel"));
		FShader::SetShard(shader, PARADIGM_RESOURCE->ShardShader("Resource/Shader/DebugNormals.ps", "PixelToFrameBuffer"));
		meshRender2.SetMaterial(shader);

		//meshRender2.GetMaterial().SetTexture("Albedo", PARADIGM_RESOURCE->Texture("Resource/Mesh/ironman/ironman.dds"));
		
		if (_shape != ParadigmEngine::Physics::Collision::MESH)
		{
			GCollider col2 = entity.AddGear<GCollider>();
			col2.Shape = _shape;
			GRigidbody rig2 = entity.AddGear<GRigidbody>();
		}

		switch (_shape)
		{
			case ParadigmEngine::Physics::Collision::NONE:
				entity.GetMetaEntity()->Name = "Entity";
				break;
			case ParadigmEngine::Physics::Collision::MESH:
				entity.GetMetaEntity()->Name = "Mesh";
				meshShape2.SetModel("Resource/Mesh/ironman/ironman.fbx");
				break;
			case ParadigmEngine::Physics::Collision::BOX:
				entity.GetMetaEntity()->Name = "Cube";
				meshShape2.SetModel("Resource/Model/Primitive/Cube.fbx");
				break;
			case ParadigmEngine::Physics::Collision::SPHERE:
				entity.GetMetaEntity()->Name = "Sphere";
				meshShape2.SetModel("Resource/Model/Primitive/Sphere.fbx");
				break;
			case ParadigmEngine::Physics::Collision::CYLINDER:
				entity.GetMetaEntity()->Name = "Cylinder";
				meshShape2.SetModel("Resource/Model/Primitive/Cylinder.fbx");
				break;
			case ParadigmEngine::Physics::Collision::CONE:
				entity.GetMetaEntity()->Name = "Cone";
				meshShape2.SetModel("Resource/Model/Primitive/Cone.fbx");
				break;
			case ParadigmEngine::Physics::Collision::CAPSULE:
				entity.GetMetaEntity()->Name = "Capsule";
				meshShape2.SetModel("Resource/Model/Primitive/Cylinder.fbx");
				break;
			default:
				break;
		}
		UCustomTreeItem* newItem;
		if (!_itemParent)
			newItem = new UCustomTreeItem(m_Tree, entity.GetMetaKey());
		else
			newItem = new UCustomTreeItem(_itemParent, entity.GetMetaKey());

		SetSelectedItem(newItem);
	}

	void UHierarchyWidget::AddVoidEntity(UCustomTreeItem* _itemParent)
	{
		ParadigmEngine::Core::DataStructure::UKeyHandler<UMetaEntity> keyHandler = PARADIGM_FACTORY->CreateMetaEntity();
		keyHandler.Pointer->Name = "Void";
		UCustomTreeItem* newItem;
		if (_itemParent)
		{
			FMetaEntity::SetParent(keyHandler.Pointer, PARADIGM_FACTORY->GetMetaEntity(_itemParent->key));
			newItem = new UCustomTreeItem(_itemParent, keyHandler.Register);
		}
		else
			newItem = new UCustomTreeItem(m_Tree, keyHandler.Register);

		SetSelectedItem(newItem);
	}
	
	void UHierarchyWidget::SetSelectedItem(UCustomTreeItem* _newSelection)
	{
		//if (m_SelectedItem)
		//	m_Tree->setItemSelected(m_SelectedItem, false);

		m_Tree->setCurrentItem(_newSelection);
		//if (_newSelection != m_SelectedItem)
		//	m_Tree->setItemSelected(_newSelection, true);
		m_SelectedItem = _newSelection;
	}

}