#ifndef WINHOOKS_H
#define WINHOOKS_H
#include <windows.h>

class WinHooks
{
public:
    WinHooks();
private:
    HHOOK hHook;
};

#endif // WINHOOKS_H
