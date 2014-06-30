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

	for (i = 0; i < cnt; i++) {
		pdata[i] = sdio_readb(func, addr+i, &err);
		if (err) {
//			DBG_871X(KERN_ERR "%s: FAIL!(%d) addr=0x%05x\n", __func__, err, addr+i);
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
		sdio_claim_host(func);
	err = _sd_cmd52_read(pintfhdl, addr, cnt, pdata);
//	if (claim_needed)
		sdio_release_host(func);

_func_exit_;

	return err;
}


__inline static u16  swab16(u16 x)
{
	u16 __x = x; 
	return 
	((u16)( 
		(((u16)(__x) & (u16)0x00ffU) << 8) |
		(((u16)(__x) & (u16)0xff00U) >> 8) ));

}


#define le16_to_cpu(x) swab16(x)

u16 sdio_read16(struct sdio_func *func, u32 addr)
{
	u32 ftaddr;
	u16 val;

_func_enter_;

	ftaddr = _cvrt2ftaddr(addr, NULL, NULL);
	sd_cmd52_read(func, ftaddr, 2, (u8*)&val);	
	val = le16_to_cpu(val);

_func_exit_;

	return val;
}

