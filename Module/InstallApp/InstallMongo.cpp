#include "InstallMongo.h"
#include "ui_InstallApp.h"
#include <QProcess>
#include <QObject>
#include <windows.h>
#include <QTimer>


InstallMongo::InstallMongo()
{
}

bool InstallMongo::isInstall() {
    QString defaultPath = "C:/Program Files/MongoDB/Server/4.4/";

    if (QFile::exists(defaultPath)) {
        qDebug() << "MongoDB is installed at:" << defaultPath;
        return true;
    }

    qDebug() << "MongoDB is not installed.";
    return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
#include <windows.h>

void InstallMongo::install() {

    QString msiFilePath = QCoreApplication::applicationDirPath() + "/Module/InstallApp/tools/mongodb-windows-x86_64-enterprise-4.4.0-signed.msi";

    if (!QFile::exists(msiFilePath)) {
        m_showMessages->showMessage("Installation file not found!");
        return;
    }

    SHELLEXECUTEINFOA sei = { sizeof(SHELLEXECUTEINFOA) };
    sei.lpVerb = "open";
    sei.lpFile = msiFilePath.toStdString().c_str();
    sei.lpParameters = nullptr;
    sei.nShow = SW_SHOWNORMAL;
    sei.fMask = SEE_MASK_NOCLOSEPROCESS;


    if (!ShellExecuteExA(&sei)) {
        m_showMessages->showMessage("Failed to start installation process. Try running as administrator.");
        return;
    }


    WaitForSingleObject(sei.hProcess, INFINITE);
    CloseHandle(sei.hProcess);


    if (isInstall()) {
        m_showMessages->showMessage("MongoDB installation completed successfully.");
    } else {
        m_showMessages->showMessage("MongoDB installation failed or was not completed. Please check the installation.");
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void InstallMongo::checkAndInstallMongo() {
    if (!isInstall()) {
        qDebug() << "MongoDB is not installed. Installing now...";
        install();
    } else {
        qDebug() << "MongoDB is already installed.";
        m_showMessages->showMessage("MongoDB is already installed.");
    }
}
