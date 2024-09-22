# Target executable name
TARGET = build/main

# Directories
SRC = src
BUILD = build

# Find all source files
SRCS = $(wildcard $(SRC)/*.c)

# Convert source files to object files in the build directory
OBJS = $(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(SRCS))

# Compiler settings
CC = gcc
CFLAGS =  -std=c11 -Wall -pedantic -O3
CFLAGS += -g
CFLAGS += -fsanitize=address -fno-omit-frame-pointer
LDFLAGS += -fsanitize=address -lSDL2

# Default target to build the project
all: $(TARGET)

# Link object files to create the final executable
$(TARGET): $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

# Compile each .c file into an object file in the build directory
$(BUILD)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Remove object files and the target
clean:
	rm -f $(BUILD)/*.o $(TARGET)

# Shortcut to run the program
run: $(TARGET)
	./$(TARGET)
