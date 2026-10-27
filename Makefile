# Linux OpenGL build (GLFW + GLAD + vendored GLM)
CXX      ?= g++
CXXFLAGS ?= -std=c++17 -g -Wall -Wextra
CPPFLAGS ?= -Iinclude
LDFLAGS  ?=
LDLIBS   ?= -lglfw -lGL -ldl -lpthread

SRC_DIR  := src
BUILD    := build
TARGET   := $(BUILD)/cutable

CXX_SRCS := $(wildcard $(SRC_DIR)/*.cpp)
C_SRCS   := $(SRC_DIR)/glad.c
OBJS     := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD)/%.o,$(CXX_SRCS)) \
            $(BUILD)/glad.o

.PHONY: all clean run

all: $(TARGET)

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/%.o: $(SRC_DIR)/%.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(BUILD)/glad.o: $(SRC_DIR)/glad.c | $(BUILD)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

# Shaders are loaded by relative path; run with cwd = src/
run: $(TARGET)
	cd $(SRC_DIR) && ../$(TARGET)

clean:
	rm -rf $(BUILD)
