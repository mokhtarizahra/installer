/********************************************************************************
** Form generated from reading UI file 'Registry.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRY_H
#define UI_REGISTRY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Registry
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *registryButton;
    QLineEdit *pathLineEditRej;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout_13;
    QLabel *messageLabel;
    QGridLayout *gridLayout_10;
    QListWidget *FileShowRegistry;

    void setupUi(QWidget *Registry)
    {
        if (Registry->objectName().isEmpty())
            Registry->setObjectName(QString::fromUtf8("Registry"));
        Registry->resize(340, 476);
        gridLayoutWidget = new QWidget(Registry);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 30, 321, 431));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        registryButton = new QPushButton(gridLayoutWidget);
        registryButton->setObjectName(QString::fromUtf8("registryButton"));

        gridLayout->addWidget(registryButton, 4, 1, 1, 2);

        pathLineEditRej = new QLineEdit(gridLayoutWidget);
        pathLineEditRej->setObjectName(QString::fromUtf8("pathLineEditRej"));

        gridLayout->addWidget(pathLineEditRej, 3, 1, 1, 2);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_13 = new QGridLayout();
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        messageLabel = new QLabel(gridLayoutWidget);
        messageLabel->setObjectName(QString::fromUtf8("messageLabel"));
        messageLabel->setWordWrap(true);

        gridLayout_13->addWidget(messageLabel, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout_13, 3, 1, 1, 1);

        gridLayout_10 = new QGridLayout();
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        FileShowRegistry = new QListWidget(gridLayoutWidget);
        FileShowRegistry->setObjectName(QString::fromUtf8("FileShowRegistry"));
        FileShowRegistry->setEnabled(true);

        gridLayout_10->addWidget(FileShowRegistry, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout_10, 5, 1, 1, 1);


        gridLayout->addLayout(gridLayout_2, 1, 1, 1, 2);


        retranslateUi(Registry);

        QMetaObject::connectSlotsByName(Registry);
    } // setupUi

    void retranslateUi(QWidget *Registry)
    {
        Registry->setWindowTitle(QCoreApplication::translate("Registry", "Form", nullptr));
        registryButton->setText(QCoreApplication::translate("Registry", "RegistryFile", nullptr));
        messageLabel->setText(QCoreApplication::translate("Registry", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Registry: public Ui_Registry {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRY_H
