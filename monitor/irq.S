.globl __disable_irq
.globl __enable_irq

__disable_irq:
	msr daifset, #2
	ret

__enable_irq:
	msr daifclr, #2
	ret