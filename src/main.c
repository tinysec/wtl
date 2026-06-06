#if defined(HELLO_SHARED) && defined(_WIN32)

#include <windows.h>

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
    UNREFERENCED_PARAMETER(instance);
    UNREFERENCED_PARAMETER(reason);
    UNREFERENCED_PARAMETER(reserved);

    return TRUE;
}

#endif /* defined(HELLO_SHARED) && defined(_WIN32) */
