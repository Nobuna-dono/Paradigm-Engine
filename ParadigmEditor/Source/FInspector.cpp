#include "../Include/ParadigmEditor.h"

namespace ParadigmEditor
{
	/* Inspector Dock Creation */
	QDockWidget* FParadigmEditor::CreateInspectorDock()
	{
		QDockWidget* inspectorDock = new QDockWidget(tr("Inspector"), this);
		inspectorDock->setStyleSheet("color: #131414; background-color: #2E2E2F;");
		QVBoxLayout* layout = new QVBoxLayout();
		inspectorDock->setWidget(new QWidget);
		inspectorDock->widget()->setLayout(layout);
		inspectorDock->widget()->setStyleSheet("color: #FFB712;");
		inspectorDock->setMaximumWidth(505);

		m_Inspector = new UInspectorWidget();
		QMenuBar* menuBar = new  QMenuBar(inspectorDock);
		menuBar->setStyleSheet("color: #FFB712;");
		
		TArray<const UArchivableData*> availableGears = PARADIGM_ARCHIVE.GetAvailableGears();

		QMenu* createMenu = menuBar->addMenu(tr("&Create"));
		for (uint i = 0; i < availableGears.Count(); ++i)
		{
			QAction* act = new QAction(tr(availableGears[i]->Name), createMenu);
			createMenu->addAction(act);
			connect(act, &QAction::triggered, this, [=]()
			{				
				m_Inspector->AddGear(availableGears[i]);
			});
		}

		/*QAction* createCollider = new QAction(tr("Collider"), createMenu);
		createMenu->addAction(createCollider);
		connect(createCollider, &QAction::triggered, this, [=]()
		{
			m_Inspector->AddGear(EBasicGear::COLLIDER);
		});

		QAction* createRigidBody = new QAction(tr("RigidBody"), createMenu);
		createMenu->addAction(createRigidBody);
		connect(createRigidBody, &QAction::triggered, this, [=]()
		{
			m_Inspector->AddGear(EBasicGear::RIGIDBODY);
		});

		QAction* createCamera = new QAction(tr("Camera"), createMenu);
		createMenu->addAction(createCamera);
		connect(createCamera, &QAction::triggered, this, [=]()
		{
			m_Inspector->AddGear(EBasicGear::CAMERA);
		});

		QAction* createMeshRender = new QAction(tr("MeshRender"), createMenu);
		createMenu->addAction(createMeshRender);
		connect(createMeshRender, &QAction::triggered, this, [=]()
		{
			m_Inspector->AddGear(EBasicGear::MESHRENDER);
		});

		QAction* createMeshShape = new QAction(tr("MeshShape"), createMenu);
		createMenu->addAction(createMeshShape);
		connect(createMeshShape, &QAction::triggered, this, [=]()
		{
			m_Inspector->AddGear(EBasicGear::MESHSHAPE);
		});

		QAction* createMatViewver = new QAction(tr("MaterialViewver"), createMenu);
		createMenu->addAction(createMatViewver);
		connect(createMatViewver, &QAction::triggered, this, [=]()
		{
			m_Inspector->AddGear(EBasicGear::MATERIALVIEWVER);
		});*/

		layout->addWidget(menuBar);

		connect(m_Hierarchy->GetTreeWidget(), &QTreeWidget::itemSelectionChanged, this, &FParadigmEditor::InspectorInfo);

		return inspectorDock;
	}
}