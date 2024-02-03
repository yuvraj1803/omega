/*
 *
 * Copyright (c) 2024 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */

#include "crypto/crypto.h"
#include "stdio.h"

#define BIT(x)                          ((1U << x))
#define ID_AA64ISAR0_EL1_SHA2_MASK       BIT(12)
#define ID_AA64ISAR0_EL1_SHA1_MASK       BIT(8)
#define ID_AA64ISAR0_EL1_AES_MASK        BIT(5)


int crypto_check_sha2_support(){
    uint64_t id_aa64isar0_el1 = get_id_aa64isar0_el1();

    return id_aa64isar0_el1 & ID_AA64ISAR0_EL1_SHA2_MASK;
}

int crypto_check_sha1_support(){
    uint64_t id_aa64isar0_el1 = get_id_aa64isar0_el1();

    return id_aa64isar0_el1 & ID_AA64ISAR0_EL1_SHA1_MASK;
}

int crypto_check_aes_support(){
    uint64_t id_aa64isar0_el1 = get_id_aa64isar0_el1();

    return id_aa64isar0_el1 & ID_AA64ISAR0_EL1_AES_MASK;
}

void crypto_init(){

    if(crypto_check_sha1_support()) log("SHA1 Supported.");
    if(crypto_check_sha2_support()) log("SHA2 Supported.");
    if(crypto_check_aes_support())  log("AES Supported.");

    log("Crypto Module Initialised.");
}


