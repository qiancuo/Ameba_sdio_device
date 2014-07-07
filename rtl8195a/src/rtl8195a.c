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

#include "include/sdio_ops.h"
#include "include/8195_sdio_reg.h"
#include "include/drv_type_sdio.h"
#include "include/rtl8195a.h"

#include "include/osdep_service_linux.h"

MODULE_AUTHOR("Realtek");
MODULE_DESCRIPTION("RealTek RTL-8195a iNIC");
MODULE_LICENSE("GPL");
MODULE_VERSION(RTL8195_VERSION);

typedef struct _SDIO_CMDDATA{
	CMD_DESC cmd;
	char cmd_data[64];
}SDIO_CMDDATA, *PSDIO_CMDDATA;

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
static int major;
static SDIO_CMDDATA g_SDIO_cmdData;
static int Print_Message(u8 *message);
static int RecvOnePkt(struct sdio_func * func);
static int SendOnePkt(struct sdio_func * func);

static ssize_t myFunc_Read(struct file *file, char *buf, size_t count, loff_t *ppos)
{
	printk(KERN_DEBUG "%s():\n", __FUNCTION__);
	return 0;
}

static ssize_t myFunc_Write(struct file *file, const char *buf, size_t count, loff_t *ppos)
{
	SDIO_CMDDATA sdioData;
	printk(KERN_DEBUG "%s():\n", __FUNCTION__);
	if(copy_from_user(&g_SDIO_cmdData,buf,sizeof(SDIO_CMDDATA)))
	 {
		 printk(KERN_DEBUG "copy from user failed!\n"); 
		 return -EFAULT;
	  }
	SendOnePkt(gHal_Data->func);
	return 0;
}

static ssize_t myFunc_Open(struct inode *inode, struct file *file)
{
	printk(KERN_DEBUG "%s():\n", __FUNCTION__);
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
		len = sdio_read32(pfunc, SDIO_RX0_REQ_LEN);
		len &= 0x0fffffff;
		printk("Rx len is %d\n", len);
		if((++i)>1000)
			break;
	}while(len<=0);
	if(len)
	{
		pBuf = kmalloc(len, GFP_KERNEL);
	sdio_claim_host(pfunc);
		res = sdio_read_port(gHal_Data, WLAN_RX0FF_DEVICE_ID, len, pBuf);
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

#define TxPktSize 314 //for test
static int SendOnePkt(struct sdio_func *func)
{
	int i;
	struct sdio_func *pfunc;
	u8 data[TxPktSize];
//	u8 data[43];
//Tx descriptor(32bytes)
	data[0] = 0x1a;
	data[1] = 0x01;
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
//at cmd descriptor(8bytes)
	data[32] = 0x03; //pktsize0
	data[33] = 0x00; //pktsize1
	data[34] = 0x08; //offset
	data[35] = 0x01; //frame type
	data[36] = 0x43; //'C'
//	data[37] = 0x44; //'D', "CD" for disconnect
	data[37] = 0x30; //'0', "C0" for connect
	data[38] = 0x00; //resv
	data[39] = 0x00; //resv
//cmd string
	data[40] = 0x72; //'r'
	data[41] = 0x74; //'t'
	data[42] = 0x6B;//'k'
//wlan pkt		
//		data[40] = 0x88;
//		data[41] = 0x01;
//		data[42] = 0x00;
	data[43] = 0x00;
	
	data[44] = 0xff;	
	data[45] = 0xff;	
	data[46] = 0xff;	
	data[47] = 0xff;	
	data[48] = 0xff;	
	data[49] = 0xff;	
	
	data[50] = 0x00;	
	data[51] = 0x00;
	data[52] = 0x00;
	data[53] = 0x00;
	data[54] = 0x00;
	data[55] = 0x02;
	
	data[56] = 0x00;	
	data[57] = 0x00;
	data[58] = 0x00;
	data[59] = 0x00;
	data[60] = 0x00;
	data[61] = 0x01;
	
	data[62] = 0x10;
	
	data[63] = 0x00;
	data[64] = 0x06;
	data[65] = 0x00;
	data[66] = 0x01;
	data[67] = 0x00;
	data[68] = 0x00;
	
	
	data[69] = 0x04;	
	data[70] = 0x06;
	data[71] = 0x99;
	data[72] = 0x99;
	data[73] = 0x99;
	data[74] = 0x3e;
	for (i=0;i<TxPktSize-75;i++)
	{
		data[i+75] = 0x3e;
	}
//		printk("tx packet length is %d\n", sizeof(data));
//	
//		for(i=0;i<sizeof(data);i++)
//		{
//			printk("tx[%d] = 0x%02x\n", i, data[i]);
//		}

	pfunc = func;
//	sdio_write_port(pfunc, WLAN_TX_HIQ_DEVICE_ID, sizeof(data), data);
	printk("tx packet length is %d\n", sizeof(g_SDIO_cmdData));
	for(i=0;i<sizeof(g_SDIO_cmdData);i++)
	{
		printk("tx[%d] = 0x%02x\n", i, g_SDIO_cmdData[i]);
	}
	sdio_write_port(pfunc, WLAN_TX_HIQ_DEVICE_ID, sizeof(g_SDIO_cmdData), (char *)&g_SDIO_cmdData);

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

static int sdio_init(struct sdio_func *func)
{
	int rc = 0;

	printk("%s():\n", __FUNCTION__);
	sdio_claim_host(func);
	rc = sdio_enable_func(func);
	if(rc ){
		printk("%s():sdio_enable_func FAIL!\n",__FUNCTION__);
		goto release;
	}
	rc = sdio_set_block_size(func, 512);
	if(rc ){
		printk("%s():sdio_set_block_size FAIL!\n",__FUNCTION__);
		goto release;
	}
	sdio_release_host(func);
	return rc;
release:
    sdio_release_host(func);
    return rc;    
}


static int __devinit rtl8195a_init_one(struct sdio_func *func, const struct sdio_device_id *id)
{
	static int board_idx = -1;

	int rc = 0;
	board_idx++;
	printk("%s():++\n",__FUNCTION__);

	gHal_Data = kmalloc(sizeof(PHAL_DATA_TYPE), GFP_KERNEL);

	// 1.init SDIO bus and read chip version	
	rc = sdio_init(func);
	if(rc)
		return rc;
	gHal_Data->func = func;
	gHal_Data->SdioRxFIFOCnt =0;
	mutex_init(&Recv_Xmit_mutex);
//	RecvOnePKt(func);
//	SendOnePkt(func);
//	Xmit_Thread = kthread_run(SendOnePkt_Thread, (void *)gHal_Data, "xmit_thread");
//	Recv_Thread = kthread_run(RecvOnePkt_Thread, (void *)gHal_Data, "recv_thread");
//    printk(KERN_INFO "%s: This product is covered by one or more of the following patents: US6,570,884, US6,115,776, and US6,327,625.\n", MODULENAME);

//    printk("%s", GPL_CLAIM);

	return rc;
}

static void __devexit rtl8195a_remove_one(struct sdio_func *func)

{

	int rc = 0;
	printk("%s():++\n", __FUNCTION__);
	if(Xmit_Thread)
	{
		printk("stop Xmit_Thread\n");
		kthread_stop(Xmit_Thread);
	}
	if(Recv_Thread)
	{
		printk("stop Recv_Thread\n");
		kthread_stop(Recv_Thread);
	}
	mutex_destroy(&Recv_Xmit_mutex);
	kfree(gHal_Data);
	sdio_claim_host(func);
	rc = sdio_disable_func(func);
	if(rc){
		printk("%s(): sdio_disable_func fail!\n", __FUNCTION__);
	}
	sdio_release_host(func);
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

struct sdio_driver rtl8195a = {
	.probe	= rtl8195a_init_one,
	.remove	= __devexit_p(rtl8195a_remove_one),
	.name	= MODULENAME,
	.id_table	= sdio_ids,
};



static int __init rtl8195a_init_module(void)
{

	int ret;
	ret = register_chrdev(0,"inic_8195a",&fops);
	if (ret < 0)
	{
		printk(KERN_WARNING "%s(): function error!\n", __FUNCTION__);
		return ret;
	}
	major = ret;
	printk(KERN_DEBUG "MAJOR : %d\n",ret);
	ret = sdio_register_driver(&rtl8195a);
	if(ret!=0)
		printk("sdio register driver Failed!\n");
	return ret;

}

static void __exit rtl8195a_cleanup_module(void)
{

	unregister_chrdev(major, "inic_8195a");
	sdio_unregister_driver(&rtl8195a);

}

module_init(rtl8195a_init_module);
module_exit(rtl8195a_cleanup_module);
