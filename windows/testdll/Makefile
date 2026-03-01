CC = g++

DLL_FLAGS = -Wall -static -shared

all: dll inject

dll:
	$(CC) $(DLL_FLAGS) -o testdll.dll testdll.c

inject:
	$(CC) $(DLL_FLAGS) -o inject.exe inject.c
