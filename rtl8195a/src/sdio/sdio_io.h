//#include "../drv_type_sdio.h"
#include "basic_types.h"
#include <linux/mmc/sdio_func.h>
#include "hal_data.h"
u8 sdio_read8(struct sdio_func *func, u32 addr);
u16 sdio_read16(struct sdio_func *func, u32 addr);
u32 sdio_read32(struct sdio_func *func, u32 addr);
//u32 sdio_read_port(struct sdio_func * func, u32 addr, u32 cnt, u8 * mem);
u32 sdio_read_port(PHAL_DATA_TYPE pData, u32 addr, u32 cnt, u8 * mem);
u32 sdio_write_port(struct sdio_func *func, u32 addr, u32 cnt, u8 *mem);
