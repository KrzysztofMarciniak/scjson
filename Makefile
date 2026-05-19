CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = scjson
SRC = scjson.c
OBJ = $(SRC:.c=.io)
all: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)
%.io: %.c scjson.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ) $(TARGET)
run: all
	./$(TARGET)
