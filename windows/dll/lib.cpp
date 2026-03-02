#include <windows.h>

// ENTRY POINT FOR DLL (WINAPI)
BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved)
{
  switch (ul_reason_for_call)
  {
  case DLL_PROCESS_ATTACH:
    MessageBoxA(NULL, "Running Inside Notepad!", "INJECTED!", MB_OK | MB_ICONEXCLAMATION);
    break;

  case DLL_THREAD_ATTACH:
    break;

  case DLL_THREAD_DETACH:
    break;

  case DLL_PROCESS_DETACH:
    break;
  }

  return TRUE;
}
