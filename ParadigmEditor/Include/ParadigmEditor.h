#ifndef _PARADIGMEDITOR_H_
#define _PARADIGMEDITOR_H_

#include "QtIncludes.h"
#include "../Include/InspectorField/UInspectorWidget.h"
#include "../Include/HierarchyTree/UHierarchyWidget.h"
#include "FParadigmEngine.h"

namespace ParadigmEditor
{
	class FParadigmEditor : public QMainWindow
	{
		Q_OBJECT

	public:
		FParadigmEditor(int _width, int _height);

	public:
		/* Creation of Multiple Widgets with colors according to our engine */
		QWidget* CreateSampleWidget(const QString& _style);
		QWidget* CreateSampleWidget(const QString& _style, QWidget* _parent);

		QWidget* CreateTextWidget(const QString& _style);
		QWidget* CreateTextWidget(const QString& _style, QWidget* _parent);

		QTreeView* CreateTreeView(const QString& _style);
		QTreeView* CreateTreeView(const QString& _style, QWidget* _parent);

		QTreeWidget* CreateTreeWidget(const QString& _style);
		QTreeWidget* CreateTreeWidget(const QString& _style, QWidget* _parent);

		/* Creation of specific functions for each tab */
		QMenuBar* CreateMenuBar();
		void FileMenu();
		void ModeMenu();
		void CreateMenu();
		void EditorMenu();
		void ToolsMenu();

		void PlayMode();
		void PauseMode();
		void InsertPlayButton();
		void InsertPauseButton();

		QTreeWidget* CreateTreeHierarchy();
		QDockWidget* CreateProjectDock();
		QDockWidget* CreateSceneDock();
		QDockWidget* CreateGameDock();
		QDockWidget* CreateInspectorDock();
		QDockWidget* CreateResourcesDock();
		QDockWidget* CreateLogDock();
		QDockWidget* CreateProfilerDock();

		void OpenFile();
		void ReadFile();
		void WriteFile();
		void CalcFile();
		void FileHandler();
		void RemoveFile();
		//void FRenameFile();

	public:
		void InspectorInfo(/*QTreeWidgetItem* _item, int _column*/);

		void SetIcon(const QString& _iconPath);
		QFont ApplyFont(const QString& _fontPath);

	public:
		/* Fill several widgets at once to display all the widgets */
		void SetSplashScreen();

	public:
		/* Initializations */
		void InitAllDocks(QMainWindow* _parent);
		void LaunchEditor();

		QTimer* Timer;
		
	private:
		int m_Width;
		int m_Height;
		
		QTreeWidget* m_HierarchyTree;

		QFileSystemModel* m_ResourcesFileSysModel;
		QTreeView* m_ResourcesTree;
		QLineEdit* m_ClassEdit;

		QPushButton* m_PlayButton;
		QPushButton* m_PauseButton;
		QMenuBar* m_MenuBar;

		UHierarchyWidget* m_Hierarchy{ nullptr };
		UInspectorWidget* m_Inspector{ nullptr };

		QTabBar* m_SceneTabBar;
		QDockWidget* m_ProjectDock;
		QDockWidget* m_InspectorDock;
		QDockWidget* m_SceneDock;
		QDockWidget* m_GameDock;
		QDockWidget* m_ResourcesDock;
	};
}

#endif