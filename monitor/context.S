/*
 *
 * Copyright (c) 2024 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */

#include "config.h"

.globl __context_switch_to_el2


__context_switch_to_el2: // (pointer to context structure, entry address of EL2.)
    // save the current context to the provided structure in x0.
    mov x2, sp
	stp x19, x20, [x0], #16
	stp x21, x22, [x0], #16
	stp x23, x24, [x0], #16
	stp x25, x26, [x0], #16
	stp x27, x28, [x0], #16
	stp x29, x2, [x0], #16
	str x30, [x0]
	
    msr elr_el3, x1
    ldr x1, =EL3_SPSR_EL2h
    msr spsr_el3, x1
    eret