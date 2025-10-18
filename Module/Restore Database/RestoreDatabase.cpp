#include "RestoreDatabase.h"
#include "StyleSheetManager.h"
#include "MainWindow.h"
#include <windows.h>
#include <Aclapi.h>
#include <sddl.h>

RestoreDatabase::RestoreDatabase(QWidget *parent)
{

    ui.setupUi(this);


    this->setFixedSize(340, 475);
    setWidgetOpacity(ui.messageLabel, 0.8);


    ui.restoreButton->setStyleSheet(StyleSheetManager::buttonStyle());
    ui.messageLabel->setText("Please select the Restore File Button for Restore Database.");
    ui.messageLabel->setStyleSheet(StyleSheetManager::LabelStyle());
    ui.pathLineEdit->setStyleSheet(StyleSheetManager::lineEditStyle());
    ui.progressBar->setStyleSheet(StyleSheetManager::ProgressBarStyle());
    ui.progressBar->setRange(0, 100);
    ui.progressBar->setValue(0);


    connect(ui.restoreButton, &QPushButton::clicked, this, &RestoreDatabase::checkSelectedComponentsUpdateBackup);

}

/////////////////////////////////////////////////////////////////////////////////
#include <QGraphicsOpacityEffect>
void RestoreDatabase::setWidgetOpacity(QWidget *widget, qreal opacity)
{
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(widget);
    effect->setOpacity(opacity);
    widget->setGraphicsEffect(effect);
}
//////////////////////////////////////////////////////////////////////////////////
void RestoreDatabase::checkSelectedComponentsUpdateBackup()
{
    //    nextButton->setDisabled(true);
    QString messages;

    QString sourceFolderPath = QDir::currentPath() + "/Backup"; // Backup folder next to the application

    // Step 1: Get the list of .bak files
    QDir sourceDir(sourceFolderPath);
    QStringList bakFiles = sourceDir.entryList(QStringList() << "*.bak", QDir::Files);

    // Step 2: Check if there are any .bak files
    if (bakFiles.isEmpty()) {
        messages.append(tr("No backup files found in the Backup folder.\n"));
    }

    // Step 3: Select the first .bak file or any file you want
    for (const QString &fileName : bakFiles) {

        QString sourceFilePath = sourceFolderPath + "/" + fileName; // You can select the first file or modify this to select another file

        // Step 4: Display the selected file path
        ui.pathLineEdit->setText(sourceFilePath);

        ui.restoreButton->setEnabled(true);

        restoreDatabase();

        messages.append(tr("The backup file '%1' has been restored successfully.\n").arg(fileName));


    }
    m_showMessages->showMessage(messages); // Show accumulated messages at once

}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void RestoreDatabase::restoreDatabase()
{
    QString filePath = ui.pathLineEdit->text();
    if (filePath.isEmpty()) {
        m_showMessages->showMessage(tr("No backup file selected.\n"));
        return;
    }

    QString messages;

    QString user = "NT SERVICE\\MSSQLSERVER";

    if (setFullAccess(filePath, user)) {
        qDebug() << "Permissions updated successfully!";
        // messages.append("Permissions updated successfully.\n");
    } else {
        qDebug() << "Failed to update permissions!";
        messages.append("Failed to update permissions.\n");
    }


    ui.progressBar->setValue(5);
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={SQL Server};SERVER=localhost;DATABASE=master;MARS_Connection=Yes;");

    if (!db.open()) {
        qDebug() << "Failed to connect to the database:" << db.lastError().text();
        messages.append("Failed to connect to the database: " + db.lastError().text() + "\n");
        m_showMessages->showMessage(messages);
        return;
    }

    ui.progressBar->setValue(15);
    // Query to get the database name from the backup file
    QString backupDetailsQuery = QString("RESTORE HEADERONLY FROM DISK = '%1'").arg(filePath);
    QSqlQuery queryBackupDetails;

    if (!queryBackupDetails.exec(backupDetailsQuery)) {
        qDebug() << "Failed to retrieve backup details:" << queryBackupDetails.lastError().text();
        messages.append("Failed to retrieve backup details: " + queryBackupDetails.lastError().text() + "\n");
        m_showMessages->showMessage(messages);
        return;    }

    QString databaseName;
    while (queryBackupDetails.next()) {
        databaseName = queryBackupDetails.value("DatabaseName").toString();
        break; // Only need the first row
    }

    queryBackupDetails.finish();

    if (databaseName.isEmpty()) {
        messages.append("Failed to retrieve database name from the backup file.\n");
        m_showMessages->showMessage(messages);
        return;    }

    ui.progressBar->setValue(30);
    // Query to get logical names
    QString fileListQuery = QString("RESTORE FILELISTONLY FROM DISK = '%1'").arg(filePath);
    QSqlQuery queryFileList;

    if (!queryFileList.exec(fileListQuery)) {
        qDebug() << "Failed to retrieve file list details:" << queryFileList.lastError().text();
        messages.append("Failed to retrieve file list details: " + queryFileList.lastError().text() + "\n");
        m_showMessages->showMessage(messages);
        return;    }

    QString logicalDataName, logicalLogName;
    while (queryFileList.next()) {
        QString logicalName = queryFileList.value("LogicalName").toString();
        QString physicalName = queryFileList.value("PhysicalName").toString();

        // Identify logical names based on file extensions
        if (physicalName.contains(".mdf")) {
            logicalDataName = logicalName;
        }
        else if (physicalName.contains(".ldf")) {
            logicalLogName = logicalName;
        }
    }

    queryFileList.finish();

    if (logicalDataName.isEmpty() || logicalLogName.isEmpty()) {
        messages.append("Logical file names could not be retrieved.\n");
        m_showMessages->showMessage(messages);
        return;
    }

    ui.progressBar->setValue(50);
    // First attempt to restore database without MOVE
    QString restoreQuery = QString(R"(
                                   RESTORE DATABASE [%1]
                                   FROM DISK = '%2'
                                   WITH REPLACE, RECOVERY;
                                   )").arg(databaseName).arg(filePath);

    QSqlQuery restoreQueryExec;
    if (!restoreQueryExec.exec(restoreQuery)) {
        qDebug() << "Failed to restore database, attempting with MOVE:" << restoreQueryExec.lastError().text();
        messages.append("Failed to restore database, attempting with MOVE: " + restoreQueryExec.lastError().text() + "\n");

        ui.progressBar->setValue(70);
        // Fallback: Restore database with MOVE
        QString restoreQueryWithMove = QString(R"(
                                               RESTORE DATABASE [%1]
                                               FROM DISK = '%2'
                                               WITH
                                               MOVE '%3' TO 'C:\\Program Files\\Microsoft SQL Server\\MSSQL15.MSSQLSERVER\\MSSQL\\DATA\\%1.mdf',
                                               MOVE '%4' TO 'C:\\Program Files\\Microsoft SQL Server\\MSSQL15.MSSQLSERVER\\MSSQL\\DATA\\%1.ldf',
                                               REPLACE,
                                               RECOVERY;
                                               )").arg(databaseName).arg(filePath).arg(logicalDataName).arg(logicalLogName);

        if (!restoreQueryExec.exec(restoreQueryWithMove)) {
            qDebug() << "Failed to restore database with MOVE:" << restoreQueryExec.lastError().text();
            messages.append("Failed to restore database with MOVE: " + restoreQueryExec.lastError().text() + "\n");
            m_showMessages->showMessage(messages);
            return;
        } else {
            ui.progressBar->setValue(100);
            qDebug() << "Database restored successfully using fallback method!";
            messages.append("Database restored successfully using fallback method!\n");
        }
    } else {
        ui.progressBar->setValue(100);
        qDebug() << "Database restored successfully!";
    }
    if(messages!="")
        m_showMessages->showMessage(messages);
    //    m_mainWindow->nextButton->setDisabled(false);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
bool RestoreDatabase::setFullAccess(const QString &filePath, const QString &user)
{
    std::wstring wideFilePath = filePath.toStdWString();
    std::wstring wideUser = user.toStdWString();
    PSECURITY_DESCRIPTOR pSD = nullptr;
    PACL pOldDACL = nullptr;
    DWORD result = GetNamedSecurityInfoW(
                wideFilePath.c_str(),
                SE_FILE_OBJECT,
                DACL_SECURITY_INFORMATION,
                nullptr,
                nullptr,
                &pOldDACL,
                nullptr,
                &pSD
                );

    QString messages;

    if (result != ERROR_SUCCESS) {
        qDebug() << "Failed to get file security info:" << result;
        messages.append(QString("Failed to get file security info. Error Code: %1\n").arg(result));
        m_showMessages->showMessage(messages);
        return false;
    }
    EXPLICIT_ACCESSW ea = {};
    ea.grfAccessPermissions = GENERIC_ALL;
    ea.grfAccessMode = SET_ACCESS;
    ea.grfInheritance = SUB_CONTAINERS_AND_OBJECTS_INHERIT;
    ea.Trustee.TrusteeForm = TRUSTEE_IS_NAME;
    ea.Trustee.TrusteeType = TRUSTEE_IS_USER;
    ea.Trustee.ptstrName = (LPWSTR)wideUser.c_str();
    PACL pNewDACL = nullptr;
    result = SetEntriesInAclW(1, &ea, pOldDACL, &pNewDACL);
    if (result != ERROR_SUCCESS) {
        messages.append(QString("Failed to set entries in ACL. Error Code: %1\n").arg(result));
        qDebug() << "Failed to set entries in ACL:" << result;
        LocalFree(pSD);
        return false;
    }
    result = SetNamedSecurityInfoW(
                (LPWSTR)wideFilePath.c_str(),
                SE_FILE_OBJECT,
                DACL_SECURITY_INFORMATION,
                nullptr,
                nullptr,
                pNewDACL,
                nullptr
                );
    if (result != ERROR_SUCCESS) {
        qDebug() << "Failed to set new file security info:" << result;
        messages.append(QString("Failed to set new file security info. Error Code: %1\n").arg(result));
        m_showMessages->showMessage(messages
                                    , QMessageBox::Critical
                                    , QMessageBox::Ok);
        LocalFree(pNewDACL);
        LocalFree(pSD);
        return false;
    }
    LocalFree(pNewDACL);
    LocalFree(pSD);

    qDebug() << "Permissions updated successfully for" << filePath;
    // messages.append("Permissions updated successfully.\n");
    //        showMessages(messages);
    //        return true;
}
