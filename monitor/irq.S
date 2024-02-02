/*
 *
 * Copyright (c) 2024 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */

.globl __disable_irq
.globl __enable_irq
.globl irq_init

__disable_irq:
	msr daifset, #2
	ret

__enable_irq:
	msr daifclr, #2
	ret

irq_init:
	adr x0, vtable
	msr vbar_el3, x0
	ret