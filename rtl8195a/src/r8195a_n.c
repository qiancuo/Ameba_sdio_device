#include <linux/module.h>
#include <linux/version.h>
#include <linux/pci.h>
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

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,26)
#include <linux/pci-aspm.h>
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)
#define dev_printk(A,B,fmt,args...) printk(A fmt,##args)
#else
#include <linux/dma-mapping.h>
#include <linux/moduleparam.h>
#endif

#include <asm/io.h>
#include <asm/irq.h>
#include <asm/uaccess.h>
//#include "r8195a.h"
//#include "r8168_asf.h"
//#include "rtl_eeprom.h"
//#include "rtltool.h"
#include "sdio/sdio_io.h"
#include "8195_common.h"
#include "sdio/hal8195sdio.h"
#include "drv_type_sdio.h"
#include "dispatchreadwrite.h"
#include "linux/fs.h"
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,8,0)
#define __devinit
#define __devexit
#define __devexit_p(func)   func
#endif

#define MODULENAME "iNIC_8195a"
#define GPL_CLAIM "\
iNIC_8195a  Copyright (C) 2013  Realtek NIC software team <nicfae@realtek.com> \n \
This program comes with ABSOLUTELY NO WARRANTY; for details, please see <http://www.gnu.org/licenses/>. \n \
This is free software, and you are welcome to redistribute it under certain conditions; see <http://www.gnu.org/licenses/>. \n"
#define RTL8195_VERSION "8195a"

MODULE_AUTHOR("Realtek and the Linux r8195a crew <netdev@vger.kernel.org>");
MODULE_DESCRIPTION("RealTek RTL-8195a iNIC");

MODULE_LICENSE("GPL");

MODULE_VERSION(RTL8195_VERSION);


int test_send(struct sdio_func *func)
{
	int i;
	u16 val16;
u32 val32;
	u8 data[314];
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
	data[32] = 0x88;
	data[33] = 0x01;
	data[34] = 0x00;
	data[35] = 0x00;

	data[36] = 0xff;	
	data[37] = 0xff;	
	data[38] = 0xff;	
	data[39] = 0xff;	
	data[40] = 0xff;	
	data[41] = 0xff;	

	data[42] = 0x00;	
	data[43] = 0x00;
	data[44] = 0x00;
	data[45] = 0x00;
	data[46] = 0x00;
	data[47] = 0x02;

	data[48] = 0x00;	
	data[49] = 0x00;
	data[50] = 0x00;
	data[51] = 0x00;
	data[52] = 0x00;
	data[53] = 0x01;

	data[54] = 0x10;
	
	data[55] = 0x00;
	data[56] = 0x06;
	data[57] = 0x00;
	data[58] = 0x01;
	data[59] = 0x00;
	data[60] = 0x00;

	
	data[61] = 0x04;	
	data[62] = 0x06;
	data[63] = 0x99;
	data[64] = 0x99;
	data[65] = 0x99;
	data[66] = 0x3e;
	for (i=0;i<247;i++)
	{
		data[i+67] = 0x3e;
	}
	printk("data length is %d\n", sizeof(data));

		for(i=0;i<314;i++)
	{
		printk("data[%d] = %d\n", i, data[i]);
	}
//	dispatchreadwrite(func, data, 314, 1);	
//#define SYS_FUNC_EN 0x02
#define FEN_MREGEN BIT(15)
#define FEN_DCORE BIT(11)
	val16 = sdio_read16(func, 0x10250020);
	printk("val16 = 0x%x\n", val16);
	if((val32 & (FEN_MREGEN | FEN_DCORE)) != (FEN_MREGEN | FEN_DCORE))
	printk("SDIO bus isn't enable.");

	return 0;	
}

static int sdio_init(struct sdio_func *func)
{
    int rc = 0;
	
 //   u8 val = 1;
	u16 val16 = 1;
//	u32 val_2 = 1;
//	u32 val_3 = 1;
//	u32 ret;

    printk("Chris=>%s():\n", __FUNCTION__);
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

	rc = test_send(func);
//		IoWrite8(func, SYS_ISO_CTRL+ SDIO_LOCAL_OFFSET, 0x0a);
//		val= IoRead8(func, SYS_ISO_CTRL+SDIO_LOCAL_OFFSET);
//	    printk("Chris=>%s(): val 0x%x\n", __FUNCTION__, val);
//	
//	//	val_1= IoRead16(func, );
//	//    printk("Chris=>%s(): val 0x%x\n", __FUNCTION__, val_1);	
//		IoWrite8(func, TX_HIQ_OFFSET, 0x00);
//		val= IoRead8(func, TX_HIQ_OFFSET);
//	    printk("Chris=>%s(): val 0x%x\n", __FUNCTION__, val);	

//	InitPowerHAL8195SDIO(func);
//	val = IoRead8(func, SYS_ISO_CTRL);

	sdio_release_host(func);

    return rc;
release:
    sdio_release_host(func);
    return rc;    
}


static int __devinit rtl8195_init_one(struct sdio_func *func, const struct sdio_device_id *id)
{
    static int board_idx = -1;

    int rc = 0;
    board_idx++;
    printk("Chris=>%s():++\n",__FUNCTION__);

    // 1.init SDIO bus and read chip version	
    rc = sdio_init(func);
    if(rc )
	return rc;

    printk(KERN_INFO "%s: This product is covered by one or more of the following patents: US6,570,884, US6,115,776, and US6,327,625.\n", MODULENAME);

    printk("%s", GPL_CLAIM);

    return rc;
}

static void __devexit rtl8195_remove_one(struct sdio_func *func)

{

    int rc = 0;
    printk("Chris=>%s():++\n", __FUNCTION__);

    sdio_claim_host(func);
    rc = sdio_disable_func(func);
    if(rc){
	printk("%s(): sdio_disable_func fail!\n", __FUNCTION__);
    }
   sdio_release_host(func);

}

static const struct sdio_device_id sdio_ids_8195a[] =
{
    { SDIO_DEVICE(0x024c, 0x8821),.driver_data = 4},
};

struct sdio_driver rtl8195 = {
    .probe	= rtl8195_init_one,
    .remove	= __devexit_p(rtl8195_remove_one),
    .name	= MODULENAME,
    .id_table	= sdio_ids_8195a,
};



static int __init rtl8195_init_module(void)
{

	int ret;
	ret = sdio_register_driver(&rtl8195);
	if(ret!=0)
		printk("sdio register driver Failed!\n");
	return ret;

}

static void __exit rtl8195_cleanup_module(void)
{

    sdio_unregister_driver(&rtl8195);

}

module_init(rtl8195_init_module);
module_exit(rtl8195_cleanup_module);
