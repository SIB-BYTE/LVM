#include "../../includes/vcpu.h"
#include "../../includes/stack.h"

// Stack insertion functions:
void push(cpu_t *cpu, qword value)
{
	if(cpu->stack_capacity == cpu->stack_length)
	{
		cpu->stack_capacity *= 2;
		cpu->integer_stack = realloc(cpu->integer_stack, cpu->stack_capacity);
	}

	cpu->sp++;
	cpu->integer_stack[cpu->sp] = value;
	cpu->stack_length++;
}

void fp_push(cpu_t *cpu, f64 value)
{
	if(cpu->fp_stack_length == cpu->fp_stack_capacity)
	{
		cpu->fp_stack_capacity *= 2;
		cpu->fp_stack = realloc(cpu->fp_stack, cpu->fp_stack_capacity);
	}

	cpu->fp_sp++;
	cpu->fp_stack[cpu->fp_sp] = value;
	cpu->fp_stack_length++;
}

// Stack deletion functions:
void pop(cpu_t *cpu)
{
	if(cpu->sp < 0)
		cpu->sp--;
}

void fp_pop(cpu_t *cpu)
{
	if(cpu->fp_sp < 0)
		cpu->fp_sp--;
}

// Stack misc functions:
void dump_stack(cpu_t *cpu)
{
	for(int i = 0; i < cpu->stack_length; ++i)
		printf("%sStack[%d] => {%lu}\n", WHI, i, cpu->integer_stack[i]);

	for(int i = 0; i < cpu->fp_stack_length; ++i)
		printf("%sFP_stack[%d] => {%lf}\n", WHI, i, cpu->fp_stack[i]);
}

qword peek(cpu_t *cpu)
{
	if(cpu->sp != -1)
		return (cpu->integer_stack[cpu->sp]);

	return (-1);
}

f64 fp_peek(cpu_t *cpu)
{
	if(cpu->sp != -1)
		return (cpu->fp_stack[cpu->fp_sp]);

	return (-1);
}

