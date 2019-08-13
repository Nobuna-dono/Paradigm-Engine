#include "Include/HierarchyTree/CustomTreeItem.h"
//#include "FParadigmEngine.h"
#include "EngineFramework/Factory/FFactorySupervisor.h"
#include "Include/QtIncludes.h"

namespace ParadigmEditor
{
	UCustomTreeItem::UCustomTreeItem(UCustomTreeItem* _parent, const UKeyRegister &_key, int _type) : QTreeWidgetItem(_parent, _type) , key{_key}
	{
		entity = PARADIGM_FACTORY->GetMetaEntity(_key);
		setText(0, entity->Name.GetData());
		//QObject::connect(this, &QTreeWidgetItem::)
	}

	UCustomTreeItem::UCustomTreeItem(QTreeWidget* _parent, const UKeyRegister &_key, int _type) : QTreeWidgetItem(_parent, _type), key{ _key }
	{
		entity = PARADIGM_FACTORY->GetMetaEntity(_key);
		setText(0, entity->Name.GetData());
	}
}