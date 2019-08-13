/********************************************************************************
** Form generated from reading UI file 'ParadigmEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARADIGMEDITOR_H
#define UI_PARADIGMEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParadigmEditorClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ParadigmEditorClass)
    {
        if (ParadigmEditorClass->objectName().isEmpty())
            ParadigmEditorClass->setObjectName(QStringLiteral("ParadigmEditorClass"));
        ParadigmEditorClass->resize(600, 400);
        menuBar = new QMenuBar(ParadigmEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        ParadigmEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ParadigmEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ParadigmEditorClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ParadigmEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ParadigmEditorClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ParadigmEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ParadigmEditorClass->setStatusBar(statusBar);

        retranslateUi(ParadigmEditorClass);

        QMetaObject::connectSlotsByName(ParadigmEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *ParadigmEditorClass)
    {
        ParadigmEditorClass->setWindowTitle(QApplication::translate("ParadigmEditorClass", "ParadigmEditor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ParadigmEditorClass: public Ui_ParadigmEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARADIGMEDITOR_H
