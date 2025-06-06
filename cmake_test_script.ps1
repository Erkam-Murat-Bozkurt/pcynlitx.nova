
# REMOVING THE TEST DIRECTORIES

cd C:\PCYNLITX.BUILD.TEST

$Path_exist = Test-Path -Path "C:\Development.Files\PCYNLITX.BUILD.TEST\Pcynlitx.Win"

if($Path_exist){

    Remove-Item -LiteralPath "C:\Development.Files\PCYNLITX.BUILD.TEST\Pcynlitx.Win" -Recurse -Force
}


cd C:\PCYNLITX.BUILD.TEST

$Path_exist = Test-Path -Path "C:\Development.Files\PCYNLITX_WIN_CMAKE_CONFIGS"

if($Path_exist){

    Remove-Item -LiteralPath "C:\Development.Files\PCYNLITX_WIN_CMAKE_CONFIGS" -Recurse -Force
}


# CONSTRUCTING THE TEST DIRECTORIES

cd C:\Development.Files

Copy-Item -LiteralPath "C:\Development.Files\Pcynlitx.Win" -Destination "C:\Development.Files\PCYNLITX.BUILD.TEST" -Recurse -Force

Write-Output ""

Write-Host "Test Environment Refreshed" -ForegroundColor red

Write-Output ""

Read-Host -Prompt "Press any key to continue"

Write-Output ""



# Pcynlitx_Kernel.exe will be updated.

cd C:\Development.Files\PCYNLITX_BUILD_CONFIGS

mingw32-make -f .\Makefile

Copy-Item -LiteralPath "C:\Development.Files\PCYNLITX_BUILD_CONFIGS\Pcynlitx_Kernel.exe" -Destination "C:\Development.Files\PCYNLITX.BUILD.TEST" -Recurse -Force




cd C:\PCYNLITX.BUILD.TEST

.\Pcynlitx_Kernel.exe C:\PCYNLITX.BUILD.TEST\Pcb_Descriptor.txt -ip

cd  C:\PCYNLITX.BUILD.TEST\Pcynlitx.Win

powershell.exe .\configure_cmake.ps1


Write-Output ""

Write-Host "CMAKE Build system constructed" -ForegroundColor green

Read-Host -Prompt "Press any key to continue for build system test"

Write-Output ""
Write-Output ""


cd C:\Development.Files\PCYNLITX_WIN_CMAKE_CONFIGS

mingw32-make -f .\Makefile

# .\Pcynlitx_Kernel.exe C:\Development.Files\PCYNLITX.BUILD.TEST\Pcb_Descriptor.txt -if 
# C:\Development.Files\PCYNLITX.BUILD.TEST\Pcynlitx.Win.Test\KERNEL.DEVELOPMENT\Kernel\Kernel_Main_File.cpp sample.exe c