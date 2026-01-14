
Write-Output ""

Write-Output "# TEST FILE CREATION STARTED "

Write-Output ""

mingw32-make.exe -f .\Child_Process.mk

Write-Output ""

Write-Output "# Executable file for child process created!"

Write-Output ""


mingw32-make.exe -f .\Redirector_Tester.mk 

Write-Output ""

Write-Output "# Executable file for parent process created!"

Write-Output ""