CXX = g++
CXXFLAGS = -Wall -O2
DLL_OUT = mydll.dll
EXE_OUT = injector.exe

all: $(DLL_OUT) $(EXE_OUT)

$(DLL_OUT): lib.cpp
	$(CXX) $(CXXFLAGS) -shared -o $(DLL_OUT) lib.cpp -luser32

$(EXE_OUT): inject.cpp
	$(CXX) $(CXXFLAGS) -o $(EXE_OUT) inject.cpp -luser32 -lkernel32

clean:
	del /f $(DLL_OUT) $(EXE_OUT)


.PHONY: clean all
