#include "../Include/ParadigmEditor.h"

namespace ParadigmEditor
{
	void FParadigmEditor::InitAllDocks(QMainWindow* _parent)
	{
		QMenuBar* menuBar = CreateMenuBar();
		m_ProjectDock = CreateProjectDock();
		_parent->addDockWidget(Qt::TopDockWidgetArea, m_ProjectDock);

		m_SceneDock = CreateSceneDock();
		_parent->addDockWidget(Qt::TopDockWidgetArea, m_SceneDock);
		
		m_GameDock = CreateGameDock();
		_parent->addDockWidget(Qt::TopDockWidgetArea, m_GameDock);
		this->tabifyDockWidget(m_GameDock, m_SceneDock);

		m_InspectorDock = CreateInspectorDock();
		_parent->addDockWidget(Qt::TopDockWidgetArea, m_InspectorDock);

		m_ResourcesDock = CreateResourcesDock();
		_parent->addDockWidget(Qt::BottomDockWidgetArea, m_ResourcesDock);

		resizeDocks({/* m_ProjectDock, */m_SceneDock, m_InspectorDock }, { /*150,*/1200,500 }, Qt::Orientation::Horizontal);
		resizeDocks({m_SceneDock, m_ResourcesDock }, {1000, 300 }, Qt::Orientation::Vertical);
	}

}