@ECHO off
chcp 1252 >nul 2>&1
setlocal

set DEBUGING=0
set /A tryCount=0
set maxTry=3
set serverURI=%1

call "%~dp0\winver.bat"

echo ************** Verificando Conectividade **************

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
	echo.

	if %errorlevel% == 0 (
		goto success
	)

	:tryError

	if %tryCount% == %maxTry% (
		goto fail
	)

	goto loop

:fail

	echo * Sem Conexão! 
	pause

	endlocal
	exit /B 1

:success
	
	echo * Existe Conexão! 
	pause

	endlocal
	exit /B 0
