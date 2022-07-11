#include "../../../includes/vcpu.h"

int main(void)
{
	qword instructions[] = {
		MOVSS_IMM, 10.00, X0,
		IDIVSS_IMM, 5.0,

		DUMP_CPU_INFO,
		HLT
	};

	cpu_t *cpu = new_cpu(instructions, LENGTH(instructions), 0);
	run_cpu(cpu);

	destroy_cpu(cpu);
}


