@ECHO off
chcp 1252 >nul 2>&1

set DEBUGING=0
set letter=%1
set serverUri=%2
set /A tryCount=0
set maxTry=3


if (%letter%) == () (
	echo É necessário informar uma letra para unidade ser montada.
	set returned=100
	goto fail
)

if (%serverUri%) == () (
	echo É necessário informar o endereço do servidor completo para ser montado.
	set returned=101
	goto fail
)

if exist %letter% (
	echo A unidade já está montada.
	set returned=102
	goto fail
)

echo Mountando %serverUri% em %letter%...

:loop
	
	set /A tryCount=%tryCount%+1
	echo %tryCount%ª Tentativa...

	if "%DEBUGING%" == "0" (
		net use %letter% %serverUri%
		set returned=%ERRORLEVEL%
	) else (
		set returned=1
	)

	if %returned% == 0 (
		goto success
	)

	if %tryCount% == %maxTry% (
		goto fail
	)

	goto loop

:fail
	ECHO Erro ao montar unidade: %returned%
	goto  exit

:success
	echo Unidade Remota Mountada com Sucesso
	exit /B 0

:exit
	exit /B %returned%