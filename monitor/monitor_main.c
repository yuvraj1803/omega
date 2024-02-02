/*
 *
 * Copyright (c) 2023 Yuvraj Sakshith <ysakshith@gmail.com>
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

int monitor_main(){

	__disable_irq();

	uart_init();
	fs_init();
	irq_init();
	
	bl33_loader_load_image("/kernel8.img", BL33_BASE);
	

	// printf("hello world");

	while(1);
}