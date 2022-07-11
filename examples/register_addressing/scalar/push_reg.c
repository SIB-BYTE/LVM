#include "../../../includes/vcpu.h"

int main(void)
{
	qword instructions[] = {
		MOV_IMM, 10, LA,
		PUSH_REG, LA,

		DUMP_STACK,
		DUMP_CPU_INFO,
		HLT
	};

	cpu_t *cpu = new_cpu(instructions, LENGTH(instructions), 5);
	run_cpu(cpu);
	destroy_cpu(cpu);
}

