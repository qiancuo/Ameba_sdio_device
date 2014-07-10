#include "../../include/osdep_service_linux.h"

u8* _rtw_malloc(u32 sz)
{
	u8 *pbuf=NULL;
	pbuf = kmalloc(sz, in_interrupt()?GFP_ATOMIC : GFP_KERNEL);

	return pbuf;
}

void _rtw_mfree(u8 *pbuf, u32 sz)
{
	kfree(pbuf);
}

void _rtw_memcpy(void* dst, void* src, u32 sz)
{
	memcpy(dst, src, sz);
}