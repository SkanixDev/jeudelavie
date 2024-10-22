CC = gcc
CFLAGS = -std=c17 -Wall
INCLUDES = -I./include -I./include/grid/
LIBS = -L./lib -lmingw32 -lSDL2main -lSDL2
SRC = $(wildcard ./src/*.c) $(wildcard ./src/grid/*.c)
TARGET = main

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(SRC) $(LIBS)

run: $(TARGET)
	$(TARGET).exe
	del $(TARGET).exe

.PHONY: clean

clean:
	del $(TARGET).exe
