@ECHO off
chcp 1252 >nul 2>&1

set DEBUGING=0
set letter=%1
set /A tryCount=0
set maxTry=3


if (%letter%) == () (
	echo É necessário informar uma letra para unidade ser montada.
	set returned=100
	goto fail
)

if not exist %letter% (
	echo A unidade não está montada.
	set returned=101
	goto fail
)

echo Desmountando unidade %letter%...

:loop
	
	set /A tryCount=%tryCount%+1
	echo %tryCount%ª Tentativa...

	if "%DEBUGING%" == "0" (
		net use %letter% /delete
		set returned=%ERRORLEVEL%
	) else (
		set returned=0
	)

	if %returned% == 0 (
		goto success
	)

	if %tryCount% == %maxTry% (
		goto fail
	)

	goto loop

:fail
	echo Erro ao desmontar unidade: %returned%
	goto  exit

:success
	echo Unidade Remota Desmountada com Sucesso %returned%
	goto exit

:exit
	exit /B %returned%