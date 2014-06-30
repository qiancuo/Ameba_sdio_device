#ifndef _8195_SDIO_REG_H
#define _8195_SDIO_REG_H
#include "basic_types.h"


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
#define WLAN_FIFO_OFFSET          0x10280000
#define  TX_HIQ_OFFSET	             0x10310000
#define  TX_MIQ_OFFSET		      0x10320000
#define  TX_LOQ_OFFSET		      0x10330000
#define  RX_RXOFF_OFFSET	      0x10340000



//88C SDIO Reg Address 

#define TRX_DMA_CTRL (0x10C | WLAN_IOREG_OFFSET)
#define WLAN_FIFO_RX (0x6000 | RX_RXOFF_OFFSET)
#define GPIO_PIN_CTRL (0x44  |  WLAN_IOREG_OFFSET)

//SDIO Local registers

#define SDIO_TX_CTRL 	                        (0x4  |SDIO_LOCAL_OFFSET)
#define SDIO_FREE_TXPG 	                        (0x20|SDIO_LOCAL_OFFSET)
#define SDIO_HIMR 	                               (0x14|SDIO_LOCAL_OFFSET)
#define SDIO_HISR 	                               (0x18|SDIO_LOCAL_OFFSET)
#define SDIO_RX0_REQ_LEN_32_BYTE      (0x1c|SDIO_LOCAL_OFFSET)
#define SDIO_RX0_REQ_LEN_1_BYTE 	   (0x1c|SDIO_LOCAL_OFFSET)

#define SDIO_RX0_REQ_LEN_1_BYTE_TEMP 	   (0x1c|SDIO_LOCAL_OFFSET)

//ULONG  _cvrt2ftaddr(const ULONG addr, ULONG *pftaddr) ;



#endif
