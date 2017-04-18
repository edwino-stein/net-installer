@ECHO off
chcp 1252 >nul 2>&1

echo.
ECHO ************** Carregar Driver **************

set DEBUGING=1
set filePath=%1
set tryNet=%2

echo Carregando arquivo "%filePath%"...

if "%DEBUGING%" == "0" (
	drvload.exe %filePath%
	set returned=%ERRORLEVEL%
) else (
	set returned=0
)

if %returned% == 0 (
	goto success
)

:fail
	ECHO ************** Correu Algum Erro **************
	goto  exit


:success

	ECHO ************** Driver Carregado com Sucesso **************

	if not (%tryNet%) == () (
		"%~dp0\net-test.bat" %tryNet%
		set returned=%ERRORLEVEL%
	)

	goto  exit

:exit

	echo Código de retorno: %returned%
	pause
	
	if "%DEBUGING%" == "0" (
		exit /B %returned%
	)
