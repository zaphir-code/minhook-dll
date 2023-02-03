#include "../include/MinHook.h"

#ifdef __cplusplus
extern "C" {
#endif

MH_STATUS(WINAPI *MH_Uninitialize)(VOID) = NULL;
MH_STATUS(WINAPI *MH_CreateHook)(LPVOID pTarget, LPVOID pDetour, LPVOID *ppOriginal) = NULL;
MH_STATUS(WINAPI *MH_CreateHookApi)(LPCWSTR pszModule, LPCSTR pszProcName, LPVOID pDetour, LPVOID *ppOriginal) = NULL;
MH_STATUS(WINAPI *MH_CreateHookApiEx)(LPCWSTR pszModule, LPCSTR pszProcName, LPVOID pDetour, LPVOID *ppOriginal, LPVOID *ppTarget) = NULL;
MH_STATUS(WINAPI *MH_RemoveHook)(LPVOID pTarget) = NULL;
MH_STATUS(WINAPI *MH_EnableHook)(LPVOID pTarget) = NULL;
MH_STATUS(WINAPI *MH_DisableHook)(LPVOID pTarget) = NULL;
MH_STATUS(WINAPI *MH_QueueEnableHook)(LPVOID pTarget) = NULL;
MH_STATUS(WINAPI *MH_QueueDisableHook)(LPVOID pTarget) = NULL;
MH_STATUS(WINAPI *MH_ApplyQueued)(VOID) = NULL;
const char *(WINAPI *MH_StatusToString)(MH_STATUS status) = NULL;

MH_STATUS WINAPI MH_Initialize(VOID) {
    #if (defined __x86_64__) || (defined _M_X64)
        #define MINHOOK_DLL "minhook.x64.dll"
        HMODULE minHookHandle = LoadLibraryA("minhook.x64.dll");

        if (minHookHandle == NULL) return MH_UNKNOWN;
    #elif (defined i386) || (defined __i386__) || (defined __i386) || (defined _M_IX86)
        HMODULE minHookHandle = LoadLibraryA("minhook.x86.dll");

        if (minHookHandle == NULL) {
            minHookHandle = LoadLibraryA("minhook.x32.dll");
        }

        if (minHookHandle == NULL) return MH_UNKNOWN;
    #else
        #error MinHook supports only x86 and x64 systems.
    #endif

    const MH_STATUS fResult = ((MH_STATUS(WINAPI *)(VOID))(GetProcAddress(minHookHandle, "MH_Initialize")))();

    if (fResult == MH_OK) {
        MH_Uninitialize = (MH_STATUS(WINAPI *)(VOID))(GetProcAddress(minHookHandle, "MH_Uninitialize"));
        MH_CreateHook = (MH_STATUS(WINAPI *)(LPVOID, LPVOID, LPVOID *))(GetProcAddress(minHookHandle, "MH_CreateHook"));
        MH_CreateHookApi = (MH_STATUS(WINAPI *)(LPCWSTR, LPCSTR, LPVOID, LPVOID *))(GetProcAddress(minHookHandle, "MH_CreateHookApi"));
        MH_CreateHookApiEx = (MH_STATUS(WINAPI *)(LPCWSTR, LPCSTR, LPVOID, LPVOID *, LPVOID *))(GetProcAddress(minHookHandle, "MH_CreateHookApiEx"));
        MH_RemoveHook = (MH_STATUS(WINAPI *)(LPVOID))(GetProcAddress(minHookHandle, "MH_RemoveHook"));
        MH_EnableHook = (MH_STATUS(WINAPI *)(LPVOID))(GetProcAddress(minHookHandle, "MH_EnableHook"));
        MH_DisableHook = (MH_STATUS(WINAPI *)(LPVOID))(GetProcAddress(minHookHandle, "MH_DisableHook"));
        MH_QueueEnableHook = (MH_STATUS(WINAPI *)(LPVOID))(GetProcAddress(minHookHandle, "MH_QueueEnableHook"));
        MH_QueueDisableHook = (MH_STATUS(WINAPI *)(LPVOID))(GetProcAddress(minHookHandle, "MH_QueueDisableHook"));
        MH_ApplyQueued = (MH_STATUS(WINAPI *)(VOID))(GetProcAddress(minHookHandle, "MH_ApplyQueued"));
        MH_StatusToString = (const char *(WINAPI *)(MH_STATUS))(GetProcAddress(minHookHandle, "MH_StatusToString"));
    }

    return fResult;
}

#ifdef __cplusplus
}
#endif