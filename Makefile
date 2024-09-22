
TARGET = build/main

SRC = src 
BUILD = build

SRCS = $(wildcard $(SRC)/*.c)

OBJS = $(patsubst %(SRC)/%.c, $(BUILD)/%.o, $(SRCS))


# Compilation

CC = gcc

CFLAGS =  -std=gnull -Wall -pedantic -O3
CFLAGS += -g
CFLAGS += -fsanitize=address -fno-omit-frame-pointer
LDFLAGS += -fsanitize=address

# Raccourcis

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

$(BUILD)/%.o : $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(BUILD)/*.o $(TARGET)

run : $(TARGET)
	./$(TARGET)