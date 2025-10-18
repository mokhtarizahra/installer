#ifndef INSTALLODBC_H
#define INSTALLODBC_H

#include "showmessages.h"
#include <QString>
#include <QDebug>
#include <QSettings>
#include <QMessageBox>
#include <QProcess>
#include <QFile>
#include <QFileInfo>

class InstallODBC
{
public:
    InstallODBC();
     void install();
     bool isInstall();


private:
    showMessages *m_showMessages;
};

#endif // INSTALLODBC_H
