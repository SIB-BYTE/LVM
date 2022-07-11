#include "../../../includes/vcpu.h"

int main(void)
{
	qword instructions[] = {
		MOV_IMM, 10, LA,
		IMUL_IMM, 2,

		DUMP_CPU_INFO,
		HLT
	};

	cpu_t *cpu = new_cpu(instructions, LENGTH(instructions), 0);
	run_cpu(cpu);
	destroy_cpu(cpu);
}

