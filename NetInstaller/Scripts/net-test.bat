@ECHO off
chcp 1252 >nul 2>&1

echo.
ECHO ************** Verificando Conectividade **************

set DEBUGING=0
set /A tryCount=0
set maxTry=3
set serverURI=%1

:loop
	
	set /A tryCount=%tryCount%+1

	echo %tryCount%� Tentativa...

	if "%DEBUGING%" == "0" (
		call net view >nul 2>&1
	) else (
		call net view
	)

	
	set returned=%ERRORLEVEL%
	echo.

	if %returned% == 0 (
		goto success
	)

	if %tryCount% == %maxTry% (
		goto fail
	)

	goto loop

:fail
	echo ************** N�o foi possivel conex�o **************
	goto exit

:success

	echo ************** Existe conex�o **************
	goto exit

:exit
	
	echo C�digo de retorno: %returned%
	pause
	
	if "%DEBUGING%" == "0" (
		exit /B %returned%
	)

@ECHO on