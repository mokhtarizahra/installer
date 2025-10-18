/********************************************************************************
** Form generated from reading UI file 'Designer.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DESIGNER_H
#define UI_DESIGNER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Designer
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *registryButton;
    QLineEdit *pathLineEditRej;
    QListWidget *FileShowRegistry;
    QLabel *messageLabel;

    void setupUi(QWidget *Designer)
    {
        if (Designer->objectName().isEmpty())
            Designer->setObjectName(QString::fromUtf8("Designer"));
        Designer->resize(400, 300);
        gridLayoutWidget = new QWidget(Designer);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(180, 10, 201, 281));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        registryButton = new QPushButton(gridLayoutWidget);
        registryButton->setObjectName(QString::fromUtf8("registryButton"));

        gridLayout->addWidget(registryButton, 2, 2, 1, 1);

        pathLineEditRej = new QLineEdit(gridLayoutWidget);
        pathLineEditRej->setObjectName(QString::fromUtf8("pathLineEditRej"));

        gridLayout->addWidget(pathLineEditRej, 2, 1, 1, 1);

        FileShowRegistry = new QListWidget(gridLayoutWidget);
        FileShowRegistry->setObjectName(QString::fromUtf8("FileShowRegistry"));

        gridLayout->addWidget(FileShowRegistry, 1, 1, 1, 2);

        messageLabel = new QLabel(gridLayoutWidget);
        messageLabel->setObjectName(QString::fromUtf8("messageLabel"));

        gridLayout->addWidget(messageLabel, 0, 1, 1, 2);


        retranslateUi(Designer);

        QMetaObject::connectSlotsByName(Designer);
    } // setupUi

    void retranslateUi(QWidget *Designer)
    {
        Designer->setWindowTitle(QCoreApplication::translate("Designer", "Form", nullptr));
        registryButton->setText(QCoreApplication::translate("Designer", "RegistryFile", nullptr));
        messageLabel->setText(QCoreApplication::translate("Designer", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Designer: public Ui_Designer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DESIGNER_H
