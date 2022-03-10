// dllmain.cpp : Defines the entry point for the DLL application.

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <stdio.h>

void DebugOut(const char* fmt, ...)
{
    va_list argp;
    va_start(argp, fmt);
    char dbg_out[4096];
    vsprintf_s(dbg_out, fmt, argp);
    va_end(argp);
    OutputDebugStringA(dbg_out);
}

//
// Main entry point
//
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID)
{
    char moduleFilename[MAX_PATH];
    GetModuleFileNameA(hModule, moduleFilename, MAX_PATH);

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DebugOut("%s: DLL_PROCESS_ATTACH\n", moduleFilename);
        break;
    case DLL_THREAD_ATTACH:
        DebugOut("%s: DLL_THREAD_ATTACH\n", moduleFilename);
        break;
    case DLL_THREAD_DETACH:
        DebugOut("%s: DLL_THREAD_DETACH\n", moduleFilename);
        break;
    case DLL_PROCESS_DETACH:
        DebugOut("%s: DLL_PROCESS_DETACH\n", moduleFilename);
        break;

    }
    return TRUE;
}
