/* vgetmem.c - vgetmem */

#include <xinu.h>

char  	*vgetmem(
	  uint32	nbytes		/* Size of memory requested	*/
	)
{
	intmask mask;			// Interrupt mask
	struct procent *prptr;	// Ptr to process' table entry
	vmem_list_blk *curr;	// Ptr to current block in free memory list
	
	mask = disable();
	if (nbytes == 0) {		// Cannot allocate 0 memory
		restore(mask);
		return (char *)SYSERR;
	}
	
	prptr = &proctab[currpid];
	curr = prptr->vmem_free_list;
	while (curr != NULL) {
		if (curr->memlen == nbytes) { // Free block is exact size needed
			curr->memlen = 0;
			restore(mask);
			return curr->mem;
		} else if (curr->memlen > nbytes) { // Free block is larger than needed
			char *loc = curr->mem;
			curr->mem = (char *)((unsigned)curr->mem + nbytes); // Allocate space at start
			curr->memlen -= nbytes;
			restore(mask);
			return loc;
		}
		curr = curr->next;
	}
	
	restore(mask);
	return (char *)SYSERR;
}
