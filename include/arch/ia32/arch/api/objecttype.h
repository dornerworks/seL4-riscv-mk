/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#ifndef __ARCH_OBJECT_TYPE_H
#define __ARCH_OBJECT_TYPE_H

typedef enum _object {
    seL4_IA32_4K = seL4_NonArchObjectTypeCount,
    seL4_IA32_LargePage,
    seL4_IA32_PageTableObject,
    seL4_IA32_PageDirectoryObject,
    seL4_IA32_PDPTObject,
#ifdef CONFIG_IOMMU
    seL4_IA32_IOPageTableObject,
#endif
#ifdef CONFIG_VTX
    seL4_IA32_VCPUObject,
    seL4_IA32_EPTPageDirectoryPointerTableObject,
    seL4_IA32_EPTPageDirectoryObject,
    seL4_IA32_EPTPageTableObject,
#endif
    seL4_ObjectTypeCount
} seL4_ArchObjectType;
typedef uint32_t object_t;

#endif
