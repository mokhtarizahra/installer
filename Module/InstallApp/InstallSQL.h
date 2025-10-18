#ifndef INSTALLSQL_H
#define INSTALLSQL_H

#include <QString>
#include <QDebug>
#include <QSettings>
#include <QProcess>
#include <QFile>
#include <QFileInfo>
#include <QObject>
#include "showmessages.h"

class InstallSQL : public QObject {
    Q_OBJECT
public:
    explicit InstallSQL(QObject *parent = nullptr);
    void install();
    bool isInstall();


private:
    showMessages *m_showMessages;
};

#endif // INSTALLSQL_H
