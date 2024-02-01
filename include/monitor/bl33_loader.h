/*
 *
 * Copyright (c) 2024 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */

#ifndef __BL33_LOADER__
#define __BL33_LOADER__

#include <stdint.h>

int8_t bl33_loader_load_image(char* image_path, uint64_t bl33_load_address);

#endif
