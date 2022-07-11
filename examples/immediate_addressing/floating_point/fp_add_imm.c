#include "../../../includes/vcpu.h"

int main(void)
{
	qword instructions[] = {
		ADDSS_IMM, 1.0, X0,
		ADDSS_IMM, 2.0, X1,
		ADDSS_IMM, 3.0, X2,
		ADDSS_IMM, 4.0, X3,
		ADDSS_IMM, 5.0, X4,

		DUMP_CPU_INFO,
		HLT
	};

	cpu_t *cpu = new_cpu(instructions, LENGTH(instructions), 0);
	run_cpu(cpu);
	destroy_cpu(cpu);
}

