#include "modulemanager.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileInfo>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QRadioButton>
#include <QRegularExpression>
#include <QIODevice>
#include <QMap>
#include <functional>
#include <QProcess>
#include <QPointer>

QPointer<Registry> ObjRegistry;
QPointer<EnvironmentManager> ObjEnvironment;
QPointer<ShowFolders> ObjShowFolders;






ModuleManager::ModuleManager(MainWindow* mainWindow, QWidget *parent)
    : QWidget(parent), mainWindow(mainWindow)
{

    radioButtonModules["Designer Mode"] = QStringList() <<"Install App"<<"Update & Copy"<< "EnvironmentManager"<<"Restore Database" <<"Set ODBC"<< "Registry Designer" ;
    radioButtonModules["HMI Mode"] = QStringList() << "Module1" << "Module2";


    for (const auto& moduleList : radioButtonModules) {
        allModules.append(moduleList);
    }
    qDebug() << "All modules:" << allModules;

    QString projectDir = QCoreApplication::applicationDirPath();
    projectDir = QDir(projectDir).absolutePath();
    qDebug() << "Project directory:" << projectDir;

}
///////////////////////////////////////////////////////////////////////////////
QStringList ModuleManager::receiveSelectedMode(const QString &name)
{
    currentMode = name;
    qDebug() << "Selected mode ComboBox:" << currentMode;

    if (radioButtonModules.contains(currentMode)) {
        QStringList selectedModules = radioButtonModules[currentMode];
        qDebug() << "Modules for" << currentMode << ":" << selectedModules;

        return  selectedModules;
    } else {
        qWarning() << "No modules found for" << currentMode;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////


void ModuleManager::handleActiveItem(QString itemText)
{
    qDebug() << "ModuleManager received active item:" << itemText;
    activeItemText = itemText;
    showUI(itemText);
}
//////////////////////////////////////////////////////////////////////////////////////
void ModuleManager::showUI(QString itemText) {
    qDebug() << "showUI received itemText:" << itemText;
    qDebug() << "Current selected item in TreeWidget: " << activeItemText;
    QMap<QString, std::function<QWidget*()>> factory;
    if(currentMode=="Designer Mode")
    {
        factory = {
            {"Registry Designer",    [this] { return new Registry(mainWindow); }},
            {"EnvironmentManager",   [this] { return new EnvironmentManager(mainWindow); }},
            {"Update & Copy",        [this] { return new ShowFolders(mainWindow); }},
            {"Install App" ,         [this] { return new InstallApp(mainWindow);}},
            {"Restore Database" ,    [this] { return new RestoreDatabase(mainWindow);}},
            {"Set ODBC" ,            [this] { return new SetODBC(mainWindow);}}
        };

    }
    else if(currentMode=="HMI Mode")
    {

        factory = {
            {"Module1",    [this] { return new Registry(mainWindow); }},
            {"Module2",   [this] { return new EnvironmentManager(mainWindow); }},

        };
    }
    for (auto widget : activeWidgets) {
        if (widget) {
            qDebug() << "Removing widget from layout:" << widget->metaObject()->className();
            mainWindow->ui->ModuleLayout->removeWidget(widget);
            widget->setParent(nullptr);
            widget->hide();
            widget->deleteLater();
        }
    }
    qDeleteAll(activeWidgets);
    activeWidgets.clear();
    mainWindow->ui->ModuleLayout->update();

    if (factory.contains(itemText)) {
        QWidget* newWidget = factory[itemText]();
        qDebug() << "New widget type: " << newWidget->metaObject()->className();


        activeWidgets[itemText] = newWidget;
        mainWindow->ui->ModuleLayout->addWidget(newWidget, 0, 1);
        qDebug() << itemText << " created successfully!";

        //        if (auto* showFoldersWidget = qobject_cast<ShowFolders*>(newWidget)) {
        //                    connect(showFoldersWidget, &ShowFolders::destinationFolderChanged,
        //                            this, &ModuleManager::receiveDestinationFolder); }


    } else {
        qDebug() << "Module not recognized, UI will not be shown.";
    }
}

//////////////////////////////////////////////////////////////////////////////////////
