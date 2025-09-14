# === Configuration ===
# === Compiler ===
CXX := g++
CXXFLAGS := -std=c++20 -g -lm 

# === Paths ===
INCLUDES := -Iinclude -I. -Iinclude/BEngine
LDFLAGS := -Llib -lglfw3dll

# === Files ===
SRCS := src/main.cpp
ENGINE_SCRS := $(wildcard include/BEngine/*.cpp) $(wildcard include/BEngine/glad/*.c) $(wildcard include/BEngine/stb/*.cpp)

ALL_SRCS:= $(SRCS) $(ENGINE_SCRS)

OUT := engine.exe

# === Targets ===

compile: test run

test:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(ALL_SRCS) -o $(OUT) $(LDFLAGS)

run:
	./$(OUT)