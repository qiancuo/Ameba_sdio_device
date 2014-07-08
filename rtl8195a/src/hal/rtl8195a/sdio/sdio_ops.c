#include "../../../include/sdio_ops.h"
#include "../../../include/8195_sdio_reg.h"
//#include <linux/string.h>


//
// Description:
//	The following mapping is for SDIO host local register space.
//
// Creadted by Roger, 2011.01.31.
//
static void HalSdioGetCmdAddr8195ASdio(
	IN	struct sdio_func	*func,
	IN 	u8				DeviceID,
	IN	u32				Addr,
	OUT	u32*			pCmdAddr
	)
{
	switch (DeviceID)
	{
		case SDIO_LOCAL_DEVICE_ID:
			*pCmdAddr = ((SDIO_LOCAL_DEVICE_ID << 13) | (Addr & SDIO_LOCAL_MSK));
			break;

//		case WLAN_IOREG_DEVICE_ID:
//			*pCmdAddr = ((WLAN_IOREG_DEVICE_ID << 13) | (Addr & WLAN_IOREG_MSK));
//			break;

		case WLAN_TX_HIQ_DEVICE_ID:
			*pCmdAddr = ((WLAN_TX_HIQ_DEVICE_ID << 13) | (Addr & WLAN_FIFO_MSK));
			break;

		case WLAN_TX_MIQ_DEVICE_ID:
			*pCmdAddr = ((WLAN_TX_MIQ_DEVICE_ID << 13) | (Addr & WLAN_FIFO_MSK));
			break;

		case WLAN_TX_LOQ_DEVICE_ID:
			*pCmdAddr = ((WLAN_TX_LOQ_DEVICE_ID << 13) | (Addr & WLAN_FIFO_MSK));
			break;

		case WLAN_RX0FF_DEVICE_ID:
//			*pCmdAddr = ((WLAN_RX0FF_DEVICE_ID << 13) | (Addr & WLAN_RX0FF_MSK));
			*pCmdAddr = ((WLAN_RX0FF_DEVICE_ID << 13) | (Addr & WLAN_RX0FF_MSK));
			break;

		default:
			break;
	}
}
static u8 get_deviceid(u32 addr)
{
	u8 deviceId;
	u16 pseudoId;


	pseudoId = (u16)(addr >> 16);
	switch (pseudoId)
	{
		case 0x1025:
			deviceId = SDIO_LOCAL_DEVICE_ID;
			break;

		case 0x1031:
			deviceId = WLAN_TX_HIQ_DEVICE_ID;
			break;

		case 0x1032:
			deviceId = WLAN_TX_MIQ_DEVICE_ID;
			break;

		case 0x1033:
			deviceId = WLAN_TX_LOQ_DEVICE_ID;
			break;

		case 0x1034:
			deviceId = WLAN_RX0FF_DEVICE_ID;
			break;

		default:
			deviceId = SDIO_LOCAL_DEVICE_ID;
			break;
	}

	return deviceId;
}


/*
 * Ref:
 *	HalSdioGetCmdAddr8723ASdio()
 */
static u32 _cvrt2ftaddr(const u32 addr, u8 *pdeviceId, u16 *poffset)
{
	u8 deviceId;
	u16 offset;
	u32 ftaddr;


	deviceId = get_deviceid(addr);
	printk("%s(): deviceId is %d\n", __func__, deviceId);
	offset = 0;

	switch (deviceId)
	{
		case SDIO_LOCAL_DEVICE_ID:
			offset = addr & SDIO_LOCAL_MSK;
			break;

		case WLAN_TX_HIQ_DEVICE_ID:
		case WLAN_TX_MIQ_DEVICE_ID:
		case WLAN_TX_LOQ_DEVICE_ID:
			offset = addr & WLAN_FIFO_MSK;
			break;

		case WLAN_RX0FF_DEVICE_ID:
			offset = addr & WLAN_RX0FF_MSK;
			break;

//		case WLAN_IOREG_DEVICE_ID:
		default:
			deviceId = SDIO_LOCAL_DEVICE_ID;
			offset = addr & SDIO_LOCAL_MSK;
			break;
	}
	ftaddr = (deviceId << 13) | offset;

	if (pdeviceId) *pdeviceId = deviceId;
	if (poffset) *poffset = offset;

	return ftaddr;
}

/*
 * Return:
 *	0		Success
 *	others	Fail
 */
s32 _sd_cmd52_read(struct sdio_func *func, u32 addr, u32 cnt, u8 *pdata)
{
//	PADAPTER padapter;
//	struct dvobj_priv *psdiodev;
//	PSDIO_DATA psdio;

	int err=0, i;
	struct sdio_func *pfunc;

_func_enter_;

	pfunc = func;
	printk("%s(): block size is %d\n", __func__, pfunc->cur_blksize);
	for (i = 0; i < cnt; i++) {
		pdata[i] = sdio_readb(pfunc, addr+i, &err);
		if (err) {
			printk("%s(): sdio_readb failed!\n", __func__);
			break;
		}
	}

_func_exit_;

	return err;
}

/*
 * Return:
 *	0		Success
 *	others	Fail
 */
s32 sd_cmd52_read(struct sdio_func *func, u32 addr, u32 cnt, u8 *pdata)
{

	int err=0, i;
	struct sdio_func *pfunc;
	bool claim_needed;	

_func_enter_;
	
	pfunc = func;
//	claim_needed = rtw_sdio_claim_host_needed(func);

//	if (claim_needed)
		sdio_claim_host(pfunc);
	err = _sd_cmd52_read(pfunc, addr, cnt, pdata);
	printk("%s(): err from _sd_cmd52_read is : %d\n", __func__, err);
//	if (claim_needed)
		sdio_release_host(pfunc);

_func_exit_;

	return err;
}

u8 sdio_read8(struct sdio_func *func, u32 addr)
{
	u32 ftaddr;
	u8 val;

_func_enter_;

	printk("%s(): read from address 0x%x\n", __func__, addr);
	ftaddr = _cvrt2ftaddr(addr, NULL, NULL);
	printk("%s(): target address is 0x%x\n", __func__, ftaddr);
	sd_cmd52_read(func, ftaddr, 1, (u8*)&val);	

_func_exit_;

	return val;
}

u16 sdio_read16(struct sdio_func *func, u32 addr)
{
	u32 ftaddr;
	u16 val;

_func_enter_;
	printk("%s(): read from address 0x%x\n", __func__, addr);
	ftaddr = _cvrt2ftaddr(addr, NULL, NULL);
	printk("%s(): target address is 0x%x\n", __func__, ftaddr);
	sd_cmd52_read(func, ftaddr, 2, (u8*)&val);	

	val = le16_to_cpu(val);

_func_exit_;

	return val;
}

u32 sdio_read32(struct sdio_func *func, u32 addr)
{
	u32 ftaddr;
	u32 val;

_func_enter_;
	printk("%s(): read from address 0x%x\n", __func__, addr);
	ftaddr = _cvrt2ftaddr(addr, NULL, NULL);
	printk("%s(): target address is 0x%x\n", __func__, ftaddr);
	sd_cmd52_read(func, ftaddr, 4, (u8*)&val);	
	printk("%s(): val32 is 0x%x\n", __func__, val);
	val = le32_to_cpu(val);
	printk("%s(): le32_to_cpu val32 is 0x%x\n", __func__, val);
_func_exit_;

	return val;
}

/*
 * Use CMD53 to read data from SDIO device.
 * This function MUST be called after sdio_claim_host() or
 * in SDIO ISR(host had been claimed).
 *
 * Parameters:
 *	psdio	pointer of SDIO_DATA
 *	addr	address to read
 *	cnt		amount to read
 *	pdata	pointer to put data, this should be a "DMA:able scratch buffer"!
 *
 * Return:
 *	0		Success
 *	others	Fail
 */
s32 _sd_read(struct sdio_func *func, u32 addr, u32 cnt, void *pdata)
{
	
	int err= -EPERM;
	struct sdio_func *pfunc;

_func_enter_;
		
	pfunc = func;

	if (unlikely((cnt==1) || (cnt==2)))
	{
		int i;
		u8 *pbuf = (u8*)pdata;

		for (i = 0; i < cnt; i++)
		{
			*(pbuf+i) = sdio_readb(pfunc, addr+i, &err);

			if (err) {
				printk("%s: FAIL!(%d) addr=0x%05x\n", __func__, err, addr);
				break;
			}
		}
		return err;
	}

	err = sdio_memcpy_fromio(pfunc, pdata, addr, cnt);
	if (err) {
		printk("%s: FAIL(%d)! ADDR=%#x Size=%d\n", __func__, err, addr, cnt);
	}

_func_exit_;

	return err;
}
/*
 * Description:
 *	Read from RX FIFO
 *	Round read size to block size,
 *	and make sure data transfer will be done in one command.
 *
 * Parameters:
 *	func		a pointer of sdio func
 *	addr		port ID
 *	cnt			size to read
 *	rmem		address to put data
 *
 * Return:
 *	_SUCCESS(1)		Success
 *	_FAIL(0)		Fail
 */

u32 sdio_read_port(
//	struct sdio_func *func,
	PHAL_DATA_TYPE pData,
	u32 addr,
	u32 cnt,
	u8 *mem)
{
	s32 err;
	struct sdio_func *func;
	func = pData->func;
	printk("%s(): addr is %d\n", __func__, addr);
	printk("%s(): SDIORxFIFOCnt is %d\n", __func__, pData->SdioRxFIFOCnt);
	HalSdioGetCmdAddr8195ASdio(func, addr, pData->SdioRxFIFOCnt++, &addr);

	printk("%s(): Get Cmd Addr is 0x%x\n", __func__, addr);


	cnt = _RND4(cnt);
	if (cnt > func->cur_blksize)
		cnt = _RND(cnt, func->cur_blksize);
	
//	cnt = sdio_align_size(cnt);
 	printk("%s(): cnt is %d\n", __func__, cnt);
	err = _sd_read(func, addr, cnt, mem);
	//err = sd_read(pintfhdl, addr, cnt, mem);
	
	if (err) return _FAIL;
	return _SUCCESS;
}

/*
 * Use CMD53 to write data to SDIO device.
 * This function MUST be called after sdio_claim_host() or
 * in SDIO ISR(host had been claimed).
 *
 * Parameters:
 *	psdio	pointer of SDIO_DATA
 *	addr	address to write
 *	cnt		amount to write
 *	pdata	data pointer, this should be a "DMA:able scratch buffer"!
 *
 * Return:
 *	0		Success
 *	others	Fail
 */
s32 _sd_write(struct sdio_func *func, u32 addr, u32 cnt, void *pdata)
{
	
	struct sdio_func *pfunc;
	u32 size;
	s32 err=-EPERM;

_func_enter_;
	
	pfunc = func;
//	size = sdio_align_size(func, cnt);

	if (unlikely((cnt==1) || (cnt==2)))
	{
		int i;
		u8 *pbuf = (u8*)pdata;

		for (i = 0; i < cnt; i++)
		{
			sdio_writeb(pfunc, *(pbuf+i), addr+i, &err);
			if (err) {
				printk("%s: FAIL!(%d) addr=0x%05x val=0x%02x\n", __func__, err, addr, *(pbuf+i));
				break;
			}
		}

		return err;
	}

	size = cnt;
	printk("%s(): write to addr 0x%x\n", __func__, addr);
	printk("%s(): write size %d\n", __func__, size);
	err = sdio_memcpy_toio(pfunc, addr, pdata, size);
	if (err) {
		printk("%s: FAIL(%d)! ADDR=%#x Size=%d(%d)\n", __func__, err, addr, cnt, size);
	}

_func_exit_;

	return err;
}

/*
 * Use CMD53 to write data to SDIO device.
 *
 * Parameters:
 *  psdio	pointer of SDIO_DATA
 *  addr	address to write
 *  cnt		amount to write
 *  pdata	data pointer, this should be a "DMA:able scratch buffer"!
 *
 * Return:
 *  0		Success
 *  others	Fail
 */
s32 sd_write(struct sdio_func *func, u32 addr, u32 cnt, void *pdata)
{
	struct sdio_func *pfunc;
//	bool claim_needed;
	s32 err=-EPERM;
_func_enter_;

	pfunc = func;
//	claim_needed = rtw_sdio_claim_host_needed(func);

//	if (claim_needed)
		sdio_claim_host(pfunc);
	err = _sd_write(pfunc, addr, cnt, pdata);
//	if (claim_needed)
		sdio_release_host(pfunc);
_func_exit_;
	return err;
}

/*
 * Description:
 *	Write to TX FIFO
 *	Align write size block size,
 *	and make sure data could be written in one command.
 *
 * Parameters:
 *	pintfhdl	a pointer of intf_hdl
 *	addr		port ID
 *	cnt			size to write
 *	wmem		data pointer to write
 *
 * Return:
 *	_SUCCESS(1)		Success
 *	_FAIL(0)		Fail
 */
u32 sdio_write_port(
	struct sdio_func *func,
	u32 addr,
	u32 cnt,
	u8 *mem)
{

	s32 err;
	struct sdio_func *pfunc = func;
//	struct xmit_buf *xmitbuf = (struct xmit_buf *)mem;
	printk("%s(): addr is %d\n", __func__, addr);
	cnt = _RND4(cnt);
	printk("%s(): cnt is %d\n", __func__, cnt);
	HalSdioGetCmdAddr8195ASdio(pfunc, addr, cnt >> 2, &addr);
	printk("%s(): Get Cmd Addr is 0x%x\n", __func__, addr);
	
	if (cnt > pfunc->cur_blksize)
		cnt = _RND(cnt, pfunc->cur_blksize);
//	cnt = sdio_align_size(cnt);

	err = sd_write(pfunc, addr, cnt, mem);

//	rtw_sctx_done_err(&xmitbuf->sctx,
//		err ? RTW_SCTX_DONE_WRITE_PORT_ERR : RTW_SCTX_DONE_SUCCESS);
	
	if (err)
	{
		printk("%s, error=%d\n", __func__, err);
		return _FAIL;
	}
	return _SUCCESS;
}
