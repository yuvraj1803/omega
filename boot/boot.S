/*
 *
 * Copyright (c) 2024 Yuvraj Sakshith <ysakshith@gmail.com>
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

	// from this point onwards WXN is turned on. so cheeky tricks like the one we did in "go_to_el3" WONT WORK FROM HERE!

	// we need to be on the primary CPU on bootup. we check this.
	// if the check fails, we halt.

	bl cpu_check

	// we initialise bss section to zero.
	bl bss_init

	// initialise the stack pointer for EL3.
	bl sp_init	

	b monitor_main
	
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

sp_init:
	ldr x0, =__omega_start
	mov sp, x0
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

/*

	:BAD SITUATION:

	Raspberry Pi-3B has an armstub8.bin that is placed at 0x0 and runs at
	 reset.

	This puts the system at EL2 at jumps to 0x80000(where we place _start).

	While emulating with QEMU, I was not able to find a way to override this armstub8.bin.

	So while at EL2, we cannot modify VBAR_EL3, which is essential to jump back to EL3.

	The reset value of VBAR_EL3 is 0x0, hence all SMC calls from EL2 jump to 0X400.

	:INTERESTING PART:

	So I placed the value 0xd61f0020 at address 0x0. This is the "br x1" instruction in little-endian format.

	So we load x1 with the address of el3_init and jump to 0x400 with "smc 0".

	AND 0x400 has value that translates too "br x1" which is nothing but a jump to "el3_init".

	NOW WE ARE FINALLY IN EL3!!!

 */

	adr x1, el3_init
	ldr x2, =0xd61f0020
	ldr x3, =0x400
	str x2, [x3]
	smc 0

	ret

el3_init:
	// now that we are in EL3, we need to initialise it before hopping into monitor_main().
	
	ldr x0, =EL3_SCR
	msr scr_el3, x0
	ret

cpu_check:
	mrs x0, mpidr_el1
	and x0, x0, 0b11
	cbnz x0, halt
	ret


halt:
	wfe
	b halt 
