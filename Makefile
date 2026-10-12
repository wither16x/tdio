SOURCE_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin

SOURCES := $(shell find $(SOURCE_DIR) -name '*.cc')
OBJECTS := $(call patsubst,$(SOURCE_DIR)/%.cc,$(OBJ_DIR)/%.cc.o,$(SOURCES))
TARGET := $(BIN_DIR)/tdio

CXX := clang++
LD := clang++

CPPFLAGS := -Iinclude
CXXFLAGS := -std=c++23 -O2 \
		-Wall -Wextra -Wpedantic -Werror \
		-Wundef -Wshadow -Wconversion -Wsign-conversion -Wold-style-cast \
		-Wnon-virtual-dtor -Woverloaded-virtual -Wnull-dereference \
		-Wimplicit-fallthrough -Wformat=2 \
		-MMD -MP
LDFLAGS := -fuse-ld=lld \
		-lncurses

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	@echo "$(LD) $^ -> $@"
	@$(LD) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.cc.o: $(SOURCE_DIR)/%.cc
	@mkdir -p $(OBJ_DIR)
	@echo "$(CXX) $^ -> $@"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ -o $@

-include $(OBJECTS:.o=.d)

clean:
	@echo "Cleaning $(BUILD_DIR)..."
	@rm -rf $(BUILD_DIR)

run:
	@echo "Running $(TARGET)..."
	@./$(TARGET)