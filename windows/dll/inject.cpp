#include <cstdio>
#include <stdio.h>
#include <windows.h>

#define DLL_NAME ("mydll.dll")
#define TARGET_PROCESS_NAME ("notepad.exe")

int main()
{
  char dllPath[MAX_PATH]{0};
  GetFullPathNameA(DLL_NAME, MAX_PATH, dllPath, NULL);

  PVOID addrLoadLibrary = (PVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");

  HWND hwnd = FindWindowA(TARGET_PROCESS_NAME, NULL);
  if (!hwnd)
  {
    std::puts("You must open notepad first");
    return 0;
  }

  DWORD pid{};
  GetWindowThreadProcessId(hwnd, &pid);
  HANDLE proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

  PVOID memAddr = (PVOID)VirtualAllocEx(proc, NULL, strlen(dllPath) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
  if (NULL == memAddr)
  {
    std::puts("VirtualAllocEx failed");
    return 0;
  }

  WriteProcessMemory(proc, memAddr, dllPath, strlen(dllPath) + 1, NULL);

  HANDLE hThread = CreateRemoteThread(proc, NULL, 0, (LPTHREAD_START_ROUTINE)addrLoadLibrary, memAddr, 0, NULL);

  CloseHandle(hThread);
  CloseHandle(proc);

  std::puts("DLL injected");
  return 0;
}
