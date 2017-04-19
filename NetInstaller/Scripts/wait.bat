@ECHO off
chcp 1252 >nul 2>&1
setlocal

PING 1.1.1.1 -n 1 -w %1% >NUL

endlocal
exit /B 0