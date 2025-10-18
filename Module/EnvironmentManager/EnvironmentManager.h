#ifndef ENVIRONMENTMANAGER_H
#define ENVIRONMENTMANAGER_H

#include <QWidget>
#include <QString>
#include "showmessages.h"
#include "ui_EnvironmentManager.h"




class EnvironmentManager : public QWidget {
    Q_OBJECT
public:
    explicit EnvironmentManager(QWidget *parent);
    bool  setEnvironmentVariable(const QString &name, const QString &value);
    void onSetEnvClicked();
    void setWidgetOpacity(QWidget *widget, qreal opacity);



private:
    Ui::EnvironmentManager ui;
    showMessages *m_showMessages;
    QString destinationFolder;




};

#endif // ENVIRONMENTMANAGER_H
