#include "../Include/ParadigmEditor.h"

namespace ParadigmEditor
{
	/* Log Dock Creation */
	QDockWidget* FParadigmEditor::CreateLogDock()
	{
		QDockWidget* logDock = new QDockWidget(tr("Log"), this);
		logDock->setStyleSheet("color: #FFB712; background-color: #2E2E2F;");
		QTabBar* logTabBar = new QTabBar(logDock);
		QStackedWidget* logStack = new QStackedWidget;
		logDock->setTitleBarWidget(logTabBar);
		logTabBar->addTab("Log");
		QPushButton* logButton = new QPushButton(tr("Coming Soon... Or Not."), logStack);
		logButton->setStyleSheet("color: #E2E2E2;");
		logStack->addWidget(logButton);

		logDock->setWidget(logStack);
		logDock->setTitleBarWidget(logTabBar);

		return logDock;
	}
}