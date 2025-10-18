#include "ui_TreeWidget.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "TreeWidget.h"
#include <QDebug>
#include <QTreeWidget>
#include <QMouseEvent>
#include <QGraphicsOpacityEffect>



TreeWidget::TreeWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::TreeWidget)
{
    qDebug() << "TreeWidget constructor called!";
    ui->setupUi(this);    
    ui->treeWidget->installEventFilter(this);
    setWidgetOpacity(ui->treeWidget, 0.9);

    this->setFixedSize(370, 570);

    connect(ui->nextButton, &QPushButton::clicked, this, &TreeWidget::nextItem);
    connect(ui->previousButton, &QPushButton::clicked, this, &TreeWidget::previousItem);
    connect(ui->treeWidget, &QTreeWidget::currentItemChanged, this,
            [this](QTreeWidgetItem *current, QTreeWidgetItem *previous) {
        if (current) {
            emit itemSelected(current->text(0));
        }
    });

    QHeaderView *header = ui->treeWidget->header();
    header->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->treeWidget->setHeaderLabels({"Installer Setup"});

    ui->treeWidget->setStyleSheet(StyleSheetManager::treeWidget());
    ui->treeWidget->header()->setStyleSheet(StyleSheetManager::header());
    ui->previousButton->setStyleSheet(StyleSheetManager::buttonStyle());
    ui->nextButton->setStyleSheet(StyleSheetManager::buttonStyle());

}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//Get the list of modules from the main class
void TreeWidget::updateTreeWidgetFromMainWindow(const QStringList &modules)
{
    qDebug() << "Connected to updateTreeWidgetFromMainWindow!";
    qDebug() << "Modules received:" << modules;

    ui->treeWidget->clear();
    for (const QString &module : modules) {
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
        item->setText(0, module);
    }
    updateTreeWidget(modules);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void TreeWidget::updateTreeWidget(const QStringList& moduleList)
{

    qDebug() << "Updating TreeWidget with" << moduleList.size() << "modules.";

    ui->treeWidget->clear();
    ui->treeWidget->setColumnCount(1);

    QTreeWidgetItem* welcomeItem = new QTreeWidgetItem(ui->treeWidget);
    welcomeItem->setText(0, "Welcome");

    foreach (const QString& module, moduleList) {
        QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
        item->setText(0, module);
    }

    QTreeWidgetItem* finishItem = new QTreeWidgetItem(ui->treeWidget);
    finishItem->setText(0, "Finish");

    qDebug() << "TreeWidget updated with modules:" << moduleList;

    if (ui->treeWidget->topLevelItemCount() > 0) {
        ui->treeWidget->setCurrentItem(welcomeItem);
        emit itemSelected(welcomeItem->text(0));
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void TreeWidget::previousItem()
{
    QTreeWidgetItem *currentItem = ui->treeWidget->currentItem();
    if (!currentItem) return;

    QTreeWidgetItem *prevItem = ui->treeWidget->itemAbove(currentItem);
    if (prevItem) {
        ui->treeWidget->blockSignals(true);
        ui->treeWidget->setCurrentItem(prevItem);
        ui->treeWidget->blockSignals(false);
        emit itemSelected(prevItem->text(0));

    }
    updateNavigationButtons();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void TreeWidget::nextItem()
{
    QTreeWidgetItem *currentItem = ui->treeWidget->currentItem();
    if (!currentItem) return;

    QString itemText = currentItem->text(0);

    QTreeWidgetItem *nextItem = ui->treeWidget->itemBelow(currentItem);
    if (nextItem) {
        ui->treeWidget->blockSignals(true);
        ui->treeWidget->setCurrentItem(nextItem);
        ui->treeWidget->blockSignals(false);
        emit itemSelected(nextItem->text(0));
    }
    updateNavigationButtons();
}
/////////////////////////////////////////////////////////////////////////
void TreeWidget::updateNavigationButtons()
{
    QTreeWidgetItem *currentItem = ui->treeWidget->currentItem();
    if (!currentItem) return;

    QTreeWidgetItem *prevItem = ui->treeWidget->itemAbove(currentItem);
    ui->previousButton->setEnabled(prevItem != nullptr);

    QTreeWidgetItem *nextItem = ui->treeWidget->itemBelow(currentItem);
    ui->nextButton->setEnabled(nextItem != nullptr);

}
///////////////////////////////////////////////////////////////////////////
void TreeWidget::setWidgetOpacity(QWidget *widget, qreal opacity)
{
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(widget);
    effect->setOpacity(opacity);
    widget->setGraphicsEffect(effect);
}
