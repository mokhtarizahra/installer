/********************************************************************************
** Form generated from reading UI file 'SetODBC.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETODBC_H
#define UI_SETODBC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetODBC
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *CreateODBC;
    QLabel *messageLabel;

    void setupUi(QWidget *SetODBC)
    {
        if (SetODBC->objectName().isEmpty())
            SetODBC->setObjectName(QString::fromUtf8("SetODBC"));
        SetODBC->resize(342, 475);
        gridLayoutWidget = new QWidget(SetODBC);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 30, 321, 431));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        CreateODBC = new QPushButton(gridLayoutWidget);
        CreateODBC->setObjectName(QString::fromUtf8("CreateODBC"));

        gridLayout->addWidget(CreateODBC, 1, 0, 1, 1);

        messageLabel = new QLabel(gridLayoutWidget);
        messageLabel->setObjectName(QString::fromUtf8("messageLabel"));
        messageLabel->setWordWrap(true);

        gridLayout->addWidget(messageLabel, 0, 0, 1, 1);


        retranslateUi(SetODBC);

        QMetaObject::connectSlotsByName(SetODBC);
    } // setupUi

    void retranslateUi(QWidget *SetODBC)
    {
        SetODBC->setWindowTitle(QCoreApplication::translate("SetODBC", "Form", nullptr));
        CreateODBC->setText(QCoreApplication::translate("SetODBC", "Create ODBC", nullptr));
        messageLabel->setText(QCoreApplication::translate("SetODBC", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetODBC: public Ui_SetODBC {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETODBC_H
