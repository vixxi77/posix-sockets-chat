CC = gcc

STD = -std=c99

CFLAGS = -Wall -Wextra $(STD) -Iinclude

SRC = $(wildcard src/*.c)

TARGET = server

all: $(TARGET)

$(TARGET):
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET)

run:
	./$(TARGET)

clean:
	rm -f $(TARGET)
