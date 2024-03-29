#ifndef _8195_SDIO_REG_H
#define _8195_SDIO_REG_H
#include "autoconf.h"
#include "basic_types.h"


//For 8195A SDIO
#define SDIO_LOCAL_DEVICE_ID			0
//#define FW_FIFO_DEVICE_ID 		1
//#define WLAN_IOREG_DEVICE_ID 		8
#define WLAN_TX_HIQ_DEVICE_ID			4
#define WLAN_TX_MIQ_DEVICE_ID			5
#define WLAN_TX_LOQ_DEVICE_ID			6
#define WLAN_RX0FF_DEVICE_ID			7
//#define   WLAN_FIFO_DEVICE_ID		3
#define   UNDEFINED_DEVICE_ID			(-1)

#define SDIO_MAX_TX_QUEUE				3 //HIQ, MIQ, LOQ
#define SDIO_TX_FREE_PG_QUEUE			4 

#define SDIO_LOCAL_MSK					0xFFF
//#define WLAN_IOREG_MSK				0xFFFF
#define WLAN_FIFO_MSK					0x1FFF
//#define WLAN_RX0FF_MSK 				0x1fff
#define WLAN_RX0FF_MSK 				0x3
//IO Bus domain address mapping
#define SDIO_LOCAL						0x10250000
#define WLAN_TX_FIFO					0x10310000
#define WLAN_RX_FIFO					0x10340000


#define SDIO_LOCAL_OFFSET				0x10250000
//#define WLAN_IOREG_OFFSET				0x10260000
//#define FW_FIFO_OFFSET					0x10270000
//#define WLAN_FIFO_OFFSET				0x10280000
#define TX_HIQ_OFFSET					0x10310000	
#define TX_MIQ_OFFSET					0x10320000
#define TX_LOQ_OFFSET					0x10330000

#define RX_RXOFF_OFFSET				0x10340000


//SDIO Local registers
#define SDIO_TX_CTRL					0x00 // 1byte
#define SDIO_STATIS_RECOVERY_TIMOUT	0x02 // 2bytes
#define SDIO_32K_TRANS_IDLE_TIME		0x04 // 2bytes
#define SDIO_HIMR						0x14 // 4bytes
#define SDIO_HISR						0x18 // 4bytes
#define SDIO_RX0_REQ_LEN				0x1c // 4bytes
#define SDIO_FREE_TXBD_NUM			0x20 // 2bytes
#define SDIO_TX_SEQNUM 				0x24 // 1byte, not used
#define HCPWM							0x38 // 1byte, host domain, sync from CCPWM
#define HCPWM2							0x3a // 2bytes, sync from CCPWM2
#define REG_SDIO_H2C_MSG				0x60 // 4bytes, host domain, sync from CPU_H2C_MSG
#define REG_SDIO_C2H_MSG				0x64 // 4bytes, sync from CPU_C2H_MSG
#define REG_SDIO_H2C_MSG_EXT			0x68 // 4bytes, sync from CPU_H2C_MSG_EXT
#define REG_SDIO_C2H_MSG_EXT			0x6c // 4bytes, sync from CPU_C2H_MSG_EXT
#define HRPWM							0x80 // 1byte, driver to FW, host domain, sync to CRPWM
#define HRPWM2							0x82 // 2bytes, driver to FW, host domain, sync to CRPWM2

// SDIO Host Interrupt Service Routine
#define SDIO_HISR_RX_REQUEST				BIT0
#define SDIO_HISR_AVAL_INT					BIT1
#define SDIO_HISR_TXPKT_OVER_BUFF		BIT2
#define SDIO_HISR_TX_AGG_SIZE_MISMATCH	BIT3
//BIT4~16 not used
#define SDIO_HISR_C2H_MSG_INT				BIT17
#define SDIO_HISR_CPWM1					BIT18
#define SDIO_HISR_CPWM2					BIT19
#define SDIO_HISR_H2C_BUS_FAIL				BIT20
#define SDIO_HISR_TXBD_OVF					BIT21
#define SDIO_HISR_CPU_NOT_RDY				BIT22
//BIT21~31 not used

#define MASK_SDIO_HISR_CLEAR				(SDIO_HISR_TXPKT_OVER_BUFF|\
											SDIO_HISR_TX_AGG_SIZE_MISMATCH|\
											SDIO_HISR_C2H_MSG_INT|\
											SDIO_HISR_CPWM1|\
											SDIO_HISR_CPWM2|\
											SDIO_HISR_H2C_BUS_FAIL|\
											SDIO_HISR_TXBD_OVF|\
											SDIO_HISR_CPU_NOT_RDY)
											
// RTL8195A SDIO Host Interrupt Mask Register
#define SDIO_HIMR_RX_REQUEST_MSK			BIT0
#define SDIO_HIMR_AVAL_MSK				BIT1
#endif
