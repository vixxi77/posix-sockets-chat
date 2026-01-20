CC = gcc

STD = -std=c99

CFLAGS = -Wall -Wextra $(STD) $(shell sdl2-config --cflags)

LDFLAGS = $(shell sdl2-config --libs)

SRC = $(wildcard src/*.c)

TARGET = client

all: $(TARGET)

$(TARGET):
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(TARGET)

run:
	./$(TARGET)

clean:
	rm -f $(TARGET)
