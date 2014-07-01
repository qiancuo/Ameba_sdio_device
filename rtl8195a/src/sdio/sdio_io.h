//#include "../drv_type_sdio.h"
#include "basic_types.h"
#include <linux/mmc/sdio_func.h>

#define WLAN_TX_HIQ_DEVICE_ID 4
#define WLAN_TX_MIQ_DEVICE_ID 5
#define WLAN_TX_LOQ_DEVICE_ID 6
#define WLAN_RX0FF_MSK 0x1fff

u8 sdio_read8(struct sdio_func *func, u32 addr);
u16 sdio_read16(struct sdio_func *func, u32 addr);
u32 sdio_read32(struct sdio_func *func, u32 addr);
u32 sdio_read_port(struct sdio_func * func, u32 addr, u32 cnt, u8 * mem);
u32 sdio_write_port(struct sdio_func *func, u32 addr, u32 cnt, u8 *mem);