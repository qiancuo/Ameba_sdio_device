#ifndef __RTL8195A_H__
#define __RTL8195A_H__
#include "autoconf.h"
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,8,0)
#define __devinit
#define __devexit
#define __devexit_p(func)   func
#endif

#define MODULENAME "iNIC_8195a"
#define GPL_CLAIM "=== iNIC_8195a ===\n"
#define RTL8195_VERSION "8195a"

enum _CHIP_TYPE {
	NULL_CHIP_TYPE,	
	RTL8195A,
	MAX_CHIP_TYPE
};

#endif