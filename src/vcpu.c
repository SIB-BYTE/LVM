#include "../../includes/vcpu.h"

// Virtual CPU functions:
cpu_t *new_cpu(qword *instructions, qword instruction_length, qword stack_size)
{
	cpu_t *cpu = calloc(1, sizeof(cpu_t));

	// Copying over the instruction array parameter context to the structures context:
	cpu->instructions = instructions;
	cpu->instruction_length = instruction_length;

	// Stack creation:
	cpu->stack = calloc(stack_size, sizeof(qword));
	cpu->stack_capacity = stack_size;
	cpu->sp = -1;

	return (cpu);
}

// Runs the execute cycle of a program:
void run_cpu(cpu_t *cpu)
{
	// Run until halted:
	while(cpu->current_instruction != HLT)
		execute(cpu);
}

// Executes the encountered byte-code:
void execute(cpu_t *cpu)
{
	if(cpu->ip >= cpu->instruction_length)
		halt_and_catch_fire(cpu);

	// Setting the current instruction to the first index of the array:
	cpu->current_instruction = cpu->instructions[cpu->ip];
	qword opcode = cpu->current_instruction;

	if(cpu->current_instruction != HLT)
	{
		cpu->src = cpu->instructions[cpu->ip + 1];
		cpu->dst = cpu->instructions[cpu->ip + 2];
	}
	else
		return;

	qword return_address = 0;

#ifdef DEBUG
	printf("%sInstruction pointer -> (%ld)\nStack pointer -> {%ld}\n", PUR, cpu->ip, cpu->sp);
	printf("%sCurrent instruction -> {%s}\nCurrent source -> {%ld}\nCurrent destination -> {%lu}\n\n", BLU, bind_name(cpu->current_instruction), cpu->src, cpu->dst);
#endif

	switch(opcode)
	{
		// Immedate addressing instructions:
		case MOV_IMM:  cpu->registers[cpu->dst] =  cpu->src; cpu->ip += 3; break;
		case ADD_IMM:  cpu->registers[cpu->dst] += cpu->src; cpu->ip += 3; break;
		case SUB_IMM:  cpu->registers[cpu->dst] -= cpu->src; cpu->ip += 3; break;
		case MUL_IMM:  cpu->registers[cpu->dst] *= cpu->src; cpu->ip += 3; break;
		case DIV_IMM:  cpu->registers[cpu->dst] /= cpu->src; cpu->ip += 3; break;
		case IMUL_IMM: cpu->registers[LA] *= (signed) cpu->dst; cpu->ip += 2; break;
		case IDIV_IMM: cpu->registers[LA] /= (signed) cpu->dst; cpu->ip += 2; break;

		// Control flow instructions:
		case JMP:     cpu->ip = cpu->src; break;
		case CALL:    push(cpu, cpu->ip); cpu->ip = cpu->registers[cpu->src]; cpu->ip += 2; break;
		case RET:     return_address = peek(cpu); cpu->ip = return_address;   cpu->ip += 2; break;
		case CMP_IMM: set_flags(cpu, cpu->src, cpu->registers[cpu->dst]); cpu->ip += 3; break;
		case CMP:     set_flags(cpu, cpu->registers[cpu->src], cpu->registers[cpu->dst]); cpu->ip += 3; break;
		case JNZ:	  if(cpu->flags.zf) cpu->ip = cpu->src; else cpu->ip += 2; break;
		case JLE:	  if(cpu->flags.lf || cpu->flags.equ_fl) cpu->ip = cpu->src; else cpu->ip += 2; break;
		case JGE:	  if(cpu->flags.gf || cpu->flags.equ_fl) cpu->ip = cpu->src; else cpu->ip += 2; break;
		case JIE:	  if(cpu->flags.equ_fl)  cpu->ip = cpu->src; else cpu->ip += 2; break;
		case JNE:	  if(!cpu->flags.equ_fl) cpu->ip = cpu->src; else cpu->ip += 2; break;
		case JG:	  if(cpu->flags.gf) cpu->ip = cpu->src; else cpu->ip += 2; break;
		case JL:	  if(cpu->flags.lf) cpu->ip = cpu->src; else cpu->ip += 2; break;

		// Misc:
		case CLF: clear_flags(cpu); cpu->ip++; break;
		case NEG: cpu->registers[cpu->src] =  -(cpu->registers[cpu->src]); cpu->ip += 2; break;
		case INC: cpu->registers[cpu->src]++; cpu->ip += 2; break;
		case DEC: cpu->registers[cpu->src]--; cpu->ip += 2; break;
		case PUSH_IMM: push(cpu, cpu->src); cpu->ip += 2; break;
		case PUSH_REG: push(cpu, cpu->registers[cpu->src]); cpu->ip += 2; break;
		case POP_REG: cpu->registers[cpu->src] = peek(cpu); cpu->ip += 2; break;
		case DUMP_STACK: dump_stack(cpu);       cpu->ip++; break;
		case DUMP_CPU_INFO: dump_cpu_info(cpu); cpu->ip++; break;
		case NOP: cpu->ip++; break;
		case HLT: return;

		// Bit-wise operation instructions:
		case SHR: cpu->registers[cpu->dst] >>= cpu->registers[cpu->src];   cpu->ip += 3;  break;
		case SHL: cpu->registers[cpu->dst] <<= cpu->registers[cpu->src];   cpu->ip += 3;  break;
		case XOR: cpu->registers[cpu->dst] ^=  cpu->registers[cpu->src];   cpu->ip += 3;  break;
		case AND: cpu->registers[cpu->dst] &=  cpu->registers[cpu->src];   cpu->ip += 3;  break;
		case NOR: cpu->registers[cpu->dst] =  ~(cpu->registers[cpu->src]); cpu->ip += 2;  break;

		// Register-based addressing mode instructions:
		case MOV_REG:  cpu->registers[cpu->dst] =  cpu->registers[cpu->src]; cpu->ip += 3; break;
		case ADD_REG:  cpu->registers[cpu->dst] += cpu->registers[cpu->src]; cpu->ip += 3; break;
		case SUB_REG:  cpu->registers[cpu->dst] -= cpu->registers[cpu->src]; cpu->ip += 3; break;
		case MUL_REG:  cpu->registers[cpu->dst] *= cpu->registers[cpu->src]; cpu->ip += 3; break;
		case IMUL_REG: cpu->registers[LA]  *= (signed) cpu->registers[cpu->dst]; cpu->ip += 3; break;
		case IDIV_REG: cpu->registers[LA]  /= (signed) cpu->registers[cpu->dst]; cpu->ip += 3; break;

		// Floating point immedate instructions:
		case MOVSS_IMM:  cpu->floating_registers[cpu->dst] =  (f64) cpu->src; cpu->ip += 3; break;
		case ADDSS_IMM:  cpu->floating_registers[cpu->dst] += (f64) cpu->src; cpu->ip += 3; break;
		case SUBSS_IMM:  cpu->floating_registers[cpu->dst] -= (f64) cpu->src; cpu->ip += 3; break;
		case MULSS_IMM:  cpu->floating_registers[cpu->dst] *= (f64) cpu->src; cpu->ip += 3; break;
		case DIVSS_IMM:  cpu->floating_registers[cpu->dst] /= (f64) cpu->src; cpu->ip += 3; break;
		case IMULSS_IMM: cpu->floating_registers[cpu->dst] *= (signed) (f64) cpu->src; cpu->ip += 3; break;
		case IDIVSS_IMM: cpu->floating_registers[cpu->dst] /= (signed) (f64) cpu->src; cpu->ip += 3; break;

		// Floating point control flow instructions:
		case FCMP_IMM: set_floating_flags(cpu, (f64) cpu->src, (f64) cpu->floating_registers[cpu->dst]); cpu->ip += 3; break;
		case FJNE:	   if(!cpu->float_flags.f_equ_fl) cpu->ip = cpu->src; else cpu->ip += 2; break;
		case FJNZ:     if(cpu->float_flags.f_zf) cpu->ip = cpu->src; else cpu->ip += 2;      break;
		case FJIE:     if(cpu->float_flags.f_equ_fl) cpu->ip = cpu->src; else cpu->ip += 2;  break;
		case FJLE:     if(cpu->float_flags.f_lf || cpu->float_flags.f_equ_fl) cpu->ip = cpu->src; else cpu->ip += 2; break;
		case FJGE:     if(cpu->float_flags.f_gf || cpu->float_flags.f_equ_fl) cpu->ip = cpu->src; else cpu->ip += 2; break;
		case FJG:	   if(cpu->float_flags.f_gf) cpu->ip = cpu->src; else cpu->ip += 2;      break;
		case FJL:      if(cpu->float_flags.f_lf) cpu->ip = cpu->src; else cpu->ip += 2;		 break;

		// Invalid operation:
		default: halt_and_catch_fire(cpu);
	}
}

// Error displaying:
void halt_and_catch_fire(cpu_t *cpu)
{
	printf("Mnemonic -> {%s}\nInstruction pointer -> {%lu}\n", bind_name(cpu->current_instruction), cpu->ip);
	exit(0);
}

// Flag functions:
void set_flags(cpu_t *cpu, qword src, qword dst)
{
	int flag_results = src - dst;

	cpu->flags.zf = (!flag_results);
	cpu->flags.equ_fl = (src == dst);
	cpu->flags.gf = (flag_results > 0);
	cpu->flags.lf = (flag_results < 0);
}

// Set floating flags:
void set_floating_flags(cpu_t *cpu, f64 src, f64 dst)
{
	f64 float_flag_results = src - dst;

	cpu->float_flags.f_zf = (!float_flag_results);
	cpu->float_flags.f_equ_fl = (src == dst);
	cpu->float_flags.f_gf = (float_flag_results > 0);
	cpu->float_flags.f_lf = (float_flag_results < 0);
}

// Clear flags:
void clear_flags(cpu_t *cpu)
{
	cpu->flags.equ_fl = 0;
	cpu->flags.gf     = 0;
	cpu->flags.lf     = 0;
	cpu->flags.zf     = 0;

	cpu->float_flags.f_equ_fl = 0;
	cpu->float_flags.f_gf     = 0;
	cpu->float_flags.f_lf     = 0;
	cpu->float_flags.f_zf     = 0;
}

// Stack functions:
void dump_stack(cpu_t *cpu)
{
	// Loops through the stack ADT and dumps the values:
	for(qword i = 0; i < cpu->stack_length; ++i)
		printf("%sStack[%lu] -> {%lu}\n", WHI, i, cpu->stack[i]);

	putchar('\n');
}

// Insert another element into a stack:
void push(cpu_t *cpu, int data)
{
	// Dynamically resize the stack:
	if(cpu->stack_length == cpu->stack_capacity)
	{
		// Doubles the size capacity of the stack:
		cpu->stack_capacity *= 2;
		cpu->stack = realloc(cpu->stack, cpu->stack_capacity);
	}

	// Inserts "data" onto the stack:
	cpu->sp++;
	cpu->stack[cpu->sp] = data;
	cpu->stack_length++;
}

// Returns the value at the top of the stack:
inline int __attribute__((__always_inline__)) peek(cpu_t *cpu)
{
	return (cpu->stack[cpu->sp]);
}

// Display cpu information:
void dump_cpu_info(cpu_t *cpu)
{
	// GRP's & FPR's. Sorta hard to read, but it just prints everything:
	printf("%sLA -> {%lu}\nLD -> {%lu}\nLC -> {%lu}\nLS -> {%lu}\nLB -> {%lu}\n", RED, cpu->registers[LA], cpu->registers[LD], cpu->registers[LC], cpu->registers[LS], cpu->registers[LB]);
	printf("%sX0 -> {%lf}\nX1 -> {%lf}\nX2 -> {%lf}\nX3 -> {%lf}\nX4 -> {%lf}\n", BLU, cpu->floating_registers[X0], cpu->floating_registers[X1], cpu->floating_registers[X2], cpu->floating_registers[X3], cpu->floating_registers[X4]);

	// Prints flag status.
	printf("%slf -> {%d}\ngf -> {%d}\nzf -> {%d}\nequ_fl -> {%d}\n", PUR, cpu->flags.lf, cpu->flags.gf, cpu->flags.zf, cpu->flags.equ_fl);

	// Prints floating flag status:
	printf("f_lf -> {%d}\nf_gf -> {%d}\nf_zf -> {%d}\nf_equ_fl -> {%d}\n", cpu->float_flags.f_lf, cpu->float_flags.f_gf, cpu->float_flags.f_zf, cpu->float_flags.f_equ_fl);
}

// Binds the a mnemonic to an opcode:
const char *bind_name(qword instruction)
{
	switch(instruction)
	{
	  // Normal instructions:
	  case INC:      return "INC";
	  case DEC:      return "DEC";
	  case SUF:      return "SUF";
      case RET:      return "RET";
	  case CALL:     return "CALL";
      case JMP:      return "JMP";
	  case JIE:      return "JIE";
	  case JNZ:      return "JNZ";
	  case JNE:		 return "JNE";
	  case JGE:      return "JGE";
	  case JG:		 return "JG";
	  case JL:		 return "JL";
	  case JLE:      return "JLE";
	  case NOP:      return "NOP";
	  case SHR:      return "SHR";
	  case SHL:      return "SHL";
	  case XOR:      return "XOR";
	  case AND:      return "AND";
	  case NOR:      return "NOR";
	  case NEG:      return "NEG";
	  case HLT:      return "HLT";
	  case CLF:      return "CLF";
	  case MOV_IMM:  return "MOV_IMM";
	  case ADD_IMM:  return "ADD_IMM";
	  case SUB_IMM:  return "SUB_IMM";
      case MUL_IMM:  return "MUL_IMM";
      case DIV_IMM:  return "DIV_IMM";
      case IMUL_IMM: return "IMUL_IMM";
      case IDIV_IMM: return "IDIV_IMM";
	  case MOV_REG:  return "MOV_REG";
	  case ADD_REG:  return "ADD_REG";
	  case SUB_REG:  return "SUB_REG";
	  case MUL_REG:  return "MUL_REG";
	  case DIV_REG:  return "DIV_REG";
	  case IMUL_REG: return "IMUL_REG";
	  case IDIV_REG: return "IDIV_REG";
	  case PUSH_REG: return "PUSH_REG";
	  case PUSH_IMM: return "PUSH_IMM";
	  case POP_REG:  return "POP_REG";
	  case CMP_IMM:  return "CMP_IMM";
	  case DUMP_STACK:  return "DUMP_STACK";
	  case DUMP_CPU_INFO: return "DUMP_CPU_INFO";

	  // Floating point instructions:
	  case MOVSS_IMM:  return "MOVSS_IMM";
	  case ADDSS_IMM:  return "ADDSS_IMM";
	  case SUBSS_IMM:  return "SUBSS_IMM";
	  case MULSS_IMM:  return "MULSS_IMM";
	  case DIVSS_IMM:  return "DIVSS_IMM";
	  case IMULSS_IMM: return "IMULSS_IMM";
	  case IDIVSS_IMM: return "IDIVSS_IMM";
	  case PUSHF_IMM:  return "PUSHF_IMM";
	  case MOVSS_REG:  return "MOVSS_REG";
	  case ADDSS_REG:  return "ADDSS_REG";
	  case SUBSS_REG:  return "SUBSS_REG";
	  case MULSS_REG:  return "MULSS_REG";
	  case DIVSS_REG:  return "DIVSS_REG";
	  case IMULSS_REG: return "IMISS_REG";
	  case IDIVSS_REG: return "IDIVSS_REG";
	  case FPOP_REG:   return "FPOP_REG";
	  case FCMP:       return "FCMP";
	  case FCMP_IMM:   return "FCMP_IMM";
	  case FJNE:       return "FJNE";
	  case FJIE:       return "FJIE";
	  case FJGE:       return "FJGE";
	  case FJG:        return "FJG";
	  case FJL:        return "FJL";
	  case FJLE:       return "FJLE";
	  default: return "Why?";
	}
}

// Garbage collection:
void destroy_cpu(cpu_t *cpu)
{
	free(cpu->stack);
 	free(cpu);
}

