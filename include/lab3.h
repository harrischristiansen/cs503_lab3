/* Purdue CS503 Fall 2017 - Lab 3 - Virtual Memory and Demand Paging */
/* @Harris Christiansen (code@harrischristiansen.com) */

#ifndef __LAB3_H_
#define __LAB3_H_

#include <paging.h>

typedef struct {
  int16 alloc_page_proc[NFRAMES];
  uint32 alloc_page[NFRAMES];
  int16 curframe;
  int16 reclaimframe;
} frame_md_t;

extern frame_md_t frame_md;

// Hooks, in hooks.c
void hook_ptable_create(uint32 pagenum);
void hook_ptable_delete(uint32 pagenum);

// changed by adil
void hook_pfault(int16 procid, void *addr, uint32 pagenum, uint32 framenum);

// changed by adil
void hook_pswap_out(int16 procid, uint32 pagenum, uint32 framenum);

/* Lab 3 Definitions */

// Helper for getting bit at index i in 32 bit word w
#define GET_BIT(w,i) (!(0 == (w & (1UL << (i)))))

#define	NUM_GLOBALPAGETABLES	4			// Number of global page tables to create
#define	PAGEFAULTINTERRUPTNUM	14			// Interrupt Code for Page Faults

extern uint32 pferrcode;				// Page Fault Error Code (set by pfdisp)

#endif // __LAB3_H_
