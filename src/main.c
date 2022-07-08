#include "../../includes/vcpu.h"

int main(void)
{
	qword instructions[] = {
		INC, LA,
		CMP_IMM, 10, LA,
		JNE, 0,

		DUMP_CPU_INFO,
		HLT
	};

	cpu_t *cpu = new_cpu(instructions, LENGTH(instructions), 15);
	run_cpu(cpu);
	destroy_cpu(cpu);
}

