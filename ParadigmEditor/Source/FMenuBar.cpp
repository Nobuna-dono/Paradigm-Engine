#include "../Include/ParadigmEditor.h"


namespace ParadigmEditor
{
	/* Menu Bar Creation */
	QMenuBar* FParadigmEditor::CreateMenuBar()
	{
		m_MenuBar = this->menuBar();
		m_MenuBar->setStyleSheet("color: #FFB712; background-color: #2F2E2F; selection-color: #2F2E2F; selection-background-color: #FFB712");

		InsertPlayButton();
		InsertPauseButton();

		FileMenu();
		ModeMenu();
		CreateMenu();
		EditorMenu();
		ToolsMenu();

		return m_MenuBar;
	}

	void FParadigmEditor::FileMenu()
	{
		QMenu* fileMenu = m_MenuBar->addMenu(tr("&File"));
		QMenu* addFileMenu = fileMenu->addMenu(tr("Add"));
		QMenu* newFile = addFileMenu->addMenu(tr("New"));
		QAction* newScriptFile = new QAction(tr("&Script"), newFile);
		newScriptFile->setShortcut(Qt::CTRL + Qt::Key_N);
		newFile->addAction(newScriptFile);
		QMenu* existingFile = addFileMenu->addMenu(tr("Existing..."));;
		QAction* existingScriptFile = new QAction(tr("Script"), existingFile);
		existingFile->addAction(existingScriptFile);

		//QMenu* Open = fileMenu->addMenu(tr("Open"));
		//QMenu* Save = fileMenu->addMenu(tr("Save"));
		QAction* Open = new QAction(tr("&Open"), fileMenu);
		Open->setShortcut(Qt::CTRL + Qt::Key_A);
		fileMenu->addAction(Open);
		QAction* Save = new QAction(tr("&Save"), fileMenu);
		Save->setShortcut(Qt::CTRL + Qt::Key_S);
		fileMenu->addAction(Save);

		connect(newScriptFile, &QAction::triggered, this, [=]()
		{
			WriteFile();
		});

		connect(existingScriptFile, &QAction::triggered, this, [=]()
		{
			QString resourcesPath = "./../ParadigmEngine/Resource/";
			QDesktopServices::openUrl(QUrl::fromLocalFile(resourcesPath));
		});

		connect(Open, &QAction::triggered, this, [=]()
		{
			QString resourcesPath = "./../ParadigmEngine/Resource/";
			QDesktopServices::openUrl(QUrl::fromLocalFile(resourcesPath));
		});

		connect(Save, &QAction::triggered, this, [=]()
		{
			QString resourcesPath = "./../ParadigmEngine/Resource/";
			QDesktopServices::openUrl(QUrl::fromLocalFile(resourcesPath));
		});
	}

	void FParadigmEditor::ModeMenu()
	{
		QMenu* modeMenu = m_MenuBar->addMenu(tr("&Mode"));
		QAction* playMode = new QAction(tr("Play"), modeMenu);
		playMode->setShortcut(Qt::Key_F5);
		modeMenu->addAction(playMode);
		modeMenu->addSeparator();
		QAction* pauseMode = new QAction(tr("Pause"), modeMenu);
		pauseMode->setShortcut(Qt::CTRL + Qt::Key_F5);
		modeMenu->addAction(pauseMode);

		connect(playMode, &QAction::triggered, this, [=]()
		{
			m_PlayButton->clicked();
		});

		connect(pauseMode, &QAction::triggered, this, [=]()
		{
			m_PauseButton->clicked();
		});
	}

	void FParadigmEditor::CreateMenu()
	{
		// Void has no component at all
		QMenu* createMenu = m_MenuBar->addMenu(tr("&Create"));
		QAction* createVoid = new QAction(tr("Void"), createMenu);
		createMenu->addAction(createVoid);

		connect(createVoid, &QAction::triggered, this, [=]()
		{
			m_Hierarchy->AddVoidEntity();
		});

		// Entity has a transform
		QAction* createEntity = new QAction(tr("Entity"), createMenu);
		createMenu->addAction(createEntity);

		connect(createEntity, &QAction::triggered, this, [=]()
		{
			m_Hierarchy->AddShape(ParadigmEngine::Physics::Collision::NONE);
		});

		QAction* createMesh = new QAction(tr("Mesh"), createMenu);
		createMenu->addAction(createMesh);

		connect(createMesh, &QAction::triggered, this, [=]()
		{
			m_Hierarchy->AddShape(ParadigmEngine::Physics::Collision::MESH);
		});

		// Cube has a transform + a collider +  a mesh renderer
		QAction* createCube = new QAction(tr("Cube"), createMenu);
		createMenu->addAction(createCube);

		connect(createCube, &QAction::triggered, this, [=]()
		{
			m_Hierarchy->AddShape(ParadigmEngine::Physics::Collision::BOX);
		});

		// Sphere has a transform + a collider +  a mesh renderer
		QAction* createSphere = new QAction(tr("Sphere"), createMenu);
		createMenu->addAction(createSphere);

		connect(createSphere, &QAction::triggered, this, [=]()
		{
			m_Hierarchy->AddShape(ParadigmEngine::Physics::Collision::SPHERE);
		});

		// Cylinder has a transform + a collider +  a mesh renderer
		QAction* createCylinder = new QAction(tr("Cylinder"), createMenu);
		createMenu->addAction(createCylinder);

		connect(createCylinder, &QAction::triggered, this, [=]()
		{
			m_Hierarchy->AddShape(ParadigmEngine::Physics::Collision::CYLINDER);
		});

		// Cone has a transform + a collider +  a mesh renderer
		QAction* createCone = new QAction(tr("Cone"), createMenu);
		createMenu->addAction(createCone);

		connect(createCone, &QAction::triggered, this, [=]()
		{
			m_Hierarchy->AddShape(ParadigmEngine::Physics::Collision::CONE);
		});

		// Capsule has a transform + a collider +  a mesh renderer
		QAction* createCapsule = new QAction(tr("Capsule"), createMenu);
		createMenu->addAction(createCapsule);

		connect(createCapsule, &QAction::triggered, this, [=]()
		{
			m_Hierarchy->AddShape(ParadigmEngine::Physics::Collision::CAPSULE);
		});
	}

	void FParadigmEditor::EditorMenu()
	{
		QMenu* editorMenu = m_MenuBar->addMenu(tr("&Editor"));
		QAction* closeFile = new QAction(tr("Close"), editorMenu);
		editorMenu->addAction(closeFile);

		connect(closeFile, SIGNAL(triggered()), qApp, SLOT(quit()));
	}

	void FParadigmEditor::ToolsMenu()
	{
		QMenu* toolsMenu = m_MenuBar->addMenu(tr("&Tools"));
		toolsMenu->setStyleSheet("color: #E2E2E2; background-color: #131414; selection-color: #2F2E2F; selection-background-color: #FFB712");
		QAction* helpFile = new QAction(tr("Help"), this);
		toolsMenu->addAction(helpFile);
		toolsMenu->addSeparator();
		QAction* creditsFile = new QAction(tr("&Credits"), this);
		toolsMenu->addAction(creditsFile);
	}
}