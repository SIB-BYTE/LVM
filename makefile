# Compiler of choice:
CC   = gcc
LLVM = clang

# Compiler setup:
CFLAGS      = -Wall -Wextra -Wpedantic -Og -g3 -o
DEBUG_FLAGS = -Wall -Wextra -Wpedantic -Og -g3 -fsanitize=address,undefined -D DEBUG -o

SRC = src/vcpu/vcpu.c src/vcpu/main.c
MAIN_BIN  = main

build:
	$(CC) $(SRC) $(CFLAGS) $(MAIN_BIN)

debug_build:
	$(CC) $(SRC) $(DEBUG_FLAGS) $(MAIN_BIN)

