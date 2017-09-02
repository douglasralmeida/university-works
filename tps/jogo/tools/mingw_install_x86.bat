@echo off
@echo.
@echo Baixando o MingW-w64 (32 bits)... 
tools\wget.exe http://ufpr.dl.sourceforge.net/project/mingw-w64/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/5.2.0/threads-posix/dwarf/i686-5.2.0-release-posix-dwarf-rt_v4-rev1.7z -O C:\Temp\mingw64.7z
@echo.
@echo Instalando MingW-w64 (32bits)...
mkdir %UserProfile%\Desktop\mingw64\
tools\7z.exe e C:\Temp\mingw64.7z -o %UserProfile%\Desktop\mingw64\