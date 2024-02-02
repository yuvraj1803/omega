/*
 *
 * Copyright (c) 2024 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 * This file includes subroutines responsible for switching context between the monitor
 * and EL2 or EL1 when required.
 
 */

#include "monitor/context.h"
#include "kstatus.h"
#include <stdint.h>
#include "stdio.h"

struct context monitor_context;

int8_t context_switch_to_el2(uint64_t entry){


    // we check if the provided entry address is within physical memory bounds
    // raspberry pi 3b has 1GB of RAM.
    if(entry < 0 || entry >= 0x40000000) return -ERR_INV_EL2_ENTRY;

    // this is a function defined in context.S (assembly)
    log("Entering BL33.");
    __context_switch_to_el2(&monitor_context, entry); 


    // we never reach this point actually, we eret from __context_switch_to_el2()
    return SUCCESS;

}
