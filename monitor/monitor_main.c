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

int monitor_main(){

	__disable_irq();

	uart_init();
	sd_init();


	printf("hello world");

	while(1);
}