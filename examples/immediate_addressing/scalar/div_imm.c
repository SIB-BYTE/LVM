#include "../../../includes/vcpu.h"

int main(void)
{
	qword instructions[] = {
		MOV_IMM, 20, LA,
		DIV_IMM, 10, LA,

		DUMP_CPU_INFO,
		HLT
	};

	cpu_t *cpu = new_cpu(instructions, LENGTH(instructions), 0);
	run_cpu(cpu);

	destroy_cpu(cpu);
}

