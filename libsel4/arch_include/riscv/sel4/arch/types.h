/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#ifndef __LIBSEL4_ARCH_TYPES_H
#define __LIBSEL4_ARCH_TYPES_H

#include <autoconf.h>
#include <stdint.h>

#define seL4_WordBits        32
#define seL4_PageBits        12
#define seL4_SlotBits         4
#define seL4_TCBBits         10
#define seL4_EndpointBits     4
#define seL4_PageTableBits   12
#define seL4_PageDirBits     12
#define seL4_IOPageTableBits 12
#define seL4_RISCV_VCPUBits 14
#define seL4_RISCV_EPTPageDirectoryPointerTableBits 13
#define seL4_RISCV_EPTPageDirectoryBits 12
#define seL4_RISCV_EPTPageTableBits 12

#ifdef CONFIG_PAE_PAGING
#define seL4_PDPTBits         5
#define seL4_LargePageBits    21
#else
#define seL4_LargePageBits    22
#endif

/* Previously large frames were explicitly assumed to be 4M. If not using
 * PAE assuming a legacy environment and leave the old definition */
#ifndef CONFIG_PAE_PAGING
#define seL4_4MBits           seL4_LargePageBits
#endif

typedef uint32_t  seL4_Word;
typedef seL4_Word seL4_CPtr;

typedef seL4_CPtr seL4_RISCV_IOSpace;
typedef seL4_CPtr seL4_RISCV_IOPort;
typedef seL4_CPtr seL4_RISCV_Page;
typedef seL4_CPtr seL4_RISCV_PageDirectory;
typedef seL4_CPtr seL4_RISCV_PageTable;
typedef seL4_CPtr seL4_RISCV_IOPageTable;
typedef seL4_CPtr seL4_RISCV_VCPU;
typedef seL4_CPtr seL4_RISCV_EPTPageDirectoryPointerTable;
typedef seL4_CPtr seL4_RISCV_EPTPageDirectory;
typedef seL4_CPtr seL4_RISCV_EPTPageTable;
typedef seL4_CPtr seL4_RISCV_IPI;

/* User context as used by seL4_TCB_ReadRegisters / seL4_TCB_WriteRegisters */

typedef struct seL4_UserContext_ {
    /* frameRegisters */
    //seL4_Word eip, esp, eflags, eax, ebx, ecx, edx, esi, edi, ebp;
    /* gpRegisters */
    //seL4_Word tls_base, fs, gs;
} seL4_UserContext;

typedef struct seL4_VCPUContext_ {
    //seL4_Word eax, ebx, ecx, edx, esi, edi, ebp;
} seL4_VCPUContext;

typedef enum {
    seL4_RISCV_Default_VMAttributes = 0,
    seL4_RISCV_WriteBack = 0,
    seL4_RISCV_WriteThrough = 1,
    seL4_RISCV_CacheDisabled = 2,
    seL4_RISCV_Uncacheable = 3,
    seL4_RISCV_WriteCombining = 4,
    SEL4_FORCE_LONG_ENUM(seL4_RISCV_VMAttributes),
} seL4_RISCV_VMAttributes;

#endif
