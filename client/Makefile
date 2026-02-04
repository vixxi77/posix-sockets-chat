CC = gcc

STD = -std=c99

CFLAGS = -Wall -Wextra $(STD) $(shell sdl2-config --cflags) $(shell pkg-config --cflags SDL2_image) \
	 $(shell pkg-config --cflags SDL2_ttf) -Iinclude

LDFLAGS = $(shell sdl2-config --libs) $(shell pkg-config --libs SDL2_image) \
	  $(shell pkg-config --libs SDL2_ttf) 

SRC = $(wildcard src/*.c)

TARGET = client

all: $(TARGET)

$(TARGET):
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(TARGET)

run:
	./$(TARGET)

clean:
	rm -f $(TARGET)
