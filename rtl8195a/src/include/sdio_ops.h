#ifndef __SDIO_IO_H__
#define __SDIO_IO_H__
/***************************************************/
#include "autoconf.h"
#include "basic_types.h"
#include <linux/mmc/sdio_func.h>
#include "hal_data.h"
//	u8 sdio_read8(struct sdio_func *func, u32 addr);
//	u16 sdio_read16(struct sdio_func *func, u32 addr);
//	u32 sdio_read32(struct sdio_func *func, u32 addr);
//	//u32 sdio_read_port(struct sdio_func * func, u32 addr, u32 cnt, u8 * mem);
//	u32 sdio_read_port(PHAL_DATA_TYPE pData, u32 addr, u32 cnt, u8 * mem);
//	u32 sdio_write_port(struct sdio_func *func, u32 addr, u32 cnt, u8 *mem);
//	s32 sdio_local_read(PHAL_DATA_TYPE pData,	u32	addr, u32 cnt, u8 *pbuf);
//	void sd_int_hal(PHAL_DATA_TYPE pHalData);


extern void sdio_set_intf_ops(_adapter *padapter,struct _io_ops *pops);
	
//extern void sdio_func1cmd52_read(struct intf_hdl *pintfhdl, u32 addr, u32 cnt, u8 *rmem);
//extern void sdio_func1cmd52_write(struct intf_hdl *pintfhdl, u32 addr, u32 cnt, u8 *wmem);
//extern u8 SdioLocalCmd52Read1Byte(PADAPTER padapter, u32 addr);
//extern void SdioLocalCmd52Write1Byte(PADAPTER padapter, u32 addr, u8 v);
extern s32 _sdio_local_read(PADAPTER padapter, u32 addr, u32 cnt, u8 *pbuf);
extern s32 sdio_local_read(PADAPTER padapter, u32 addr, u32 cnt, u8 *pbuf);
extern s32 _sdio_local_write(PADAPTER padapter, u32 addr, u32 cnt, u8 *pbuf);
extern s32 sdio_local_write(PADAPTER padapter, u32 addr, u32 cnt, u8 *pbuf);

u32 _sdio_read32(PADAPTER padapter, u32 addr);
s32 _sdio_write32(PADAPTER padapter, u32 addr, u32 val);

extern void sd_int_hdl(PADAPTER padapter);

/**************************************************/
#endif
