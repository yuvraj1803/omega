/*
 *
 * Copyright (c) 2024 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */

#include "monitor/bl33_loader.h"
#include "fs/ff.h"
#include <stdint.h>
#include "kstatus.h"
#include "memory.h"
#include "stdio.h"

int8_t bl33_loader_load_image(char* image_path, uint64_t bl33_load_address){
    FIL bl33_image;

    if(f_open(&bl33_image,image_path, FA_READ)){
        return -ERR_BL33_IMAGE_LOAD_FAIL;
    }

    FILINFO bl33_image_info;
    f_stat(image_path, &bl33_image_info);


    // at this point in time, we cant load large BL33 images. Since we only deal with small images, we store it temporarily in the runtime stack.
    uint64_t bl33_image_size = bl33_image_info.fsize;

    f_read(&bl33_image, (void*)bl33_load_address, bl33_image_size, 0);
    f_close(&bl33_image);

    

    log("BL33 Image Loaded.");

    return SUCCESS;

}