param(
    [string]$moduleName  
)

$projectDir = (Get-Location).Path

$headerFilePath = Join-Path $projectDir "mainwindow.h"

if (Test-Path $headerFilePath) {
    $contentLines = Get-Content $headerFilePath

    $includeLine = "#include `"$moduleName.h`""

    $insertPosition = $contentLines.IndexOf('#include <QMainWindow>') + 1

    if ($insertPosition -gt 0) {

        if ($contentLines -notcontains $includeLine) {

            $contentLines = $contentLines[0..($insertPosition-1)] + $includeLine + $contentLines[$insertPosition..($contentLines.Length-1)]

            $contentLines | Set-Content $headerFilePath
            Write-Host "Successfully wrote to mainwindow.h"
        } else {
            Write-Host "Module already included in mainwindow.h"
        }
    } else {
        Write-Host "QMainWindow include not found in mainwindow.h"
    }
} else {
    Write-Host "Failed to open mainwindow.h"
}

$proFilePath = Join-Path $projectDir "A.pro"


if (Test-Path $proFilePath) {
    $contentLines = Get-Content $proFilePath

    $includeLine = "include(Module/$moduleName/$moduleName.pri)"

    if ($contentLines -notcontains $includeLine) {
        $contentLines += $includeLine

        $contentLines | Set-Content $proFilePath
        Write-Host "Successfully wrote to A.pro"
    } else {
        Write-Host "Module already included in A.pro"
    }
} else {
    Write-Host "Failed to open A.pro"
}
