#
# Makefile for drag_race_cli_tree.c
#
CC=gcc
CFLAGS+=-std=c99
CPPFLAGS+=-D_POSIX_C_SOURCE=199309L
LDLIBS=-lncurses
SRC_FILES=$(wildcard *.c)
BIN_FILE=drag_race_cli_tree

.PHONY: all
all: $(BIN_FILE)

$(BIN_FILE): $(SRC_FILES)

.PHONY: debug
debug: CPPFLAGS+=-D_DEBUG_
debug: $(BIN_FILE)

.PHONY: clean
clean:
	$(RM) $(BIN_FILE)

