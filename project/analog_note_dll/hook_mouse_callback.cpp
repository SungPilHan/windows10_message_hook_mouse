#include "pch.h"

hook_mouse_callback* volatile hook_mouse_callback::_instance = nullptr;
std::mutex hook_mouse_callback::_mutex;

hook_mouse_callback::hook_mouse_callback() :
    _hook(nullptr) {

}

LRESULT hook_mouse_callback::new_function(
    __in int code,
    __in WPARAM wparam,
    __in LPARAM lparam
    ) {
        if (code >= HC_ACTION) {
            if (wparam == WM_LBUTTONDOWN) {
                OutputDebugString(L"mouse left button down");
            }
            else if (wparam == WM_LBUTTONUP) {
                OutputDebugString(L"mouse left button up");
            }
            if (wparam == WM_RBUTTONDOWN) {
                OutputDebugString(L"mouse right button down");
            }
            else if (wparam == WM_RBUTTONUP) {
                //
                char szPath[MAX_PATH] = { 0, };
                char* p = NULL;

                wchar_t sPath[MAX_PATH] = { 0, };

                GetModuleFileNameA(NULL, szPath, MAX_PATH);
                p = strrchr(szPath, '\\');

                if (!_stricmp(p + 1, "notepad.exe")) {
                    mbstowcs(sPath, p + 1, MAX_PATH);
                    //MessageBox(nullptr, sPath, L"hook success", MB_OK);
                    return 1;
                }
                //
                OutputDebugString(L"mouse right button up");
            }
            else if (wparam == WM_MOUSEMOVE) {
                //OutputDebugString(L"mouse move");
            }
        }

    return ::CallNextHookEx(_hook, code, wparam, lparam);
}