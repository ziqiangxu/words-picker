#include "winhooks.h"

WinHooks::WinHooks()
{
    /*
    //安装钩子
    int idHook = WH_KEYBOARD;  //指定接收哪种消息
    HOOKPROC lpfn;  //钩子函数的地址
    HINSTANCE hMode = NULL;  //1. 钩子函数所在DLL在进程内的地址; 2. 如果是当前线程的话，且lpfn指向当前
    DWORD dwTreadId = 0;  //要安装钩子的线程（0表示在所有的GUI线程中安装钩子）
    hHook = SetWindowsHookEx(
                idHook,
                lpfn,
                hMode,
                dwTreadId
                );
                */
}

/*
//钩子函数
LRESULT CALLBACK KeyHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode < 0 | nCode == HC_NOREMOVE){
        return CallNextHookEx(hHook, nCode, wParam, lParam);
    }
    if (lParam & 0x40000000){  //只对WM_KEYDOWN响应
        PostMessage(hWnd, WM_KEYDOWN, wParam, lParam);
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}
*/
