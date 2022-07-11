#include "../../../includes/vcpu.h"

int main(void)
{
	qword instructions[] = {
		ADD_IMM, 10, LA,
		ADD_IMM, 20, LD,
		ADD_IMM, 30, LC,
		ADD_IMM, 40, LS,
		ADD_IMM, 50, LB,

		DUMP_CPU_INFO,
		HLT
	};

	cpu_t *cpu = new_cpu(instructions, LENGTH(instructions), 0);
	run_cpu(cpu);
	destroy_cpu(cpu);
}

