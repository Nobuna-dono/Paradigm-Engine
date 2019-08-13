#ifndef _CUSTOMTREEITEM_H_
#define _CUSTOMTREEITEM_H_
#include "../QtIncludes.h"
#include "IKeyTable.h"
#include "EngineFramework/Factory/UMetaEntity.h"

namespace ParadigmEditor
{
	class UCustomTreeItem : public QTreeWidgetItem
	{
	public:
		UCustomTreeItem(UCustomTreeItem *parent, const UKeyRegister &_key, int _type = Type);
		UCustomTreeItem(QTreeWidget *parent, const UKeyRegister &_key, int _type = Type);
		~UCustomTreeItem() = default;

//		QString name;
		UKeyRegister key;
		UMetaEntity* entity;

	private:
	};
}

#endif // !_CUSTOMTREEITEM_H_
