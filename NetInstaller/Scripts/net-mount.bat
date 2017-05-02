@ECHO off
chcp 1252 >nul 2>&1

set DEBUGING=0
set user=pxe
set passwd=gwh28dgcmp
set letter=%1
set serverUri=%2
set /A tryCountMount=0
set maxTry=3

if (%letter%) == () (
	echo * ERRO: É necessário informar uma letra para unidade ser montada.
	goto fail
)

if (%serverUri%) == () (
	echo * ERRO: É necessário informar o endereço do servidor completo para ser montado.
	goto fail
)

if exist %letter% (
	echo * A unidade já está montada.
	set mounted=1
	goto done
)

echo * Mountando %serverUri% em %letter%...

:loop
	
	set /A tryCountMount=%tryCountMount%+1
	echo %tryCountMount%ª Tentativa...

	if "%DEBUGING%" == "0" (

		call net use %letter% %serverUri% /u:%user% %passwd%
		
		if exist %letter% (
			set mounted=1
		) else (
			set mounted=0
		)

	) else (
		set mounted=1
		goto success
	)

	echo * Codigo de retorno: %errorlevel%
	echo.

	if %errorlevel% == 0 (
		goto success
	)

	if %tryCountMount% == %maxTry% (
		goto fail
	)

	goto loop

:fail
	echo * Erro ao montar unidade!
	goto done

:success
	echo * Unidade remota mountada com sucesso!
	goto done

:done