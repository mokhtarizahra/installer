#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "environmentmanager.h"
#include "modulemanager.h"
#include "ui_mainwindow.h"
#include "TreeWidget.h"
#include "showmessages.h"
#include "ShowFolders.h"
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setWidgetOpacity(QWidget *widget, qreal opacity);
    void showTreeWidget(const QString& radioButtonName);
    void updateCancelButtonText(const QString &itemText);
    void updateActiveItem(const QString& itemText);
    void onCancelButtonClicked();
//    void setupCustomTitleBar();



private:
    ModuleManager* moduleManager;
    TreeWidget* treeWidget;
    QString activeItemText;
    showMessages *m_showMessages;
    ShowFolders *m_showfolders;

    EnvironmentManager *m_environmentManager;


private slots:
    void setupComboBox();
    void onComboBoxChanged(int index);


    void receiveSelectedItem(QString itemText);

signals:
    void modulesListUpdated(const QStringList &modules);
    void activeItemChanged(QString itemText);

};
#endif // MAINWINDOW_H
