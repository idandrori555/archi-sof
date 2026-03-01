#include <iostream>
#include <windows.h>

HMODULE hDLL = LoadLibrary("my_library.dll");

int main(void)
{
  if (hDLL)
  {
    int (*func)(int, int) = (int (*)(int, int))GetProcAddress(hDLL, "AddNumbers");

    if (func)
      std::cout << func(1, 2) << std::endl;

    FreeLibrary(hDLL);
  }
  return 0;
}
