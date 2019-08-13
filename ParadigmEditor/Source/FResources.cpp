#include "../Include/ParadigmEditor.h"

namespace ParadigmEditor
{
	/* Resources Dock Creation */
	QDockWidget* FParadigmEditor::CreateResourcesDock()
	{
		QDockWidget* resourcesDock = new QDockWidget(tr("Resources"), this);
		resourcesDock->setStyleSheet("background-color: #2E2E2F;");
		QVBoxLayout* layout = new QVBoxLayout();

		m_ResourcesFileSysModel = new QFileSystemModel(this);
		m_ResourcesFileSysModel->setRootPath("Resource/");
		m_ResourcesTree = CreateTreeView("color: #FFB712; background-color: #131414; selection-color: #2F2E2F; selection-background-color: #FFB712");
		m_ResourcesTree->setSelectionMode(QAbstractItemView::ExtendedSelection);
		m_ResourcesTree->setModel(m_ResourcesFileSysModel);
		m_ResourcesTree->setRootIndex(m_ResourcesFileSysModel->index("Resource/"));

		layout->addWidget(m_ResourcesTree);

		resourcesDock->setWidget(new QWidget);
		resourcesDock->widget()->setLayout(layout);
		resourcesDock->widget()->resize(1000,200);

		//FFileHandler();
		//connect() // stuff for New -> FFileHandler

		connect(m_ResourcesTree, &QTreeView::doubleClicked, this, &FParadigmEditor::OpenFile);

		return resourcesDock;
	}

	void FParadigmEditor::OpenFile()
	{
		QModelIndex resourcesIndex = m_ResourcesTree->currentIndex();
		QString resourcesPath = m_ResourcesFileSysModel->fileInfo(resourcesIndex).filePath();
		QFileInfo resourcesFileInfo(resourcesPath);
		QString extent = resourcesFileInfo.completeSuffix();

		if (resourcesFileInfo.isFile())
		{
			if (extent == "fbx")
				FPrint::Print("Its an fbx file! OPEN THE MESH VIEWER!!!");
			QDesktopServices::openUrl(QUrl::fromLocalFile(resourcesPath));
		}
	}


	void FParadigmEditor::ReadFile()
	{
		QTextEdit textZone;
		textZone.setGeometry(100, 100, 400, 200);
		textZone.setReadOnly(true);

		QString text;

		QFile file("./../ParadigmEngine/Resource/Log.txt");
		QFile file2("./../ParadigmEngine/Resource/Log.png");

		if (file.open(QIODevice::ReadWrite | QIODevice::Text))
		{
			QTextStream stream(&file);
			while (!stream.atEnd())
			text += stream.readLine() + "/n";
			text.resize(text.size() - 1);
			file.close();
		}
		else
		text = "Error: the file could not have been opened.";

		textZone.setText(text);
		textZone.show();
	}

	void FParadigmEditor::WriteFile()
	{
		QString scriptName;
		if ((scriptName = QInputDialog::getText(NULL, "Create new Scripts", "Please enter the scripts names")).isEmpty())
			QMessageBox::critical(NULL, "ERROR", "No path specified");
		else
		{
			QFile headerFile("./../ParadigmEngine/Resource/" + scriptName + ".h");
			QFile preProcessorFile("./../ParadigmEngine/Resource/" + scriptName + ".cpp");
			headerFile.open(QIODevice::ReadWrite | QIODevice::Text);
			preProcessorFile.open(QIODevice::ReadWrite | QIODevice::Text);
		}
	}

	void FParadigmEditor::CalcFile()
	{
		QString fileName = "Anything.txt";
		QFile file(fileName);
		if (!file.exists())
			QMessageBox::critical(NULL, "ERROR", fileName + " cannot exists.");
		else
		{
			if (!file.copy("ItsCopy.txt"))
				QMessageBox::critical(NULL, "ERROR", "Cannot copy " + fileName);
		}
	}

	void FParadigmEditor::FileHandler()
	{
		QString pathName = QFileDialog::getSaveFileName(this, "Save as...", QDir::homePath(), "Text(*.txt)");
		//getExistingDirectory();
		//getOpenFileName();
		//getOpenFileNames();
	}

	void FParadigmEditor::RemoveFile()
	{
		QString fileName = "Anything.txt";
		if (!QFile::remove(fileName))
			QMessageBox::critical(NULL, "ERROR", "Cannot remove " + fileName);
	}
}