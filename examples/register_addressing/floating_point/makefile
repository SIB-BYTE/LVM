# Compiler of choice:
GCC   = gcc
LLVM = clang

# Compiler setup:
CFLAGS      = -Wall -Wextra -Wpedantic -Og -g3 -o
DEBUG_FLAGS = -Wall -Wextra -Wpedantic -Og -g3 -fsanitize=address,undefined -D DEBUG -o

VCPU_SRC = ../../../src/vcpu/vcpu.c ../../../src/vcpu/stack.c

MOV_SRC  = fp_mov_imm.c
ADD_SRC  = fp_add_imm.c
SUB_SRC  = fp_sub_imm.c
MUL_SRC  = fp_mul_imm.c
DIV_SRC  = fp_div_imm.c
CMP_SRC  = fp_cmp_imm.c
IMUL_SRC = fp_imul_imm.c
IDIV_SRC = fp_idiv_imm.c
PUSH_SRC = fp_push_imm.c

MOV_BIN  = fp_mov_imm
ADD_BIN  = fp_add_imm
SUB_BIN  = fp_sub_imm
MUL_BIN  = fp_mul_imm
DIV_BIN  = fp_div_imm
CMP_BIN  = fp_cmp_imm
IMUL_BIN = fp_imul_imm
IDIV_BIN = fp_idiv_imm
PUSH_BIN = fp_push_imm

build_mov:
	$(GCC) $(MOV_SRC) $(VCPU_SRC) $(CFLAGS) $(MOV_BIN)

buld_debug_mov:
	$(GCC) $(MOV_SRC) $(VCPU_SRC) $(DEBUG_FLAGS) $(MOV_BIN)

build_add:
	$(GCC) $(ADD_SRC) $(VCPU_SRC) $(CFLAGS) $(ADD_BIN)

build_debug_add:
	$(GCC) $(ADD_SRC) $(VCPU_SRC) $(DEBUG_FLAGS) $(ADD_BIN)

build_sub:
	$(GCC) $(SUB_SRC) $(VCPU_SRC) $(CFLAGS) $(SUB_BIN)

build_debug_sub:
	$(GCC) $(SUB_SRC) $(VCPU_SRC) $(DEBUG_FLAGS) $(SUB_BIN)

build_mul:
	$(GCC) $(MUL_SRC) $(VCPU_SRC) $(CFLAGS) $(MUL_BIN)

build_debug_mul:
	$(GCC) $(MUL_SRC) $(VCPU_SRC) $(DEBUG_FLAGS) $(MUL_BIN)

build_div:
	$(GCC) $(DIV_SRC) $(VCPU_SRC) $(CFLAGS) $(DIV_BIN)

build_debug_div:
	$(GCC) $(DIV_SRC) $(VCPU_SRC) $(DEBUG_FLAGS) $(DIV_BIN)

build_cmp:
	$(GCC) $(CMP_SRC) $(VCPU_SRC) $(CFLAGS) $(CMP_BIN)

build_debug_cmp:
	$(GCC) $(CMP_SRC) $(VCPU_SRC) $(DEBUG_FLAGS) $(CMP_BIN)

build_imul:
	$(GCC) $(IMUL_SRC) $(VCPU_SRC) $(CFLAGS) $(IMUL_BIN)

build_debug_imul:
	$(GCC) $(IMUL_SRC) $(VCPU_SRC) $(DEBUG_FLAGS) $(IMUL_BIN)

build_idiv:
	$(GCC) $(IDIV_SRC) $(VCPU_SRC) $(CFLAGS) $(IDIV_BIN)

build_debug_idiv:
	$(GCC) $(IDIV_SRC) $(VCPU_SRC) $(DEBUG_FLAGS) $(IDIV_BIN)

build_push:
	$(GCC) $(PUSH_SRC) $(VCPU_SRC) $(CFLAGS) $(PUSH_BIN)

build_debug_push:
	$(GCC) $(PUSH_SRC) $(VCPU_SRC) $(DEBUG_FLAGS) $(PUSH_BIN)
