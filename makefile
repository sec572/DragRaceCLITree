#
# Makefile for drag_race_cli_tree.c
#
CC=gcc
CFLAGS=-lncurses
SRC_FILES=drag_race_cli_tree.c
BIN_FILE=drag_race_cli_tree

drag_race_cli_tree:
	$(CC) $(SRC_FILES) $(CFLAGS) -o $(BIN_FILE)

debug:
	$(CC) -D _DEBUG_ $(SRC_FILES) $(CFLAGS) -o $(BIN_FILE)

all: drag_race_cli_tree

clean:
	rm $(BIN_FILE)

