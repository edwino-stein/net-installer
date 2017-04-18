@ECHO off
chcp 1252 >nul 2>&1

echo Por favor, aguarde...
call "%~dp0\wait.bat" 5000

cd \
NetInstaller.exe