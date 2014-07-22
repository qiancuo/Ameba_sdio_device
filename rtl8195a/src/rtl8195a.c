#include <linux/module.h>
#include <linux/version.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/delay.h>
#include <linux/ethtool.h>
#include <linux/mii.h>
#include <linux/if_vlan.h>
#include <linux/crc32.h>
#include <linux/interrupt.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/init.h>
#include <linux/rtnetlink.h>
#include <linux/fs.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)
#define dev_printk(A,B,fmt,args...) printk(A fmt,##args)
#else
#include <linux/dma-mapping.h>
#include <linux/moduleparam.h>
#endif

#include <asm/io.h>
#include <asm/irq.h>
#include <asm/uaccess.h>

#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/errno.h>

#include "include/rtl8195a.h"
#include "include/basic_types.h"
#include "include/drv_types.h"
#include "include/rtw_debug.h"
#include "include/osdep_service_linux.h"
#include "include/osdep_service.h"
#include "include/sdio_ops.h"
#include "include/8195_desc.h"
#include "include/8195_sdio_reg.h"
#include "include/drv_types_sdio.h"
#include "include/osdep_intf.h"
#include "include/xmit_osdep.h"
#include "include/rtw_proc.h"
//	MODULE_LICENSE("GPL");
//	MODULE_DESCRIPTION("Realtek Wireless Lan Driver");
//	MODULE_AUTHOR("Realtek Semiconductor Corp.");
//	MODULE_VERSION(DRIVERVERSION);
MODULE_AUTHOR("Realtek");
MODULE_DESCRIPTION("RealTek RTL-8195a iNIC");
MODULE_LICENSE("GPL");
MODULE_VERSION(RTL8195_VERSION);

typedef struct _AT_CMD_DESC{
//DWORD 0
unsigned int pktsize: 16; //=tx_desc.pktsize - cmd_desc.offset
unsigned int offset: 8; //cmd header size
unsigned int resv: 7;
unsigned int datatype: 1; // only one bit used, 0: data frame 1: management frame
//DWORD 1
//unsigned char cmdtype[2]; //to call which API
//unsigned int resv: 16;
}AT_CMD_DESC, *PAT_CMD_DESC;

CHRIS_XMIT_BUF chris_xmit_buf_pool[20];
_list chris_buf_list;
#define Message_Recv		"Here is Recv action!"
#define Message_Xmit			"Here is Xmit action!"
#ifndef SLEEP_MILLI_SEC
#define SLEEP_MILLI_SEC(nMilliSec) \
	do{\
		long timeout = (nMilliSec) * HZ/1000;\
		while(timeout > 0) \
			{\
			timeout = schedule_timeout(timeout);\
			}\
	}while(0);
#endif
static struct task_struct *Xmit_Thread = NULL;
static struct task_struct *Recv_Thread = NULL;
PHAL_DATA_TYPE gHal_Data = NULL;
static _mutex Recv_Xmit_mutex;
static int major = 250;
static unsigned char g_SDIO_cmdData[2048] = {0};//2048
static int Print_Message(u8 *message);
static int RecvOnePkt(struct sdio_func * func);
static int SendOnePkt(struct sdio_func * func);
//	static void init_chris_Buf_Pool(void){	
//		int i;	
//		memset(chris_xmit_buf_pool, '\0', sizeof(chris_xmit_buf_pool));	
//		_rtw_init_listhead(&chris_buf_list);		
//		for (i=0; i<20; i++) {				
//			_rtw_init_listhead(&chris_xmit_buf_pool[i].list);		
//			rtw_list_insert_tail(&chris_xmit_buf_pool[i].list, &chris_buf_list);	
//			}	
//	}
static TX_DESC TxDescGen(u16 pktsize, u16 seqNum)
{
	TX_DESC txdesc;
//DWORD 0
	txdesc.txpktsize = pktsize;

	txdesc.offset = 0x20;

	txdesc.bmc = 1;
	txdesc.htc = 0;
	txdesc.ls = 1;
	txdesc.fs = 1;
	txdesc.linip = 0;
	txdesc.noacm = 0;
	txdesc.gf = 0;
	txdesc.own = 1;

//DWORD 1
	txdesc.macid = 0;
	txdesc.agg_en = 0;
	txdesc.bk = 0;
	txdesc.rdg_en = 0;

	txdesc.qsel = 6;
	txdesc.rdg_nav_ext = 0;
	txdesc.lsig_txop_en = 0;
	txdesc.pifs = 0;

	txdesc.rate_id = 0;
	txdesc.navusehdr = 0;
	txdesc.en_desc_id = 1;
	txdesc.sectype = 0;

	txdesc.rsvd2 = 0;
	txdesc.pkt_offset = 0;
	txdesc.rsvd3 = 0;

//DWORD 2
	txdesc.rts_rc = 0;
	txdesc.data_rc = 0;
	txdesc.rsvd8 = 0;
	txdesc.bar_rty_th = 0;

	txdesc.rsvd4 = 0;
	txdesc.morefrag = 0;
	txdesc.raw = 0;
	txdesc.ccx = 0;
	txdesc.ampdu_density = 7;
	txdesc.rsvd5 = 0;

	txdesc.antsel_a = 0;
	txdesc.antsel_b =0;
	txdesc.tx_ant_cck = 0;
	txdesc.tx_antl = 0;
	txdesc.tx_antht = 0;

//DWORD 3
	txdesc.nextheadpage = 0;
	txdesc.tailpage = 0;
	txdesc.seq = seqNum;
	txdesc.pkt_id = 0;

//DWORD 4
	txdesc.rtsrate = 3;
	txdesc.ap_dcfe = 0;
	txdesc.qos =1;
	txdesc.hwseq_en =0;

	txdesc.userate = 1;
	txdesc.disrtsfb =1;
	txdesc.disdatafb =1;
	txdesc.cts2self =0;
	txdesc.rtsen =0;
	txdesc.hw_rts_en = 0;
	txdesc.port_toggle =0;
	txdesc.rsvd6 =0;

	txdesc.rsvd7 =0;
	txdesc.wait_dcts =0;
	txdesc.cts2ap_en=0;
	txdesc.data_txsc=0;

	txdesc.data_short =0;
	txdesc.databw =0;
	txdesc.rts_short =0;
	txdesc.rtsbw =0;
	txdesc.rts_sc =0;
	txdesc.vcs_stbc=0;

//DWORD 5
	txdesc.datarate = 0;

	txdesc.data_ratefb_lmt =0;
	txdesc.rts_ratefb_lmt =0;
	txdesc.rty_en =0;
	txdesc.data_rt_lmt =0;

	txdesc.usb_txagg_num=0;

//DWORD 6
	txdesc.txagc_a = 0;
	txdesc.txagc_b =0;
	txdesc.use_max_len =0;
	txdesc.max_agg_num = 0xf;

	txdesc.mcsg1_max_len = 8;
	txdesc.mcsg2_max_len =8;

	txdesc.mcsg3_max_len = 8;
	txdesc.mcsg7_max_len =8;

//DWORD 7
	txdesc.txbuffsize = 0x7da0;

	txdesc.mcsg4_max_len =0;
	txdesc.mcsg5_max_len =0;
	txdesc.mcsg6_max_len =0;
	txdesc.mcsg15_max_len =0;

	return txdesc;
	
}

static int SendWlanCmdPkt(PAT_CMD_DESC pWlan_cmd)
{
	int i, len, totlen;
	struct sdio_func *pfunc;	
	TX_DESC txdesc;
	len = pWlan_cmd->pktsize+pWlan_cmd->offset;
	totlen = len + sizeof(TX_DESC);
	u8 data[totlen];	
	printk("pWlan_cmd->pktsize = %d\n\r", pWlan_cmd->pktsize);
	printk("pWlan_cmd->offset = %d\n\r", pWlan_cmd->offset);
	printk("pWlan_cmd->datatype = %d\n\r", pWlan_cmd->datatype);
	memset(data, 0, sizeof(data));
	txdesc = TxDescGen(len, 1);
	memcpy(data, &txdesc, txdesc.offset);
	memcpy((data+sizeof(TX_DESC)), g_SDIO_cmdData, len);

//		for(i=0;i<totlen;i++)
//		{
//			printk("data[%d] = 0x%02x\n", i, data[i]);
//		}

	chris_sdio_write_port(gHal_Data->func, WLAN_TX_HIQ_DEVICE_ID, totlen, data);
	return 0;	
}

static int RecvWlanCmdPkt(PAT_CMD_DESC pWlan_cmd, u16 *pLen)
{
	int res, i=0;
	u32 tmp;
	u16 len = 0;
	u8 *pBuf;
	struct sdio_func *pfunc;
	PRX_DESC pRxDesc;
	pfunc = gHal_Data->func;
	memset(g_SDIO_cmdData, 0, sizeof(g_SDIO_cmdData)); 
	do{
//	len = sdio_local_read(gHal_Data, SDIO_RX0_REQ_LEN, 4, (u8 *)&tmp);
	len = le16_to_cpu(tmp);
	if((++i)>1000)
		break;
	}while(len<=0);
	printk("Rx len is %d\n", len);
	if(len>0)
	{
		pBuf = kmalloc(len, GFP_KERNEL);
	sdio_claim_host(pfunc);
//		res = sdio_read_port(gHal_Data, WLAN_RX0FF_DEVICE_ID, len, pBuf);
	sdio_release_host(pfunc);
		if (res == _FAIL)
		{	
			printk("sdio read port failed!\n");
			return res;
		}
		pRxDesc = (PRX_DESC)pBuf;	
		printk("pRxDesc->pkt_len + sizeof(RX_DESC) = %d\n", pRxDesc->pkt_len+sizeof(RX_DESC));
//			for(i=0;i<(pRxDesc->pkt_len+sizeof(RX_DESC));i++)
//			{
//				printk("Rx[%d] = 0x%02x\n", i, *(pBuf+i));
//			}
		memcpy(g_SDIO_cmdData, pBuf+sizeof(RX_DESC), pRxDesc->pkt_len);
		*pLen = pRxDesc->pkt_len;	
//			printk("RX Desc: \n");
//			DumpForOneBytes ((u8*)pRxDesc, sizeof(RX_DESC));
//			printk("RX Payload: \n");
//			DumpForOneBytes ((u8*)(pBuf+sizeof(RX_DESC)), pRxDesc->pkt_len);		
		kfree(pBuf);
	}
	return 0;
}
static ssize_t myFunc_Read(struct file *file, char *buf, size_t count, loff_t *ppos)
{
	PAT_CMD_DESC pWlan_cmd;
	u16 len =0;
	printk(KERN_DEBUG "%s():\n", __FUNCTION__);
	RecvWlanCmdPkt(NULL, &len);
	printk("copy_to_user: len is %d\n", len);
	if (copy_to_user(buf, g_SDIO_cmdData, sizeof(g_SDIO_cmdData)))
	{	
		printk("copy_to_user failed!\n");
		return -EFAULT;
	}
	return 0;
}

static ssize_t myFunc_Write(struct file *file, const char *buf, size_t count, loff_t *ppos)
{
	PAT_CMD_DESC pwlan_cmd;
	printk(KERN_DEBUG "%s():\n", __FUNCTION__);
	memset(g_SDIO_cmdData, 0, sizeof(g_SDIO_cmdData)); 

	if(copy_from_user(g_SDIO_cmdData,buf,sizeof(g_SDIO_cmdData)))
	 {
		 printk(KERN_DEBUG "copy from user failed!\n"); 
		 return -EFAULT;
	  }
//		
		pwlan_cmd = (PAT_CMD_DESC)g_SDIO_cmdData;
//		if(pwlan_cmd->datatype == 1)
//		{
			SendWlanCmdPkt(pwlan_cmd);
//	}
//		else if(pwlan_cmd->datatype == 0)
//		{
//			SendOnePkt(gHal_Data->func);
//		}
	return 0;
}

static ssize_t myFunc_Open(struct inode *inode, struct file *file)
{
	printk(KERN_DEBUG "%s():\n", __FUNCTION__);
	if(gHal_Data == NULL)
	{
		 printk(KERN_DEBUG "SDIO Init havn't finished!\n"); 
		 return -EFAULT;
	}
	return 0;
}

static ssize_t myFunc_Close(struct inode *inode, struct file *file)
{ 	
	printk(KERN_DEBUG "%s():\n", __FUNCTION__);
	return 0;
}

static long myFunc_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	printk(KERN_DEBUG "%s():\n", __FUNCTION__);
	return 0;
}

static int RecvOnePkt_Thread(void * pData)
{
	struct sdio_func *pfunc;
	PHAL_DATA_TYPE pHal_Data;
	pHal_Data = (PHAL_DATA_TYPE) pData;
	pfunc = pHal_Data->func;	
	while(!kthread_should_stop()){
		SLEEP_MILLI_SEC(100);
		mutex_lock(&Recv_Xmit_mutex);
		RecvOnePkt(pfunc);
//		Print_Message((u8 *)Message_Recv);
		mutex_unlock(&Recv_Xmit_mutex);
	}
	return 0;
}
static int SendOnePkt_Thread(void * pData)
{
	struct sdio_func *pfunc;
	PHAL_DATA_TYPE pHal_Data;
	pHal_Data = (PHAL_DATA_TYPE) pData;
	pfunc = pHal_Data->func;
	while(!kthread_should_stop()){
		SLEEP_MILLI_SEC(1000);
		mutex_lock(&Recv_Xmit_mutex);
		SendOnePkt(pfunc);		
//		Print_Message((u8 *)Message_Xmit);
		mutex_unlock(&Recv_Xmit_mutex);
	}
	return 0;
}
static int SendPkt_Thread(void *pData)
{
	struct sdio_func *pfunc;
	int i;
	_list *plist;
	PCHRIS_XMIT_BUF pchris_buf;
	PHAL_DATA_TYPE pHal_Data;
	PTXDESC_8195A ptxdesc;
	pHal_Data = (PHAL_DATA_TYPE) pData;
	pfunc = pHal_Data->func;
	printk("%s()=========>\n", __FUNCTION__);
	mutex_lock(&gHal_Data->buf_mutex);
	while(!kthread_should_stop()){
		SLEEP_MILLI_SEC(1000);
		if (rtw_is_list_empty(&chris_buf_list)) {
			printk("Err!! List is empty!!\n");
			mutex_unlock(&gHal_Data->buf_mutex);
			SendOnePkt(pfunc);
//			break;
		}
		else
		{
		plist = get_next(&chris_buf_list);
		pchris_buf = LIST_CONTAINOR(plist, CHRIS_XMIT_BUF, list);
		rtw_list_delete(&pchris_buf->list);	
		mutex_unlock(&gHal_Data->buf_mutex);
//		ptxdesc = (PTXDESC_8195A)pchris_buf->buf;
		printk("List isn't null\n");
//			for(i=0;i<(ptxdesc->txpktsize+ptxdesc->offset);i++)
//				printk("chris_buf.buf[%d] = 0x%02x\n", i, *(pchris_buf->buf+i));
//		chris_sdio_write_port(pfunc, WLAN_TX_HIQ_DEVICE_ID, (ptxdesc->txpktsize+ptxdesc->offset), pchris_buf->buf);
		}
	}
	return 0;
}
static int Print_Message(u8 *message)
{
	printk("%s(): %s\n\n", __FUNCTION__, message);
	return 0;
}
static int RecvOnePkt(struct sdio_func *func)
{
	int res, i=0;
	u32 len;
	u8 *pBuf;
	struct sdio_func *pfunc;
	pfunc = (struct sdio_func *)func;
	do{
//		len = sdio_read32(pfunc, SDIO_RX0_REQ_LEN);
		len &= 0x0fffffff;
		printk("Rx len is %d\n", len);
		if((++i)>1000)
			break;
	}while(len<=0);
	if(len)
	{
		pBuf = kmalloc(len, GFP_KERNEL);
	sdio_claim_host(pfunc);
//		res = sdio_read_port(gHal_Data, WLAN_RX0FF_DEVICE_ID, len, pBuf);
	sdio_release_host(pfunc);
		if (res == _FAIL)
			printk("sdio read port failed!\n");
		for(i=0;i<len;i++)
		{
			printk("Rx[%d] = 0x%02x\n", i, *(pBuf+i));
		}
		kfree(pBuf);
	}
	else
	{
		printk("No pkt received!\n");
	}
	return _SUCCESS;
}

#define TxPktSize (318) //for test
static int SendOnePkt(struct sdio_func *func)
{
	int i;
	struct sdio_func *pfunc;
	u8 data[TxPktSize];

//Tx descriptor(32bytes)
	data[0] = 0x1e;
	data[1] = 0x01;//290
	data[2] = 0x20;
	data[3] = 0x8d;
	data[4] = 0x00;
	data[5] = 0x06;
	data[6] = 0x20;
	data[7] = 0x00;
	data[8] = 0x00;
	data[9] = 0x00;
	data[10] = 0x70;
	data[11] = 0x00;
	data[12] = 0x00;
	data[13] = 0x00;	
	data[14] = 0x01;
	data[15] = 0x00;
	data[16] = 0x43;
	data[17] = 0x07;
	data[18] = 0x00;
	data[19] = 0x00;
	data[20] = 0x00;
	data[21] = 0x00;
	data[22] = 0x00;	
	data[23] = 0x00;
	data[24] = 0x00;
	data[25] = 0x78;
	data[26] = 0x88;
	data[27] = 0x88;
	data[28] = 0xa0;
	data[29] = 0x7d;
	data[30] = 0x00;
	data[31] = 0x00;
//at cmd descriptor(4bytes)
		data[32] = 0x1a; //pktsize0
		data[33] = 0x01; //pktsize1
		data[34] = 0x04; //offset
		data[35] = 0x00; //frame type: data
//		data[36] = 0x00; 
//		data[37] = 0x00; 
//		data[38] = 0x00; //resv
//		data[39] = 0x00; //resv
//	
//wlan pkt		
	data[36] = 0x88;
	data[37] = 0x01;
	data[38] = 0x00;
	data[39] = 0x00;
	
	data[40] = 0xff;	
	data[41] = 0xff;	
	data[42] = 0xff;	
	data[43] = 0xff;	
	data[44] = 0xff;	
	data[45] = 0xff;	
	
	data[46] = 0x00;	
	data[47] = 0x00;
	data[48] = 0x00;
	data[49] = 0x00;
	data[50] = 0x00;
	data[51] = 0x02;
	
	data[52] = 0x00;	
	data[53] = 0x00;
	data[54] = 0x00;
	data[55] = 0x00;
	data[56] = 0x00;
	data[57] = 0x01;
	
	data[58] = 0x10;
	
	data[59] = 0x00;
	data[60] = 0x06;
	data[61] = 0x00;
	data[62] = 0x01;
	data[63] = 0x00;
	data[64] = 0x00;
	
	
	data[65] = 0x04;	
	data[66] = 0x06;
	data[67] = 0x99;
	data[68] = 0x99;
	data[69] = 0x99;
	data[70] = 0x3e;
	for (i=0;i<TxPktSize-71;i++)
	{
		data[i+71] = 0x3e;
	}
//	memcpy(data+32, g_SDIO_cmdData, strlen(g_SDIO_cmdData));
//	printk("tx packet length is %d\n", strlen(data));

	for(i=0;i<TxPktSize;i++)
	{
		printk("tx[%d] = 0x%02x\n", i, data[i]);
	}

	pfunc = func;
	chris_sdio_write_port(pfunc, WLAN_TX_HIQ_DEVICE_ID, TxPktSize, data);
//	sdio_write_port(pfunc, WLAN_TX_HIQ_DEVICE_ID, strlen(data), data);
/*
	for(i=0; i<10;i++)
	{
		sdio_write_port(func, WLAN_TX_HIQ_DEVICE_ID, 314, data);
	}
	for(i=0; i<10;i++)
	{
		sdio_write_port(func, WLAN_TX_MIQ_DEVICE_ID, 314, data);
	}
	for(i=0; i<10;i++)
	{
		sdio_write_port(func, WLAN_TX_LOQ_DEVICE_ID, 314, data);
	}
*/
	return 0;	
}

static void sd_sync_int_hdl(struct sdio_func *func)
{
//	u32 sdio_himr;
	gHal_Data->sdio_himr = (u32)(	\
								SDIO_HIMR_RX_REQUEST_MSK | 
								SDIO_HIMR_AVAL_MSK	|	
								0);
//	sd_int_hal(gHal_Data);
//	rtw_sdio_set_irq_thd(psdpriv, NULL);
}
static int chris_sdio_init(struct sdio_func *func)
{
	int rc;
	printk("Chris=====>%s():\n", __FUNCTION__);
	sdio_claim_host(func);
	rc = sdio_enable_func(func);
	if(rc)
	{
		printk("%s(): sdio_enable_func FAIL!\n", __FUNCTION__);
		goto release;
	}
	rc = sdio_set_block_size(func, 512);
	if(rc)
	{
		printk("%s(): sdio_set_block_size FAIL!\n", __FUNCTION__);
		goto release;
	}

	sdio_release_host(func);
	return rc;
release:
	sdio_release_host(func);
	return rc;
}
static int sdio_init(struct dvobj_priv *dvobj)
{
	PSDIO_DATA psdio_data;
	struct sdio_func *func;
	int err;

_func_enter_;

	psdio_data = &dvobj->intf_data;
	func = psdio_data->func;
	// 1.init SDIO bus
	sdio_claim_host(func);
	err = sdio_enable_func(func);
	if(err ){
		dvobj->drv_dbg.dbg_sdio_init_error_cnt++;
		DBG_8192C(KERN_CRIT "%s: sdio_enable_func FAIL(%d)!\n", __func__, err);
		goto release;
	}
	err = sdio_set_block_size(func, 512);
	if(err ){
		dvobj->drv_dbg.dbg_sdio_init_error_cnt++;
		DBG_8192C(KERN_CRIT "%s: sdio_enable_func FAIL(%d)!\n", __func__, err);
		goto release;
	}
	psdio_data->block_transfer_len = 512;
	psdio_data->tx_block_mode = 1;
	psdio_data->rx_block_mode = 1;
	sdio_release_host(func);
	return _SUCCESS;
release:
    sdio_release_host(func);
exit:
_func_exit_;

	if(err) return _FAIL;
	return _SUCCESS;   
}
static void sdio_deinit(struct dvobj_priv *dvobj)
{
	struct sdio_func *func;
	int err;


	RT_TRACE(_module_hci_intfs_c_, _drv_notice_, ("+sdio_deinit\n"));

	func = dvobj->intf_data.func;

	if (func) {
		sdio_claim_host(func);
		err = sdio_disable_func(func);
		if (err)
		{
			dvobj->drv_dbg.dbg_sdio_deinit_error_cnt++;
			DBG_8192C(KERN_ERR "%s: sdio_disable_func(%d)\n", __func__, err);
		}

		if (dvobj->irq_alloc) {
			err = sdio_release_irq(func);
			if (err)
			{
				dvobj->drv_dbg.dbg_sdio_free_irq_error_cnt++;
				DBG_8192C(KERN_ERR "%s: sdio_release_irq(%d)\n", __func__, err);
			}
			else
				dvobj->drv_dbg.dbg_sdio_free_irq_cnt++;
		}

		sdio_release_host(func);
	}
}
static int rtw_sdio_suspend(struct device *dev)
{
	int ret =0;
	return ret;
}
static int rtw_sdio_resume(struct device *dev)
{
	int ret = 0;
	return ret;
}
static struct dvobj_priv *sdio_dvobj_init(struct sdio_func *func)
{
	int status = _FAIL;
	struct dvobj_priv *dvobj = NULL;
	PSDIO_DATA psdio;
_func_enter_;

	if((dvobj = devobj_init()) == NULL) {
		goto exit;
	}

	sdio_set_drvdata(func, dvobj);

	psdio = &dvobj->intf_data;
	psdio->func = func;

	if (sdio_init(dvobj) != _SUCCESS) {
		RT_TRACE(_module_hci_intfs_c_, _drv_err_, ("%s: initialize SDIO Failed!\n", __FUNCTION__));
		goto free_dvobj;
	}
//	rtw_reset_continual_io_error(dvobj);
	status = _SUCCESS;

free_dvobj:
	if (status != _SUCCESS && dvobj) {
		sdio_set_drvdata(func, NULL);
		
		devobj_deinit(dvobj);
		
		dvobj = NULL;
	}
exit:
_func_exit_;
	return dvobj;
}
static void sdio_dvobj_deinit(struct sdio_func *func)
{
	struct dvobj_priv *dvobj = sdio_get_drvdata(func);
_func_enter_;

	sdio_set_drvdata(func, NULL);
	if (dvobj) {
		sdio_deinit(dvobj);
		devobj_deinit(dvobj);
	}

_func_exit_;
	return;
}
static void rtw_decide_chip_type_by_device_id(PADAPTER padapter, const struct sdio_device_id  *pdid)
{
	padapter->chip_type = pdid->driver_data;

#if defined(CONFIG_RTL8723A)
	if( padapter->chip_type == RTL8723A){
		padapter->HardwareType = HARDWARE_TYPE_RTL8723AS;
		DBG_871X("CHIP TYPE: RTL8723A\n");
	}
#endif

#if defined(CONFIG_RTL8188E)
	if(padapter->chip_type == RTL8188E){
		padapter->HardwareType = HARDWARE_TYPE_RTL8188ES;
		DBG_871X("CHIP TYPE: RTL8188E\n");
	}
#endif

#if defined(CONFIG_RTL8723B)
	padapter->chip_type = RTL8723B;
	padapter->HardwareType = HARDWARE_TYPE_RTL8723BS;
#endif

#if defined(CONFIG_RTL8821A)
	if (padapter->chip_type == RTL8821) {
		padapter->HardwareType = HARDWARE_TYPE_RTL8821S;
		DBG_871X("CHIP TYPE: RTL8821A\n");
	}
#endif
	if (padapter->chip_type == RTL8195A) {
		padapter->HardwareType = HARDWARE_TYPE_RTL8195A;
		DBG_871X("CHIP TYPE: RTL8195A\n");
	}
}

PCHRIS_ADAPTER chris_rtw_sdio_if_init(struct sdio_func *func)
{
	int status = _FAIL;
	PCHRIS_ADAPTER padapter = NULL;
	struct net_device *pnetdev;
	u8 *pdata = NULL;
	if ((padapter = (PCHRIS_ADAPTER *)rtw_zvmalloc(sizeof(*padapter))) == NULL) {
		goto exit;
	}
//		if ((padapter = (u8 *)rtw_zvmalloc(2048)) == NULL) {
//			goto exit;
//		}	
	padapter->func = func;
//	padapter->pdata = pdata;

	//3 1. init network device data
	pnetdev = chris_rtw_init_netdev(padapter);
	if (!pnetdev)
	{
		printk("rtw_init_netdev Failed\n");
		goto free_adapter;
	}
//	SET_NETDEV_DEV(pnetdev, &padapter->func->dev);
	return padapter;
free_adapter:
	if (status != _SUCCESS) {
		if (pnetdev)
			rtw_free_netdev(pnetdev);
		else
			rtw_vmfree((u8*)padapter, sizeof(*padapter));
		padapter = NULL;
	}
exit:
	return padapter;
}
_adapter *rtw_sdio_if1_init(struct dvobj_priv *dvobj, const struct sdio_device_id  *pdid)
{
	int status = _FAIL;
	struct net_device *pnetdev;
	PADAPTER padapter = NULL;
	
	if ((padapter = (_adapter *)rtw_zvmalloc(sizeof(*padapter))) == NULL) {
		goto exit;
	}

//	#ifdef RTW_SUPPORT_PLATFORM_SHUTDOWN
//		g_test_adapter = padapter;
//	#endif // RTW_SUPPORT_PLATFORM_SHUTDOWN
	padapter->dvobj = dvobj;
	dvobj->if1 = padapter;

	padapter->bDriverStopped=_TRUE;
	
	dvobj->padapters[dvobj->iface_nums++] = padapter;
	padapter->iface_id = IFACE_ID0;
	
//	#if defined(CONFIG_CONCURRENT_MODE) || defined(CONFIG_DUALMAC_CONCURRENT)
//		//set adapter_type/iface type for primary padapter
//		padapter->isprimary = _TRUE;
//		padapter->adapter_type = PRIMARY_ADAPTER;	
//		#ifndef CONFIG_HWPORT_SWAP
//		padapter->iface_type = IFACE_PORT0;
//		#else
//		padapter->iface_type = IFACE_PORT1;
//		#endif
//	#endif
//	
	padapter->interface_type = RTW_SDIO;
	rtw_decide_chip_type_by_device_id(padapter, pdid);
	
	//3 1. init network device data
	pnetdev = rtw_init_netdev(padapter);
	if (!pnetdev)
	{
		printk("rtw_init_netdev Failed\n");
		goto free_adapter;
	}
	SET_NETDEV_DEV(pnetdev, dvobj_to_dev(dvobj));
	
	padapter = rtw_netdev_priv(pnetdev);
	if(!padapter)
		printk("%s()==>padapter is null\n", __FUNCTION__);
	return padapter;
	
	//3 3. init driver special setting, interface, OS and hardware relative
	
	//4 3.1 set hardware operation functions
//	rtw_set_hal_ops(padapter);
//	
//	
//		//3 5. initialize Chip version
//		padapter->intf_start = &sd_intf_start;
//		padapter->intf_stop = &sd_intf_stop;
//	
//		padapter->intf_init = &sdio_init;
//		padapter->intf_deinit = &sdio_deinit;
//		padapter->intf_alloc_irq = &sdio_alloc_irq;
//		padapter->intf_free_irq = &sdio_free_irq;
//	
//		if (rtw_init_io_priv(padapter, sdio_set_intf_ops) == _FAIL)
//		{
//			RT_TRACE(_module_hci_intfs_c_, _drv_err_,
//				("rtw_drv_init: Can't init io_priv\n"));
//			goto free_hal_data;
//		}
//	
//		rtw_hal_read_chip_version(padapter);
//	
//		rtw_hal_chip_configure(padapter);
//	
//	#ifdef CONFIG_BT_COEXIST
//		rtw_btcoex_Initialize(padapter);
//	#endif // CONFIG_BT_COEXIST
//	
//		//3 6. read efuse/eeprom data
//		rtw_hal_read_chip_info(padapter);
//	
//		//3 7. init driver common data
//		if (rtw_init_drv_sw(padapter) == _FAIL) {
//			RT_TRACE(_module_hci_intfs_c_, _drv_err_,
//				 ("rtw_drv_init: Initialize driver software resource Failed!\n"));
//			goto free_hal_data;
//		}
//	
//		//3 8. get WLan MAC address
//		// set mac addr
//		rtw_macaddr_cfg(padapter->eeprompriv.mac_addr);
//		rtw_init_wifidirect_addrs(padapter, padapter->eeprompriv.mac_addr, padapter->eeprompriv.mac_addr);
//	
//		rtw_hal_disable_interrupt(padapter);
//	
//		DBG_871X("bDriverStopped:%d, bSurpriseRemoved:%d, bup:%d, hw_init_completed:%d\n"
//			,padapter->bDriverStopped
//			,padapter->bSurpriseRemoved
//			,padapter->bup
//			,padapter->hw_init_completed
//		);
//		
//		status = _SUCCESS;
	
//	free_hal_data:
//		if(status != _SUCCESS && padapter->HalData)
//			rtw_mfree(padapter->HalData, sizeof(*(padapter->HalData)));
//	
//	free_wdev:
//		if(status != _SUCCESS) {
//			#ifdef CONFIG_IOCTL_CFG80211
//			rtw_wdev_unregister(padapter->rtw_wdev);
//			rtw_wdev_free(padapter->rtw_wdev);
//			#endif
//		}
//	
free_adapter:
	if (status != _SUCCESS) {
		if (pnetdev)
			rtw_free_netdev(pnetdev);
		else
			rtw_vmfree((u8*)padapter, sizeof(*padapter));
		padapter = NULL;
	}
exit:
	return padapter;
}

static void rtw_sdio_if1_deinit(_adapter *if1)
{
		struct net_device *pnetdev = if1->pnetdev;
//		struct mlme_priv *pmlmepriv= &if1->mlmepriv;
//	
//		if(check_fwstate(pmlmepriv, _FW_LINKED))
//			rtw_disassoc_cmd(if1, 0, _FALSE);
//	
//	#ifdef CONFIG_AP_MODE
//		free_mlme_ap_info(if1);
//		#ifdef CONFIG_HOSTAPD_MLME
//		hostapd_mode_unload(if1);
//		#endif
//	#endif
//	
//	#ifdef CONFIG_GPIO_WAKEUP
//	#ifdef CONFIG_PLATFORM_ARM_SUN6I 
//	        sw_gpio_eint_set_enable(gpio_eint_wlan, 0);
//	        sw_gpio_irq_free(eint_wlan_handle);
//	#else  
//		gpio_hostwakeup_free_irq(if1);
//	#endif
//	#endif
//	
//		rtw_cancel_all_timer(if1);
//	
//	#ifdef CONFIG_WOWLAN
//		adapter_to_pwrctl(if1)->wowlan_mode=_FALSE;
//		DBG_871X_LEVEL(_drv_always_, "%s wowlan_mode:%d\n", __func__, adapter_to_pwrctl(if1)->wowlan_mode);
//	#endif //CONFIG_WOWLAN
//	
//		rtw_dev_unload(if1);
//		DBG_871X("+r871xu_dev_remove, hw_init_completed=%d\n", if1->hw_init_completed);
//		
//		rtw_handle_dualmac(if1, 0);
//	
//	#ifdef CONFIG_IOCTL_CFG80211
//		if (if1->rtw_wdev) {
//			rtw_wdev_free(if1->rtw_wdev);
//		}
//	#endif
//	
		rtw_free_drv_sw(if1);
//	
		if(pnetdev)
			rtw_free_netdev(pnetdev);
		else
			rtw_vmfree((u8*)if1, sizeof(*if1));
//	
//	#ifdef CONFIG_PLATFORM_RTD2880B
//		DBG_871X("wlan link down\n");
//		rtd2885_wlan_netlink_sendMsg("linkdown", "8712");
//	#endif
//	
//	#ifdef RTW_SUPPORT_PLATFORM_SHUTDOWN
//		g_test_adapter = NULL;
//	#endif // RTW_SUPPORT_PLATFORM_SHUTDOWN
}

/*
 * drv_init() - a device potentially for us
 *
 * notes: drv_init() is called when the bus driver has located a card for us to support.
 *        We accept the new device by returning 0.
 */
static int __devinit rtw_drv_init(struct sdio_func *func, const struct sdio_device_id *id)
{
//	static int board_idx = -1;
	int status = _FAIL;
	struct net_device *pnetdev;
		PADAPTER if1 = NULL, if2 = NULL;
		struct dvobj_priv *dvobj;
//	PCHRIS_ADAPTER if1=NULL;
	int ret = 0;
//	board_idx++;
//	printk("%s():++\n",__FUNCTION__);

	RT_TRACE(_module_hci_intfs_c_, _drv_info_,
		("+rtw_drv_init: vendor=0x%04x device=0x%04x class=0x%02x\n",
		func->vendor, func->device, func->class));
	
	if ((dvobj = sdio_dvobj_init(func)) == NULL) {
		RT_TRACE(_module_hci_intfs_c_, _drv_err_, ("initialize device object priv Failed!\n"));
		goto exit;
	}
	if ((if1 = rtw_sdio_if1_init(dvobj, id)) == NULL) {
		DBG_871X("rtw_init_primary_adapter Failed!\n");
		goto free_dvobj;
	}
	
//	init_chris_Buf_Pool();

	_rtw_init_listhead(&chris_buf_list);
	gHal_Data = kmalloc(sizeof(PHAL_DATA_TYPE), GFP_KERNEL);
//	g_SDIO_cmdData = kmalloc(2048, GFP_KERNEL);
	// 1.init SDIO bus and read chip version	
//		ret = chris_sdio_init(func);
//		if(ret)
//			return ret;
	mutex_init(&gHal_Data->buf_mutex);	
	gHal_Data->func = func;
	gHal_Data->SdioRxFIFOCnt =0;
//	mutex_init(&Recv_Xmit_mutex);
//	RecvOnePKt(func);
//	SendOnePkt(func);
	Xmit_Thread = kthread_run(SendPkt_Thread, (void *)gHal_Data, "xmit_thread");
//	Recv_Thread = kthread_run(RecvOnePkt_Thread, (void *)gHal_Data, "recv_thread");
//    printk(KERN_INFO "%s: This product is covered by one or more of the following patents: US6,570,884, US6,115,776, and US6,327,625.\n", MODULENAME);

//    printk("%s", GPL_CLAIM);
//	return ret;
//		if1 = chris_rtw_sdio_if_init(func);
//		if(!if1)
//		{	
//			printk("if1 is null\n");
//			goto exit;
//		}
//	sdio_set_drvdata(func, if1);
//			status = register_netdev(if1->pnetdev);
//		if(status)
//			printk("register_netdev FAIL.\n");
//			return status;
//		netif_carrier_off(pnetdev);
	//dev_alloc_name && register_netdev
//		if((status = rtw_drv_register_netdev(if1)) != _SUCCESS) {
//			DBG_871X("drv_register_netdev Failed!\n");
//			goto free_if1;
//		}
free_if1:
	if (status != _SUCCESS && if1) {
		rtw_sdio_if1_deinit(if1);
	}
free_dvobj:
	if (status != _SUCCESS)
		sdio_dvobj_deinit(func);
exit:
	return status == _SUCCESS?0:-ENODEV;
}

static void __devexit rtw_dev_remove(struct sdio_func *func)

{

	int rc = 0;
		struct dvobj_priv *dvobj = sdio_get_drvdata(func);
//		//	struct pwrctrl_priv *pwrctl = dvobj_to_pwrctl(dvobj);
		PADAPTER padapter = dvobj->if1;
//	
	dvobj->processing_dev_remove = _TRUE;
	
	
	rtw_unregister_netdevs(dvobj);
	rtw_sdio_if1_deinit(padapter);
	sdio_dvobj_deinit(func);

	printk("%s():++\n", __FUNCTION__);

	if(Xmit_Thread)
	{
		printk("stop Xmit_Thread\n");
		kthread_stop(Xmit_Thread);
	}
//		if(Recv_Thread)
//		{
//			printk("stop Recv_Thread\n");
//			kthread_stop(Recv_Thread);
//		}
//	mutex_destroy(&Recv_Xmit_mutex);
	mutex_destroy(&gHal_Data->buf_mutex);
	if(gHal_Data)
		kfree(gHal_Data);
	
//	kfree(g_SDIO_cmdData);
//		sdio_claim_host(func);
//		rc = sdio_disable_func(func);
//		if(rc){
//			printk("%s(): sdio_disable_func fail!\n", __FUNCTION__);
//		}
//	rc = sdio_release_irq(func);
//	if(rc){
//		printk("%s(): sdio_disable_func fail!\n", __FUNCTION__);
//	}	
//	sdio_release_host(func);
}

static struct file_operations fops = 
{
	read : myFunc_Read,
	write : myFunc_Write,
	open : myFunc_Open,
	release : myFunc_Close,
	unlocked_ioctl : myFunc_ioctl
};

static const struct sdio_device_id sdio_ids[] =
{
	{ SDIO_DEVICE(0x024c, 0x8821),.driver_data = RTL8195A},
};

//	struct sdio_driver rtl8195a = {
//		.probe	= rtl8195a_init_one,
//		.remove	= __devexit_p(rtl8195a_remove_one),
//		.name	= MODULENAME,
//		.id_table	= sdio_ids,
//	};

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,29)) 
static const struct dev_pm_ops rtw_sdio_pm_ops = {
	.suspend	= rtw_sdio_suspend,
	.resume	= rtw_sdio_resume,
};
#endif
	
struct sdio_drv_priv {
	struct sdio_driver r8195a_drv;
	int drv_registered;
};

static struct sdio_drv_priv sdio_drvpriv = {
	.r8195a_drv.probe = rtw_drv_init,
	.r8195a_drv.remove = rtw_dev_remove,
	.r8195a_drv.name = (char*)DRV_NAME,
	.r8195a_drv.id_table = sdio_ids,
	#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,29)) 
	.r8195a_drv.drv = {
		.pm = &rtw_sdio_pm_ops,
	}
	#endif
};

static int platform_wifi_power_on(void)
{
	int ret = 0;
	return ret;
}
void platform_wifi_power_off(void)
{

}
static int __init rtl8195a_init_module(void)
{
	int ret;


	DBG_871X_LEVEL(_drv_always_, "module init start\n");
	dump_drv_version(RTW_DBGDUMP);
//	#ifdef BTCOEXVERSION
//		DBG_871X_LEVEL(_drv_always_, DRV_NAME" BT-Coex version = %s\n", BTCOEXVERSION);
//	#endif // BTCOEXVERSION

//		ret = platform_wifi_power_on();
//		if (ret)
//		{
//			DBG_871X("%s: power on failed!!(%d)\n", __FUNCTION__, ret);
//			ret = -1;
//			goto exit;
//		}	

	ret = register_chrdev(major,"inic_8195a",&fops);
	if (ret < 0)
	{
		printk(KERN_WARNING "%s(): function error!\n", __FUNCTION__);
		return ret;
	}

	
	sdio_drvpriv.drv_registered = _TRUE;
//	rtw_suspend_lock_init();
//	rtw_drv_proc_init();
//	rtw_ndev_notifier_register();
	ret = sdio_register_driver(&sdio_drvpriv.r8195a_drv);
	if(ret!=0)
	{	
		sdio_drvpriv.drv_registered = _FALSE;
		DBG_871X("%s: register driver failed!!(%d)\n", __FUNCTION__, ret);
		goto poweroff;
	}
	goto exit;
poweroff:
	platform_wifi_power_off();
exit:
	DBG_871X_LEVEL(_drv_always_, "module init ret=%d\n", ret);
	return ret;
}

static void __exit rtl8195a_cleanup_module(void)
{
	DBG_871X_LEVEL(_drv_always_, "module exit start\n");

	sdio_drvpriv.drv_registered = _FALSE;
	unregister_chrdev(major, "inic_8195a");
	sdio_unregister_driver(&sdio_drvpriv.r8195a_drv);
//		platform_wifi_power_off();
//		rtw_suspend_lock_uninit();
//		rtw_drv_proc_deinit();
//	rtw_ndev_notifier_unregister();
	DBG_871X_LEVEL(_drv_always_, "module exit success\n");
}

module_init(rtl8195a_init_module);
module_exit(rtl8195a_cleanup_module);
