/*
 *
 * Copyright (c) 2024 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */

#include "config.h"

.globl enable_mmu
.globl disable_mmu

enable_mmu:
        ldr x1, = EL3_SCTLR_WITH_MMU
        dsb ish
        isb
        msr sctlr_el3, x1        
        isb
	    ret

disable_mmu:
	ldr x1, =(EL3_SCTLR_NO_MMU)  
        dsb ish
        isb
        msr sctlr_el3, x1
        isb
	ret

get_vttbr_el2:
	mrs x0, vttbr_el2
	ret