# Compiler of choice:
GCC  = gcc
LLVM = clang

# Compiler setup:
CFLAGS      = -Wall -Wextra -Wpedantic -Og -g3 -o
DEBUG_FLAGS = -Wall -Wextra -Wpedantic -Og -g3 -fsanitize=address,undefined -D DEBUG -o

VCPU_SRC = ../../../src/vcpu/vcpu.c ../../../src/vcpu/stack.c

MOV_SRC  = mov_reg.c
ADD_SRC  = add_reg.c
SUB_SRC  = sub_reg.c
MUL_SRC  = mul_reg.c
DIV_SRC  = div_reg.c
CMP_SRC  = cmp_reg.c
IMUL_SRC = imul_reg.c
IDIV_SRC = idiv_reg.c
PUSH_SRC = push_reg.c

MOV_BIN  = mov_reg
ADD_BIN  = add_reg
SUB_BIN  = sub_reg
MUL_BIN  = mul_reg
DIV_BIN  = div_reg
CMP_BIN  = cmp_reg
IMUL_BIN = imul_reg
IDIV_BIN = idiv_reg
PUSH_BIN = push_reg

build_mov:
	$(GCC) $(MOV_SRC) $(VCPU_SRC) $(CFLAGS) $(MOV_BIN)

build_debug_mov:
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

