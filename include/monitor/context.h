/*
 *
 * Copyright (c) 2024 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 * This file includes subroutines responsible for switching context between the monitor
 * and EL2 or EL1 when required.
 
 */

#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include <stdint.h>

struct context{
    uint64_t x19;
    uint64_t x20;
    uint64_t x21;
    uint64_t x22;
    uint64_t x23;
    uint64_t x24;
    uint64_t x25;
    uint64_t x26;
    uint64_t x27;
    uint64_t x28;
    uint64_t fp;
    uint64_t sp; 
    uint64_t pc;
};


int8_t context_switch_to_el2(uint64_t entry);
void __context_switch_to_el2(struct context* context, uint64_t entry);

#endif