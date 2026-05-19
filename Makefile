CFLAGS = -Wall -Wextra -std=c99 -O2

TARGET = scjson

SRC = scjson.c scjson.h $(wildcard internal/*.c) $(wildcard internal/*.h)  

TESTS = $(wildcard internal/tests/*.c)

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) test_scjson

run: all
	./$(TARGET)

test:
	$(CC) $(CFLAGS) $(SRC) $(TESTS) -o test_scjson
	./test_scjson
