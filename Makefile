CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -I.

SRC = scjson.c $(wildcard internal/*.c)
TEST_SRC = $(wildcard internal/tests/*.c)

OBJ = $(SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)

TARGET = scjson
TEST_BIN = test_scjson

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

test: $(OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $(TEST_BIN) $^
	./$(TEST_BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET) $(TEST_BIN)

.PHONY: all test clean
