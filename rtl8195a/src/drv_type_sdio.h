#ifndef __DRV_TYPES_SDIO_H__
#define __DRV_TYPES_SDIO_H__

#define PLATFORM_LINUX

// SDIO Header Files
#ifdef PLATFORM_LINUX
	#include <linux/mmc/sdio_func.h> 
	#include <linux/mmc/sdio_ids.h>
#endif

typedef struct sdio_data
{
	u8  func_number;
 
	u8  tx_block_mode;
	u8  rx_block_mode;
	u32 block_transfer_len;

#ifdef PLATFORM_LINUX
	struct sdio_func	 *func;
	//_thread_hdl_ sys_sdio_irq_thd;
#endif
} SDIO_DATA, *PSDIO_DATA;

struct pkt_file {
	struct sk_buffer *pkt;
	SIZE_T pkt_len;	 //the remainder length of the open_file
	u8 *cur_buffer;
	u8 *buf_start;
	u8 *cur_addr;
	SIZE_T buf_len;
};

#endif

