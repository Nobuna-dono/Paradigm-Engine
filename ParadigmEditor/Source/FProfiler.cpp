#include "../Include/ParadigmEditor.h"

namespace ParadigmEditor
{
	/* Profiler Dock Creation */
	QDockWidget* FParadigmEditor::CreateProfilerDock()
	{
		QDockWidget* profilerDock = new QDockWidget(tr("Profiler"), this);
		profilerDock->setStyleSheet("color: #FFB712; background-color: #2E2E2F;");
		QTabBar* profilerTabBar = new QTabBar(profilerDock);
		QStackedWidget* profilerStack = new QStackedWidget;
		profilerDock->setTitleBarWidget(profilerTabBar);
		profilerTabBar->addTab("Profiler");
		QPushButton* profilerButton = new QPushButton(tr("Coming Soon... Or Not."), profilerStack);
		profilerButton->setStyleSheet("color: #E2E2E2;");
		profilerStack->addWidget(profilerButton);
		profilerDock->setWidget(profilerStack);
		profilerDock->setTitleBarWidget(profilerTabBar);

		return profilerDock;
	}
}