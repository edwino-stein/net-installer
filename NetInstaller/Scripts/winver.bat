@echo off

for /f "tokens=4-5 delims=. " %%i in ('ver') do set VERSION=%%i.%%j
set win_ver=0 

if "%version%" == "6.0" ( REM Windows Vista
	set win_ver=Vista
)

if "%version%" == "6.1" (
	REM Windows 7
	set win_ver=7
) 

if "%version%" == "6.2" (
	REM Windows 8
	set win_ver=8
)

if "%version%" == "6.3" (
	REM Windows 8.1
	set win_ver=8.1
)

if "%version%" == "10.0" (
	REM Windows 10
	set win_ver=10
)

rem etc etc