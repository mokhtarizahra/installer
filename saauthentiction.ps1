$serverName = "localhost"
$connectionString = "Server=$serverName;Integrated Security=True;TrustServerCertificate=True"

$loginName = "sa"         
$newPassword = "2015@paya" 

$sqlConnection = New-Object System.Data.SqlClient.SqlConnection
$sqlConnection.ConnectionString = $connectionString

$sqlConnection.Open()

$checkLoginQuery = "SELECT name FROM sys.server_principals WHERE name = '$loginName';"
$command = $sqlConnection.CreateCommand()
$command.CommandText = $checkLoginQuery
$reader = $command.ExecuteReader()

if ($reader.HasRows) {
    $reader.Close()

    $enableLoginQuery = "ALTER LOGIN $loginName ENABLE;"
    $command.CommandText = $enableLoginQuery
    $command.ExecuteNonQuery()

    $changePasswordQuery = "ALTER LOGIN $loginName WITH PASSWORD = '$newPassword';"
    $command.CommandText = $changePasswordQuery
    $command.ExecuteNonQuery()

    # تنظیمات برای غیرفعال کردن Enforce password policy و Enforce password expiration
    $disablePasswordPolicyQuery = "ALTER LOGIN $loginName WITH CHECK_POLICY = OFF, CHECK_EXPIRATION = OFF;"
    $command.CommandText = $disablePasswordPolicyQuery
    $command.ExecuteNonQuery()

    $grantConnectQuery = "GRANT CONNECT TO $loginName;"
    $command.CommandText = $grantConnectQuery
    $command.ExecuteNonQuery()

    Write-Host "Login 'sa' enabled, password changed, and CONNECT permission granted successfully."
}
else {
    $reader.Close()

    $createLoginQuery = "CREATE LOGIN $loginName WITH PASSWORD = '$newPassword';"
    $command.CommandText = $createLoginQuery
    $command.ExecuteNonQuery()

    Write-Host "Login 'sa' created successfully."

    $enableLoginQuery = "ALTER LOGIN $loginName ENABLE;"
    $command.CommandText = $enableLoginQuery
    $command.ExecuteNonQuery()

    $grantConnectQuery = "GRANT CONNECT TO $loginName;"
    $command.CommandText = $grantConnectQuery
    $command.ExecuteNonQuery()

    Write-Host "Login 'sa' enabled, and CONNECT permission granted successfully."
}

$sqlConnection.Close()
Write-Host "Checking connection to $serverName..."
try {
    Invoke-Sqlcmd -ConnectionString $connectionString -Query "SELECT 1" 
    Write-Host "Connection successful to $serverName"
} catch {
    Write-Error "Error connecting to ${serverName}: $($_.Exception.Message)"
}

Write-Host "Checking current LoginMode on $serverName..."
$loginModeQuery = "SELECT SERVERPROPERTY('IsIntegratedSecurityOnly') AS LoginMode"
try {
    $loginMode = Invoke-Sqlcmd -ConnectionString $connectionString -Query $loginModeQuery
    Write-Host "Current LoginMode: $($loginMode.LoginMode)"
} catch {
    Write-Error "Error executing query to check LoginMode: $($_.Exception.Message)"
}

Write-Host "Changing LoginMode to Mixed Mode via Registry..."

$updateLoginModeQuery = @"
    EXEC xp_instance_regwrite N'HKEY_LOCAL_MACHINE', N'Software\Microsoft\MSSQLServer\MSSQLServer', N'LoginMode', REG_DWORD, 2;
"@

try {
    Invoke-Sqlcmd -ConnectionString $connectionString -Query $updateLoginModeQuery
    Write-Host "LoginMode changed to Mixed Mode."
} catch {
    Write-Error "Error changing LoginMode: $($_.Exception.Message)"
}

Write-Host "You may need to restart SQL Server for the changes to take effect."
