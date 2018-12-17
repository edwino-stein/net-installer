@ECHO off

cd \
set python=Python3\python.exe
set mainEntry=net-installer\main.py

call %python% %mainEntry%

if errorlevel 1 (
    echo Ocorreu um erro inesperado e programa foi encerrado. O sistema sera reinicado.
    pause
)

call wpeutil reboot