
CXX = g++
RC = windres

CXXFLAGS = -std=c++20 -O2 -Wall -g -Iapp/include
CXXFLAGS += -Icore/include -Ithirdparty/glfw/include -Ithirdparty/glm -Ithirdparty/glad/include -Ithirdparty/imgui -Ithirdparty/entt/single_include -Ithirdparty/tinyfiledialogs -Ithirdparty/tinyobjloader -Ithirdparty/stb -Ithirdparty/imguizmo
LIBS = thirdparty/imgui/lib/libimgui.a thirdparty/glfw/lib/libglfw3.a core/lib/libcore.a thirdparty/glad/build/glad.o thirdparty/tinyfiledialogs/build/tinyfiledialogs.o thirdparty/tinyobjloader/build/tiny_obj_loader.o thirdparty/imguizmo/lib/libimguizmo.a
LIBS +=  -lopengl32 -lgdi32 -luser32 -lkernel32 -lshell32 -lcomdlg32 -lole32

RES = app/src/app_icon.rc
RES_OBJ = $(BUILD_DIR)/app_icon.o

SRC = $(wildcard app/src/*.cpp) $(wildcard app/src/*.c)
OBJ = $(patsubst app/src/%.cpp, $(BUILD_DIR)/%.o, $(wildcard app/src/*.cpp)) \
      $(patsubst app/src/%.c, $(BUILD_DIR)/%.o, $(wildcard app/src/*.c))

OUT_DIR = out
BUILD_DIR = build
TARGET = $(OUT_DIR)/app.exe

all: libs $(TARGET)

$(BUILD_DIR)/app_icon.o: $(RES)
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	$(RC) $< -O coff -o $@

$(BUILD_DIR)/%.o: app/src/%.cpp
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: app/src/%.c
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJ) $(RES_OBJ)
	@if not exist "$(OUT_DIR)" mkdir "$(OUT_DIR)"
	$(CXX) $(CXXFLAGS) $(OBJ) $(RES_OBJ) $(LIBS) -o $@

run: $(TARGET)
	./$(TARGET)

clean:
# 	if exist "$(OUT_DIR)" rmdir /s /q "$(OUT_DIR)"
	if exist "$(BUILD_DIR)" rmdir /s /q "$(BUILD_DIR)"

libs:
	cd make/ && $(MAKE) -f glfw.mk
	cd make/ && $(MAKE) -f glad.mk
	cd make/ && $(MAKE) -f core.mk
	cd make/ && $(MAKE) -f imgui.mk
	cd make/ && $(MAKE) -f imguizmo.mk
	cd make/ && $(MAKE) -f tfd.mk
	cd make/ && $(MAKE) -f tol.mk

.PHONY: all clean run libs