/*
 *
 * Copyright (c) 2024 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */


#ifndef __uart_h__
#define __uart_h__

#include <stdint.h>

void uart_init();
void uart_tx(char ch);
char uart_rx();
void uart_write(char* str);
void uart_write_hex(unsigned long long x);
void uart_write_size(char* str, uint64_t size);

#endif
