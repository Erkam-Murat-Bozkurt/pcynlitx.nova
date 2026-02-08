
cmake --build .\BUILD -j 8

powershell.exe .\SOURCE\update_exe_files.ps1

powershell.exe .\SOURCE\desktop_link_setter.ps1