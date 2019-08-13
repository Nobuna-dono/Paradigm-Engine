#include "../Include/ParadigmEditor.h"

namespace ParadigmEditor
{
	void FParadigmEditor::SetIcon(const QString& _iconPath)
	{
		setWindowIcon(QIcon(_iconPath));
	}

	QFont FParadigmEditor::ApplyFont(const QString& _fontPath)
	{
		int id = QFontDatabase::addApplicationFont(_fontPath);
		QString fontStr = QFontDatabase::applicationFontFamilies(id).at(0);
		QFont fontStyle(fontStr);

		return fontStyle;
	}

	void FParadigmEditor::SetSplashScreen()
	{
		QSplashScreen paradigmSplashScreen(QPixmap("./Resource/LogoSplashScreen.png"));
		paradigmSplashScreen.setFixedSize(QSize(250, 250));
		paradigmSplashScreen.show();

		LaunchEditor();
		paradigmSplashScreen.close();
	}
}