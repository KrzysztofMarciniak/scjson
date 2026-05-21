CFLAGS = -Wall -Wextra -std=c99 -O2 -I.
PICFLAGS = -fPIC

PREFIX ?= /usr/local
INCLUDE_DIR = $(PREFIX)/include
LIB_DIR = $(PREFIX)/lib

SRC = $(wildcard internal/*.c) scjson_wrappers.c
TEST_SRC = $(wildcard internal/tests/*.c)

OBJ = $(SRC:.c=.o)
PIC_OBJ = $(SRC:.c=.pic.o)

TEST_OBJ = $(TEST_SRC:.c=.o)

STATIC_LIB = libscjson.a
SHARED_LIB = libscjson.so

TEST_BIN = test_scjson

all: static

static: $(STATIC_LIB)

$(STATIC_LIB): $(OBJ)
	$(AR) rcs $@ $^

linked: $(SHARED_LIB)

$(SHARED_LIB): $(PIC_OBJ)
	$(CC) -shared -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.pic.o: %.c
	$(CC) $(CFLAGS) $(PICFLAGS) -c $< -o $@

test: $(OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $(TEST_BIN) $^
	./$(TEST_BIN)

clean:
	rm -f \
		$(OBJ) \
		$(PIC_OBJ) \
		$(TEST_OBJ) \
		$(STATIC_LIB) \
		$(SHARED_LIB) \
		$(TEST_BIN)

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDE_DIR)
	cp -f scjson.h $(DESTDIR)$(INCLUDE_DIR)/

install-static: static install-headers
	mkdir -p $(DESTDIR)$(LIB_DIR)
	cp -f $(STATIC_LIB) $(DESTDIR)$(LIB_DIR)/

install-linked: linked install-headers
	mkdir -p $(DESTDIR)$(LIB_DIR)
	cp -f $(SHARED_LIB) $(DESTDIR)$(LIB_DIR)/

install: install-static

.PHONY: all static linked test clean install install-headers install-static install-linked
