#include <stdio.h>
#include <windows.h>

int main()
{
  char dllPath[MAX_PATH];
  GetFullPathNameA("mydll.dll", MAX_PATH, dllPath, NULL);

  PVOID addrLoadLibrary = (PVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");

  HWND hwnd = FindWindowA("Notepad", NULL);
  if (!hwnd)
  {
    printf("Please open Notepad first!\n");
    return 0;
  }

  DWORD pid;
  GetWindowThreadProcessId(hwnd, &pid);
  HANDLE proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

  PVOID memAddr = (PVOID)VirtualAllocEx(proc, NULL, strlen(dllPath) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
  if (NULL == memAddr)
  {
    printf("VirtualAllocEx failed!\n");
    return 0;
  }

  WriteProcessMemory(proc, memAddr, dllPath, strlen(dllPath) + 1, NULL);

  HANDLE hThread = CreateRemoteThread(proc, NULL, 0, (LPTHREAD_START_ROUTINE)addrLoadLibrary, memAddr, 0, NULL);

  CloseHandle(hThread);
  CloseHandle(proc);

  printf("DLL injected successfully!\n");
  return 0;
}
