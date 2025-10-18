#include "SetODBC.h"
#include "MainWindow.h"
#include "showmessages.h"
#include "StyleSheetManager.h"
#include <QMessageBox>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QDialog>
#include <QDebug>

#include <winsock2.h>

SetODBC::SetODBC(QWidget *parent)
{

    ui.setupUi(this);

    this->setFixedSize(340, 475);
    setWidgetOpacity(ui.messageLabel, 0.8);

    ui.CreateODBC->setStyleSheet(StyleSheetManager::buttonStyle());
    ui.messageLabel->setText("Please select the Button for Set ODBC.");
    ui.messageLabel->setStyleSheet(StyleSheetManager::LabelStyle());



    connect(ui.CreateODBC, &QPushButton::clicked, this, &SetODBC::createUserAndSetPrivileges);

}
/////////////////////////////////////////////////////////////////////////////////////////////
#include <QGraphicsOpacityEffect>
void SetODBC::setWidgetOpacity(QWidget *widget, qreal opacity)
{
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(widget);
    effect->setOpacity(opacity);
    widget->setGraphicsEffect(effect);
}
////////////////////////////////////////////////////////////////////////////////////////////
void SetODBC::createUserAndSetPrivileges() {

    // Define the path to the PowerShell script
    QString scriptPath = QCoreApplication::applicationDirPath() + "/saauthentiction.ps1";
    createODBCDataandandpowershell(scriptPath);

}

////////////////////////////////////////////////////////////////////////////////////////////
void SetODBC::createODBCDataandandpowershell(const QString &scriptPath)
{

    if (!QFile::exists(scriptPath)) {
        m_showMessages->showMessage(QString("PowerShell script not found: %1").arg(scriptPath), QMessageBox::Critical, QMessageBox::Ok);
        return;
    }

    // Build the PowerShell command for execution
    QString command = QString("powershell.exe -NoProfile -ExecutionPolicy Bypass -File \"%1\"").arg(scriptPath);

    // Create a QProcess to execute the script//  Administrator
    QProcess process;
    process.setProgram("powershell.exe");
    process.setArguments(QStringList()
                         << "-NoProfile"                        // Run without loading a user profile
                         << "-ExecutionPolicy" << "Bypass"      // Allow script execution by bypassing security restrictions
                         << "-File" << scriptPath);             // Specify the path to the script file


#ifdef Q_OS_WIN

    // Modify process arguments to suppress the creation of a console window (Windows-specific)
    process.setCreateProcessArgumentsModifier([](QProcess::CreateProcessArguments *args) {
        args->flags |= CREATE_NO_WINDOW;
    });
#endif

    // Start the process to execute the PowerShell script
    process.start();

    // Wait for the process to finish and check for errors
    if (!process.waitForFinished()) {
        m_showMessages->showMessage("Failed to execute PowerShell script silently.", QMessageBox::Critical, QMessageBox::Ok);  // استفاده از showMessages
        return;
    }

    m_showMessages->showMessage("Restart the system for better performance", QMessageBox::Critical, QMessageBox::Ok);
    m_showMessages->showMessage("Authentication settings updated, user access enabled.", QMessageBox::Information, QMessageBox::Ok);  // استفاده از showMessages

    createODBCDataSourceWithAuth();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QString dsnPath = "SOFTWARE\\ODBC\\ODBC.INI\\ODBC Data Sources";

bool createRegistryKey(const QString &fullPath) {
    QStringList parts = fullPath.split("\\");
    QString currentPath;
    HKEY hKey;
    LONG result;

    for (const QString &part : parts) {
        currentPath += (currentPath.isEmpty() ? "" : "\\") + part;

        result = RegCreateKeyExW(HKEY_CURRENT_USER,
                                 reinterpret_cast<LPCWSTR>(currentPath.utf16()),
                                 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hKey, NULL);

        if (result != ERROR_SUCCESS) {
            qDebug() << "Failed to create registry key:" << currentPath
                     << "Error code:" << result;
            return false;
        }

        RegCloseKey(hKey);
    }

    qDebug() << "Successfully created or verified registry path:" << fullPath;
    return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetODBC::createODBCDataSourceWithAuth(){


    // Create a dialog for the user to input or select a server name
    QDialog dialog(this);
    dialog.setWindowTitle("Enter Server Name");
    dialog.setLayout(new QVBoxLayout(&dialog));

    // Create a dropdown (QComboBox) for server selection
    QComboBox* serverComboBox = new QComboBox(&dialog);
    serverComboBox->addItem("localhost");
    serverComboBox->addItem("");
    serverComboBox->setEditable(true);
    dialog.layout()->addWidget(serverComboBox);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    dialog.layout()->addWidget(buttonBox);


    QObject::connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QObject::connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    dialog.setStyleSheet(StyleSheetManager::dialogStyleSheet());

    QString serverName;
    // Show the dialog and check if the user accepted it
    if (dialog.exec() == QDialog::Accepted) {
        serverName = serverComboBox->currentText();
        if (serverName.isEmpty() ) {
            qDebug() << "User entered empty values.";
            m_showMessages->showMessage("User entered empty values.", QMessageBox::Critical, QMessageBox::Ok);
            return;
        }

        qDebug() << "Server Name:" << serverName;


        // Define the DSN names to be created
        QStringList dsnNames = { "MNC_SCADA", "HIS", "Event_DB","PAYA_ICCP" };
        static const QString userId = "sa";
        static const QString password = "2015@paya";

        QString dsnPath = "SOFTWARE\\ODBC\\ODBC.INI\\ODBC Data Sources";

        if (createRegistryKey(dsnPath)) {
            qDebug() << "ODBC Data Sources key created successfully.";
        } else {
            qDebug() << "Failed to create ODBC Data Sources key.";
        }




        for (const QString& dsnName : dsnNames) {

            QString databaseName = dsnName;
            QString dsnPath64 = QString("SOFTWARE\\ODBC\\ODBC.INI\\%1").arg(dsnName);
            QString dsnPath32 = QString("SOFTWARE\\WOW6432Node\\ODBC\\ODBC.INI\\%1").arg(dsnName);
            QString dsnDataSourcesPath32 = "SOFTWARE\\ODBC\\ODBC.INI\\ODBC Data Sources";
            QString dsnDataSourcesPath64 = "SOFTWARE\\ODBC\\ODBC.INI\\ODBC Data Sources";



            auto createDSN = [&](const QString &dsnPath) {
                HKEY hKey;
                if (RegCreateKeyExW(HKEY_CURRENT_USER, reinterpret_cast<LPCWSTR>(dsnPath.utf16()), 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hKey, NULL) == ERROR_SUCCESS) {
                    RegSetValueExW(hKey, L"Database", 0, REG_SZ, reinterpret_cast<const BYTE *>(databaseName.utf16()), (databaseName.size() + 1) * sizeof(wchar_t));
                    RegSetValueExW(hKey, L"Server", 0, REG_SZ, reinterpret_cast<const BYTE *>(serverName.utf16()), (serverName.size() + 1) * sizeof(wchar_t));
                    RegSetValueExW(hKey, L"Driver", 0, REG_SZ, reinterpret_cast<const BYTE *>(L"SQL Server"), (wcslen(L"SQL Server") + 1) * sizeof(wchar_t));
                    RegSetValueExW(hKey, L"UID", 0, REG_SZ, reinterpret_cast<const BYTE *>(userId.utf16()), (userId.size() + 1) * sizeof(wchar_t));
                    RegSetValueExW(hKey, L"PWD", 0, REG_SZ, reinterpret_cast<const BYTE *>(password.utf16()), (password.size() + 1) * sizeof(wchar_t));
                    RegCloseKey(hKey);
                    qDebug() << "DSN created at" << dsnPath;
                } else {
                    qDebug() << "Failed to create DSN at" << dsnPath << ". Error:" << GetLastError();
                    QString errMsg = QString("Failed to create DSN at %1. Error: %2").arg(dsnPath).arg(GetLastError());
                    m_showMessages->showMessage(errMsg, QMessageBox::Critical, QMessageBox::Ok);
                }
            };

            createDSN(dsnPath32);
            createDSN(dsnPath64);

            HKEY hKeySources32;
            if (RegOpenKeyExW(HKEY_CURRENT_USER, reinterpret_cast<LPCWSTR>(dsnDataSourcesPath32.utf16()), 0, KEY_WRITE | KEY_WOW64_32KEY, &hKeySources32) == ERROR_SUCCESS) {
                RegSetValueExW(hKeySources32, reinterpret_cast<LPCWSTR>(dsnName.utf16()), 0, REG_SZ, reinterpret_cast<const BYTE *>(L"SQL Server"), (wcslen(L"SQL Server") + 1) * sizeof(wchar_t));
                RegCloseKey(hKeySources32);
                qDebug() << "32-bit ODBC Data Source created successfully under HKEY_CURRENT_USER.";
            } else {
                qDebug() << "Failed to open 32-bit ODBC Data Sources registry key under HKEY_CURRENT_USER. Error:" << GetLastError();
                QString errMsg = QString("Failed to open 32-bit ODBC Data Sources registry key under HKEY_CURRENT_USER. Error: %1").arg(GetLastError());
                m_showMessages->showMessage(errMsg, QMessageBox::Critical, QMessageBox::Ok);
            }

            HKEY hKeySources64;
            if (RegOpenKeyExW(HKEY_CURRENT_USER, reinterpret_cast<LPCWSTR>(dsnDataSourcesPath64.utf16()), 0, KEY_WRITE | KEY_WOW64_64KEY, &hKeySources64) == ERROR_SUCCESS) {
                RegSetValueExW(hKeySources64, reinterpret_cast<LPCWSTR>(dsnName.utf16()), 0, REG_SZ, reinterpret_cast<const BYTE *>(L"SQL Server"), (wcslen(L"SQL Server") + 1) * sizeof(wchar_t));
                RegCloseKey(hKeySources64);
                qDebug() << "64-bit ODBC Data Source created successfully under HKEY_CURRENT_USER.";
            } else {
                qDebug() << "Failed to open 64-bit ODBC Data Sources registry key under HKEY_CURRENT_USER. Error:" << GetLastError();
                QString errMsg = QString("Failed to open 64-bit ODBC Data Sources registry key under HKEY_CURRENT_USER. Error: %1").arg(GetLastError());
                m_showMessages->showMessage(errMsg, QMessageBox::Critical, QMessageBox::Ok);
            }
        }



    } else {
        qDebug() << "User canceled the dialog.";
        m_showMessages->showMessage("User canceled the dialog.", QMessageBox::Information, QMessageBox::Ok);
    }
    QStringList dsnNames = { "MNC_SCADA", "HIS", "Event_DB" ,"PAYA_ICCP"};
    for (const QString& dsn : dsnNames){
        QString databaseName = dsn;
        setDefaultDatabaseAndTest(dsn ,databaseName);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
void SetODBC::setDefaultDatabaseAndTest(const QString &dsnName, const QString &databaseName )
{
    HKEY hKey;
    QString dsnPath = QString("SOFTWARE\\ODBC\\ODBC.INI\\%1").arg(dsnName);

    if (RegOpenKeyExW(HKEY_CURRENT_USER, reinterpret_cast<LPCWSTR>(dsnPath.utf16()), 0, KEY_WRITE, &hKey) == ERROR_SUCCESS) {
        if (RegSetValueExW(hKey, L"Database", 0, REG_SZ, reinterpret_cast<const BYTE *>(databaseName.utf16()), (databaseName.size() + 1) * sizeof(wchar_t)) == ERROR_SUCCESS) {
            qDebug() << "Default database set successfully.";
        } else {
            qDebug() << "Failed to set default database. Error:" << GetLastError();
            m_showMessages->showMessage("Failed to set the default database.", QMessageBox::Critical, QMessageBox::Ok);
        }
        RegCloseKey(hKey);
    } else {
        qDebug() << "Failed to open registry key for DSN. Error:" << GetLastError();
        m_showMessages->showMessage("Failed to open registry key for the DSN.", QMessageBox::Critical, QMessageBox::Ok);
        return;
    }

    QProcess process;
    process.start("where sqlcmd");
    process.waitForFinished();
    if (process.exitCode() != 0) {
        qDebug() << "SQLCMD is not installed or not found in PATH.";
        m_showMessages->showMessage("SQLCMD tool is not installed or not found in PATH.", QMessageBox::Critical, QMessageBox::Ok);
        return;
    }

    QStringList arguments;
    arguments << "-U" << "sa"
              << "-P" << "2015@paya"
              << "-S" << "localhost"
              << "-d" << databaseName
              << "-Q" << "SELECT 1";
    process.start("sqlcmd", arguments);
    process.waitForFinished();
    QByteArray output = process.readAllStandardOutput();
    QByteArray errorOutput = process.readAllStandardError();

    if (!output.isEmpty()) {
        qDebug() << "SQL Command Output:" << output;
    }
    if (!errorOutput.isEmpty()) {
        qDebug() << "Error Output:" << errorOutput;
        QString errorStr = QString::fromUtf8(errorOutput);

        QRegExp loginErrorRegex("Login failed for user '([^']+)'");
        if (loginErrorRegex.indexIn(errorStr) != -1) {
            QString userName = loginErrorRegex.cap(1);
            QString errorMessage = QString("Login failed for user \"%1\". Please check the credentials and authentication mode.").arg(userName);
            m_showMessages->showMessage(errorMessage, QMessageBox::Critical, QMessageBox::Ok);
        }

        QRegExp dbErrorRegex("Cannot open database \"([^\"]+)\" requested by the login");
        if (dbErrorRegex.indexIn(errorStr) != -1) {
            QString dbNameFromError = dbErrorRegex.cap(1);
            QString errorMessage = QString("A database named \"%1\" has not been created here. Please restore a database with this name.").arg(dbNameFromError);
            m_showMessages->showMessage(errorMessage, QMessageBox::Critical, QMessageBox::Ok);
        }
    }
    else {
        qDebug() << "Connection test completed successfully.";
        m_showMessages->showMessage("Connection test completed successfully.", QMessageBox::Information, QMessageBox::Ok);
    }

}
