/*
 *
 * Copyright (c) 2023 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */


#ifndef __config_h__
#define __config_h__

#define BIT(x)                          ((1U << x))

#define EL3_SCTLR_M                     BIT(0)
#define EL3_SCTLR_WXN                   BIT(19)

// #define DEBUG

#define EL3_SCTLR_NO_MMU                EL3_SCTLR_WXN                
#define EL3_SCTLR_WITH_MMU              EL3_SCTLR_NO_MMU | EL3_SCTLR_M

#endif
