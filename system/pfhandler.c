/* pfhandler.c - pfhandler */

#include <xinu.h>

static status load_page();

/*------------------------------------------------------------------------
 * pfhandler - Page Fault Interrupt Handler
 *------------------------------------------------------------------------
 */
void pfhandler() // Interrupts are already disabled by pfdisp
{
	kprintf("Page Fault Occured: %x\n", pferrcode);
	
	if (GET_BIT(pferrcode, 0) == 0) { // Virtual page was not present, load page
		if (load_page() == SYSERR) {
			kprintf("ERROR: Page fault resulted in failure to load page");
			kill(currpid); // Ended in error, kill current process
		}
	} else { // Fault due to attempt to load invalid page
		kprintf("ERROR: Page fault occured due to attempt to load invalid page");
		kill(currpid); // Ended in error, kill current process
	}
}

status load_page()
{
	return OK;
}