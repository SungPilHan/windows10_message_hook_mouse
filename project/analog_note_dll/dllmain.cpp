// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        if (hook_mouse_callback::instance()->attach(hModule)) {
            ;
        }
        break;

    case DLL_THREAD_ATTACH:
        break;

    case DLL_THREAD_DETACH:
        if (hook_mouse_callback::instance()->attached()) {
            hook_mouse_callback::instance()->detach();
        }
        
        break;

    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

