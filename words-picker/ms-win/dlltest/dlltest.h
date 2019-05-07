#define DLLTESTSHARED_EXPORT __declspec(dllexport)
#ifdef DLLTESTSHARED_EXPORT
#else
#define DLLTESTSHARED_EXPORT __declspec(dllimport)
#endif
#include <windows.h>
extern "C" DLLTESTSHARED_EXPORT VOID SetHookOff();
extern "C" DLLTESTSHARED_EXPORT VOID SetHookOn();
extern "C" DLLTESTSHARED_EXPORT INT test1();
//extern "C" DLLTESTSHARED_EXPORT BOOL DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved);
//#include "dlltest_global.h"

//class DLLTESTSHARED_EXPORT Dlltest
//{

//public:
  //  Dlltest();
  //  DLLTESTSHARED_EXPORT int test1();
    HHOOK hHook = NULL;  //钩子句柄
    HINSTANCE hInst = NULL;  //dll句柄
// };

//#endif // DLLTEST_H
