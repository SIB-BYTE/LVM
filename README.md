# LVM
32-bit RISC-based virtual machine made in C 

# Instruction set:

	Immediate addressing opcodes:
	MOV_IMM,  // MOV_IMM,  IMM32/IMM64, REG
	ADD_IMM,  // ADD_IMM,  IMM32/IMM64, REG
	SUB_IMM,  // SUB_IMM,  IMM32/IMM64, REG
	MUL_IMM,  // MUL_IMM,  IMM32/IMM64, REG
	DIV_IMM,  // DIV_IMM,  IMM32/IMM64, REG
	IDIV_IMM, // IDIV_IMM, IMM32/IMM64, REG
	IMUL_IMM, // IMUL_IMM, IMM32/IMM64, REG
	PUSH_IMM, // PUSH_IMM, IMM32/IMM64

  	// Misc:
	INC,  // INC, REG  
	DEC,  // DEC, REG
	SUF,  // (Setup stack frame)
	
  	Control-flow:
  	CALL, //
	RET,  //
	JMP,  //
	CMP,  //
	JNE,  //
	JIE,  //
	JNZ,  //
	JGE,  //
	JG,   //
	JL,   //
	JLE,  //
	NOP,  //
	SHR,  //
	SHL,  //
	XOR,  //
	AND,  //
	NOR,  //
	NEG,  //
	HLT,  //

	Register addressing opcodes:
	MOV_REG,  //
	ADD_REG,  //
	SUB_REG,  //
	MUL_REG,  //
	DIV_REG,  //
	IMUL_REG, //
	IDIV_REG, //
	PUSH_REG, //
	POP_REG,  //

	// Register-memory addressing opcodes:
	MOV_MEM,  //

# Examples:

