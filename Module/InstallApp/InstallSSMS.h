#ifndef INSTALLSSMS_H
#define INSTALLSSMS_H

#include "showmessages.h"
#include <QString>
#include <QDebug>
#include <QSettings>
#include <QMessageBox>
#include <QProcess>
#include <QFile>
#include <QFileInfo>
#include <QObject>


class InstallSSMS: public QObject {
    Q_OBJECT
public:

    explicit InstallSSMS(QObject *parent = nullptr);
    void install();
    bool isInstall();


private:
    showMessages *m_showMessages;
};

#endif // INSTALLSSMS_H
