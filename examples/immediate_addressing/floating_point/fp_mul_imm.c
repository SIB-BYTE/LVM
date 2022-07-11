#include "../../../includes/vcpu.h"

int main(void)
{
	qword instructions[] = {
		MOVSS_IMM, 1.0, X0,
		MOVSS_IMM, 2.0, X1,
		MOVSS_IMM, 3.0, X2,
		MOVSS_IMM, 4.0, X3,
		MOVSS_IMM, 5.0, X4,

		MULSS_IMM, 1.0, X0,
		MULSS_IMM, 2.0, X1,
		MULSS_IMM, 3.0, X2,
		MULSS_IMM, 4.0, X3,
		MULSS_IMM, 5.0, X4,

		DUMP_CPU_INFO,
		HLT
	};

	cpu_t *cpu = new_cpu(instructions, LENGTH(instructions), 0);
	run_cpu(cpu);
	destroy_cpu(cpu);
}


