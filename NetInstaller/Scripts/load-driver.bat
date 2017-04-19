@ECHO off
chcp 1252 >nul 2>&1
setlocal

set DEBUGING=0
set filePath=%1
set tryNet=%2

echo ************** Carregar Driver **************
echo * Carregando arquivo "%filePath%"...

if "%DEBUGING%" == "0" (
	call drvload.exe %filePath%
)

echo * Codigo de retorno: %errorlevel%
echo.

if %errorlevel% == 0 (
	goto success
)

:fail
	
	call "%~dp0\wait.bat" 3000

	echo * Erro ao carregar o driver! 
	pause

	endlocal
	exit /B 1

:success
	
	call "%~dp0\wait.bat" 3000
	
	if not (%tryNet%) == () (
		echo * Verificando Conectividade...
		goto nettry
	)

:successExit

	echo.
	echo * Driver Carregado!
	pause
	exit /B 0


:nettry

set /A tryCount=0
set maxTry=3
set serverURI=%tryNet%

call "%~dp0\winver.bat"

:loop
	
	set /A tryCount=%tryCount%+1
	echo %tryCount%ª Tentativa...

	echo * Verificando Ping...

	if "%DEBUGING%" == "0" (
		ping %serverURI% -n 4 -w 250 >nul
	) else (
		ping %serverURI% -n 4 -w 250
	)

	echo * Codigo de retorno: %errorlevel%
	echo.

	if %errorlevel% == 1 (
		goto tryError
	)

	echo * Verificando Compartilhamentos...

	if "%DEBUGING%" == "0" (

		if "%win_ver%" == "10" (
			call net view >nul 2>&1
		) else (
			net view %serverURI% >nul 2>&1
		)

	) else (
		call net view %serverURI%
	)

	echo * Codigo de retorno: %errorlevel%

	if %errorlevel% == 0 (
		goto successExit
	)

	:tryError

	if %tryCount% == %maxTry% (
		goto fail
	)

	goto loop