//#include "../drv_type_sdio.h"
#include "basic_types.h"
#include <linux/mmc/sdio_func.h>

int sdioReadWrite_CMD53_byte(IN struct sdio_func *func, 
		IN u8 *pData, 
		IN u32 Address, 
		IN u32 Length, 
		IN BOOLEAN WriteToDevice);
u16 sdio_read16(struct sdio_func *func, u32 addr);
u32 sdio_read32(struct sdio_func *func, u32 addr);
u32 sdio_read_port(struct sdio_func * func, u32 addr, u32 cnt, u8 * mem);