#ifndef STACK_H
#define STACK_H

#include "vcpu.h"

// Stack insertion functions:
void push(cpu_t *, qword);
void fp_push(cpu_t *, f64);

// Stack deletion functions:
void pop(cpu_t *);
void fp_pop(cpu_t *);

// Stack misc: functions:
qword peek(cpu_t *);
f64 fp_peek(cpu_t *);
void dump_stack(cpu_t *);

#endif

