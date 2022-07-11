# LVM
64-bit RISC-based virtual machine made in C 

# TODO:
1.) Implement an assembler so we can have labels and have string support along with syntactical error detection.

2.) Fix stack overflows.

3.) Fix issues with cascading instructions fucking with the output

4.) Profit???

5.) ???

# What is a virtual machine?
Whenever you think about the word "virtual machine" you most likely think of operating system virtual machine, this type of virtual machine isn't that. This type of virtual machine is a piece of software that emulates how a processor internally works, fetching operands, decoding opcodes from mnemonics and what not. They have many uses such as: interpretered programming languages, it's also used for certain obfuscation techniques where we use a virtual machine to emulate the program so reverse engineers have another ISA to work around, it's really interesting. But we feed these byte-code ISA's that the virtual machine can emulate and run the instructions in a run-time environment, the given instruction set is defined below:

# Instruction set synax:
```
// Immediate addressing opcodes:
MOV_IMM,  // MOV_IMM,  IMM32/IMM64, REG
ADD_IMM,  // ADD_IMM,  IMM32/IMM64, REG
SUB_IMM,  // SUB_IMM,  IMM32/IMM64, REG
MUL_IMM,  // MUL_IMM,  IMM32/IMM64, REG
DIV_IMM,  // DIV_IMM,  IMM32/IMM64, REG
IMUL_IMM, // IMUL_IMM, IMM32/IMM64, REG
IDIV_IMM, // IDIV_IMM, IMM32/IMM64, REG
PUSH_IMM, // PUSH_IMM, IMM32/IMM64
CMP_IMM,  // CMP_IMM,  REG, IMM32/IMM64

// Misc:
NOR,  // NOR, REG
NEG,  // NEG, REG
CLF,  // CLF (clear flags)
INC,  // INC, REG
DEC,  // DEC, REG
SUF,  // SUF (Setup stack frame)
DSF,  // DSF (Destroy stack frame)
HLT,  // HLT
DUMP_STACK, // PRINT_STACK
DUMP_CPU_INFO, // DUMP_CPU_INFO

// Control-flow instructions:
CALL, // CALL, LABEL
RET,  // RET
JMP,  // JMP, LABEL
CMP,  // CMP, REG, REG
JIE,  // JIE, LABEL
JNE,  // JNE, LABEL
JNZ,  // JNZ, LABEL
JGE,  // JGE, LABEL
JG,   // JG,  LABEL
JL,   // JL,  LABEL
JLE,  // JLE, LABEL
NOP,  // NOP

// Bitwise operations:
SHR,  // SHR, REG, REG
SHL,  // SHL, REG, REG
XOR,  // XOR, REG, REG
AND,  // AND, REG, REG

// Register addressing opcodes:
MOV_REG,  // MOV_REG,  REG, REG
ADD_REG,  // ADD_REG,  REG, REG
SUB_REG,  // SUB_REG,  REG, REG
MUL_REG,  // MUL_REG,  REG, REG
DIV_REG,  // DIV_REG,  REG, REG
IMUL_REG, // IMUL_REG, REG, REG
IDIV_REG, // IDIV_REG, REG, REG
PUSH_REG, // PUSH_REG, REG
POP_REG,  // POP_REG,  REG

/*
Register-memory addressing opcodes:

Work in progress:
MOV_IMM_MEM,   // MOV_IMM_MEM, DATA, PTR
MOV_STR_MEM,   // MOV_STR_MEM, DATA, PTR
PRINT_IMM_MEM, // PRINT_IMM_MEM
PRINT_STR_MEM, // PRINT_STR_MEM
*/

// Floating point immediate instructions:
MOVSS_IMM,  // MOVSS_IMM,  FP64, FP_REG
ADDSS_IMM,  // ADDSS_IMM,  FP64, FP_REG
SUBSS_IMM,  // SUBSS_IMM,  FP64, FP_REG
MULSS_IMM,  // MULSS_IMM,  FP64, FP_REG
DIVSS_IMM,  // DIVSS_IMM,  FP64, FP_REG
IMULSS_IMM, // IMULSS_IMM, FP64, FP_REG
IDIVSS_IMM, // IDIVSS_IMM, FP64, FP_REG	
PUSHF_IMM,  // PUSHF_IMM,  FP64, FP_REG

// Floating point register instructions:
MOVSS_REG,  // MOVSS_REG,  FP_REG, FP_REG
ADDSS_REG,  // ADDSS_REG,  FP_REG, FP_REG
SUBSS_REG,  // SUBSS_REG,  FP_REG, FP_REG
MULSS_REG,  // MULSS_REG,  FP_REG, FP_REG
DIVSS_REG,  // DIVSS_REG,  FP_REG, FP_REG
IMULSS_REG, // IMULSS_REG, FP_REG, FP_REG
IDIVSS_REG, // IDIVSS_REG, FP_REG, FP_REG
PUSHF_REG,  // PUSHF_REG,  FP_REG
POPF_REG,   // FPOP_REG,   FP_REG

// Control-flow:
FCMP,      // FCMP, FP_REG, FP_REG
FCMP_IMM,  // FCMP_IMM, FP64, FP_REG
FJNE,      // FJNE, LABEL
FJIE,      // FJIE, LABEL
FJNZ,      // FJNZ, LABEL
FJGE,      // FJGE, LABEL
FJG,       // FJG,  LABEL
FJL,       // FJL,  LABEL
FJLE,      // FJLE, LABEL
```

# Registers:
```
// General purpose registers:
LA = 0x00, // Accumlator register.
LD = 0x01, // data index : data register.
LC = 0x02, // Count register
LS = 0x03, // Source index register
LB = 0x04  // Base index register
```

```
// Floating point registers:
X0 = 0x00,
X1 = 0x01,
X2 = 0x02,
X3 = 0x03,
X4 = 0x04
```

# Where to store the instructions at:
We store the instructions inside of an ``unsigned long`` array of bytes like so:
```c
qword instructions[] = {
	DUMP_CPU_INFO,
	HLT
};
```
We store the mnemonics and the operands as indices in an array. This is the array we will operate on with other functions. Speaking of which let's setup the virtual cpu structure:

# How to populate the cpu structure:
We populate the structure using the ``new_cpu`` function that sets up the structure and gets everything ready run the cpu with. It should look like this: ``cpu_t *cpu = new_cpu(instructions, LENGTH(instructions), 15);``, let's break this down. The first argument is where we're reading instructions from, the second is the length of the array using the ``LENGTH()`` macro-defined function. The next parameter is the length of the stack our cpu is using.

# How to emulate the byte-code:
We emulate the simulation using the ``run_cpu()`` function, this function basically just runs until there's a ``HLT`` mnemonic which halts the program and breaks out of the execution cycle. You NEED this at the end of your byte-code instruction. An example would look like so: ``	run_cpu(cpu);``. The argument is the structure we're passing by reference that we populated before.

# How to garbage collect the program:
We destroy the structure and free the memory with the ``destroy_cpu()`` function, we pass the ``cpu`` reference we defined 2 lines ago. A valgrind from this program:
```c
#include "../../includes/vcpu.h"

int main(void)
{
	qword instructions[] = {
		DUMP_CPU_INFO,
		HLT
	};

	cpu_t *cpu = new_cpu(instructions, LENGTH(instructions), 15);
	run_cpu(cpu);
	destroy_cpu(cpu);
}
```
looks like:
```
   ~/De/p/LVM ❯ valgrind --leak-check=full ./main   1.03   9.57G  38%
==2347== Memcheck, a memory error detector
==2347== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==2347== Using Valgrind-3.17.0 and LibVEX; rerun with -h for copyright info
==2347== Command: ./main
==2347== 
2
16
LA -> {0}
LD -> {0}
LC -> {0}
LS -> {0}
LB -> {0}
X0 -> {0.000000}
X1 -> {0.000000}
X2 -> {0.000000}
X3 -> {0.000000}
X4 -> {0.000000}
lf -> {0}
gf -> {0}
zf -> {0}
equ_fl -> {0}
f_lf -> {0}
f_gf -> {0}
f_zf -> {0}
f_equ_fl -> {0}
==2347== 
==2347== HEAP SUMMARY:
==2347==     in use at exit: 0 bytes in 0 blocks
==2347==   total heap usage: 3 allocs, 3 frees, 1,312 bytes allocated
==2347== 
==2347== All heap blocks were freed -- no leaks are possible
==2347== 
==2347== For lists of detected and suppressed errors, rerun with: -s
==2347== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

# How to dump cpu register & flag information:
We have a mnemonic specificaly called: ``DUMP_CPU_INFO`` and it basically just calls: ``dump_cpu_info()`` and passes ``cpu`` by reference to it's arguments.

# How to dump cpu stack information:
We have a mnemonic specially called: ``DUMP_STACK`` and it basically just calls: ``dump_stack()`` and passes ``cpu`` by reference to it's arguments.

# How to enable debugging mode:
In the makefile we can simply ``make debug`` which will compile the binary with debugging symbols + an address sanitizer. Now there is some stack overflows for specific instructions. Why? I have no fucking clue.

