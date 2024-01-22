/*
 *
 * Copyright (c) 2023 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */

#include "monitor/irq.h"
#include "drivers/uart.h"
#include "stdio.h"

int monitor_main(){

	__disable_irq();

	uart_init();

	while(1);
}