CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++23
BUILD_DIR = build

DLL_NAME = my_library.dll
EXE_NAME = injector.exe

DLL_TARGET = $(BUILD_DIR)/$(DLL_NAME)
EXE_TARGET = $(BUILD_DIR)/$(EXE_NAME)

ifeq ($(OS), Windows_NT)
    MKDIR = if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
    RM = rmdir /s /q $(BUILD_DIR)
else
    MKDIR = mkdir -p $(BUILD_DIR)
    RM = rm -rf $(BUILD_DIR)
endif

# --- מטרות (Targets) ---

# ברירת מחדל: בונה הכל
all: $(BUILD_DIR) $(DLL_TARGET) $(EXE_TARGET)
	@echo "--- Build Finished! Everything is in /$(BUILD_DIR) ---"

# יצירת תיקיית ה-build
$(BUILD_DIR):
	@$(MKDIR)

# בניית ה-DLL
$(DLL_TARGET): dll_source.cpp
	$(CXX) $(CXXFLAGS) -static -shared -o $@ $^
	@echo "[+] DLL Built: $@"

# בניית ה-Injector
$(EXE_TARGET): main_injector.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "[+] Injector Built: $@"

# ניקוי
clean:
	$(RM)
	@echo "[!] Build folder removed."
