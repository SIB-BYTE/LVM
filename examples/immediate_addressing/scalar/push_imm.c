#include "../../../includes/vcpu.h"

int main(void)
{
	qword instructions[] = {
		PUSH_IMM, 10,
		PUSH_IMM, 20,
		PUSH_IMM, 30,
		PUSH_IMM, 40,
		PUSH_IMM, 50,

		DUMP_STACK,
		HLT
	};

	cpu_t *cpu = new_cpu(instructions, LENGTH(instructions), 5);
	run_cpu(cpu);
	destroy_cpu(cpu);
}

