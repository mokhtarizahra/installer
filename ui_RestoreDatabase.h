/********************************************************************************
** Form generated from reading UI file 'RestoreDatabase.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESTOREDATABASE_H
#define UI_RESTOREDATABASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RestoreDatabase
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *restoreButton;
    QLineEdit *pathLineEdit;
    QProgressBar *progressBar;
    QLabel *messageLabel;

    void setupUi(QWidget *RestoreDatabase)
    {
        if (RestoreDatabase->objectName().isEmpty())
            RestoreDatabase->setObjectName(QString::fromUtf8("RestoreDatabase"));
        RestoreDatabase->resize(341, 476);
        gridLayoutWidget = new QWidget(RestoreDatabase);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 30, 321, 431));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        restoreButton = new QPushButton(gridLayoutWidget);
        restoreButton->setObjectName(QString::fromUtf8("restoreButton"));

        gridLayout->addWidget(restoreButton, 1, 1, 1, 1);

        pathLineEdit = new QLineEdit(gridLayoutWidget);
        pathLineEdit->setObjectName(QString::fromUtf8("pathLineEdit"));

        gridLayout->addWidget(pathLineEdit, 1, 0, 1, 1);

        progressBar = new QProgressBar(gridLayoutWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        gridLayout->addWidget(progressBar, 2, 0, 1, 2);

        messageLabel = new QLabel(gridLayoutWidget);
        messageLabel->setObjectName(QString::fromUtf8("messageLabel"));
        messageLabel->setWordWrap(true);

        gridLayout->addWidget(messageLabel, 0, 0, 1, 2);


        retranslateUi(RestoreDatabase);

        QMetaObject::connectSlotsByName(RestoreDatabase);
    } // setupUi

    void retranslateUi(QWidget *RestoreDatabase)
    {
        RestoreDatabase->setWindowTitle(QCoreApplication::translate("RestoreDatabase", "Form", nullptr));
        restoreButton->setText(QCoreApplication::translate("RestoreDatabase", "Restore File", nullptr));
        messageLabel->setText(QCoreApplication::translate("RestoreDatabase", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RestoreDatabase: public Ui_RestoreDatabase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESTOREDATABASE_H
