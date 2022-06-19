# LVM
32-bit RISC-based virtual machine made in C 

# Instruction set synax:
	Immediate addressing mode opcodes:
	MOV_IMM,  // MOV_IMM,  IMM32/IMM64, REG
	ADD_IMM,  // ADD_IMM,  IMM32/IMM64, REG
	SUB_IMM,  // SUB_IMM,  IMM32/IMM64, REG
	MUL_IMM,  // MUL_IMM,  IMM32/IMM64, REG
	DIV_IMM,  // DIV_IMM,  IMM32/IMM64, REG
	IDIV_IMM, // IDIV_IMM, LA, REG
	IMUL_IMM, // IMUL_IMM, LA, REG
	PUSH_IMM, // PUSH_IMM, IMM32/IMM64
	CMP_IMM,  // CMP_IMM,  REG, IMM32/IMM64

	// Control-flow instructions:
	CALL, // CALL, LABEL
	RET,  // RET
	JMP,  // JMP, LABEL
	CMP,  // CMP, REG, REG
	JNE,  // JNE, LABEL
	JIE,  // JIE, LABEL
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

	// Misc:
	NOR,  // NOR, REG
	NEG,  // NEG, REG
	CLR,  // CLR (clear flags)
	CLF,  // CLF (clear floating point flags)
	INC,  // INC, REG
	DEC,  // DEC, REG
	SUF,  // SUF (Setup stack frame)
	DSF,  // DSF (Destroy stack frame)
	HLT,  // HLT

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

	// Register-memory addressing opcodes:
	MOV_MEM,  // MOV_MEM, PTR, REG

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
	IMULSS_REG, // IMULSS_REG, X0, FP_REG
	IDIVSS_REG, // IDIVSS_REG, X0, FP_REG
	FPOP_REG,   // FPOP_REG,   FP_REG

	// Floating point control flow:
	FCMP,      // FCMP, FP_REG, FP_REG
	FCMP_IMM,  // FCMP_IMM, FP64, FP_REG
	FJNE,      // FJNE, LABEL
	FJIE,      // FJIE, LABEL
	FJNZ,      // FJNZ, LABEL
	FJGE,      // FJGE, LABEL
	FJG,       // FJG,  LABEL
	FJL,       // FJL,  LABEL
	FJLE,      // FJLE, LABEL

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
# Examples:
Addition:
```c

```

Subtraction:

Multplication:

Division:

Signed Multiplication:

Signed Division:

Negation:

Comparing immediates:

Comparing registers:

Incrementation:

Decrementation:

