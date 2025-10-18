#ifndef INSTALLMONGO_H
#define INSTALLMONGO_H

#include "showmessages.h"
#include "InstallApp.h"
#include <QString>
#include <QProcess>
#include <QFile>
#include <QSettings>
#include <QCoreApplication>
#include <windows.h>
#include <QDebug>
#include <QObject>
#include <QProgressBar>


//class InstallApp;
class InstallMongo : public QObject {
    Q_OBJECT
public:
    explicit InstallMongo();
    bool isInstall();
    void install();
    void checkAndInstallMongo();



signals:
    void progressUpdated(int value);


private:
    showMessages *m_showMessages;
    QString messages;
//    InstallApp *objinstallapp;


};

#endif // INSTALLMONGO_H
