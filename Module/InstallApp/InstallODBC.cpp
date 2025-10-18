#include "InstallODBC.h"


InstallODBC::InstallODBC()
{

}


void InstallODBC::install()
{
    // First, check if the ODBC Driver is installed or not
    if (isInstall()) {
        qDebug() << "ODBC Driver installed successfully.";
        m_showMessages->showMessage("ODBC Driver installed successfully.", QMessageBox::Information, QMessageBox::Ok);
    } else {
        // If the ODBC Driver is not installed, start the installation process
        QString installerPath3 = "./Module/InstallApp/ODBC/msodbcsql.msi";

        if (QFile::exists(installerPath3)) {
            QProcess process3;
            process3.setProgram("cmd.exe");
            process3.setArguments(QStringList() << "/c" << "start /wait msodbcsql.msi");

            process3.setWorkingDirectory(QFileInfo(installerPath3).absolutePath());
            process3.start();

            if (!process3.waitForStarted()) {
                qDebug() << "Failed to start the ODBC Driver installer!";
            } else {
                qDebug() << "ODBC Driver installer started successfully.";
            }

            if (!process3.waitForFinished()) {
                qDebug() << "Error while waiting for ODBC Driver installer to finish!";
            } else {
                qDebug() << "ODBC Driver installer finished.";
            }

            // After installation, check again if the ODBC Driver is installed or not
            if (isInstall()) {
                qDebug() << "ODBC Driver installed successfully.";
                m_showMessages->showMessage("ODBC Driver installed successfully.", QMessageBox::Information, QMessageBox::Ok);
            } else {
                qDebug() << "ODBC Driver installation failed.";
                m_showMessages->showMessage("ODBC Driver installation failed or not detected!", QMessageBox::Critical, QMessageBox::Ok);
            }
        } else {
            qDebug() << "Checking if file 3 exists:" << installerPath3;
            qDebug() << "Installer 3 exists: " << QFile::exists(installerPath3);
            m_showMessages->showMessage("ODBC Driver installer is missing in the application directory.", QMessageBox::Critical, QMessageBox::Ok);

        }
    }

    if (isInstall()) {
        qDebug() << "ODBC Driver installed successfully.";
        m_showMessages->showMessage("ODBC Driver installed successfully.", QMessageBox::Information, QMessageBox::Ok);
    }

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool InstallODBC::isInstall() {
    try {
        // Check if ODBC Driver is installed in HKEY_CURRENT_USER
        QSettings registry32("HKEY_CURRENT_USER\\SOFTWARE\\WOW6432Node\\ODBC\\ODBCINST.INI", QSettings::NativeFormat);
        QSettings registry64("HKEY_LOCAL_MACHINE\\SOFTWARE\\ODBC\\ODBCINST.INI", QSettings::NativeFormat);

        registry32.setFallbacksEnabled(false);
        registry64.setFallbacksEnabled(false);

        qDebug() << "Checking ODBC registry entries for 32-bit and 64-bit drivers...";

        if (registry32.childGroups().contains("ODBC Drivers") || registry64.childGroups().contains("ODBC Drivers")) {
            QSettings drivers32("HKEY_CURRENT_USER\\SOFTWARE\\WOW6432Node\\ODBC\\ODBCINST.INI\\ODBC Drivers", QSettings::NativeFormat);
            QSettings drivers64("HKEY_LOCAL_MACHINE\\SOFTWARE\\ODBC\\ODBCINST.INI\\ODBC Drivers", QSettings::NativeFormat);

            QStringList installedDrivers32 = drivers32.allKeys();
            QStringList installedDrivers64 = drivers64.allKeys();

            qDebug() << "Installed ODBC Drivers (32-bit, CurrentUser):" << installedDrivers32;
            qDebug() << "Installed ODBC Drivers (64-bit, LocalMachine):" << installedDrivers64;

            return !installedDrivers32.isEmpty() || !installedDrivers64.isEmpty();
        } else {
            qDebug() << "No ODBC Drivers found in the registry.";
            return false;
        }
    } catch (...) {
        qDebug() << "Error accessing registry for ODBC Drivers.";
        return false;
    }
}
