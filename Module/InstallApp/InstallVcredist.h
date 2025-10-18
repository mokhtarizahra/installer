#ifndef INSTALLVCREDIST_H
#define INSTALLVCREDIST_H


#include "showmessages.h"
#include <QObject>


class InstallVcredist: public QObject {
    Q_OBJECT
public:

    explicit InstallVcredist(QObject *parent = nullptr);
    void install() ;
    bool isInstall() ;

private:
    showMessages *m_showMessages;

};

#endif // INSTALLVCREDIST_H
