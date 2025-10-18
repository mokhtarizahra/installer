#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QWidget>
#include <QStringList>
#include <QTreeWidget>
#include "ui_TreeWidget.h"
#include "showmessages.h"
#include "StyleSheetManager.h"
#include <QTreeWidget>



class TreeWidget :  public QWidget
{
    Q_OBJECT
public:
    Ui::TreeWidget* ui;
    explicit TreeWidget(QWidget *parent = nullptr);
    void updateTreeWidget(const QStringList& moduleList);
    void updateNavigationButtons();
    void setWidgetOpacity(QWidget *widget, qreal opacity);

private:

    MainWindow* m_mainWindow;
    showMessages *m_showMessages;

signals:
    void itemSelected(QString itemText);

public slots:
    void updateTreeWidgetFromMainWindow(const QStringList &modules);
    void nextItem();
    void previousItem();

};

#endif // TREEWIDGET_H
