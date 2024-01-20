/*
 *
 * Copyright (c) 2023 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */


#ifndef __config_h__
#define __config_h__

#define BIT(x)  ((1U << x))

#define SCTLR_EL3_M     BIT(0)

// #define DEBUG

#define EL3_SCTLR_WITH_MMU              SCTLR_EL3_M
#define EL3_SCTLR_NO_MMU                0

#endif
