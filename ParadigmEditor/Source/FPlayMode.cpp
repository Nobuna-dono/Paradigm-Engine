#include "../Include/ParadigmEditor.h"

namespace ParadigmEditor
{
	void FParadigmEditor::InsertPlayButton()
	{
		m_PlayButton = new QPushButton(QIcon("./../ParadigmEngine/Resource/PlayButton1.png"), "", m_MenuBar);
		m_PlayButton->setStyleSheet("selection-color: #131414; selection-background-color: #FFB712");
		m_PlayButton->setIconSize(m_PlayButton->size());
		m_PlayButton->setGeometry(QRect(QPoint(600, 20), QSize(40, 40)));

		connect(m_PlayButton, &QPushButton::clicked, this, [=]()
		{
			PlayMode();
		});
		m_PlayButton->setCheckable(false);
	}

	void FParadigmEditor::InsertPauseButton()
	{
		m_PauseButton = new QPushButton(QIcon("./../ParadigmEngine/Resource/PauseButton1.png"), "", m_MenuBar);
		m_PauseButton->setStyleSheet("selection-color: #131414; selection-background-color: #FFB712");
		m_PauseButton->setIconSize(m_PauseButton->size());
		m_PauseButton->setGeometry(QRect(QPoint(640, 20), QSize(40, 40)));

		connect(m_PauseButton, &QPushButton::clicked, this, [=]()
		{
			PauseMode();
		});
		m_PauseButton->setCheckable(false);
	}

	void FParadigmEditor::PlayMode()
	{
		if (m_PlayButton->isCheckable())
		{
			m_PlayButton->setCheckable(false);
			m_PauseButton->setCheckable(false);
			m_SceneDock->setFocus();
			m_SceneDock->setStyleSheet("color:#E2E2E2; background-color: #131414; selection-color: #2F2E2F; selection-background-color: #FFB712");
		}
		else
		{
			m_PlayButton->setCheckable(true);
			m_GameDock->setFocus();
			m_GameDock->setStyleSheet("color: #2F2E2F; background-color: #FFB712; selection-color: #E2E2E2; selection-background-color: #131414");
		}
	}

	void FParadigmEditor::PauseMode()
	{
		if (m_PauseButton->isCheckable())
		{
			m_PauseButton->setCheckable(false);
			m_GameDock->setFocus();
		}
		else
		{
			if (m_PlayButton->isCheckable())
			{
				m_PauseButton->setCheckable(true);
				m_SceneDock->setFocus();
			}
		}
	}
}