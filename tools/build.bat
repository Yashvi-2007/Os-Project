@echo off
echo [*] Building evil version.dll...
gcc -shared -o version.dll ..\src\evil_version.c version.def -luser32

if %errorlevel% == 0 (
    echo [+] Build successful: version.dll created
    echo [*] Verifying exports...
    objdump -p version.dll | findstr "Ver Get"
    echo.
    echo [!] Place version.dll in C:\Program Files (x86)\Notepad++\
) else (
    echo [-] Build failed. Check errors above.
)
pause
