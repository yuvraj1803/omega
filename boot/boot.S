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

    b halt

halt:
	wfe
	b halt 
	
