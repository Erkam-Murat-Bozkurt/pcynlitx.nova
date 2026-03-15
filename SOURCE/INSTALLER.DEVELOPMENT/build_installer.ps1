Set-Location ..\..\

powershell.exe .\build_script.ps1

Set-Location .\BUILD

Copy-Item Pcynlitx_Kernel.exe ..\SOURCE\INSTALLER.DEVELOPMENT

Copy-Item Pcynlitx.exe ..\SOURCE\INSTALLER.DEVELOPMENT

Set-Location ..\SOURCE\INSTALLER.DEVELOPMENT

$Current_Dir=Get-Location

$IS_INSTALLER_EXIST=Test-Path -Path "$Current_Dir\Mingw64.Setup.exe"

if(-Not $IS_INSTALLER_EXIST){

    ISCC.exe .\mingw64_installer_script.iss
}

g++ -o mingw64_path_set.exe mingw64_path_set.cpp -static-libstdc++ -static-libgcc

g++ -o pcynlitx_path_set.exe pcynlitx_path_set.cpp -static-libstdc++ -static-libgcc

g++ -o setup_fonts.exe font_installer.cpp -static-libstdc++ -static-libgcc

ISCC.exe .\installer_script.iss