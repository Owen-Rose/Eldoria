# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Source files (only the ones we have implementations for)
SOURCES = $(SRC_DIR)/main.cpp \
         $(SRC_DIR)/game_engine.cpp \
         $(SRC_DIR)/command_parser.cpp \
         $(SRC_DIR)/game_world.cpp \
         $(SRC_DIR)/location_grid.cpp \
         $(SRC_DIR)/location.cpp \
         $(SRC_DIR)/environment_builder.cpp \
         $(SRC_DIR)/item.cpp \
         $(SRC_DIR)/usable_item.cpp \
         $(SRC_DIR)/npc.cpp \
         $(SRC_DIR)/puzzle.cpp \
         $(SRC_DIR)/riddle_puzzle.cpp \
         $(SRC_DIR)/reflection_puzzle.cpp \
         $(SRC_DIR)/book_sorting_puzzle.cpp

# Object files
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Main target
TARGET = $(BUILD_DIR)/game

# Default target
all: $(TARGET)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link the game
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean