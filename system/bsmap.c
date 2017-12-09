/* bsmap.c - Backing Store Map */

#include <xinu.h>

// --------------- Backing Store Map ---------------

syscall getStoreForVAddress(pid32 pid, char* vaddr, bsd_t* bsid, uint32* poffset)
{
	intmask mask = disable();					// Disable Interupts
	
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}
	
	uint32 vPageNum_addr = (uint32)vaddr >> 12;	// Get virtual page number
	struct procent *prptr = &proctab[currpid];	// Ptr to current process entry
	uint32 vPageNum_process = prptr->vPageNum;	// Get current process vPageNum
	
	*bsid = prptr->bsid;
	*poffset = vPageNum_addr - vPageNum_process;
	
	restore(mask);
	return OK;
}
