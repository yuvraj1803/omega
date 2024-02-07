/*
 *
 * Copyright (c) 2024 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */

#ifndef __OCOM_H__
#define __OCOM_H__

#define OCOM_STORE_SMC_NR   0
#define OCOM_LOAD_SMC_NR    1

#include <stdint.h>

int ocom_load_page(uint64_t key, uint64_t dest_virt);
int ocom_store_page(uint64_t key, uint64_t src_virt);


#endif