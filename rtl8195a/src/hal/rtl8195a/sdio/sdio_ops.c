#include "../../../include/drv_types.h"
#include "../../../include/rtw_debug.h"
#include "../../../include/sdio_ops.h"
#include "../../../include/sdio_ops_linux.h"
#include "../../../include/8195_sdio_reg.h"
#include "../../../include/osdep_service_linux.h"
#include "../../../include/osdep_service.h"

//
// Description:
//	The following mapping is for SDIO host local register space.
//
// Creadted by Roger, 2011.01.31.
//
static void chris_HalSdioGetCmdAddr8195ASdio(
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
//
// Description:
//	The following mapping is for SDIO host local register space.
//
// Creadted by Roger, 2011.01.31.
//
static void HalSdioGetCmdAddr8195ASdio(
//	IN	struct sdio_func	*func,
	IN	PADAPTER		padapter,
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

//	/*
//	 * Return:
//	 *	0		Success
//	 *	others	Fail
//	 */
//	s32 _sd_cmd52_read(struct sdio_func *func, u32 addr, u32 cnt, u8 *pdata)
//	{
//	//	PADAPTER padapter;
//	//	struct dvobj_priv *psdiodev;
//	//	PSDIO_DATA psdio;
//	
//		int err=0, i;
//		struct sdio_func *pfunc;
//	
//	_func_enter_;
//	
//		pfunc = func;
//		printk("%s(): block size is %d\n", __func__, pfunc->cur_blksize);
//		for (i = 0; i < cnt; i++) {
//			pdata[i] = sdio_readb(pfunc, addr+i, &err);
//			if (err) {
//				printk("%s(): sdio_readb failed!\n", __func__);
//				break;
//			}
//		}
//	
//	_func_exit_;
//	
//		return err;
//	}
//	
//	/*
//	 * Return:
//	 *	0		Success
//	 *	others	Fail
//	 */
//	s32 sd_cmd52_read(struct sdio_func *func, u32 addr, u32 cnt, u8 *pdata)
//	{
//	
//		int err=0, i;
//		struct sdio_func *pfunc;
//		bool claim_needed;	
//	
//	_func_enter_;
//		
//		pfunc = func;
//	//	claim_needed = rtw_sdio_claim_host_needed(func);
//	
//	//	if (claim_needed)
//			sdio_claim_host(pfunc);
//		err = _sd_cmd52_read(pfunc, addr, cnt, pdata);
//		printk("%s(): err from _sd_cmd52_read is : %d\n", __func__, err);
//	//	if (claim_needed)
//			sdio_release_host(pfunc);
//	
//	_func_exit_;
//	
//		return err;
//	}
//	
//	u8 sdio_read8(struct sdio_func *func, u32 addr)
//	{
//		u32 ftaddr;
//		u8 val;
//	
//	_func_enter_;
//	
//		printk("%s(): read from address 0x%x\n", __func__, addr);
//		ftaddr = _cvrt2ftaddr(addr, NULL, NULL);
//		printk("%s(): target address is 0x%x\n", __func__, ftaddr);
//		sd_cmd52_read(func, ftaddr, 1, (u8*)&val);	
//	
//	_func_exit_;
//	
//		return val;
//	}
//	
//	u16 sdio_read16(struct sdio_func *func, u32 addr)
//	{
//		u32 ftaddr;
//		u16 val;
//	
//	_func_enter_;
//		printk("%s(): read from address 0x%x\n", __func__, addr);
//		ftaddr = _cvrt2ftaddr(addr, NULL, NULL);
//		printk("%s(): target address is 0x%x\n", __func__, ftaddr);
//		sd_cmd52_read(func, ftaddr, 2, (u8*)&val);	
//	
//		val = le16_to_cpu(val);
//	
//	_func_exit_;
//	
//		return val;
//	}
//	
//	u32 sdio_read32(struct sdio_func *func, u32 addr)
//	{
//		u32 ftaddr;
//		u32 val;
//	
//	_func_enter_;
//		printk("%s(): read from address 0x%x\n", __func__, addr);
//		ftaddr = _cvrt2ftaddr(addr, NULL, NULL);
//		printk("%s(): target address is 0x%x\n", __func__, ftaddr);
//		sd_cmd52_read(func, ftaddr, 4, (u8*)&val);	
//		printk("%s(): val32 is 0x%x\n", __func__, val);
//		val = le32_to_cpu(val);
//		printk("%s(): le32_to_cpu val32 is 0x%x\n", __func__, val);
//	_func_exit_;
//	
//		return val;
//	}
//	
//	/*
//	 * Use CMD53 to read data from SDIO device.
//	 * This function MUST be called after sdio_claim_host() or
//	 * in SDIO ISR(host had been claimed).
//	 *
//	 * Parameters:
//	 *	psdio	pointer of SDIO_DATA
//	 *	addr	address to read
//	 *	cnt		amount to read
//	 *	pdata	pointer to put data, this should be a "DMA:able scratch buffer"!
//	 *
//	 * Return:
//	 *	0		Success
//	 *	others	Fail
//	 */
//	s32 _sd_read(struct sdio_func *func, u32 addr, u32 cnt, void *pdata)
//	{
//		
//		int err= -EPERM;
//		struct sdio_func *pfunc;
//	
//	_func_enter_;
//			
//		pfunc = func;
//	
//		if (unlikely((cnt==1) || (cnt==2)))
//		{
//			int i;
//			u8 *pbuf = (u8*)pdata;
//	
//			for (i = 0; i < cnt; i++)
//			{
//				*(pbuf+i) = sdio_readb(pfunc, addr+i, &err);
//	
//				if (err) {
//					printk("%s: FAIL!(%d) addr=0x%05x\n", __func__, err, addr);
//					break;
//				}
//			}
//			return err;
//		}
//	
//		err = sdio_memcpy_fromio(pfunc, pdata, addr, cnt);
//		if (err) {
//			printk("%s: FAIL(%d)! ADDR=%#x Size=%d\n", __func__, err, addr, cnt);
//		}
//	
//	_func_exit_;
//	
//		return err;
//	}
//	/*
//	 * Description:
//	 *	Read from RX FIFO
//	 *	Round read size to block size,
//	 *	and make sure data transfer will be done in one command.
//	 *
//	 * Parameters:
//	 *	func		a pointer of sdio func
//	 *	addr		port ID
//	 *	cnt			size to read
//	 *	rmem		address to put data
//	 *
//	 * Return:
//	 *	_SUCCESS(1)		Success
//	 *	_FAIL(0)		Fail
//	 */
//	
//	u32 sdio_read_port(
//	//	struct sdio_func *func,
//		PHAL_DATA_TYPE pHalData,
//		u32 addr,
//		u32 cnt,
//		u8 *mem)
//	{
//		s32 err;
//		struct sdio_func *func;
//		func = pHalData->func;
//		printk("%s(): addr is %d\n", __func__, addr);
//		printk("%s(): SDIORxFIFOCnt is %d\n", __func__, pHalData->SdioRxFIFOCnt);
//		HalSdioGetCmdAddr8195ASdio(func, addr, pHalData->SdioRxFIFOCnt++, &addr);
//	
//		printk("%s(): Get Cmd Addr is 0x%x\n", __func__, addr);
//	
//	
//		cnt = _RND4(cnt);
//		if (cnt > func->cur_blksize)
//			cnt = _RND(cnt, func->cur_blksize);
//		
//	//	cnt = sdio_align_size(cnt);
//	 	printk("%s(): cnt is %d\n", __func__, cnt);
//		err = _sd_read(func, addr, cnt, mem);
//		//err = sd_read(pintfhdl, addr, cnt, mem);
//		
//		if (err) return _FAIL;
//		return _SUCCESS;
//	}
//	
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
s32 _chris_sd_write(struct sdio_func *func, u32 addr, u32 cnt, void *pdata)
{
	
	struct sdio_func *pfunc;
	u32 size;
	s32 err=-EPERM;
	
_func_enter_;
	
	pfunc = func;
//	size = sdio_align_size(func, cnt);
	printk("%s()==> cnt is %d\n", __FUNCTION__, cnt);	
	if (unlikely((cnt==1) || (cnt==2)))
	{
		int i;
		u8 *pbuf = (u8*)pdata;
	
		for (i = 0; i < cnt; i++)
		{
//			sdio_writeb(pfunc, *(pbuf+i), addr+i, &err);
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
//	err = sdio_memcpy_toio(pfunc, addr, pdata, size);
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
s32 chris_sd_write(struct sdio_func *func, u32 addr, u32 cnt, void *pdata)
{
	struct sdio_func *pfunc;
//	bool claim_needed;
	s32 err=-EPERM;
_func_enter_;
	printk("%s()===========>\n", __FUNCTION__);	
	pfunc = func;
//	claim_needed = rtw_sdio_claim_host_needed(func);
printk("pfunc->cur_blksize=>%d\n", pfunc->cur_blksize);		
//	if (claim_needed)
//		sdio_claim_host(pfunc);
	err = _chris_sd_write(pfunc, addr, cnt, pdata);
//	if (claim_needed)
//		sdio_release_host(pfunc);
_func_exit_;
	return err;
}
//	
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
u32 chris_sdio_write_port(
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
	chris_HalSdioGetCmdAddr8195ASdio(pfunc, addr, cnt >> 2, &addr);
	printk("%s(): Get Cmd Addr is 0x%x\n", __func__, addr);
	
	if (cnt > pfunc->cur_blksize)
		cnt = _RND(cnt, pfunc->cur_blksize);
//	cnt = sdio_align_size(cnt);
	
	err = chris_sd_write(pfunc, addr, cnt, mem);
	
//	rtw_sctx_done_err(&xmitbuf->sctx,
//		err ? RTW_SCTX_DONE_WRITE_PORT_ERR : RTW_SCTX_DONE_SUCCESS);
	
	if (err)
	{
		printk("%s, error=%d\n", __func__, err);
		return _FAIL;
	}
	return _SUCCESS;
}
//	
//	/*
//	 * Todo: align address to 4 bytes.
//	 */
//	s32 sdio_local_read(
//		PHAL_DATA_TYPE pHalData,
//		u32		addr,
//		u32		cnt,
//		u8		*pbuf)
//	{
//		s32 err;
//		u8 *ptmpbuf;
//		u32 n;
//		struct sdio_func *pfunc;
//		pfunc=pHalData->func;
//		HalSdioGetCmdAddr8195ASdio(pfunc, SDIO_LOCAL_DEVICE_ID, addr, &addr);
//	
//	//		rtw_hal_get_hwreg(padapter, HW_VAR_APFM_ON_MAC, &bMacPwrCtrlOn);
//	//		if ((_FALSE == bMacPwrCtrlOn)
//	//	#ifdef CONFIG_LPS_LCLK
//	//			|| (_TRUE == adapter_to_pwrctl(padapter)->bFwCurrentInPSMode)
//	//	#endif
//	//			)
//	//		{
//	//			err = sd_cmd52_read(pintfhdl, addr, cnt, pbuf);
//	//			return err;
//	//		}
//		
//	       n = RND4(cnt);
//		ptmpbuf = (u8 *)rtw_malloc(n);
//		if(!ptmpbuf)
//			return (-1);
//		sdio_claim_host(pfunc);
//		err = _sd_read(pfunc, addr, n, ptmpbuf);
//		sdio_release_host(pfunc);
//		if (!err)
//			_rtw_memcpy(pbuf, ptmpbuf, cnt);
//	
//		if(ptmpbuf)
//			rtw_mfree(ptmpbuf, n);	
//	
//		return err;
//	}
//	/*
//	 * Todo: align address to 4 bytes.
//	 */
//	s32 _sdio_local_write(
//	//	PADAPTER	padapter,
//		PHAL_DATA_TYPE pHalData,
//		u32		addr,
//		u32		cnt,
//		u8		*pbuf)
//	{
//	//		struct intf_hdl * pintfhdl;
//	//		u8 bMacPwrCtrlOn;
//		s32 err;
//		u8 *ptmpbuf;
//		struct sdio_func *pfunc;
//		pfunc = pHalData->func;
//		if(addr & 0x3)
//			printk("%s, address must be 4 bytes alignment\n", __FUNCTION__);
//	
//		if(cnt  & 0x3)
//			printk("%s, size must be the multiple of 4 \n", __FUNCTION__);
//	
//	//	pintfhdl=&padapter->iopriv.intf;
//		
//		HalSdioGetCmdAddr8195ASdio(pfunc, SDIO_LOCAL_DEVICE_ID, addr, &addr);
//	
//	//		rtw_hal_get_hwreg(padapter, HW_VAR_APFM_ON_MAC, &bMacPwrCtrlOn);
//	//		if ((_FALSE == bMacPwrCtrlOn)
//	//	#ifdef CONFIG_LPS_LCLK
//	//	//		|| (_TRUE == adapter_to_pwrctl(padapter)->bFwCurrentInPSMode)
//	//	#endif
//	//			)
//	//		{
//	//			err = _sd_cmd52_write(pintfhdl, addr, cnt, pbuf);
//	//			return err;
//	//		}
//	
//	        ptmpbuf = (u8*)rtw_malloc(cnt);
//		if(!ptmpbuf)
//			return (-1);
//	
//		_rtw_memcpy(ptmpbuf, pbuf, cnt);
//	
//		err = _sd_write(pfunc, addr, cnt, ptmpbuf);
//		
//		if (ptmpbuf)
//			rtw_mfree(ptmpbuf, cnt);
//	
//		return err;
//	}

u8 _sdio_read8(PADAPTER padapter, u32 addr)
{
	struct intf_hdl * pintfhdl;
	u32 ftaddr;
	u8 val;

_func_enter_;

	//psdiodev = pintfhdl->pintf_dev;
	//psdio = &psdiodev->intf_data;

	pintfhdl=&padapter->iopriv.intf;
	
	ftaddr = _cvrt2ftaddr(addr, NULL, NULL);
	val = _sd_read8(pintfhdl, ftaddr, NULL);

_func_exit_;

	return val;
}

u8 sdio_read8(struct intf_hdl *pintfhdl, u32 addr)
{
	u32 ftaddr;
	u8 val;

_func_enter_;
	ftaddr = _cvrt2ftaddr(addr, NULL, NULL);
	val = sd_read8(pintfhdl, ftaddr, NULL);

_func_exit_;

	return val;
}

u16 sdio_read16(struct intf_hdl *pintfhdl, u32 addr)
{
	u32 ftaddr;
	u16 val;

_func_enter_;

	ftaddr = _cvrt2ftaddr(addr, NULL, NULL);
	sd_cmd52_read(pintfhdl, ftaddr, 2, (u8*)&val);	
	val = le16_to_cpu(val);

_func_exit_;

	return val;
}

u32 _sdio_read32(PADAPTER padapter, u32 addr)
{
	//PADAPTER padapter;

	struct intf_hdl * pintfhdl;
	u8 bMacPwrCtrlOn;
	u8 deviceId;
	u16 offset;
	u32 ftaddr;
	u8 shift;
	u32 val;
	s32 err;

_func_enter_;

	//padapter = pintfhdl->padapter;
	//psdiodev = pintfhdl->pintf_dev;
	pintfhdl=&padapter->iopriv.intf;
	
	ftaddr = _cvrt2ftaddr(addr, &deviceId, &offset);

//		rtw_hal_get_hwreg(padapter, HW_VAR_APFM_ON_MAC, &bMacPwrCtrlOn);
//		if (((deviceId == WLAN_IOREG_DEVICE_ID) && (offset < 0x100))
//			|| (_FALSE == bMacPwrCtrlOn)
//	#ifdef CONFIG_LPS_LCLK
//			|| (_TRUE == adapter_to_pwrctl(padapter)->bFwCurrentInPSMode)
//	#endif
//			)
//	        {
//			err = _sd_cmd52_read(pintfhdl, ftaddr, 4, (u8*)&val);
//	#ifdef SDIO_DEBUG_IO
//			if (!err) {
//	#endif
//				val = le32_to_cpu(val);
//				return val;
//	#ifdef SDIO_DEBUG_IO
//			}
//	
//			DBG_871X(KERN_ERR "%s: Mac Power off, Read FAIL(%d)! addr=0x%x\n", __func__, err, addr);
//			return SDIO_ERR_VAL32;
//	#endif
//		}

	// 4 bytes alignment
	shift = ftaddr & 0x3;
	if (shift == 0) {
		val = _sd_read32(pintfhdl, ftaddr, NULL);
	} else {
		u8 *ptmpbuf;

		ptmpbuf = (u8*)rtw_malloc(8);
		if (NULL == ptmpbuf) {
			DBG_871X(KERN_ERR "%s: Allocate memory FAIL!(size=8) addr=0x%x\n", __func__, addr);
			return SDIO_ERR_VAL32;
		}

		ftaddr &= ~(u16)0x3;
		_sd_read(pintfhdl, ftaddr, 8, ptmpbuf);
		_rtw_memcpy(&val, ptmpbuf+shift, 4);
		val = le32_to_cpu(val);

		rtw_mfree(ptmpbuf, 8);
	}

_func_exit_;

	return val;
}

u32 sdio_read32(struct intf_hdl *pintfhdl, u32 addr)
{
	PADAPTER padapter;
	u8 bMacPwrCtrlOn;
	u8 deviceId;
	u16 offset;
	u32 ftaddr;
	u8 shift;
	u32 val;
	s32 err;

_func_enter_;

	padapter = pintfhdl->padapter;

	ftaddr = _cvrt2ftaddr(addr, &deviceId, &offset);

//	        rtw_hal_get_hwreg(padapter, HW_VAR_APFM_ON_MAC, &bMacPwrCtrlOn);
//		if (((deviceId == WLAN_IOREG_DEVICE_ID) && (offset < 0x100))
//			|| (_FALSE == bMacPwrCtrlOn)
//	#ifdef CONFIG_LPS_LCLK
//			|| (_TRUE == adapter_to_pwrctl(padapter)->bFwCurrentInPSMode)
//	#endif
//			)
//	        {
//			err = sd_cmd52_read(pintfhdl, ftaddr, 4, (u8*)&val);
//	#ifdef SDIO_DEBUG_IO
//			if (!err) {
//	#endif
//				val = le32_to_cpu(val);
//				return val;
//	#ifdef SDIO_DEBUG_IO
//			}
//	
//			DBG_871X(KERN_ERR "%s: Mac Power off, Read FAIL(%d)! addr=0x%x\n", __func__, err, addr);
//			return SDIO_ERR_VAL32;
//	#endif
//		}

	// 4 bytes alignment
	shift = ftaddr & 0x3;
	if (shift == 0) {
		val = sd_read32(pintfhdl, ftaddr, NULL);
	} else {
		u8 *ptmpbuf;
				
		ptmpbuf = (u8*)rtw_malloc(8);
		if (NULL == ptmpbuf) {
			DBG_871X(KERN_ERR "%s: Allocate memory FAIL!(size=8) addr=0x%x\n", __func__, addr);
			return SDIO_ERR_VAL32;
		}

		ftaddr &= ~(u16)0x3;
		sd_read(pintfhdl, ftaddr, 8, ptmpbuf);
		_rtw_memcpy(&val, ptmpbuf+shift, 4);
		val = le32_to_cpu(val);

		rtw_mfree(ptmpbuf, 8);
	}

_func_exit_;

	return val;
}

s32 sdio_readN(struct intf_hdl *pintfhdl, u32 addr, u32 cnt, u8* pbuf)
{
	PADAPTER padapter;
	u8 bMacPwrCtrlOn;
	u8 deviceId;
	u16 offset;
	u32 ftaddr;
	u8 shift;
	s32 err;

_func_enter_;

	padapter = pintfhdl->padapter;
	err = 0;

	ftaddr = _cvrt2ftaddr(addr, &deviceId, &offset);

//		rtw_hal_get_hwreg(padapter, HW_VAR_APFM_ON_MAC, &bMacPwrCtrlOn);
//		if (((deviceId == WLAN_IOREG_DEVICE_ID) && (offset < 0x100))
//			|| (_FALSE == bMacPwrCtrlOn)
//	#ifdef CONFIG_LPS_LCLK
//			|| (_TRUE == adapter_to_pwrctl(padapter)->bFwCurrentInPSMode)
//	#endif
//			)
//		{
//			err = sd_cmd52_read(pintfhdl, ftaddr, cnt, pbuf);
//			return err;
//		}

	// 4 bytes alignment
	shift = ftaddr & 0x3;
	if (shift == 0) {
		err = sd_read(pintfhdl, ftaddr, cnt, pbuf);
	} else {
		u8 *ptmpbuf;
		u32 n;

		ftaddr &= ~(u16)0x3;
		n = cnt + shift;
		ptmpbuf = rtw_malloc(n);
		if (NULL == ptmpbuf) return -1;
		err = sd_read(pintfhdl, ftaddr, n, ptmpbuf);
		if (!err)
			_rtw_memcpy(pbuf, ptmpbuf+shift, cnt);
		rtw_mfree(ptmpbuf, n);
	}

_func_exit_;

	return err;
}

s32 sdio_write8(struct intf_hdl *pintfhdl, u32 addr, u8 val)
{
	u32 ftaddr;
	s32 err;

_func_enter_;
	ftaddr = _cvrt2ftaddr(addr, NULL, NULL);
	sd_write8(pintfhdl, ftaddr, val, &err);

_func_exit_;

	return err;
}

s32 sdio_write16(struct intf_hdl *pintfhdl, u32 addr, u16 val)
{
	u32 ftaddr;
	u8 shift;
	s32 err;

_func_enter_;

	ftaddr = _cvrt2ftaddr(addr, NULL, NULL);
	val = cpu_to_le16(val);
	err = sd_cmd52_write(pintfhdl, ftaddr, 2, (u8*)&val);

_func_exit_;

	return err;
}

s32 _sdio_write32(PADAPTER padapter, u32 addr, u32 val)
{
	//PADAPTER padapter;
	struct intf_hdl * pintfhdl;
	u8 bMacPwrCtrlOn;
	u8 deviceId;
	u16 offset;
	u32 ftaddr;
	u8 shift;
	s32 err;

_func_enter_;

	//padapter = pintfhdl->padapter;
	//psdiodev = pintfhdl->pintf_dev;
	pintfhdl=&padapter->iopriv.intf;
	err = 0;

	ftaddr = _cvrt2ftaddr(addr, &deviceId, &offset);

//		rtw_hal_get_hwreg(padapter, HW_VAR_APFM_ON_MAC, &bMacPwrCtrlOn);
//		if (((deviceId == WLAN_IOREG_DEVICE_ID) && (offset < 0x100))
//			|| (_FALSE == bMacPwrCtrlOn)
//	#ifdef CONFIG_LPS_LCLK
//			|| (_TRUE == adapter_to_pwrctl(padapter)->bFwCurrentInPSMode)
//	#endif
//			)
//		{
//			val = cpu_to_le32(val);
//			err = _sd_cmd52_write(pintfhdl, ftaddr, 4, (u8*)&val);
//			return err;
//		}

	// 4 bytes alignment
	shift = ftaddr & 0x3;
#if 1
	if (shift == 0)
	{
		_sd_write32(pintfhdl, ftaddr, val, &err);
	}
	else
	{
		val = cpu_to_le32(val);
		err = _sd_cmd52_write(pintfhdl, ftaddr, 4, (u8*)&val);
	}
#else
	if (shift == 0) {
		sd_write32(pintfhdl, ftaddr, val, &err);
	} else {
		u8 *ptmpbuf;

		ptmpbuf = (u8*)rtw_malloc(8);
		if (NULL == ptmpbuf) return (-1);

		ftaddr &= ~(u16)0x3;
		err = sd_read(pintfhdl, ftaddr, 8, ptmpbuf);
		if (err) {
			rtw_mfree(ptmpbuf, 8);
			return err;
		}
		val = cpu_to_le32(val);
		_rtw_memcpy(ptmpbuf+shift, &val, 4);
		err = sd_write(pintfhdl, ftaddr, 8, ptmpbuf);

		rtw_mfree(ptmpbuf, 8);
	}
#endif

_func_exit_;

	return err;
}


s32 sdio_write32(struct intf_hdl *pintfhdl, u32 addr, u32 val)
{
	PADAPTER padapter;
	u8 bMacPwrCtrlOn;
	u8 deviceId;
	u16 offset;
	u32 ftaddr;
	u8 shift;
	s32 err;

_func_enter_;

	padapter = pintfhdl->padapter;
	err = 0;

	ftaddr = _cvrt2ftaddr(addr, &deviceId, &offset);

//		rtw_hal_get_hwreg(padapter, HW_VAR_APFM_ON_MAC, &bMacPwrCtrlOn);
//		if (((deviceId == WLAN_IOREG_DEVICE_ID) && (offset < 0x100))
//			|| (_FALSE == bMacPwrCtrlOn)
//	#ifdef CONFIG_LPS_LCLK
//			|| (_TRUE == adapter_to_pwrctl(padapter)->bFwCurrentInPSMode)
//	#endif
//			)
//		{
//			val = cpu_to_le32(val);
//			err = sd_cmd52_write(pintfhdl, ftaddr, 4, (u8*)&val);
//			return err;
//		}

	// 4 bytes alignment
	shift = ftaddr & 0x3;
#if 1
	if (shift == 0)
	{
		sd_write32(pintfhdl, ftaddr, val, &err);
	}
	else
	{
		val = cpu_to_le32(val);
		err = sd_cmd52_write(pintfhdl, ftaddr, 4, (u8*)&val);
	}
#else
	if (shift == 0) {	
		sd_write32(pintfhdl, ftaddr, val, &err);
	} else {
		u8 *ptmpbuf;

		ptmpbuf = (u8*)rtw_malloc(8);
		if (NULL == ptmpbuf) return (-1);

		ftaddr &= ~(u16)0x3;
		err = sd_read(pintfhdl, ftaddr, 8, ptmpbuf);
		if (err) {
			rtw_mfree(ptmpbuf, 8);
			return err;
		}
		val = cpu_to_le32(val);
		_rtw_memcpy(ptmpbuf+shift, &val, 4);
		err = sd_write(pintfhdl, ftaddr, 8, ptmpbuf);
		
		rtw_mfree(ptmpbuf, 8);
	}
#endif	

_func_exit_;

	return err;
}

s32 sdio_writeN(struct intf_hdl *pintfhdl, u32 addr, u32 cnt, u8* pbuf)
{
	PADAPTER padapter;
	u8 bMacPwrCtrlOn;
	u8 deviceId;
	u16 offset;
	u32 ftaddr;
	u8 shift;
	s32 err;

_func_enter_;

	padapter = pintfhdl->padapter;
	err = 0;

	ftaddr = _cvrt2ftaddr(addr, &deviceId, &offset);

//		rtw_hal_get_hwreg(padapter, HW_VAR_APFM_ON_MAC, &bMacPwrCtrlOn);
//		if (((deviceId == WLAN_IOREG_DEVICE_ID) && (offset < 0x100))
//			|| (_FALSE == bMacPwrCtrlOn)
//	#ifdef CONFIG_LPS_LCLK
//			|| (_TRUE == adapter_to_pwrctl(padapter)->bFwCurrentInPSMode)
//	#endif
//			)
//		{
//			err = sd_cmd52_write(pintfhdl, ftaddr, cnt, pbuf);
//			return err;
//		}

	shift = ftaddr & 0x3;
	if (shift == 0) {
		err = sd_write(pintfhdl, ftaddr, cnt, pbuf);
	} else {
		u8 *ptmpbuf;
		u32 n;

		ftaddr &= ~(u16)0x3;
		n = cnt + shift;
		ptmpbuf = rtw_malloc(n);
		if (NULL == ptmpbuf) return -1;
		err = sd_read(pintfhdl, ftaddr, 4, ptmpbuf);
		if (err) {
			rtw_mfree(ptmpbuf, n);
			return err;
		}
		_rtw_memcpy(ptmpbuf+shift, pbuf, cnt);
		err = sd_write(pintfhdl, ftaddr, n, ptmpbuf);
		rtw_mfree(ptmpbuf, n);
	}

_func_exit_;

	return err;
}

u8 sdio_f0_read8(struct intf_hdl *pintfhdl, u32 addr)
{
	u32 ftaddr;
	u8 val;

_func_enter_;
	val = sd_f0_read8(pintfhdl, addr, NULL);

_func_exit_;

	return val;
}

void sdio_read_mem(struct intf_hdl *pintfhdl, u32 addr, u32 cnt, u8 *rmem)
{
	s32 err;

_func_enter_;

	err = sdio_readN(pintfhdl, addr, cnt, rmem);

_func_exit_;
}

void sdio_write_mem(struct intf_hdl *pintfhdl, u32 addr, u32 cnt, u8 *wmem)
{
_func_enter_;

	sdio_writeN(pintfhdl, addr, cnt, wmem);

_func_exit_;
}

/*
 * Description:
 *	Read from RX FIFO
 *	Round read size to block size,
 *	and make sure data transfer will be done in one command.
 *
 * Parameters:
 *	pintfhdl	a pointer of intf_hdl
 *	addr		port ID
 *	cnt			size to read
 *	rmem		address to put data
 *
 * Return:
 *	_SUCCESS(1)		Success
 *	_FAIL(0)		Fail
 */
static u32 sdio_read_port(
	struct intf_hdl *pintfhdl,
	u32 addr,
	u32 cnt,
	u8 *mem)
{
	PADAPTER padapter = pintfhdl->padapter;
	PSDIO_DATA psdio= &adapter_to_dvobj(padapter)->intf_data;
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);
	s32 err;

	HalSdioGetCmdAddr8195ASdio(padapter, addr, pHalData->SdioRxFIFOCnt++, &addr);


	cnt = _RND4(cnt);
	if (cnt > psdio->block_transfer_len)
		cnt = _RND(cnt, psdio->block_transfer_len);
	
//	cnt = sdio_align_size(cnt);

	err = _sd_read(pintfhdl, addr, cnt, mem);
	//err = sd_read(pintfhdl, addr, cnt, mem);
	


	if (err) return _FAIL;
	return _SUCCESS;
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
	struct intf_hdl *pintfhdl,
	u32 addr,
	u32 cnt,
	u8 *mem)
{
	PADAPTER padapter;
	PSDIO_DATA psdio;
	s32 err;
	struct xmit_buf *xmitbuf = (struct xmit_buf *)mem;
	u8 *pdata = mem;
	DBG_871X("%s()====>\n", __func__);
	padapter = pintfhdl->padapter;
	psdio = &adapter_to_dvobj(padapter)->intf_data;
		
		if (padapter->hw_init_completed == _FALSE) {
			DBG_871X("%s [addr=0x%x cnt=%d] padapter->hw_init_completed == _FALSE\n",__func__,addr,cnt);
			return _FAIL;
		}
	
	cnt = _RND4(cnt);
	HalSdioGetCmdAddr8195ASdio(padapter, addr, cnt >> 2, &addr);
//	HalSdioGetCmdAddr8195ASdio(NULL, addr, cnt >> 2, &addr);	
	if (cnt > psdio->block_transfer_len)
		cnt = _RND(cnt, psdio->block_transfer_len);
	//cnt = sdio_align_size(cnt);

	err = sd_write(pintfhdl, addr, cnt, xmitbuf->pdata);
//	err = sd_write(pintfhdl, addr, cnt, pdata);
//	rtw_sctx_done_err(&xmitbuf->sctx,
//		err ? RTW_SCTX_DONE_WRITE_PORT_ERR : RTW_SCTX_DONE_SUCCESS);
	
	if (err)
	{
		DBG_871X("%s, error=%d\n", __func__, err);

		return _FAIL;
	}
	return _SUCCESS;
}


void sdio_set_intf_ops(_adapter *padapter,struct _io_ops *pops)
{
_func_enter_;

	pops->_read8 = &sdio_read8;
	pops->_read16 = &sdio_read16;
	pops->_read32 = &sdio_read32;
	pops->_read_mem = &sdio_read_mem;
	pops->_read_port = &sdio_read_port;

	pops->_write8 = &sdio_write8;
	pops->_write16 = &sdio_write16;
	pops->_write32 = &sdio_write32;
	pops->_writeN = &sdio_writeN;
	pops->_write_mem = &sdio_write_mem;
	pops->_write_port = &sdio_write_port;

	pops->_sd_f0_read8 = sdio_f0_read8;

_func_exit_;
}
/*
 * Todo: align address to 4 bytes.
 */
s32 _sdio_local_read(
	PADAPTER	padapter,
	u32		addr,
	u32		cnt,
	u8		*pbuf)
{
	struct intf_hdl * pintfhdl;
	u8 bMacPwrCtrlOn;
	s32 err;
	u8 *ptmpbuf;
	u32 n;

	pintfhdl=&padapter->iopriv.intf;
	
	HalSdioGetCmdAddr8195ASdio(padapter, SDIO_LOCAL_DEVICE_ID, addr, &addr);

//		rtw_hal_get_hwreg(padapter, HW_VAR_APFM_ON_MAC, &bMacPwrCtrlOn);
//		if ((_FALSE == bMacPwrCtrlOn)
//	#ifdef CONFIG_LPS_LCLK
//	//		|| (_TRUE == adapter_to_pwrctl(padapter)->bFwCurrentInPSMode)
//	#endif
//			)
//		{
//			err = _sd_cmd52_read(pintfhdl, addr, cnt, pbuf);
//			return err;
//		}

        n = RND4(cnt);
	ptmpbuf = (u8*)rtw_malloc(n);
	if(!ptmpbuf)
		return (-1);

	err = _sd_read(pintfhdl, addr, n, ptmpbuf);
	if (!err)
		_rtw_memcpy(pbuf, ptmpbuf, cnt);

	if(ptmpbuf)
		rtw_mfree(ptmpbuf, n);	

	return err;
}

/*
 * Todo: align address to 4 bytes.
 */
s32 sdio_local_read(
	PADAPTER	padapter,
	u32		addr,
	u32		cnt,
	u8		*pbuf)
{
	struct intf_hdl * pintfhdl;
	u8 bMacPwrCtrlOn;
	s32 err;
	u8 *ptmpbuf;
	u32 n;

	pintfhdl=&padapter->iopriv.intf;
	
	HalSdioGetCmdAddr8195ASdio(padapter, SDIO_LOCAL_DEVICE_ID, addr, &addr);

//		rtw_hal_get_hwreg(padapter, HW_VAR_APFM_ON_MAC, &bMacPwrCtrlOn);
//		if ((_FALSE == bMacPwrCtrlOn)
//	#ifdef CONFIG_LPS_LCLK
//			|| (_TRUE == adapter_to_pwrctl(padapter)->bFwCurrentInPSMode)
//	#endif
//			)
//		{
//			err = sd_cmd52_read(pintfhdl, addr, cnt, pbuf);
//			return err;
//		}

        n = RND4(cnt);
	ptmpbuf = (u8*)rtw_malloc(n);
	if(!ptmpbuf)
		return (-1);

	err = sd_read(pintfhdl, addr, n, ptmpbuf);
	if (!err)
		_rtw_memcpy(pbuf, ptmpbuf, cnt);

	if(ptmpbuf)
		rtw_mfree(ptmpbuf, n);	

	return err;
}

/*
 * Todo: align address to 4 bytes.
 */
s32 _sdio_local_write(
	PADAPTER	padapter,
	u32		addr,
	u32		cnt,
	u8		*pbuf)
{
	struct intf_hdl * pintfhdl;
	u8 bMacPwrCtrlOn;
	s32 err;
	u8 *ptmpbuf;

	if(addr & 0x3)
		DBG_8192C("%s, address must be 4 bytes alignment\n", __FUNCTION__);

	if(cnt  & 0x3)
		DBG_8192C("%s, size must be the multiple of 4 \n", __FUNCTION__);

	pintfhdl=&padapter->iopriv.intf;
	
	HalSdioGetCmdAddr8195ASdio(padapter, SDIO_LOCAL_DEVICE_ID, addr, &addr);

//		rtw_hal_get_hwreg(padapter, HW_VAR_APFM_ON_MAC, &bMacPwrCtrlOn);
//		if ((_FALSE == bMacPwrCtrlOn)
//	#ifdef CONFIG_LPS_LCLK
//	//		|| (_TRUE == adapter_to_pwrctl(padapter)->bFwCurrentInPSMode)
//	#endif
//			)
//		{
//			err = _sd_cmd52_write(pintfhdl, addr, cnt, pbuf);
//			return err;
//		}

        ptmpbuf = (u8*)rtw_malloc(cnt);
	if(!ptmpbuf)
		return (-1);

	_rtw_memcpy(ptmpbuf, pbuf, cnt);

	err = _sd_write(pintfhdl, addr, cnt, ptmpbuf);
	
	if (ptmpbuf)
		rtw_mfree(ptmpbuf, cnt);

	return err;
}

/*
 * Todo: align address to 4 bytes.
 */
s32 sdio_local_write(
	PADAPTER	padapter,
	u32		addr,
	u32		cnt,
	u8		*pbuf)
{

	struct intf_hdl * pintfhdl;
	u8 bMacPwrCtrlOn;
	s32 err;
	u8 *ptmpbuf;

	if(addr & 0x3)
		DBG_8192C("%s, address must be 4 bytes alignment\n", __FUNCTION__);

	if(cnt  & 0x3)
		DBG_8192C("%s, size must be the multiple of 4 \n", __FUNCTION__);

	pintfhdl=&padapter->iopriv.intf;
	HalSdioGetCmdAddr8195ASdio(padapter, SDIO_LOCAL_DEVICE_ID, addr, &addr);

//		rtw_hal_get_hwreg(padapter, HW_VAR_APFM_ON_MAC, &bMacPwrCtrlOn);
//		if ((_FALSE == bMacPwrCtrlOn)
//	#ifdef CONFIG_LPS_LCLK
//			|| (_TRUE == adapter_to_pwrctl(padapter)->bFwCurrentInPSMode)
//	#endif
//			)
//		{
//			err = sd_cmd52_write(pintfhdl, addr, cnt, pbuf);
//			return err;
//		}

        ptmpbuf = (u8*)rtw_malloc(cnt);
	if(!ptmpbuf)
		return (-1);

	_rtw_memcpy(ptmpbuf, pbuf, cnt);

	err = sd_write(pintfhdl, addr, cnt, ptmpbuf);

	if (ptmpbuf)
		rtw_mfree(ptmpbuf, cnt);

	return err;
}

void sd_int_dpc(PHAL_DATA_TYPE pHalData)
{
	if (pHalData->sdio_hisr & SDIO_HISR_RX_REQUEST)
	{
//		struct recv_buf *precvbuf;

		//DBG_8192C("%s: RX Request, size=%d\n", __func__, phal->SdioRxFIFOSize);
		pHalData->sdio_hisr ^= SDIO_HISR_RX_REQUEST;
//	#ifdef CONFIG_MAC_LOOPBACK_DRIVER
//			sd_recv_loopback(padapter, pHalData->SdioRxFIFOSize);
//	#else
		do {
			//Sometimes rx length will be zero. driver need to use cmd53 read again.
			if(pHalData->SdioRxFIFOSize == 0)
			{
				u8 data[4];

				sdio_local_read(pHalData, SDIO_RX0_REQ_LEN, 4, data);

				pHalData->SdioRxFIFOSize = le16_to_cpu(*(u16*)data);
			}

			if(pHalData->SdioRxFIFOSize)
			{
//				precvbuf = sd_recv_rxfifo(padapter, pHalData->SdioRxFIFOSize);

				pHalData->SdioRxFIFOSize = 0;

//				if (precvbuf)
//					sd_rxhandler(padapter, precvbuf);
//				else
//					break;
			}
			else
				break;

		} while (1);

	}
}
//	void sd_int_hal(PHAL_DATA_TYPE pHalData)
//	{
//		u8 data[4];
//	
//		sdio_local_read(pHalData, SDIO_HISR, 4, data);
//		pHalData->sdio_hisr = le32_to_cpu(*(u32*)data);
//		pHalData->SdioRxFIFOSize = le16_to_cpu(*(u16*)&data[4]);
//	
//		if (pHalData->sdio_hisr & pHalData->sdio_himr)
//		{
//			u32 v32;
//	
//			pHalData->sdio_hisr &= pHalData->sdio_himr;
//	
//			// clear HISR
//			v32 = pHalData->sdio_hisr & MASK_SDIO_HISR_CLEAR;
//			if (v32) {
//				v32 = cpu_to_le32(v32);
//				_sdio_local_write(pHalData, SDIO_HISR, 4, (u8*)&v32);
//			}
//	
//			sd_int_dpc(pHalData);
//			
//		} 
//		else 
//		{
//			printk("%s: HISR(0x%08x) and HIMR(0x%08x) not match!\n",
//					__FUNCTION__, pHalData->sdio_hisr, pHalData->sdio_himr);
//		}	
//	}
void sd_int_hdl(PADAPTER padapter)
{
	u8 data[6];
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);
	if ((padapter->bDriverStopped == _TRUE) ||
	    (padapter->bSurpriseRemoved == _TRUE))
		return;

	_sdio_local_read(padapter, SDIO_HISR, 6, data);
	pHalData->sdio_hisr = le32_to_cpu(*(u32*)data);
	pHalData->SdioRxFIFOSize = le16_to_cpu(*(u16*)&data[4]);

	if (pHalData->sdio_hisr & pHalData->sdio_himr)
	{
		u32 v32;

		pHalData->sdio_hisr &= pHalData->sdio_himr;

		// clear HISR
		v32 = pHalData->sdio_hisr & MASK_SDIO_HISR_CLEAR;
		if (v32) {
			v32 = cpu_to_le32(v32);
			_sdio_local_write(padapter, SDIO_HISR, 4, (u8*)&v32);
		}

//		sd_int_dpc(padapter);
		
	} 
	else 
	{
		RT_TRACE(_module_hci_ops_c_, _drv_err_,
				("%s: HISR(0x%08x) and HIMR(0x%08x) not match!\n",
				__FUNCTION__, pHalData->sdio_hisr, pHalData->sdio_himr));
	}
	
}

