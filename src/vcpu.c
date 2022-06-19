#include "../includes/vcpu.h"

cpu_t *new_cpu(dword *instructions, dword instruction_length, dword stack_size)
{
	cpu_t *cpu = calloc(1, sizeof(cpu_t));

	cpu->instruction_length = instruction_length;
	cpu->instructions = malloc(cpu->instruction_length);
	cpu->instructions = instructions;

	cpu->stack = calloc(stack_size, sizeof(dword));
	cpu->sp = -1;
	cpu->bp = cpu->sp;

	return (cpu);
}

void run_cpu(cpu_t *cpu)
{
	while(cpu->current_instruction != HLT)
	{
		execute(cpu);
		cpu->ip++;
	}
}

void execute(cpu_t *cpu)
{
	cpu->current_instruction = cpu->instructions[cpu->ip];
	dword opcode = cpu->current_instruction;

	cpu->src = cpu->instructions[cpu->ip + 1];
	cpu->dst = cpu->instructions[cpu->ip + 2];

	dword src = cpu->src, dst = cpu->dst;
	dword return_address = 0;

#ifdef DEBUG
	printf("%sCurrent instruction -> {%s}\nCurrent source -> {%d}\nCurrent destination -> {%d}\n\n", BLU, bind_name(cpu->current_instruction), src, dst);
	printf("Instruction pointer -> %d\n", cpu->ip);
#endif

	switch(opcode)
	{
		// Immedate addressing instructions:
		case MOV_IMM:  cpu->registers[dst] =  src; cpu->ip += 2;	  break;
		case ADD_IMM:  cpu->registers[dst] += src; cpu->ip += 2;      break;
		case SUB_IMM:  cpu->registers[dst] -= src; cpu->ip += 2;      break;
		case MUL_IMM:  cpu->registers[dst] *= src; cpu->ip += 2;      break;
		case DIV_IMM:  cpu->registers[dst] /= src; cpu->ip += 2;      break;
		case IMUL_IMM: cpu->registers[LA] *= (signed) dst; cpu->ip++; break;
		case IDIV_IMM: cpu->registers[LA] /= (signed) dst; cpu->ip++; break;

		// Control flow instructions:
		case JMP:  cpu->ip = src; break;
		case CALL: push(cpu, cpu->ip); cpu->ip = cpu->registers[src];   cpu->ip++; break;
		case RET:  return_address = pop(cpu); cpu->ip = return_address; cpu->ip++; break;
		case CMP_IMM:  set_flags(cpu, src, cpu->registers[dst]); cpu->ip += 2;     break;
		case CMP:      set_flags(cpu, cpu->registers[src], cpu->registers[dst]); cpu->ip += 2; break;
		case JNE:
					if(cpu->registers[src] != cpu->registers[dst]) { cpu->ip = src; }
					else { cpu->ip++; }
					cpu->ip += 2; break;

		case JNZ:
				   if(!cpu->zf) { cpu->ip = src; }
				   else { cpu->ip++; }
				   cpu->ip += 2; break;

		case JIE:
				   if(cpu->registers[src] == cpu->registers[dst]) { cpu->ip = src; }
				   else { cpu->ip++; }
				   cpu->ip += 2; break;

		case JG:
				   if(cpu->gf) { cpu->ip = src; }
				   else { cpu->ip++; }
				   cpu->ip += 2; break;
		case JL:
					if(cpu->lf) { cpu->ip = src; }
					else { cpu->ip++; }
					cpu->ip += 2; break;

		case JLE:  break;

		case JGE:  break;

		// Misc:
		case NEG: cpu->registers[src] =  -(cpu->registers[src]); cpu->ip++;     break;
		case INC: cpu->registers[src]++; cpu->ip++; break;
		case DEC: cpu->registers[src]--; cpu->ip++; break;
		case SUF: /* Figure out how to do this */ ; break;
		case DSF: /* Figure out how to do this */ ; break;
		case NOP: cpu->ip++; break;
		case PUSH_IMM: push(cpu, src); cpu->ip++;      break;
		case PUSH_REG: push(cpu, cpu->registers[src]); cpu->ip++;break;
		case HLT: break;

		// Bit-wise operation instructions:
		case SHR: cpu->registers[dst] >>= cpu->registers[src];   cpu->ip += 2;  break;
		case SHL: cpu->registers[dst] <<= cpu->registers[src];   cpu->ip += 2;  break;
		case XOR: cpu->registers[dst] ^=  cpu->registers[src];   cpu->ip += 2;  break;
		case AND: cpu->registers[dst] &=  cpu->registers[src];   cpu->ip += 2;  break;
		case NOR: cpu->registers[dst] =  ~(cpu->registers[src]); cpu->ip++;     break;

		// Register-based addressing mode instructions:
		case MOV_REG:  cpu->registers[dst] =  cpu->registers[src]; cpu->ip += 2; break;
		case ADD_REG:  cpu->registers[dst] += cpu->registers[src]; cpu->ip += 2; break;
		case SUB_REG:  cpu->registers[dst] -= cpu->registers[src]; cpu->ip += 2; break;
		case MUL_REG:  cpu->registers[dst] *= cpu->registers[src]; cpu->ip += 2; break;
		case IMUL_REG: cpu->registers[LA]  *= (signed) cpu->registers[dst]; cpu->ip += 2; break;
		case IDIV_REG: cpu->registers[LA]  /= (signed) cpu->registers[dst]; cpu->ip += 2; break;

		// Floating point immedate instructions:
		case MOVSS_IMM:  cpu->floating_registers[dst] =  (f64) src; cpu->ip += 2; break;
		case ADDSS_IMM:  cpu->floating_registers[dst] += (f64) src; cpu->ip += 2; break;
		case SUBSS_IMM:  cpu->floating_registers[dst] -= (f64) src; cpu->ip += 2; break;
		case MULSS_IMM:  cpu->floating_registers[dst] *= (f64) src; cpu->ip += 2; break;
		case DIVSS_IMM:  cpu->floating_registers[dst] /= (f64) src; cpu->ip += 2; break;
		case IMULSS_IMM: cpu->floating_registers[dst] *= (signed) (f64) src; cpu->ip += 2; break;
		case IDIVSS_IMM: cpu->floating_registers[dst] /= (signed) (f64) src; cpu->ip += 2; break;

		// Floating point control flow instructions:
		case FCMP_IMM: fset_flags(src, (f64) src, cpu->floating_registers[dst]); cpu->ip += 2; break;

		// Invalid operation:
		default: puts("Invalid opcode / instruction monkey!"); return;
	}
}

void dump_cpu_info(cpu_t *cpu)
{
	// GRP's & FPR's. Sorta hard to read, but it just prints everything:
	printf("%sLA -> {%d}\nLD -> {%d}\nLC -> {%d}\nLS -> {%d}\nLB -> {%d}\n%sX0 -> {%lf}\nX1 -> {%lf}\nX2 -> {%lf}\nX3 -> {%lf}\nX4 -> {%lf}\n"
			,RED, cpu->registers[LA], cpu->registers[LD], cpu->registers[LC], cpu->registers[LS], cpu->registers[LB],
			BLU, cpu->floating_registers[X0], cpu->floating_registers[X1], cpu->floating_registers[X2], cpu->floating_registers[X3], cpu->floating_registers[X4]);

	// Prints flag status.
	printf("%slf -> {%d}\ngf -> {%d}\nzf -> {%d}\n", PUR, cpu->lf, cpu->gf, cpu->zf);
}

void destroy_cpu(cpu_t *cpu)
{
	free(cpu->instructions);
	free(cpu->stack);
 	free(cpu);
}

#ifdef DEBUG
const char *bind_name(dword instruction)
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
	  case JNE:      return "JNE";
	  case JIE:      return "JIE";
	  case JNZ:      return "JNZ";
	  case JGE:      return "JGE";
	  case JG:		   return "JG";
	  case JL:		   return "JL";
	  case JLE:      return "JLE";
	  case NOP:      return "NOP";
	  case SHR:      return "SHR";
	  case SHL:      return "SHL";
	  case XOR:      return "XOR";
	  case AND:      return "AND";
	  case NOR:      return "NOR";
	  case NEG:      return "NEG";
	  case HLT:      return "HLT";
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
	  case POP_REG:  return "POP_REG";
	  case MOV_MEM:  return "MOV_MEM";
	  case CMP_IMM:  return "CMP_IMM";

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
#endif

