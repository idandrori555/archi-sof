#include <iostream>
#include <windows.h>

extern "C" __declspec(dllexport) int AddNumbers(int a, int b)
{
  return a + b;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
  switch (ul_reason_for_call)
  {
  case DLL_PROCESS_ATTACH:
    std::cout << "ATTACHED DLL!\n";
    break;
  case DLL_THREAD_ATTACH:
  case DLL_THREAD_DETACH:
  case DLL_PROCESS_DETACH:
    break;
  }
  return TRUE;
}
