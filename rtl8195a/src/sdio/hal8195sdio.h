
/******************************************/
	/* Include files*/
/******************************************/
#include "basic_types.h"

/******************************************/
	/*Macro*/
/******************************************/
//For 88C SDIO
#define  SDIO_LOCAL_DEVICE_ID           0
#define   FW_FIFO_DEVICE_ID 		1

#define   WLAN_IOREG_DEVICE_ID 		8

#define   WLAN_HIQ_DEVICE_ID 			4
#define   WLAN_MIQ_DEVICE_ID 		5
#define   WLAN_LOQ_DEVICE_ID 		6
#define   WLAN_RX0FF_DEVICE_ID 		7
#define   WLAN_FIFO_DEVICE_ID		3
#define   UNDEFINED_DEVICE_ID    	(-1)


#define SDIO_LOCAL_MSK				0xFFF
#define WLAN_IOREG_MSK 	             0xFFFF
#define WLAN_FIFO_MSK			      0x1FFF

//IO Bus domain address mapping
#define SDIO_LOCAL_OFFSET         0x10250000
#define WLAN_IOREG_OFFSET        0x10260000
#define FW_FIFO_OFFSET 	      0x10270000
#define  TX_HIQ_OFFSET	             0x10310000
#define  TX_MIQ_OFFSET		      0x1032000
#define  TX_LOQ_OFFSET		      0x10330000
#define  RX_RXOFF_OFFSET	      0x10340000


//88C SDIO Reg Address 

#define TRX_DMA_CTRL         (0x10C | WLAN_IOREG_OFFSET)
#define RD_CTRL		          (0x524 | WLAN_IOREG_OFFSET)
#define GPIO_PIN_CTRL        (0x44  |  WLAN_IOREG_OFFSET)
#define RECIVE_CONF_REG   (0x608 | WLAN_IOREG_OFFSET)
//SDIO Local registers

#define SDIO_TX_CTRL 	                        (0x4  |SDIO_LOCAL_OFFSET)
#define SDIO_FREE_TXPG 	                        (0x20|SDIO_LOCAL_OFFSET)
#define SDIO_HIMR 	                               (0x14|SDIO_LOCAL_OFFSET)
#define SDIO_HISR 	                               (0x18|SDIO_LOCAL_OFFSET)
//#define SDIO_RX0_REQ_LEN_32_BYTE      (0x19|SDIO_LOCAL_OFFSET)
#define SDIO_RX0_REQ_LEN_1_BYTE 	   (0x1c|SDIO_LOCAL_OFFSET)


//SDIO HIMR MASK


#define RX_REQUEST_MSK    BIT(0)
#define LOQ_AVAL_MSK        BIT(1)
#define MIQ_AVAL_MSK        BIT(2)
#define HIQ_AVAL_MSK        BIT(3)
#define CPWM_MSK               BIT(6)
#define C2HCMD_MSK           BIT(5)
#define WLLANOFF_MSK       BIT(6)
#define RXERR_MSK              BIT(7)

/******************************************/
	/* Data Structure Declaration*/
/******************************************/
typedef struct _TX_QUEUE_MAPPING
{

      u1Byte HIQueueToPriorty;
      u1Byte MGQueueToPriorty;
      u1Byte BEQueueToPriorty;
      u1Byte BKQueueToPriorty;
      u1Byte VIQueueToPriorty;
      u1Byte VOQueueToPriorty;
	 

}TX_QUEUE_MAPPING,*PTX_QUEUE_MAPPING;


typedef struct _SDIO_IO_DESC {
	IN      BOOLEAN    WriteFlag;
	IN      u4Byte    uOffset;
	IN      unsigned    uLength;
	IN OUT  UCHAR      pbyData;
	IN      unsigned    uAddress;
} SDIO_IO_DESC, *PSDIO_IO_DESC;

/******************************************/

u32 InitPowerHAL8195SDIO(struct sdio_func *func);
