#ifndef __PT_REGS_H__
#define __PT_REGS_H__

#include <stdint.h>

struct pt_regs{
	uint64_t regs[31];
	uint64_t sp;
	uint64_t pc;
	uint64_t pstate;
};

#endif