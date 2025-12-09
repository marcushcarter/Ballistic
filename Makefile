# Compiler
CXX = g++
CXXFLAGS = -O2 -I. -IBallistic/src

SRCS := BallisticEditor/src/EditorMain.cpp
OBJS := $(SRCS:.cpp=.o)
LIBS := Ballistic/libBallistic.a Ballistic/Thirdparty/glfw/lib/libglfw3.a -lopengl32 -lgdi32 -luser32 -lkernel32

OUT_DIR = out
BUILD_DIR = build
TARGET = $(OUT_DIR)/BallisticEngine.exe

all: libs $(TARGET)

$(TARGET): $(OBJS)
	@if not exist "$(OUT_DIR)" mkdir "$(OUT_DIR)"
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	$(TARGET)

libs:
	cd Ballistic/ && $(MAKE) -f make.mk

clean:
	@if exist "$(OUT_DIR)" rmdir /s /q "$(OUT_DIR)"

.PHONY: all run libs clean