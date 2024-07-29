

cd D:\PCYNLITX.BUILD.TEST

$Path_exist = Test-Path -Path "D:\PCYNLITX.BUILD.TEST\Pcynlitx.Win.Test"

if($Path_exist){

    Remove-Item -LiteralPath "D:\PCYNLITX.BUILD.TEST\Pcynlitx.Win.Test" -Recurse -Force
}

cd D:\

Copy-Item -LiteralPath "D:\Pcynlitx.Win.Test" -Destination "D:\PCYNLITX.BUILD.TEST" -Recurse -Force

Write-Output ""

Write-Host "Test Environment Refreshed" -ForegroundColor red

Write-Output ""

cd D:\pcynlitx_build_platform

.\CMAKE_Build.exe -bs D:\PCYNLITX.BUILD.TEST\Pcb_Descriptor.txt Pcynlitx_Project 1.0

cd  D:\PCYNLITX.BUILD.TEST\Pcynlitx.Win.Test

powershell.exe .\configure_cmake.ps1


Write-Output ""

Write-Host "CMAKE Build system constructed" -ForegroundColor green

Write-Output ""

cd D:\PCYNLITX_WIN_CMAKE_CONFIGS

mingw32-make -f .\Makefile

cd D:\pcynlitx_build_platform

.\CMAKE_Build.exe -ef D:\PCYNLITX.BUILD.TEST\Pcb_Descriptor.txt D:\PCYNLITX.BUILD.TEST\Pcynlitx.Win.Test\KERNEL.DEVELOPMENT\Kernel\Kernel_Main_File.cpp _pcyKernel

cd D:\PCYNLITX_WIN_CMAKE_CONFIGS

mingw32-make -f .\Makefile