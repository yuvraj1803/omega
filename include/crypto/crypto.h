/*
 *
 * Copyright (c) 2024 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */

#ifndef __CRYPTO_H__
#define __CRYPTO_H__

#include <stdint.h>

void crypto_init();
uint64_t get_id_aa64isar0_el1();
int crypto_check_sha1_support();
int crypto_check_sha2_support();
int crypto_check_aes_support();


#endif