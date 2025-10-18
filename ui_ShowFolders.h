/********************************************************************************
** Form generated from reading UI file 'ShowFolders.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWFOLDERS_H
#define UI_SHOWFOLDERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowFolders
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QPushButton *copyFileButton;
    QPushButton *updateFileButton;
    QListWidget *FileShowList;
    QLabel *messageLabel;
    QVBoxLayout *verticalLayout_3;
    QProgressBar *progressBar;
    QLineEdit *pathLineEdit;
    QPushButton *InstallationButton;

    void setupUi(QWidget *ShowFolders)
    {
        if (ShowFolders->objectName().isEmpty())
            ShowFolders->setObjectName(QString::fromUtf8("ShowFolders"));
        ShowFolders->resize(341, 472);
        gridLayoutWidget = new QWidget(ShowFolders);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 30, 321, 431));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        copyFileButton = new QPushButton(gridLayoutWidget);
        copyFileButton->setObjectName(QString::fromUtf8("copyFileButton"));

        verticalLayout_2->addWidget(copyFileButton);

        updateFileButton = new QPushButton(gridLayoutWidget);
        updateFileButton->setObjectName(QString::fromUtf8("updateFileButton"));

        verticalLayout_2->addWidget(updateFileButton);


        gridLayout->addLayout(verticalLayout_2, 2, 2, 1, 1);

        FileShowList = new QListWidget(gridLayoutWidget);
        FileShowList->setObjectName(QString::fromUtf8("FileShowList"));

        gridLayout->addWidget(FileShowList, 1, 0, 1, 3);

        messageLabel = new QLabel(gridLayoutWidget);
        messageLabel->setObjectName(QString::fromUtf8("messageLabel"));
        messageLabel->setWordWrap(true);

        gridLayout->addWidget(messageLabel, 0, 0, 1, 3);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        progressBar = new QProgressBar(gridLayoutWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        verticalLayout_3->addWidget(progressBar);

        pathLineEdit = new QLineEdit(gridLayoutWidget);
        pathLineEdit->setObjectName(QString::fromUtf8("pathLineEdit"));

        verticalLayout_3->addWidget(pathLineEdit);

        InstallationButton = new QPushButton(gridLayoutWidget);
        InstallationButton->setObjectName(QString::fromUtf8("InstallationButton"));

        verticalLayout_3->addWidget(InstallationButton);


        gridLayout->addLayout(verticalLayout_3, 2, 0, 1, 2);


        retranslateUi(ShowFolders);

        QMetaObject::connectSlotsByName(ShowFolders);
    } // setupUi

    void retranslateUi(QWidget *ShowFolders)
    {
        ShowFolders->setWindowTitle(QCoreApplication::translate("ShowFolders", "Form", nullptr));
        copyFileButton->setText(QCoreApplication::translate("ShowFolders", "MNC_SCADA Files", nullptr));
        updateFileButton->setText(QCoreApplication::translate("ShowFolders", "Update Files", nullptr));
        messageLabel->setText(QCoreApplication::translate("ShowFolders", "TextLabel", nullptr));
        InstallationButton->setText(QCoreApplication::translate("ShowFolders", "Installation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowFolders: public Ui_ShowFolders {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWFOLDERS_H
