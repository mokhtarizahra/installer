/********************************************************************************
** Form generated from reading UI file 'InstallApp.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSTALLAPP_H
#define UI_INSTALLAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InstallApp
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *messageLabel;
    QPushButton *InstallButton;
    QListWidget *ToolsappList;

    void setupUi(QWidget *InstallApp)
    {
        if (InstallApp->objectName().isEmpty())
            InstallApp->setObjectName(QString::fromUtf8("InstallApp"));
        InstallApp->resize(342, 495);
        gridLayoutWidget = new QWidget(InstallApp);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 30, 321, 431));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        messageLabel = new QLabel(gridLayoutWidget);
        messageLabel->setObjectName(QString::fromUtf8("messageLabel"));
        messageLabel->setWordWrap(true);

        gridLayout->addWidget(messageLabel, 0, 0, 1, 1);

        InstallButton = new QPushButton(gridLayoutWidget);
        InstallButton->setObjectName(QString::fromUtf8("InstallButton"));

        gridLayout->addWidget(InstallButton, 3, 0, 1, 1);

        ToolsappList = new QListWidget(gridLayoutWidget);
        ToolsappList->setObjectName(QString::fromUtf8("ToolsappList"));

        gridLayout->addWidget(ToolsappList, 2, 0, 1, 1);


        retranslateUi(InstallApp);

        QMetaObject::connectSlotsByName(InstallApp);
    } // setupUi

    void retranslateUi(QWidget *InstallApp)
    {
        InstallApp->setWindowTitle(QCoreApplication::translate("InstallApp", "Form", nullptr));
        messageLabel->setText(QCoreApplication::translate("InstallApp", "TextLabel", nullptr));
        InstallButton->setText(QCoreApplication::translate("InstallApp", "InstallApp", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InstallApp: public Ui_InstallApp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSTALLAPP_H
