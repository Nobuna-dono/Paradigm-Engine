#include "Include/ParadigmEditor.h"
#include <FParadigmEngine.h>

namespace ParadigmEditor
{
	FParadigmEditor::FParadigmEditor(int _width, int _height)
		: m_Width{ _width }, m_Height{ _height }
	{
		Timer = new QTimer();
		Timer->start(0);
	}

	//~FParadigmEditor::FParadigmEditor()
	/* Editor Launcher */
	void FParadigmEditor::LaunchEditor()
	{
		InitAllDocks(this);
	}
}