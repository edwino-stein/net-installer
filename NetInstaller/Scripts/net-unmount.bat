@ECHO off
chcp 1252 >nul 2>&1

set DEBUGING=0
set letter=%1
set /A tryCountUnmount=0
set maxTry=3


if (%letter%) == () (
	echo * Erro: É necessário informar uma letra para unidade ser montada.
	goto fail
)

if not exist %letter% (
	echo * A unidade não está montada.
	set mounted=1
	goto done
)

echo * Desmountando unidade %letter%...

:loop
	
	set /A tryCountUnmount=%tryCountUnmount%+1
	echo %tryCountUnmount%ª Tentativa...

	if "%DEBUGING%" == "0" (
		call net use %letter% /delete
	) else (
		set mounted=1
	)

	echo * Codigo de retorno: %errorlevel%
	echo.

	if %errorlevel% == 0 (
		goto success
	)

	if %tryCountUnmount% == %maxTry% (
		goto fail
	)

	goto loop

:fail
	echo * Erro ao desmontar unidade!
	goto done

:success
	echo * Unidade Remota desmountada com sucesso!
	goto done

:done
