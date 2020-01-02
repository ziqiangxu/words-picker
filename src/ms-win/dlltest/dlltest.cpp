#include "dlltest.h"
#include <iostream>
#include <windows.h>

//Dlltest::Dlltest()
//{
//}

//此处的WINAPI非常关键（没有的话不会调用此函数，则无法获取DLL句柄）
bool WINAPI DllMain(HANDLE hModule,
             DWORD ul_reason_for_call,
             LPVOID lpReserved)
{
    std::cout << "DllMain() called\n";
    //保存DLL模块句柄
    hInst = (HINSTANCE)hModule;  //强制类型转换
    return true;
}

int test1()
{
    std::cout << "This is the test1()\n";
    //return 0;
}


LRESULT CALLBACK KeyHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode < 0 | (nCode == HC_NOREMOVE)){
        return CallNextHookEx(hHook, nCode, wParam, lParam);
    }
    if (lParam & 0x40000000){  //只对WM_KEYDOWN响应
        //std::cout << "你按下了键盘";
        MessageBoxA(NULL, "Pressed the keyborad", "Test", MB_OK);
        //PostMessage(hWnd, WM_KEYDOWN, wParam, lParam);
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}


//安装钩子
void SetHookOn()
{
    int idHook = WH_KEYBOARD;  //指定接收哪种消息
    //HOOKPROC lpfn;  //钩子函数的地址
    HINSTANCE hMode = hInst;  //1. 钩子函数所在DLL在进程内的地址; 2. 如果是当前线程的话，且lpfn指向当前
    DWORD dwTreadId = 0;  //要安装钩子的线程（0表示在所有的GUI线程中安装钩子）
    std::cout << "SetHookOn:\nType of the hook--idHook:" << idHook
              << "\nAddress of the callback function--KeyHookProc:" << KeyHookProc
              << "\nHandle of the dll module--hMode:" << hMode
              << "\Listen area--ndwTreadId:" << dwTreadId << std::endl;

    hHook = SetWindowsHookEx(
                idHook,
                KeyHookProc,
                hMode,
                dwTreadId
                );
    std::cout << "The hHook:" << hHook << "---errocode" << GetLastError() << std::endl;
}

//卸载钩子
void SetHookOff()
{
    UnhookWindowsHookEx(hHook);
    std::cout << "卸载钩子";
}
