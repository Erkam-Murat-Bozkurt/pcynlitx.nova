
param (
    [Parameter(Mandatory)]
    [string]$Test_Directory_Path
)


Write-Output ""

Write-Output ""

Write-Host "TEST REPOSITORY CONSTRUCTION STARTED" -ForegroundColor Green

Write-Output ""

Write-Output "The construction point:" 

Write-Output "-------------------------------"

Write-Output $Test_Directory_Path

Write-Output ""

cd $Test_Directory_Path

#Write-Output (Get-Location).Path

git clone https://github.com/Erkam-Murat-Bozkurt/pcynlitx.nova.git pcynlitx.nova.test

cd pcynlitx.nova.test

rm Target_Link_Settings.cmake

rm Mingw64_Configuration.cmake

rm Gui_Build_Settings.cmake

rm Executable_File_List.cmake

rm CMakeLists.txt

cd SOURCE

rm CMakeLists.txt

cd BASIC.TOOLS

rm CMakeLists.txt

cd ..

cd CMAKE.LISTS.FILE.BUILD.SYSTEM

rm CMakeLists.txt

cd CMAKE_Build_System_Generator

rm CMakeLists.txt

cd ..\CMAKE_Executable_Target_Constructor

rm CMakeLists.txt

cd ..\CMAKE_Main_File_Writer

rm CMakeLists.txt

cd ..\CMAKE_System_Constructor

rm CMakeLists.txt

cd ..\CMake_Target_Library_Builder

rm CMakeLists.txt

cd ..\..\DESCRIPTION.PROCESSING.SYSTEM

rm CMakeLists.txt

cd ..\EXECUTABLE.MAKE.FILE.BUILD.SYSTEM

rm CMakeLists.txt

cd ..\GIT.DATA.PROCESSING.SYSTEM

rm CMakeLists.txt

cd ..\GUI.DEVELOPMENT

rm CMakeLists.txt

cd ..\KERNEL.DEVELOPMENT

rm CMakeLists.txt

cd ..\MAKE.FILE.BUILD.SYSTEM

rm CMakeLists.txt

cd ..\PROJECT.BUILD.TOOLS

rm CMakeLists.txt

cd ..\SCRIPT.WRITERS

rm CMakeLists.txt

cd ..\SOURCE.FILE.DATA.COLLECTORS

rm CMakeLists.txt

cd ..\SOURCE.FILE.PROCESSING.SYSTEM

rm CMakeLists.txt

Write-Output ""

Write-Host "Test directory successfully constructed" -ForegroundColor Green

Write-Output ""

Write-Output ""

