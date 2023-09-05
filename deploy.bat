
@echo off
set PACKAGE="package"

:: 创建部署目录
mkdir %PACKAGE%

:: windeployqt  path
set WINDEPLOY="E:\Qt\5.15.2\mingw81_64\bin\windeployqt.exe" 
set PATH=E:\Qt\5.15.2\mingw81_64\bin;%PATH%

:: set target name
set TARGET=RandomStringCreator.exe

:: Copy target
@echo off
@copy "%CD%\build\release\%TARGET%" "%CD%\%PACKAGE%\"

:: used windeployqt deploy
windeployqt  %PACKAGE%\%TARGET%

:: Copy dependent files
@REM @xcopy "%PWD%\dependent\" "%PACKAGE%\" /e /y


explorer %PACKAGE%
:: 完成