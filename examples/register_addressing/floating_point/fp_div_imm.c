#include "../../../includes/vcpu.h"

int main(void)
{
	qword instructions[] = {
		MOVSS_IMM, 10.00, X0,
		DIVSS_IMM, 2.0, X0,

		DUMP_CPU_INFO,
		HLT
	};

	cpu_t *cpu = new_cpu(instructions, LENGTH(instructions), 0);
	run_cpu(cpu);

	destroy_cpu(cpu);
}

