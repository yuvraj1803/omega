/*
 *
 * Copyright (c) 2024 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */


#include "monitor/sync.h"
#include "stdio.h"
#include "kstatus.h"
#include "debug/debug.h"
#include <stdint.h>
#include "monitor/pt_regs.h"
#include "ocom/ocom.h"

const char *sync_info[] = {
	"Unknown reason.",
	"Trapped WFI or WFE instruction execution.",
	"(unknown)",
	"Trapped MCR or MRC access with (coproc==0b1111).",
	"Trapped MCRR or MRRC access with (coproc==0b1111).",
	"Trapped MCR or MRC access with (coproc==0b1110).",
	"Trapped LDC or STC access.",
	"Access to SVE, Advanced SIMD, or floating-point functionality trapped by CPACR_EL1.FPEN, CPTR_EL3.FPEN, CPTR_EL3.TFP, or CPTR_EL3.TFP control.",
	"Trapped VMRS access, from ID group trap.",
	"Trapped use of a Pointer authentication instruction because HCR_EL3.API == 0 || SCR_EL3.API == 0.",
	"(unknown)",
	"(unknown)",
	"Trapped MRRC access with (coproc==0b1110).",
	"Branch Target Exception.",
	"Illegal Execution state.",
	"(unknown)",
	"(unknown)",
	"SVC instruction execution in AArch32 state.",
	"HVC instruction execution in AArch32 state.",
	"SMC instruction execution in AArch32 state.",
	"(unknown)",
	"SVC instruction execution in AArch64 state.",
	"HVC instruction execution in AArch64 state.",
	"SMC instruction execution in AArch64 state.",
	"Trapped MSR, MRS or System instruction execution in AArch64 state.",
	"Access to SVE functionality trapped as a result of CPACR_EL1.ZEN, CPTR_EL3.ZEN, CPTR_EL3.TZ, or CPTR_EL3.EZ.",
	"Trapped ERET, ERETAA, or ERETAB instruction execution.",
	"(unknown)",
	"Exception from a Pointer Authentication instruction authentication failure.",
	"(unknown)",
	"(unknown)",
	"(unknown)",
	"Instruction Abort from a lower Exception level.",
	"Instruction Abort taken without a change in Exception level.",
	"PC alignment fault exception.",
	"(unknown)",
	"Data Abort from a lower Exception level.",
	"Data Abort without a change in Exception level, or Data Aborts taken to EL3 as a result of accesses generated associated with VNCR_EL3 as part of nested virtualization support.",
	"SP alignment fault exception.",
	"(unknown)",
	"Trapped floating-point exception taken from AArch32 state.",
	"(unknown)",
	"(unknown)",
	"(unknown)",
	"Trapped floating-point exception taken from AArch64 state.",
	"(unknown)",
	"(unknown)",
	"SError interrupt.",
	"Breakpoint exception from a lower Exception level.",
	"Breakpoint exception taken without a change in Exception level.",
	"Software Step exception from a lower Exception level.",
	"Software Step exception taken without a change in Exception level.",
	"Watchpoint from a lower Exception level.",
	"Watchpoint exceptions without a change in Exception level, or Watchpoint exceptions taken to EL3 as a result of accesses generated associated with VNCR_EL3 as part of nested virtualization support.",
	"(unknown)",
	"(unknown)",
	"BKPT instruction execution in AArch32 state.",
	"(unknown)",
	"Vector Catch exception from AArch32 state.",
	"(unknown)",
	"BRK instruction execution in AArch64 state.",
};

#define ESR_EC_SHIFT 			26
#define ESR_EC_SMC_AA64_MASK 	0b010111

extern void halt();

uint8_t get_exception_class(uint64_t esr_el3){
    return (esr_el3 >> ESR_EC_SHIFT) & 0b111111;
}

void handle_sync(uint64_t esr_el3, uint64_t elr_el3, uint64_t far_el3, 	uint64_t smc_number, 
																	   	uint64_t smc_arg0,
																		uint64_t smc_arg1,
																		uint64_t pt_regs_base){

// smc_number = the SMC function id called from the lower aarch64 exception level.
// smc_arg0 is the value of the hash index according to the ocom specification
// smc_arg1 is the page aligned address of the page to be put in isolated storage. This adderss is in the VM's IPA
// pt_regs_base is the address of the saved context in the interrupt stack.


    uint8_t EC = get_exception_class(esr_el3);

	struct pt_regs* regs = (struct pt_regs*) pt_regs_base;

    switch(EC){	
		
		// sync came from aa64 smc 
		case ESR_EC_SMC_AA64_MASK:	
			int ret;

			if(smc_number == OCOM_STORE_SMC_NR) ret = ocom_store_page(smc_arg0, smc_arg1);
			if(smc_number == OCOM_LOAD_SMC_NR)	ret = ocom_load_page (smc_arg0, smc_arg1);

			 regs->regs[0] = ret;	// regs[0] is nothing but the first register in the pt_regs structure which is X0 reg placeholder.
							// this value will be put back to the actual X0 register when interrupt context is restore while 
							// jumping back to the virtual machine.

			break;

        default:
            debug("[OMEGA]: Unsupported sync exception occurred => INFO: %s ESR: %x ELR: %x FAR: %x\n", sync_info[EC], esr_el3, elr_el3, far_el3);
            halt();
            break;
    }

}
