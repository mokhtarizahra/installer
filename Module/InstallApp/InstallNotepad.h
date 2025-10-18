#ifndef INSTALLNOTEPAD_H
#define INSTALLNOTEPAD_H


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

//class InstallApp;
class InstallNotepad: public QObject {
    Q_OBJECT
public:

    explicit InstallNotepad();
    bool isInstall();
    void install();
    void checkAndInstall();



signals:
    void progressUpdated(int value);



private:
    showMessages *m_showMessages;
    QString messages;

};

#endif // INSTALLNOTEPAD_H
