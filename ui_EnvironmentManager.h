/********************************************************************************
** Form generated from reading UI file 'EnvironmentManager.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENVIRONMENTMANAGER_H
#define UI_ENVIRONMENTMANAGER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EnvironmentManager
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *SetEnvironment;
    QLineEdit *pathLineEdit;
    QLabel *messageLabel;

    void setupUi(QWidget *EnvironmentManager)
    {
        if (EnvironmentManager->objectName().isEmpty())
            EnvironmentManager->setObjectName(QString::fromUtf8("EnvironmentManager"));
        EnvironmentManager->resize(341, 472);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        EnvironmentManager->setWindowIcon(icon);
        gridLayoutWidget = new QWidget(EnvironmentManager);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 30, 321, 431));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        SetEnvironment = new QPushButton(gridLayoutWidget);
        SetEnvironment->setObjectName(QString::fromUtf8("SetEnvironment"));

        gridLayout->addWidget(SetEnvironment, 1, 1, 1, 1);

        pathLineEdit = new QLineEdit(gridLayoutWidget);
        pathLineEdit->setObjectName(QString::fromUtf8("pathLineEdit"));

        gridLayout->addWidget(pathLineEdit, 1, 0, 1, 1);

        messageLabel = new QLabel(gridLayoutWidget);
        messageLabel->setObjectName(QString::fromUtf8("messageLabel"));
        messageLabel->setWordWrap(true);

        gridLayout->addWidget(messageLabel, 0, 0, 1, 2);


        retranslateUi(EnvironmentManager);

        QMetaObject::connectSlotsByName(EnvironmentManager);
    } // setupUi

    void retranslateUi(QWidget *EnvironmentManager)
    {
        EnvironmentManager->setWindowTitle(QCoreApplication::translate("EnvironmentManager", "Modje Niro", nullptr));
        SetEnvironment->setText(QCoreApplication::translate("EnvironmentManager", "Set Environment", nullptr));
        messageLabel->setText(QCoreApplication::translate("EnvironmentManager", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EnvironmentManager: public Ui_EnvironmentManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENVIRONMENTMANAGER_H
