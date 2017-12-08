# CS 503 - Lab 3: Virtual Memory and Demand Paging 

@Harris Christiansen (christih@purdue.edu) (HarrisChristiansen.com)  
December 2017  

## Description
- The objective of this lab is to build Virtual Memory and Demand Paging for the XINU operating system.

## Usage
- Build: `make` in compile/ directory
	- Clean: `make clean`
	- Rebuild: `make rebuild`

## Tasks
- [ ] Demand Paging Services
	- [ ] pid32 vcreate(void *funcaddr, uint32 ssize, uint32 hsize, pri16 priority, char *name, uint32 nargs, ...)
	- [X] char* vgetmem(uint32 nbytes)
	- [ ] syscall vfreemem(char *blkaddr, uint32 nbytes)
	- [ ] syscall srpolicy(int policy)
- [ ] Backing Store
	- [ ] bsd_t allocate_bs(uint32 npages)
	- [ ] bsd_t deallocate_bs(bsd_t store)
	- [ ] bsd_t open_bs(bsd_t store)
	- [ ] bsd_t close_bs(bsd_t store)
	- [ ] syscall read_bs(char *dst, bsd_t store, uint32 pagenum)
	- [ ] syscall write_bs(char *src, bsd_t store, uint32 pagenum)
- [ ] Instrumentation Hooks
	- [ ] uint32 get_faults()
	- [ ] void hook_ptable_create(uint32 pagenum)
	- [ ] void hook_ptable_delete(uint32 pagenum)
	- [ ] void hook_pfault(int16 procid, void *addr, uint32 pagenum, uint32 framenum)
	- [ ] void hook_pswap_out(int16 procid, uint32 pagenum, uint32 framenum)
