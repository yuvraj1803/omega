/*
 *
 * Copyright (c) 2023 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */


#include "config.h"

.section ".text.boot"

.globl _start
.globl halt

_start:

	// first we need to make sure we are in EL3.
	// raspi3b boots up in EL3, but qemu starts in EL2.
	bl go_to_el3

	bl disable_mmu

	// we need to be on the primary CPU on bootup. we check this.
	// if the check fails, we halt.

	bl cpu_check

	// we initialise bss section to zero.

	bl bss_init

    b halt

bss_init:	
	ldr x0, =__bss_start
	ldr x1, =__bss_end
	ldr x2, =0

1:	str x2, [x0]
	add x0, x0, 1
	cmp x0, x1
	ble 1b
	ret

go_to_el3:
	mrs x0, currentel
	lsr x0, x0, 2

	cmp x0,2 
	beq el2_to_el3

// if we are in EL0 or EL1, we just halt.
	cmp x0, 1
	beq halt

	cmp x0, 0
	beq halt

	// if we are already in EL3, we reach this point. so from here we just go to el3_init
	bl el3_init

	ret

el2_to_el3:
	ret

el3_init:
	// now that we are in EL3, we need to initialise it before hopping into monitor_main().

	ret

cpu_check:
	mrs x0, mpidr_el1
	and x0, x0, 0b11
	cbnz x0, halt
	ret


halt:
	wfe
	b halt 
	
