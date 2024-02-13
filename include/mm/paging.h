
/*
 *
 * Copyright (c) 2024 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */

#ifndef __PAGING_H__
#define __PAGING_H__

#include <stdint.h>

uint64_t get_vttbr_el2();
uint64_t paging_va_to_pa(uint64_t va);

#endif