/*
 *
 * Copyright (c) 2024 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */


#ifndef __SYNC_H__
#define __SYNC_H__

#include <stdint.h>

void handle_sync(uint64_t esr_el3, uint64_t elr_el3, uint64_t far_el3, uint64_t smc_number);

#endif