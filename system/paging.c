/* paging.c - Paging Management */

#include <xinu.h>

// --------------- Page Directory ---------------

syscall init_pageDirEntry(uint32 frameNum)
{
	intmask mask;			// Interrupt mask
	
	if (frameNum < FRAME0 || frameNum >= FRAME_END) { // Can only create pte between frames 1024-4096
		return SYSERR;
	}
	
	mask = disable();		// Disable Interupts
	
	pd_t *pde = (pd_t *)(frameNum * BYTESPERFRAME);
	
	int i;
	for (i = 0; i < NUM_GLOBALPAGETABLES; i++) { // Load addresses of global page tables
		pde[i].pd_pres = 1;
		pde[i].pd_write = 1;
		pde[i].pd_base = ((FRAME0 + i) * BYTESPERFRAME) >> 12;
	}
	
	restore(mask);
	return OK;
}

// --------------- Page Table ---------------

syscall init_pageTableEntry(uint32 frameNum)
{
	intmask mask;			// Interrupt mask
	
	if (frameNum < FRAME0 || frameNum >= FRAME_END) { // Can only create pte between frames 1024-4096
		return SYSERR;
	}
	
	mask = disable();		// Disable Interupts
	
	pt_t *pte = (pt_t *)(frameNum * BYTESPERFRAME);
	
	int i;
	for (i = 0; i < PAGETABSIZE; i++) {
		pte[i].pt_pres = 1;
		pte[i].pt_write = 1;
		pte[i].pt_base = ((frameNum + FRAME0) * PAGETABSIZE) + i; // Start pt_base at 0 for FRAME0
	}
	
	restore(mask);
	return OK;
}

syscall init_globalPageTables(uint32 numFrames)
{
	uint32 frameNum;
	
	int i;
	for (i = 0; i < numFrames; i++) {
		frameNum = FRAME0 + i;
		if (init_pageTableEntry(frameNum) == SYSERR) {
			return SYSERR;
		}
	}
	
	return OK;
}

// --------------- Control Register Setup ---------------

syscall enable_paging()
{
	uint32 cr0_val =  read_cr(0);
	cr0_val = cr0_val | 0x80000000;
	write_cr(0, cr0_val);
	return OK;
}

uint32 tmp;

uint32 read_cr(uint32 cr)
{
	intmask mask;			// Interrupt mask
	uint32 cr_value;		// CR Value
	
	if (cr > 4) {
		return SYSERR;
	}
	
	mask = disable();		// Disable Interupts

	asm("pushl %eax");
	switch (cr) {
	case 0:
		asm("movl %cr0, %eax");
		break;
	case 1:
		asm("movl %cr1, %eax");
		break;
	case 2:
		asm("movl %cr2, %eax");
		break;
	case 3:
		asm("movl %cr3, %eax");
		break;
	case 4:
		asm("movl %cr4, %eax");
		break;
	}
	asm("movl %eax, tmp");
	asm("popl %eax");
	cr_value = tmp;
	
	restore(mask);
	return cr_value;
}

syscall write_cr(uint32 cr, uint32 v)
{
	intmask mask;			// Interrupt mask
	
	if (cr > 4) {
		return SYSERR;
	}
	
	mask = disable();		// Disable Interupts

	tmp = v;
	asm("pushl %eax");
	asm("movl tmp, %eax");
	switch (cr) {
	case 0:
		asm("movl %eax, %cr0");
		break;
	case 1:
		asm("movl %eax, %cr1");
		break;
	case 2:
		asm("movl %eax, %cr2");
		break;
	case 3:
		asm("movl %eax, %cr3");
		break;
	case 4:
		asm("movl %eax, %cr4");
		break;
	}
	asm("popl %eax");
	
	restore(mask);
	return OK;

}