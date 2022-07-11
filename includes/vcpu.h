#ifndef VCPU_H
#define VCPU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ease of typing more fit for a virtual machine:
typedef double f64;
typedef unsigned long qword;

// Colors:
#define RED "\x1b[0;31m"
#define PUR "\x1b[0;34m"
#define BLU "\x1b[0;32m"
#define WHI "\x1b[1;37m"

// Marco-defined functions:
#define LENGTH(array) sizeof(array) / sizeof(*array)

// General purpose registers:
enum GRPs {
	LA = 0x00, // Accumlator register.
	LD = 0x01, // data index : data register.
	LC = 0x02, // Count register
	LS = 0x03, // Source index register
	LB = 0x04  // Base index register
};

// Floating point registers:
enum FPRs {
	X0 = 0x00,
	X1 = 0x01,
	X2 = 0x02,
	X3 = 0x03,
	X4 = 0x04
};

// Flag structures:
typedef struct flags {
	unsigned char lf : 1;
	unsigned char gf : 1;
	unsigned char zf : 1;
	unsigned char equ_fl : 1;
} flag_t;

// Floating flag structures:
typedef struct float_flags {
	unsigned char f_lf : 1;
	unsigned char f_gf : 1;
	unsigned char f_zf : 1;
	unsigned char f_equ_fl : 1;
} float_flags_t;

// Instruction map:
enum mnemonics {
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
};

// cpu structure (holds instruction ptr, stack ptr and more)
typedef struct cpu {
    	// Instructions:
    	qword *instructions;
	qword current_instruction, instruction_length;

	// CPU internals:
	qword registers[5], ip;

	// floating-point registers
	f64 floating_registers[5];

	// Instruction operands:
	qword src, dst;

	// Integer memory stack:
	qword *integer_stack;
	int sp, stack_length, stack_capacity;

	// Floating point memory stack:
	f64 *fp_stack;
	int fp_sp, fp_stack_length, fp_stack_capacity;

	// Flags:
	flag_t flags;
	float_flags_t float_flags;
} cpu_t;

// Virtual CPU functions:
void run_cpu(cpu_t *);
void execute(cpu_t *);
void destroy_cpu(cpu_t *);
void dump_cpu_info(cpu_t *);
void halt_and_catch_fire(cpu_t *);
cpu_t *new_cpu(qword *, qword, qword);

// Flags:
void clear_flags(cpu_t *);
void set_flags(cpu_t *, qword, qword);

// Floating point flags:
void set_floating_flags(cpu_t *, f64, f64);

// Debugging:
const char *bind_name(qword instruction);

#endif

