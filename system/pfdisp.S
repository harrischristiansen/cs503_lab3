/* pfdisp.s - pfdisp */

/*------------------------------------------------------------------------
 * pfdisp  -  Interrupt dispatcher for page faults
 *------------------------------------------------------------------------
 */
#include <icu.s>
		.text
pferrcode: .long 0
		.globl	pfdisp,pferrcode	
pfdisp:
		cli						# 1. Clear all interrupts / disable further interupts
		popl pferrcode			# 2. Store error code in a global variable / 6. Remove error code from stack
		pushfl					# 3. Save all registers
		pushal
		
		call pfhandler			# 4. Call pfhandler to handle interrupt
		
		popal					# 5. Restore all registers
		popfl
		sti						# 7. Restore interrupt status
		iret					# 8. iret
