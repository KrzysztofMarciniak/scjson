CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O0 -g -I..

LIB = ../libscjson.a

EXAMPLE_BIN = example.bin
ERROR_BIN   = example_error.bin

all: $(EXAMPLE_BIN) $(ERROR_BIN)

$(EXAMPLE_BIN): main.c $(LIB)
	$(CC) $(CFLAGS) main.c $(LIB) -o $@

$(ERROR_BIN): example_error.c $(LIB)
	$(CC) $(CFLAGS) example_error.c $(LIB) -o $@

run: $(EXAMPLE_BIN)
	./$(EXAMPLE_BIN)

run_error: $(ERROR_BIN)
	./$(ERROR_BIN)

clean:
	rm -f $(EXAMPLE_BIN) $(ERROR_BIN)

.PHONY: all run run_error clean
