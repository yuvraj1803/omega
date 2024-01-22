/*
 *
 * Copyright (c) 2023 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */


#include "monitor/exceptions.h"


.macro monitor_entry
		
.endm

.macro monitor_exit
		
.endm


.macro handle_unsupported_interrupt interrupt_type
	monitor_entry
	mov x0, #\interrupt_type
	mrs x1, esr_el3
	mrs x2, elr_el3
	mrs x3, far_el3
	bl log_unsupported_exception
	b halt 
.endm

.macro handle_sync_interrupt
	monitor_entry
	
	monitor_exit
.endm

.macro ventry handler
.align 7
b \handler
.endm


.align 11
.globl vtable
vtable:
	ventry current_el_sp0_sync
	ventry current_el_sp0_irq
	ventry current_el_sp0_fiq
	ventry current_el_sp0_serror

	ventry current_el_spx_sync
	ventry current_el_spx_irq
	ventry current_el_spx_fiq
	ventry current_el_spx_serror

	ventry lower_el_a64_sync
	ventry lower_el_a64_irq
	ventry lower_el_a64_fiq
	ventry lower_el_a64_serror
	
	ventry lower_el_a32_sync
	ventry lower_el_a32_irq
	ventry lower_el_a32_fiq
	ventry lower_el_a32_serror

 current_el_sp0_sync:
 	handle_unsupported_interrupt CURRENT_EL_SP0_SYNC 	
 current_el_sp0_irq:
  	handle_unsupported_interrupt CURRENT_EL_SP0_IRQ
 current_el_sp0_fiq:
  	handle_unsupported_interrupt CURRENT_EL_SP0_FIQ
 current_el_sp0_serror:
  	handle_unsupported_interrupt CURRENT_EL_SP0_SERROR

 current_el_spx_sync:
  	handle_unsupported_interrupt CURRENT_EL_SPX_SYNC
 current_el_spx_irq:
  	handle_unsupported_interrupt CURRENT_EL_SPX_IRQ
 current_el_spx_fiq:
  	handle_unsupported_interrupt CURRENT_EL_SPX_FIQ
 current_el_spx_serror:
  	handle_unsupported_interrupt CURRENT_EL_SPX_SERROR

 lower_el_a64_sync:
  	handle_sync_interrupt 
 lower_el_a64_irq:
  	handle_unsupported_interrupt LOWER_EL_A64_IRQ
 lower_el_a64_fiq:
  	handle_unsupported_interrupt LOWER_EL_A64_FIQ
 lower_el_a64_serror:
  	handle_unsupported_interrupt LOWER_EL_A64_SERROR

 lower_el_a32_sync:
  	handle_unsupported_interrupt LOWER_EL_A32_SYNC
 lower_el_a32_irq:
  	handle_unsupported_interrupt LOWER_EL_A32_IRQ
 lower_el_a32_fiq:
  	handle_unsupported_interrupt LOWER_EL_A32_FIQ
 lower_el_a32_serror:
  	handle_unsupported_interrupt LOWER_EL_A32_SERROR








