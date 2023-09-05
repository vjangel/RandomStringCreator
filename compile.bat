@echo off

@REM Qt Path
set PATH=E:\Qt\5.15.2\mingw81_64\bin;E:\Qt\Tools\mingw810_64\bin\;%PATH%

qmake

mingw32-make -f Makefile qmake_all

if /i "%~1"=="-c" (
    mingw32-make clean -j20
) else (
    mingw32-make -j20
    if /i "%~1"=="-r" (
        start .\build\release\RandomStringCreator.exe
    )
)

