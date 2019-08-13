#include "../Include/ParadigmEditor.h"

namespace ParadigmEditor
{
	QWidget* FParadigmEditor::CreateSampleWidget(const QString& _color)
	{
		QWidget* widget = new QWidget(this);
		widget->setAutoFillBackground(true);
		widget->setStyleSheet(_color);

		return widget;
	}

	QWidget* FParadigmEditor::CreateSampleWidget(const QString& _color, QWidget* _parent)
	{
		QWidget* widget = new QWidget(_parent);
		widget->setAutoFillBackground(true);
		widget->setStyleSheet(_color);

		return widget;
	}

	QWidget* FParadigmEditor::CreateTextWidget(const QString& _color)
	{
		QWidget* widget = new QWidget(this);
		widget->setAutoFillBackground(true);
		widget->setStyleSheet(_color);

		return widget;
	}

	QWidget* FParadigmEditor::CreateTextWidget(const QString& _color, QWidget* _parent)
	{
		QWidget* widget = new QWidget(_parent);
		widget->setAutoFillBackground(true);
		widget->setStyleSheet(_color);

		return widget;
	}

	QTreeView* FParadigmEditor::CreateTreeView(const QString& _color)
	{
		QTreeView* treeView = new QTreeView(this);
		treeView->setStyleSheet(_color);

		return treeView;
	}

	QTreeView* FParadigmEditor::CreateTreeView(const QString& _color, QWidget* _parent)
	{
		QTreeView* treeView = new QTreeView(_parent);
		treeView->setStyleSheet(_color);

		return treeView;
	}

	QTreeWidget* FParadigmEditor::CreateTreeWidget(const QString& _color)
	{
		QTreeWidget* treeWidget = new QTreeWidget(this);
		treeWidget->setStyleSheet(_color);

		return treeWidget;
	}

	QTreeWidget* FParadigmEditor::CreateTreeWidget(const QString& _color, QWidget* _parent)
	{
		QTreeWidget* treeWidget = new QTreeWidget(_parent);
		treeWidget->setStyleSheet(_color);

		return treeWidget;
	}
}