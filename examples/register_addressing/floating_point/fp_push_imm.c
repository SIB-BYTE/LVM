#include "../../../includes/vcpu.h"

int main(void)
{
	qword instructions[] = {
		PUSHF_IMM, 1.0,
		PUSHF_IMM, 2.0,
		PUSHF_IMM, 3.0,
		PUSHF_IMM, 4.0,
		PUSHF_IMM, 5.0,

		DUMP_STACK,
		HLT
	};

	cpu_t *cpu = new_cpu(instructions, LENGTH(instructions), 5);
	run_cpu(cpu);
	destroy_cpu(cpu);
}

