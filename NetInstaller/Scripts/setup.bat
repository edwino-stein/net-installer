@ECHO off
chcp 1252 >nul 2>&1

echo ************** Iniciando Instala��o Remota **************

set letter=%1
set serverUri=%2
set installPath=%3

if (%letter%) == () (
	echo * Erro: � necess�rio informar uma letra para unidade ser montada.
	goto fail
)

if (%serverUri%) == () (
	echo * Erro: � necess�rio informar o endere�o do servidor completo para ser montado.
	goto fail
)

if (%installPath%) == () (
	echo * Erro: � necess�rio informar o endere�o para os arquivos de instala��o.
	goto fail
)

set installFullPath=%letter%\%installPath%

if exist %installFullPath% (
	goto startSetup
)

if exist %letter% (
	echo * A unidade esta em uso!
	call "%~dp0\net-unmount.bat" %letter%
	if exist %letter% (
		echo * Erro: N�o foi possivel desmountar a unidade "%letter%", tente outra!
		goto fail
	)
)

echo * Configurando servidor remoto...

call "%~dp0\net-mount.bat" %letter% %serverUri%

if exist %letter% (
	goto mountSuccess
)

:fail
	echo * Erro ao inicializar instala��o remota!
	exit /B 1

:mountSuccess
	
	if exist %installFullPath% (
		goto startSetup
	)

	echo * Erro: N�o foi possivel encontrar o arquivo "installFullPath"...
	goto fail

:startSetup
	echo * Executanto "%installFullPath%"...
	call %installFullPath%
