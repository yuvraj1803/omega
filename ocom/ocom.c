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
#include "string.h"
#include "stdlib.h"
#include "fs/ff.h"
#include "kstatus.h"

/*

All data of a particular VM is stored in /VM_x, where x is the VMID.

OCOM files are kept as /VM_x/OCOM_key where 'key' is the key provided by the VM in EL1.

Any conflicts with the key results in failure in storing thr data.

*/


#define MAKE_SANDBOX_ID(key, vmid)      char sandbox_id[128] = "/VM_";                      \
                                        strcat(sandbox_id, (char*) itoa((long long) vmid)); \
                                        strcat(sandbox_id, (char*) "/OCOM_");               \
                                        strcat(sandbox_id, (char*) itoa((long long) key));
                                        

static int ocom_store_page_in_sandbox(uint64_t key, uint16_t vmid, uint8_t data[]){
    
    MAKE_SANDBOX_ID(key, vmid)

    FIL file;

    if(f_open(&file, sandbox_id, FA_OPEN_ALWAYS | FA_WRITE) != FR_OK) return -ERR_OCOM_STORE_FAILED;

    unsigned int bytes_written;
    if(f_write(&file, data, PAGE_SIZE, &bytes_written) != FR_OK) return -ERR_OCOM_STORE_FAILED;

    if(bytes_written != PAGE_SIZE) return -ERR_OCOM_STORE_FAILED;

    f_close(&file);


    return SUCCESS;
}

static int ocom_load_page_from_sandbox(uint64_t key, uint16_t vmid, uint8_t data[]){

    MAKE_SANDBOX_ID(key, vmid)

    FIL file;

    if(f_open(&file, sandbox_id, FA_OPEN_ALWAYS | FA_READ) != FR_OK) return -ERR_OCOM_LOAD_FAILED;

    unsigned int bytes_read;
    if(f_read(&file, data, PAGE_SIZE, &bytes_read) != FR_OK){
        f_close(&file);
        return -ERR_OCOM_LOAD_FAILED;
    }

    if(bytes_read != PAGE_SIZE) {
        f_close(&file);
        return -ERR_OCOM_LOAD_FAILED;
    }

    f_close(&file);

    return SUCCESS;

}


// the monitor will take the mapping of key and place the page in the destination virtual address provided.
int ocom_load_page(uint64_t key, uint64_t dest_virt){

    uint64_t dest_phys = paging_va_to_pa(dest_virt); // this is the physical address of the page which the VM provided us.
    uint8_t data[PAGE_SIZE];
    uint16_t vmid = (get_vttbr_el2() & 0xffff000000000000) + 1;


    if(dest_phys == 0){
        printf("Invalid page provided. Does not exist in IPA.\n");
        return -ERR_OCOM_LOAD_FAILED;
    }

    if(ocom_load_page_from_sandbox(key, vmid, data) < 0){
        printf("ocom failed to retrieve page.\n");
        return -ERR_OCOM_LOAD_FAILED;
    }
    
    memcpy((uint64_t*) dest_phys, data, PAGE_SIZE);

    return SUCCESS;
}


// the monitor will take the contents from the virtual address provided of the page.
int ocom_store_page(uint64_t key, uint64_t src_virt){

    uint64_t src_phys = paging_va_to_pa(src_virt);  // physical address of the page provided.

    if(src_phys == 0){
        printf("Invalid page provided. Does not exist in IPA.\n");
        return -ERR_OCOM_STORE_FAILED;
    }

    uint8_t data[PAGE_SIZE]; // contents of the page provided.
    memcpy(data, (uint64_t*) src_phys, PAGE_SIZE);

    uint16_t vmid = (get_vttbr_el2() & 0xffff000000000000) + 1;   // VMID of the guest is stored in VTTBR_EL2 by the hypervisor.

    return ocom_store_page_in_sandbox(key, vmid, data);
}