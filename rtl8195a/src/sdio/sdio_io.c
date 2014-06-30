#include "sdio_io.h"
#include "../drv_type_sdio.h"
#include "8195_sdio_reg.h"
 #include <linux/string.h>

#define _func_enter_ do{}while(0)
#define _func_exit_ do{}while(0)
#define WLAN_TX_HIQ_DEVICE_ID 4
#define WLAN_TX_MIQ_DEVICE_ID 5
#define WLAN_TX_LOQ_DEVICE_ID 6
#define WLAN_RX0FF_MSK 0x1fff

static u8 get_deviceid(u32 addr)
{
	u8 devideId;
	u16 pseudoId;


	pseudoId = (u16)(addr >> 16);
	switch (pseudoId)
	{
		case 0x1025:
			devideId = SDIO_LOCAL_DEVICE_ID;
			break;

		case 0x1026:
			devideId = WLAN_IOREG_DEVICE_ID;
			break;

//		case 0x1027:
//			devideId = SDIO_FIRMWARE_FIFO;
//			break;

		case 0x1031:
			devideId = WLAN_TX_HIQ_DEVICE_ID;
			break;

		case 0x1032:
			devideId = WLAN_TX_MIQ_DEVICE_ID;
			break;

		case 0x1033:
			devideId = WLAN_TX_LOQ_DEVICE_ID;
			break;

		case 0x1034:
			devideId = WLAN_RX0FF_DEVICE_ID;
			break;

		default:
//			devideId = (u8)((addr >> 13) & 0xF);
			devideId = WLAN_IOREG_DEVICE_ID;
			break;
	}

	return devideId;
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
//	padapter = pintfhdl->padapter;
//	psdiodev = pintfhdl->pintf_dev;
//	psdio = &psdiodev->intf_data;

//	if(padapter->bSurpriseRemoved){
//		//DBG_871X(" %s (padapter->bSurpriseRemoved ||adapter->pwrctrlpriv.pnp_bstop_trx)!!!\n",__FUNCTION__);
//		return err;
//	}
	
	gfunc = func;
	printk("block size is %d\n", gfunc->cur_blksize);
	for (i = 0; i < cnt; i++) {
		pdata[i] = sdio_readb(gfunc, addr+i, &err);
		if (err) {
//			DBG_871X(KERN_ERR "%s: FAIL!(%d) addr=0x%05x\n", __func__, err, addr+i);
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
//	PADAPTER padapter;
//	struct dvobj_priv *psdiodev;
//	PSDIO_DATA psdio;
	
	int err=0, i;
	struct sdio_func *pfunc;
	bool claim_needed;	

_func_enter_;
//	padapter = pintfhdl->padapter;
//	psdiodev = pintfhdl->pintf_dev;
//	psdio = &psdiodev->intf_data;

//	if(padapter->bSurpriseRemoved){
//		//DBG_871X(" %s (padapter->bSurpriseRemoved ||adapter->pwrctrlpriv.pnp_bstop_trx)!!!\n",__FUNCTION__);
//		return err;
//	}	
	
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

/*
static u16 swab16(u16 x)
{
	u16 __x = x; 
	return 
	((u16)( 
		(((u16)(__x) & (u16)0x00ffU) << 8) |
		(((u16)(__x) & (u16)0xff00U) >> 8) ));

}
*/

//#define le16_to_cpu(x) swab16(x)
u16 sdio_read16(struct sdio_func *func, u32 addr)
{
	u32 ftaddr;
	u16 val;
u32 val32;

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
	u16 val;
u32 val32;

_func_enter_;
	printk("read from address 0x%x\n", addr);
	ftaddr = _cvrt2ftaddr(addr, NULL, NULL);
	printk("target address is 0x%x\n", ftaddr);
//	sd_cmd52_read(func, ftaddr, 2, (u8*)&val);	
	sd_cmd52_read(func, ftaddr, 4, (u8*)&val32);	

//	val = le16_to_cpu(val);
	val32 = le32_to_cpu(val32);

_func_exit_;

	return val32;
}




