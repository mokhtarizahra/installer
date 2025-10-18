#include "InstallNotepad.h"
#include "MainWindow.h"
#include <QProcess>
#include <QObject>
#include <windows.h>
#include <QTimer>

InstallNotepad::InstallNotepad()
{

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool InstallNotepad::isInstall() {
    QStringList defaultPaths = {
        "C:/Program Files/Notepad++/notepad++.exe",
        "C:/Program Files (x86)/Notepad++/notepad++.exe"
    };

    for (const QString &path : defaultPaths) {
        if (QFile::exists(path)) {
            qDebug() << "Notepad++ is installed in default location:" << path;
            return true;
        }
    }

    QStringList registryPaths = {
        "HKEY_LOCAL_MACHINE\\SOFTWARE\\Notepad++",
        "HKEY_LOCAL_MACHINE\\SOFTWARE\\WOW6432Node\\Notepad++",
        "HKEY_LOCAL_MACHINE\\SOFTWARE\\Classes\\*\\shell\\ANotepad++64"
    };

    for (const QString &path : registryPaths) {
        QSettings reg(path, QSettings::NativeFormat);

        QString installPath;
        if (path.contains("ANotepad++64")) {
            QString dllPath = reg.value("(Default)").toString();
            installPath = dllPath.left(dllPath.lastIndexOf("\\contextMenu"));
        } else {
            installPath = reg.value("InstallLocation").toString();
        }

        if (!installPath.isEmpty() && QFile::exists(installPath + "/notepad++.exe")) {
            qDebug() << "Notepad++ is installed via registry.";
            qDebug() << "Install Path:" << installPath;
            return true;
        }
    }

    qDebug() << "Notepad++ is not installed.";
    return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InstallNotepad::install() {
    QString installerPath = "./Module/InstallApp/tools/npp.8.7.5.Installer.x64.exe";
    QString installDir = "C:/Notepad++";

    if (!QFile::exists(installerPath)) {
        m_showMessages->showMessage("Installer not found!");
        return;
    }

    // اجرای نصب بی‌صدا
    m_showMessages->showMessage("Notepad++ is not installed. Installation has started.\n");
    QProcess *process = new QProcess(this);
    QStringList arguments = {"/S", QString("INSTALLDIR=%1").arg(installDir)};


    QObject::connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                     [=](int exitCode, QProcess::ExitStatus exitStatus) {

        if (exitStatus == QProcess::NormalExit && exitCode == 0) {
            QTimer::singleShot(500, [=]() {
            });
            m_showMessages->showMessage("Notepad++ installation completed successfully!");

        } else {
            m_showMessages->showMessage("Installation failed!");
        }
        process->deleteLater();
    });


    process->start(installerPath, arguments);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InstallNotepad::checkAndInstall() {
    if (!isInstall()) {
        qDebug() << "Notepad++ is not installed. Installing now...";
        install();
        //        n_mainWindow->showMessages("Notepad++ is not installed. Installation has started.\n");
    } else {
        qDebug() << "Notepad++ is already installed.";
        m_showMessages->showMessage("Notepad++ is already installed.\n");
    }
}
