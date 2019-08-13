#include "Include/ParadigmEditor.h"
#include <QtWidgets/QApplication>
#include<FParadigmEngine.h>

int main(int argc, char* argv[])
{
	PARADIGM.Initialize();
	QApplication a(argc, argv);
	QPalette palette;
	palette.setColor(QPalette::Window, QColor(100, 100, 100, 255));
//	palette.setColor(QPalette::ColorRole::Base, QColor(100,100,100,255));
	a.setPalette(palette);
	//a.setWindowIcon(QIcon("./../ParadigmEngine/Resource/Logo.png"));
	ParadigmEditor::FParadigmEditor editor(750, 500);
	a.setStyle(QStyleFactory::create("Fusion"));


	QFont aldrich = editor.ApplyFont("./Resource/Aldrich-Regular.ttf");
	aldrich.setPointSize(8);
	QApplication::setFont(aldrich);
	
	editor.SetSplashScreen();
	//editor.LaunchEditor();

	editor.showMaximized();

	//a.exec();
	//while (true)
	//{
	//	editor.show();
	//	editor.update();
	//}

	return a.exec();
}