/*
 *
 * Copyright (c) 2024 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */


#ifndef __config_h__
#define __config_h__

// #define DEBUG

#define BIT(x)                          ((1U << x))
#define BL33_BASE                       0x1000000

#define EL3_SCTLR_M                     BIT(0)
#define EL3_SCTLR_WXN                   BIT(19)
#define EL3_SCTLR_NO_MMU                EL3_SCTLR_WXN                
#define EL3_SCTLR_WITH_MMU              EL3_SCTLR_NO_MMU | EL3_SCTLR_M

#define EL3_SCR_NS                      BIT(0)
#define EL3_SCR_HCE                     BIT(8)
#define EL3_SCR_RW                      BIT(10)
#define EL3_SCR                         EL3_SCR_NS | EL3_SCR_HCE | EL3_SCR_RW

#define EL3_SPSR_DAIF_MASK              (BIT(9) | BIT(8) | BIT(7) | BIT(6))
#define EL3_SPSR_M_EL2h                 (0b1001)
#define EL3_SPSR_EL2h                   EL3_SPSR_DAIF_MASK | EL3_SPSR_M_EL2h

#endif
