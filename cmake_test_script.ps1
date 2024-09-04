

cd C:\Development.Files\PCYNLITX.BUILD.TEST

$Path_exist = Test-Path -Path "C:\Development.Files\PCYNLITX.BUILD.TEST\Pcynlitx.Win.Test"

if($Path_exist){

    Remove-Item -LiteralPath "C:\Development.Files\PCYNLITX.BUILD.TEST\Pcynlitx.Win.Test" -Recurse -Force
}


cd C:\Development.Files\PCYNLITX.BUILD.TEST

$Path_exist = Test-Path -Path "C:\Development.Files\PCYNLITX_WIN_CMAKE_CONFIGS"

if($Path_exist){

    Remove-Item -LiteralPath "C:\Development.Files\PCYNLITX_WIN_CMAKE_CONFIGS" -Recurse -Force
}



cd C:\Development.Files

Copy-Item -LiteralPath "C:\Development.Files\Pcynlitx.Win.Test" -Destination "C:\Development.Files\PCYNLITX.BUILD.TEST" -Recurse -Force

Write-Output ""

Write-Host "Test Environment Refreshed" -ForegroundColor red

Write-Output ""

Read-Host -Prompt "Press any key to continue"

Write-Output ""


cd C:\Development.Files\Project.Test.platform

.\CBuild.exe C:\Development.Files\PCYNLITX.BUILD.TEST\Pcb_Descriptor.txt -ip

cd  C:\Development.Files\PCYNLITX.BUILD.TEST\Pcynlitx.Win.Test

powershell.exe .\configure_cmake.ps1


Write-Output ""

Write-Host "CMAKE Build system constructed" -ForegroundColor green

Read-Host -Prompt "Press any key to continue"

Write-Output ""
Write-Output ""

cd C:\Development.Files\PCYNLITX_WIN_CMAKE_CONFIGS

mingw32-make -f .\Makefile

cd C:\Development.Files\Project.Test.platform

.\CBuild.exe C:\Development.Files\PCYNLITX.BUILD.TEST\Pcb_Descriptor.txt -if C:\Development.Files\PCYNLITX.BUILD.TEST\Pcynlitx.Win.Test\KERNEL.DEVELOPMENT\Kernel\Kernel_Main_File.cpp _pcyKernel c

cd C:\Development.Files\PCYNLITX_WIN_CMAKE_CONFIGS

mingw32-make -f .\Makefile