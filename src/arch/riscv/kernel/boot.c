/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <assert.h>
#include <kernel/boot.h>
#include <machine/io.h>
#include <model/statedata.h>
#include <object/interrupt.h>
#include <arch/machine.h>
#include <arch/kernel/boot.h>
#include <arch/kernel/vspace.h>
#include <arch/benchmark.h>
//#include <arch/user_access.h>
#include <arch/linker.h>
#include <plat/machine/hardware.h>
#include <machine.h>
#include <limits.h>
//#include <string.h>

void trap_entry();
void pop_tf(trapframe_t*);

typedef struct { pte_tt addr; void* next; } freelist_t;

char test_area[4096] __attribute__((aligned(4*1024*1024)));

uint32_t l1pt[PTES_PER_PT] __attribute__((aligned(RISCV_PGSIZE)));
pte_tt l2pt[PTES_PER_PT] __attribute__((aligned(RISCV_PGSIZE)));
pte_tt l3pt[PTES_PER_PT] __attribute__((aligned(RISCV_PGSIZE)));

/* pointer to the end of boot code/data in kernel image */
/* need a fake array to get the pointer from the linker script */
extern char ki_boot_end[1];
/* pointer to end of kernel image */
extern char ki_end[1];

/**
 * Split mem_reg about reserved_reg. If memory exists in the lower
 * segment, insert it. If memory exists in the upper segment, return it.
 */
BOOT_CODE static region_t
insert_region_excluded(region_t mem_reg, region_t reserved_reg)
{
}

BOOT_CODE static void
init_freemem(region_t ui_reg)
{
}

BOOT_CODE static void
init_irqs(cap_t root_cnode_cap)
{
}

/* Create a frame cap for the initial thread. */

static BOOT_CODE cap_t
create_it_frame_cap(pptr_t pptr, vptr_t vptr, asid_t asid, bool_t use_large)
{
}

BOOT_CODE cap_t
create_unmapped_it_frame_cap(pptr_t pptr, bool_t use_large)
{
}

BOOT_CODE cap_t
create_mapped_it_frame_cap(cap_t pd_cap, pptr_t pptr, vptr_t vptr, bool_t
use_large, bool_t executable)
{
}

/* Create a page table for the initial thread */

static BOOT_CODE cap_t
create_it_page_table_cap(cap_t pd, pptr_t pptr, vptr_t vptr, asid_t asid)
{
}

BOOT_CODE static bool_t
create_device_frames(cap_t root_cnode_cap)
{
    return true;
}

/* This and only this function initialises the CPU. It does NOT initialise any kernel state. */

BOOT_CODE static void
init_cpu(void)
{
}

/* This and only this function initialises the platform. It does NOT initialise any kernel state. */

BOOT_CODE static void
init_plat(void)
{
    initIRQController();
    initTimer();
    initL2Cache();
}

/* Main kernel initialisation function. */


static BOOT_CODE bool_t
try_init_kernel(
    paddr_t ui_p_reg_start,
    paddr_t ui_p_reg_end,
    int32_t pv_offset,
    vptr_t  v_entry
)
{
    /* kernel successfully initialized */
    map_kernel_window();
    
    // page directory
    return true;
}

void vm_boot(long test_addr, long seed)
{
  while (read_csr(mhartid) > 0); // only core 0 proceeds
  long i = 0;
  //assert(SIZEOF_TRAPFRAME_T == sizeof(trapframe_t));

  /*  4 MB */
  for(i = 0; i < 1024; i++)
    l1pt[i] = i <<  20 | PTE_TYPE_SRWX_GLOBAL |  PTE_V;

  uint32_t pteidx = ((uint32_t) &test_area) & (1 << RISCV_PGSHIFT);

  l1pt[2] = 2 <<  20 | PTE_TYPE_SRX_GLOBAL |  PTE_V;

  write_csr(sptbr, l1pt);
  set_csr(mstatus, MSTATUS_IE1 | MSTATUS_MPRV);
  clear_csr(mstatus, MSTATUS_VM);
  set_csr(mstatus, (long)VM_SV32 << __builtin_ctzl(MSTATUS_VM));

  /* Set to supervisor mode */
  clear_csr(mstatus, (long) PRV_H << __builtin_ctzl(MSTATUS_PRV));
  //clear_csr(mstatus, MSTATUS_PRV);
}


BOOT_CODE VISIBLE void
init_kernel(
    paddr_t ui_p_reg_start,
    paddr_t ui_p_reg_end,
    int32_t pv_offset,
    vptr_t  v_entry
)
{
  printf("********* Platform Information ********** \n");
  init_plat();

  //set_csr(mstatus,PRV_U);
  vm_boot(&init_kernel, 1337);
  printf("Initializing platform ...... \n");
  printf("Trying to write to invalid page ... \n");
  
  test_area[0] = 0xDEADBEAF;
 
  printf("Exiting....\n");
  terminate(0);
  while(1);
}

