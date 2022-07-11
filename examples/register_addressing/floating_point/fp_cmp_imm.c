#include "../../../includes/vcpu.h"

int main(void)
{
	qword instructions[] = {
		MOVSS_IMM, 1.0, X0,
		FCMP_IMM, 1.0, X0,

		DUMP_CPU_INFO,
		HLT
	};

	cpu_t *cpu = new_cpu(instructions, LENGTH(instructions), 0);
	run_cpu(cpu);

	destroy_cpu(cpu);
}

