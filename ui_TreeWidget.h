/********************************************************************************
** Form generated from reading UI file 'TreeWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TREEWIDGET_H
#define UI_TREEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TreeWidget
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QGridLayout *buttonLayout;
    QPushButton *nextButton;
    QPushButton *previousButton;
    QGridLayout *treeLayout;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *TreeWidget)
    {
        if (TreeWidget->objectName().isEmpty())
            TreeWidget->setObjectName(QString::fromUtf8("TreeWidget"));
        TreeWidget->resize(369, 570);
        gridLayoutWidget = new QWidget(TreeWidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 30, 341, 511));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        buttonLayout = new QGridLayout();
        buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));
        nextButton = new QPushButton(gridLayoutWidget);
        nextButton->setObjectName(QString::fromUtf8("nextButton"));

        buttonLayout->addWidget(nextButton, 1, 1, 1, 1);

        previousButton = new QPushButton(gridLayoutWidget);
        previousButton->setObjectName(QString::fromUtf8("previousButton"));

        buttonLayout->addWidget(previousButton, 1, 0, 1, 1);


        gridLayout->addLayout(buttonLayout, 2, 0, 1, 2);

        treeLayout = new QGridLayout();
        treeLayout->setObjectName(QString::fromUtf8("treeLayout"));
        treeWidget = new QTreeWidget(gridLayoutWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setEnabled(true);

        treeLayout->addWidget(treeWidget, 0, 0, 1, 1);


        gridLayout->addLayout(treeLayout, 0, 0, 2, 2);


        retranslateUi(TreeWidget);

        QMetaObject::connectSlotsByName(TreeWidget);
    } // setupUi

    void retranslateUi(QWidget *TreeWidget)
    {
        TreeWidget->setWindowTitle(QCoreApplication::translate("TreeWidget", "Form", nullptr));
        nextButton->setText(QCoreApplication::translate("TreeWidget", "Next", nullptr));
        previousButton->setText(QCoreApplication::translate("TreeWidget", "Previous", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TreeWidget: public Ui_TreeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TREEWIDGET_H
