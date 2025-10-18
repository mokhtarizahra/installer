/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *mainGridLayout;
    QGridLayout *TreewidgetLayout;
    QLabel *label;
    QGridLayout *ButtonLayout;
    QPushButton *cancelButton;
    QComboBox *modeComboBox;
    QGridLayout *ModuleLayout;
    QLabel *messageLabel;
    QGridLayout *gridLayout_3;
    QLabel *messageLabel2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(764, 590);
        QIcon icon;
        icon.addFile(QString::fromUtf8("Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 30, 711, 511));
        mainGridLayout = new QGridLayout(gridLayoutWidget);
        mainGridLayout->setObjectName(QString::fromUtf8("mainGridLayout"));
        mainGridLayout->setContentsMargins(0, 0, 0, 0);
        TreewidgetLayout = new QGridLayout();
        TreewidgetLayout->setObjectName(QString::fromUtf8("TreewidgetLayout"));
        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        TreewidgetLayout->addWidget(label, 1, 3, 1, 1);


        mainGridLayout->addLayout(TreewidgetLayout, 1, 0, 5, 1);

        ButtonLayout = new QGridLayout();
        ButtonLayout->setObjectName(QString::fromUtf8("ButtonLayout"));
        cancelButton = new QPushButton(gridLayoutWidget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        ButtonLayout->addWidget(cancelButton, 0, 1, 1, 1);

        modeComboBox = new QComboBox(gridLayoutWidget);
        modeComboBox->setObjectName(QString::fromUtf8("modeComboBox"));

        ButtonLayout->addWidget(modeComboBox, 0, 0, 1, 1);


        mainGridLayout->addLayout(ButtonLayout, 5, 4, 1, 1);

        ModuleLayout = new QGridLayout();
        ModuleLayout->setObjectName(QString::fromUtf8("ModuleLayout"));
        messageLabel = new QLabel(gridLayoutWidget);
        messageLabel->setObjectName(QString::fromUtf8("messageLabel"));
        messageLabel->setWordWrap(true);

        ModuleLayout->addWidget(messageLabel, 1, 1, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        messageLabel2 = new QLabel(gridLayoutWidget);
        messageLabel2->setObjectName(QString::fromUtf8("messageLabel2"));
        messageLabel2->setWordWrap(true);

        gridLayout_3->addWidget(messageLabel2, 0, 0, 1, 1);


        ModuleLayout->addLayout(gridLayout_3, 2, 1, 1, 1);


        mainGridLayout->addLayout(ModuleLayout, 0, 4, 5, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 764, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Modje Niro", nullptr));
        label->setText(QString());
        cancelButton->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
        messageLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        messageLabel2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
