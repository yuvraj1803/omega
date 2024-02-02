/*
 *
 * Copyright (c) 2024 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */

#include "monitor/irq.h"
#include "mm/mm.h"
#include "drivers/uart.h"
#include "drivers/sd.h"
#include "stdio.h"
#include "fs/ff.h"
#include "config.h"
#include "monitor/bl33_loader.h"
#include "monitor/context.h"

int monitor_main(){

	__disable_irq();

	uart_init();
	fs_init();
	irq_init();
	
	// kernel8.img is the compiled binary of the deltaV hypervisor.
	// deltaV is compiled with entry at BL33_BASE while building itself. check makefile and OMEGA env variable.
	bl33_loader_load_image("/kernel8.img", BL33_BASE);	
	context_switch_to_el2(BL33_BASE);

	while(1);
}