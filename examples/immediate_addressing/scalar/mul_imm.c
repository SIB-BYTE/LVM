#include "../../../includes/vcpu.h"

int main(void)
{
	qword instructions[] = {
		MOV_IMM, 10, LA,
		MOV_IMM, 20, LD,
		MOV_IMM, 30, LC,
		MOV_IMM, 40, LS,
		MOV_IMM, 50, LB,

		MUL_IMM, 1, LA,
		MUL_IMM, 2, LD,
		MUL_IMM, 3, LC,
		MUL_IMM, 4, LS,
		MUL_IMM, 5, LB,

		DUMP_CPU_INFO,
		HLT
	};

	cpu_t *cpu = new_cpu(instructions, LENGTH(instructions), 0);
	run_cpu(cpu);
	destroy_cpu(cpu);
}


