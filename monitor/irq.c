/*
 *
 * Copyright (c) 2024 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */


#include "monitor/irq.h"
#include "mm/mm.h"
#include <stdint.h>
#include "stdio.h"
#include "drivers/uart.h"

const char* exception_info[] = {
	"CURRENT_EL_SP0_SYNC",
	"CURRENT_EL_SP0_IRQ",
	"CURRENT_EL_SP0_FIQ",
	"CURRENT_EL_SP0_SERROR",
	
	"CURRENT_EL_SPX_SYNC",
	"CURRENT_EL_SPX_IRQ",
	"CURRENT_EL_SPX_FIQ",
	"CURRENT_EL_SPX_SERROR",
	
	"LOWER_EL_A64_SYNC",
	"LOWER_EL_A64_IRQ",
	"LOWER_EL_A64_FIQ",
	"LOWER_EL_A64_SERROR",
	
	"LOWER_EL_A32_SYNC",
	"LOWER_EL_A32_IRQ",
	"LOWER_EL_A32_FIQ",
	"LOWER_EL_A32_SERROR"
};

void log_unsupported_exception(uint64_t exception_type,
			       uint64_t esr_el3,
			       uint64_t elr_el3,
			       uint64_t far_el3){

	printf("[UNCAUGHT EXCEPTION] : %s [ESR_EL3] : %x [ELR_EL3] : %x [FAR_EL3] : %x\n", exception_info[exception_type], esr_el3, elr_el3, far_el3);
}