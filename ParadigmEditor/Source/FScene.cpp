#include "../Include/ParadigmEditor.h"
#include "../Include/Scene/FContext.h"
#include "GameFramework/GameEntity/GEntity.h"
#include "GameFramework/GameGear/LowRenderer/GCamera.h"
#include "GameFramework/GameGear/LowRenderer/GMeshRender.h"
#include "GameFramework/GameGear/LowRenderer/GMeshShape.h"
#include "../Resource/FResourceSupervisor.h"
#include <Physics/UTransform.h>
#include "../Include/Scene/CameraMoves.h"

namespace ParadigmEditor
{
	/* Scene Dock Creation */
	QDockWidget* FParadigmEditor::CreateSceneDock()
	{
		QDockWidget* sceneDock = new RenderWidget(ETargetViewport::VIEWPORT_EDITOR, tr("Scene"), this);
		sceneDock->setStyleSheet("color: #131414;");

		GEntity entity = GEntity::Instanciate();
		entity.GetMetaEntity()->GetTransform()->Position = FVector3(0,0,-3);
		GCamera camera = entity.AddGear<GCamera>();
		FMetaEntity::AddGear<CameraMoves>(entity.GetMetaEntity());

		camera.Data.ClearColor = UColor::ParadigmDarkGray;
		camera.Data.DisplayTarget = ETargetViewport::VIEWPORT_EDITOR;

		return sceneDock;
	}

	QDockWidget* FParadigmEditor::CreateGameDock()
	{
		QDockWidget* gameDock = new RenderWidget(ETargetViewport::VIEWPORT_0, tr("Game"), this);
		gameDock->setStyleSheet("color: #131414;");

		//QHBoxLayout* gameLayout = new QHBoxLayout();

		//gameDock->setWidget(new QWidget);
		//gameDock->widget()->setLayout(gameLayout);

		return gameDock;
	}
}