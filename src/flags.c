#include "../includes/vcpu.h"

void clear_flags(cpu_t *cpu)
{
	cpu->lf ^= cpu->lf;
    	cpu->zf ^= cpu->zf;
    	cpu->gf ^= cpu->gf;
}

void set_flags(cpu_t *cpu, long src, long dest)
{
	long status = (src - dest);

	cpu->zf = (status == 0);
	cpu->lf = (status < 0);
	cpu->gf = (status > 0);
}

void fset_flags(cpu_t *cpu, float src, float dest)
{
	float status = (src - dest);

	cpu->zf = (status == 0);
	cpu->lf = (status < 0);
	cpu->gf = (status > 0);
}

