/*
 *
 * Copyright (c) 2024 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */

#include "ocom/ocom.h"
#include "mm/paging.h" 
#include "mm/mm.h"
#include "memory.h"
#include "stdio.h"

// the monitor will take the mapping of key and place the page in the destination virtual address provided.
int ocom_load_page(uint64_t key, uint64_t dest_virt){

    uint64_t dest_phys = paging_va_to_pa(dest_virt); // this is the physical address of the page which the VM provided us.
    uint8_t data_plain[PAGE_SIZE];
    
    if(dest_phys == 0){
        printf("Invalid page provided. Does not exist in IPA.\n");
        return -1;
    }


    

    return 0;
}


// the monitor will take the contents from the virtual address provided of the page.
// this contents will be store in the NAS.
int ocom_store_page(uint64_t key, uint64_t src_virt){

    return 0;   
}