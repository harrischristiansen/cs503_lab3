/* vfreemem.c - vfreemem */

#include <xinu.h>

syscall	vfreemem(
	  char		*blkaddr,	/* Pointer to memory block	*/
	  uint32	nbytes		/* Size of block in bytes	*/
	)
{
	intmask mask;			// Interrupt mask
	struct procent *prptr;	// Ptr to process' table entry
	vmem_list_blk *curr;	// Ptr to current block in free memory list
	vmem_list_blk *vnew;	// Ptr to new block in free memory list
	
	mask = disable();
	if (nbytes == 0) {		// Cannot deallocate 0 memory
		restore(mask);
		return SYSERR;
	}
	
	prptr = &proctab[currpid];
	curr = prptr->vmem_free_list;
	
	while (curr->next != NULL && curr->memlen != 0) { // Find location in free list to insert
		curr = curr->next;
	}
	
	if (curr->memlen > 0) { // Create and insert new entry
		vnew = (vmem_list_blk *)(getmem(sizeof(vmem_list_blk)));
		curr->next = vnew;
		curr = vnew;
	}
	
	curr->mem = blkaddr;
	curr->memlen = nbytes;

	restore(mask);
	return OK;
}
