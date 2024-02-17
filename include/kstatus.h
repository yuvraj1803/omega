/*
 *
 * Copyright (c) 2024 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */

#ifndef __KSTATUS_H__
#define __KSTATUS_H__

enum ERRORS{

    SUCCESS = 0,

    ERR_INVARG,

    ERR_MALLOC_FAIL,

    ERR_BL33_IMAGE_LOAD_FAIL,
    ERR_INV_EL2_ENTRY,

    ERR_OCOM_LOAD_FAILED,
    ERR_OCOM_STORE_FAILED

};

#endif

