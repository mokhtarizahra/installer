#ifndef INSTALLAPP_H
#define INSTALLAPP_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include "InstallSQL.h"
#include "InstallMongo.h"
#include "InstallNotepad.h"
#include "InstallODBC.h"
#include "InstallSSMS.h"
#include "InstallVcredist.h"
#include "showmessages.h"
#include "ui_InstallApp.h"

class InstallMongo;
class InstallNotepad;
class InstallApp : public QWidget {
    Q_OBJECT
public:
    explicit InstallApp(QWidget *parent = nullptr);
    ~InstallApp();
    void setWidgetOpacity(QWidget *widget, qreal opacity);
    void checkInstallationStatus();



private slots:
    void onInstallButtonClicked();
    void onSoftwareSelected();

private:
    Ui::InstallApp *ui;
    showMessages *m_showMessages;
    InstallSQL *m_sqlInstaller;
    InstallSSMS *m_ssmsInstaller;
    InstallODBC *m_odbcInstaller;
    InstallVcredist *m_VcredistInstaller;
    InstallMongo *m_mongoInstaller;
    InstallNotepad *m_notepadInstaller;



};

#endif // INSTALLAPP_H
