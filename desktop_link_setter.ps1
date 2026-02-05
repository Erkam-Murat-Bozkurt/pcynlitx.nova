
function New-Shortcut {
param (
[Parameter(Mandatory = $true)]
$ShortcutLocation,
[Parameter(Mandatory = $true)]
$ShortcutName,
[Parameter(Mandatory = $true)]
$IconPath,
[Parameter(Mandatory = $true)]
$WorkingDirectory,
$TargetPath,
$Arguments
)

$ShortCutPath = $ShortcutLocation +  ".lnk"
$WScriptShell = New-Object -ComObject WScript.Shell
$Shortcut = $WScriptShell.CreateShortcut($ShortcutPath)
$Shortcut.TargetPath = $targetPath
$shortcut.Arguments = $arguments
$shortcut.IconLocation = $iconPath
$shortcut.workingdirectory = $WorkingDirectory
$Shortcut.Save()
}

$argments = @{
ShortcutLocation = [Environment]::GetFolderPath("Desktop") + "\Pcynlitx"
ShortcutName = "Pcynlitx"
TargetPath =  "C:" + $env:HOMEPATH + "\Pcynlitx\Pcynlitx.exe"
Arguments = ""
IconPath =  "C:" + $env:HOMEPATH + "\Pcynlitx\Pcynlitx.exe"
WorkingDirectory = "C:" + $env:HOMEPATH + "\Pcynlitx"
}

New-Shortcut @argments