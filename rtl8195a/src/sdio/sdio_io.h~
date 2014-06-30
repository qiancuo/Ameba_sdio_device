//#include "../drv_type_sdio.h"
//#include "../8195_common.h"
#include "basic_types.h"
#include <linux/mmc/sdio_func.h>
u8 IoRead8(struct sdio_func *func, u32 addr);
u16 IoRead16(struct sdio_func *func, u32 addr);
u32 IoRead32(struct sdio_func *func, u32 addr);
void IoWrite8(struct sdio_func *func, u32 addr, u8 value);
void IoWrite16(struct sdio_func *func, u32 addr, u16 value);
void IoWrite32(struct sdio_func *func, u32 addr, u32 value);
int sdioReadWrite_CMD53_byte(IN struct sdio_func *func, 
		IN u8 *pData, 
		IN u32 Address, 
		IN u32 Length, 
		IN BOOLEAN WriteToDevice);
u16 sdio_read16(struct sdio_func *func, u32 addr);
u32 sdio_read32(struct sdio_func *func, u32 addr);
