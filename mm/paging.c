/*
 *
 * Copyright (c) 2024 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */

#include "mm/paging.h"
#include "mm/mm.h"
#include <stdint.h>

#define LV1_SHIFT		30
#define LV2_SHIFT   	21
#define PAGE_SHIFT		12
#define TABLE_SHIFT		9
#define TABLE_ENTRIES	(1U << TABLE_SHIFT) 

uint64_t paging_va_to_pa(uint64_t va){
    uint64_t __vttbr_el2 = get_vttbr_el2();
    

    // the VMID is loaded in the most significant 16-bits of the VTTBR_EL2 by the hypervisor.
    // __vttbr_el2 is this value. but vttbr_el2 is the value without the VMID. This is important because we need the physical address of the page tables
    // of the IPA loaded by the hypervisor.
    uint64_t vttbr_el2 = __vttbr_el2 & 0x0000ffffffffffff;

    uint64_t ipa_page_offset = va & (PAGE_SIZE - 1);
	uint64_t ipa_page		 = va &~(PAGE_SIZE - 1);

	uint64_t lv1_table = vttbr_el2;	// 512 GB block
	
	uint64_t lv2_table = ((uint64_t*)lv1_table)[0] & ~(PAGE_SIZE - 1);				// 1 GB block
	uint64_t lv2_index = (ipa_page >> LV2_SHIFT) & (TABLE_ENTRIES - 1);

	uint64_t lv3_table = ((uint64_t*)lv2_table)[lv2_index] & ~(PAGE_SIZE - 1);
	uint64_t lv3_index = (ipa_page >> PAGE_SHIFT) & (TABLE_ENTRIES - 1);


	return (((uint64_t*)lv3_table)[lv3_index] & ~(PAGE_SIZE-1)) + ipa_page_offset;



}