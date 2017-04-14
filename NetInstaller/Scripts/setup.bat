@ECHO off
chcp 1252 >nul 2>&1

echo.
ECHO ************** Iniciando Instala��o Remota **************

set letter=%1
set serverUri=%2
set installPath=%3

if (%letter%) == () (
	echo � necess�rio informar uma letra para unidade ser montada.
	set returned=100
	goto fail
)

if (%serverUri%) == () (
	echo � necess�rio informar o endere�o do servidor completo para ser montado.
	set returned=101
	goto fail
)

if (%installPath%) == () (
	echo � necess�rio informar o endere�o para os arquivos de instala��o.
	set returned=102
	goto fail
)

set installFullPath=%letter%\%installPath%

if exist %installFullPath% (
	goto startSetup
)

call "%~dp0\net-mount.bat" %letter% %serverUri%
set returned=%ERRORLEVEL%

if not %returned% == 0 (
	goto fail
)

if not exist %installFullPath% (
	echo N�o foi possivel encontrar o arquivo "installFullPath"...
	set returned=200
	goto fail
)

:startSetup
echo Executanto "%installFullPath%"...
call %installFullPath%

set returned=%ERRORLEVEL%

goto success

:fail
	ECHO ************** Correu Algum Erro **************
	goto  exit

:success
	echo Instala��o inicializada com sucesso
	goto exit

:exit
	echo C�digo de retorno: %returned%
	timeout 5
	exit /B %returned%