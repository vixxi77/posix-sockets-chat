CC = gcc

STD = -std=c99

CFLAGS = $(shell sdl2-config --cflags --libs)

SRC = $(wildcard src/*.c)

TARGET = client

all:
	$(CC) $(SRC) $(STD) $(CFLAGS) -o $(TARGET)

run:
	./$(TARGET)

clean:
	rm $(TARGET)
