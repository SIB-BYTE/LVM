#ifndef ASM_H
#define ASM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vcpu.h"

typedef struct instruction_layout {
	char *mnemonic;
	short opcode;

	int src, dst;
} instruction_t;

void compile_file(char *);
void emit_bytecode(FILE *);

#endif

