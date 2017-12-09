/* allocate_bs.c - allocate_bs */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  allocate_bs  -  Allocates a free backing store; returns a bs number if
 *  successful or SYSERR if they are all occupied.
 *------------------------------------------------------------------------
 */
bsd_t	allocate_bs (
	uint32 npages
	)
{
	int32	i;
	intmask	mask;

	/* Ensure only one process accesses bstab */
	mask = disable();

	if(PAGE_SERVER_STATUS == PAGE_SERVER_INACTIVE){
		psinit();
	}

	/* Find an unallocated store */
	for(i = 0; i < MAX_BS_ENTRIES; i++) {
		if(bstab[i].isallocated == FALSE) { /* Found an unallocated store */
			if(get_bs(i, npages) == SYSERR) { /* Try to open it */
				continue;
			}
			/* Successfully opened, allocate it */
			bstab[i].isallocated = TRUE;
			bstab[i].usecount = 0;
			
			// Begin Lab 3 Modifications
			
			bstab[i].pid = currpid;
			bstab[i].pageNum = 0; // TODO
			bstab[i].npages = npages;
			
			// End Lab 3 Modifications

			restore(mask);
			return i;
		}
	}

	restore(mask);
	return SYSERR;
}
