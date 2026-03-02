/**
 * Idan Drori LLC Copyright (c) 2026
 */

#include <cstdio>
#include <iostream>
#include <stdio.h>
#include <windows.h>

#define DLL_NAME ("mydll.dll")
#define TARGET_PROCESS_NAME ("Notepad.exe")

int main(void)
{
  char dllPath[MAX_PATH]{0};
  GetFullPathNameA(DLL_NAME, MAX_PATH, dllPath, NULL);

  // Get addr of LoadLibraryA (func in kernel32.dll)
  auto addrLoadLibrary = (PVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");

  // Get handle to target process (Notepad)
  HWND hwnd = FindWindowA(TARGET_PROCESS_NAME, NULL);
  if (NULL == hwnd)
  {
    std::cout << "You must open notepad first";
    return 0;
  }

  // Get PID of Notepad first
  DWORD pid{};
  GetWindowThreadProcessId(hwnd, &pid);

  // Open process (for writing memory)
  auto proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
  if (NULL == proc)
  {
    std::cout << "OpenProcess failed";
    return 0;
  }

  // Allocate sufficient memory in target process in order to write dll path into it
  auto memAddr = (PVOID)VirtualAllocEx(proc, NULL, strlen(dllPath) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
  if (NULL == memAddr)
  {
    std::cout << "VirtualAllocEx failed";
    return 0;
  }

  // Write dll path into target process (memory we just allocated)
  if (0 == WriteProcessMemory(proc, memAddr, dllPath, strlen(dllPath) + 1, NULL))
  {
    std::cout << "WriteProcessMemory failed";
    return 0;
  }

  // Create therad inside Notepad with entry point of LoadLibraryA and pass the memory address of dll path as a parameter to it (LoadLibraryA)
  auto hThread = CreateRemoteThread(proc, NULL, 0, (LPTHREAD_START_ROUTINE)addrLoadLibrary, memAddr, 0, NULL);
  if (NULL == hThread)
  {
    std::cout << "CreateRemoteThread failed";
    return 0;
  }

  // Wait for thread to finish
  WaitForSingleObject(hThread, INFINITE);

  // cleanuip
  CloseHandle(hThread);
  CloseHandle(proc);

  std::puts("DLL injected");
  return 0;
}
