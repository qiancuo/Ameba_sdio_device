#include "sdio_io.h"
#include "8195_sdio_reg.h"
 #include <linux/string.h>
 
#define WLAN_TX_HIQ_DEVICE_ID 4
#define WLAN_TX_MIQ_DEVICE_ID 5
#define WLAN_TX_LOQ_DEVICE_ID 6
#define WLAN_RX0FF_MSK 0x1fff


//
// Description:
//	The following mapping is for SDIO host local register space.
//
// Creadted by Roger, 2011.01.31.
//
static void HalSdioGetCmdAddr8723ASdio(
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

		case WLAN_IOREG_DEVICE_ID:
			*pCmdAddr = ((WLAN_IOREG_DEVICE_ID << 13) | (Addr & WLAN_IOREG_MSK));
			break;

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

//		case 0x1026:
//			devideId = WLAN_IOREG_DEVICE_ID;
//			break;

//		case 0x1027:
//			devideId = SDIO_FIRMWARE_FIFO;
//			break;

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
//			devideId = (u8)((addr >> 13) & 0xF);
//			devideId = WLAN_IOREG_DEVICE_ID;
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
	printk("deviceId is %d\n", deviceId);
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

		case WLAN_IOREG_DEVICE_ID:
		default:
			deviceId = WLAN_IOREG_DEVICE_ID;
			offset = addr & WLAN_IOREG_MSK;
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
	struct sdio_func *gfunc;

_func_enter_;

	gfunc = func;
	printk("block size is %d\n", gfunc->cur_blksize);
	for (i = 0; i < cnt; i++) {
		pdata[i] = sdio_readb(gfunc, addr+i, &err);
		if (err) {
			printk("sdio_readb failed!\n");
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
	printk("err is : %d\n", err);
//	if (claim_needed)
		sdio_release_host(pfunc);

_func_exit_;

	return err;
}

u16 sdio_read16(struct sdio_func *func, u32 addr)
{
	u32 ftaddr;
	u16 val;

_func_enter_;
	printk("read from address 0x%x\n", addr);
	ftaddr = _cvrt2ftaddr(addr, NULL, NULL);
	printk("target address is 0x%x\n", ftaddr);
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
	printk("read from address 0x%x\n", addr);
	ftaddr = _cvrt2ftaddr(addr, NULL, NULL);
	printk("target address is 0x%x\n", ftaddr);
	sd_cmd52_read(func, ftaddr, 4, (u8*)&val);	
	printk("val32 is 0x%x\n", val);
	val = le32_to_cpu(val);
	printk("le32_to_cpu val32 is 0x%x\n", val);
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
	struct sdio_func *func,
	u32 addr,
	u32 cnt,
	u8 *mem)
{
	s32 err;
	printk("sdio_read_port addr is %d\n", addr);

	HalSdioGetCmdAddr8723ASdio(func, addr, 0, &addr);

	printk("Get Cmd Addr is %d\n", addr);


	cnt = _RND4(cnt);
	if (cnt > 512)
		cnt = _RND(cnt, 512);
	
//	cnt = sdio_align_size(cnt);
 	printk("cnt is %d\n", cnt);
//	err = _sd_read(func, addr, cnt, mem);
	//err = sd_read(pintfhdl, addr, cnt, mem);
	


	if (err) return _FAIL;
	return _SUCCESS;
}


