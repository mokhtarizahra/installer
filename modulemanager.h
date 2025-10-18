#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H

#include <QWidget>
#include "Registry.h"
#include "EnvironmentManager.h"
#include "ShowFolders.h"
#include "InstallApp.h"
#include "RestoreDatabase.h"
#include "SetODBC.h"
#include "showmessages.h"
#include <QString>
#include <QList>
#include <QMap>
#include <QStringList>
#include "ui_Registry.h"
#include "ui_TreeWidget.h"


#include <QTimer>





class MainWindow;

class ModuleManager : public QWidget
{
    Q_OBJECT

public:
    explicit ModuleManager(MainWindow* mainWindow, QWidget *parent = nullptr);
    void showUI(QString itemText);
    const QMap<QString, QStringList>& getRadioButtonModules() const;

    QStringList receiveSelectedMode(const QString &name);
    void setWidgetOpacity(QWidget *widget, qreal opacity);



private:
    QString currentMode;
    QMap<QString, QStringList> radioButtonModules;
    QStringList allModules;
    QString projectDir;
    QMap<QString, QStringList> designerModules;
    QMap<QString, QStringList> hmiModules;
    QMap<QString, QWidget*> activeWidgets;

    MainWindow* mainWindow;
    showMessages* showMsgs;
    QString activeItemText;


public slots:
    void handleActiveItem(QString itemText);




};

#endif // MODULEMANAGER_H
