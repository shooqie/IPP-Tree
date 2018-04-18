SRC_FILES = node.c tree.c io.c solution.c
OBJ_FILES = $(SRC_FILES:.c=.o)
EXE_NAME = solution
DBG_EXE_NAME = solution.dbg

CFLAGS = -std=c99
CC = gcc
RM = rm -f

build:
	$(CC) $(CFLAGS) -c $(SRC_FILES)
	$(CC) $(CFLAGS) -o $(EXE_NAME) $(OBJ_FILES)

debug: CFLAGS += -g
debug: EXE_NAME = $(DBG_EXE_NAME)
debug: build

clean:
	$(RM) $(OBJ_FILES) $(EXE_NAME) $(DBG_EXE_NAME)