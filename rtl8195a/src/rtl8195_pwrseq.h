//#include "pwrseqcmd.h"
/* 
	Check document WM-20110607-Paul-RTL8195_Power_Architecture-R02.vsd
	There are 6 HW Power States:
	0: POFF--Power Off
	1: PDN--Power Down
	2: CARDEMU--Card Emulation
	3: ACT--Active Mode
	4: LPS--Low Power State
	5: SUS--Suspend

	The transision from different states are defined below
	TRANS_CARDEMU_TO_ACT
	TRANS_ACT_TO_CARDEMU
	TRANS_CARDEMU_TO_SUS
	TRANS_SUS_TO_CARDEMU
	TRANS_CARDEMU_TO_PDN
	TRANS_ACT_TO_LPS
	TRANS_LPS_TO_ACT	

	TRANS_END
*/

#include "drv_type_sdio.h"
#include "sdio/basic_types.h"



#define POLLING_READY_TIMEOUT_COUNT 500

/*---------------------------------------------*/
//3 The value of cmd: 4 bits
/*---------------------------------------------*/
#define  PWR_CMD_READ 		0x00
     // offset: the read register offset
     // msk: the mask of the read value
     // value: N/A, left by 0
     // note: dirver shall implement this function by read & msk
#define    PWR_CMD_WRITE	0x01
     // offset: the read register offset
     // msk: the mask of the write bits
     // value: write value
     // note: driver shall implement this cmd by read & msk after write
#define    PWR_CMD_POLLING	0x02
     // offset: the read register offset
     // msk: the mask of the polled value
     // value: the value to be polled, masked by the msd field.
     // note: driver shall implement this cmd by
     // do{
     // if( (Read(offset) & msk) == (value & msk) )
     // break;
     // } while(not timeout);
#define    PWR_CMD_DELAY	0x03
     // offset: the value to delay
     // msk: N/A
     // value: the unit of delay, 0: us, 1: ms

#define    PWR_CMD_END		0x04
     // offset: N/A
     // msk: N/A
     // value: N/A

/*---------------------------------------------*/
//3 The value of base: 4 bits
/*---------------------------------------------*/
   // define the base address of each block
#define   PWR_BASEADDR_MAC		0x00
#define   PWR_BASEADDR_USB		0x01
#define   PWR_BASEADDR_PCIE	0x02
#define   PWR_BASEADDR_SDIO 	0x03

/*---------------------------------------------*/
//3 The value of interface_msk: 4 bits
/*---------------------------------------------*/
#define	PWR_INTF_SDIO_MSK	BIT0
#define	PWR_INTF_USB_MSK		BIT1
#define	PWR_INTF_PCI_MSK		BIT2
#define	PWR_INTF_ALL_MSK		(BIT0|BIT1|BIT2|BIT3)

/*---------------------------------------------*/
//3 The value of fab_msk: 4 bits
/*---------------------------------------------*/
#define	PWR_FAB_TSMC_MSK		BIT0
#define	PWR_FAB_UMC_MSK		BIT1
#define	PWR_FAB_ALL_MSK		(BIT0|BIT1|BIT2|BIT3)

/*---------------------------------------------*/
//3The value of cut_msk: 8 bits
/*---------------------------------------------*/
#define	PWR_CUT_TESTCHIP_MSK	BIT0
#define	PWR_CUT_A_MSK		BIT1
#define	PWR_CUT_B_MSK			BIT2
#define	PWR_CUT_C_MSK			BIT3
#define	PWR_CUT_D_MSK		BIT4
#define	PWR_CUT_E_MSK			BIT5
#define	PWR_CUT_F_MSK			BIT6
#define	PWR_CUT_G_MSK		BIT7
#define	PWR_CUT_ALL_MSK		0xFF


typedef enum _PWRSEQ_CMD_DELAY_UNIT_
{
   PWRSEQ_DELAY_US,
   PWRSEQ_DELAY_MS,
} PWRSEQ_DELAY_UNIT;

typedef struct _WL_PWR_CFG_
{
	u2Byte 	offset;
	u1Byte 	cut_msk; 		
	u1Byte 	fab_msk:4; 		
	u1Byte 	interface_msk:4; 		
	u1Byte 	base:4; 	
	u1Byte 	cmd:4; 	
	u1Byte 	msk;
	u1Byte 	value;
	
} WLAN_PWR_CFG, *PWLAN_PWR_CFG;


#define	RTL8195_TRANS_CARDEMU_TO_ACT_STEPS	10
#define	RTL8195_TRANS_ACT_TO_CARDEMU_STEPS	10
#define	RTL8195_TRANS_CARDEMU_TO_SUS_STEPS	10
#define	RTL8195_TRANS_SUS_TO_CARDEMU_STEPS	10
#define	RTL8195_TRANS_CARDEMU_TO_PDN_STEPS	10
#define	RTL8195_TRANS_PDN_TO_CARDEMU_STEPS	10
#define	RTL8195_TRANS_ACT_TO_LPS_STEPS	15
#define	RTL8195_TRANS_LPS_TO_ACT_STEPS	15	
#define	RTL8195_TRANS_END_STEPS	1


#define RTL8195_TRANS_CARDEMU_TO_ACT 														\
	/* format */																\
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value }, // comments here*/								\
	{0x0006, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_POLLING, BIT1, BIT1},/* wait till 0x04[17] = 1    power ready*/	\
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT7, 0}, /* 0x04[15] = 0 disable HWPDN (control by DRV)*/\
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT4|BIT3, 0}, /*0x04[12:11] = 2b'00 disable WL suspend*/	\
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT0, BIT0}, /*0x04[8] = 1 polling until return 0*/	\
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_POLLING, BIT0, 0}, /*wait till 0x04[8] = 0*/	

#define RTL8195_TRANS_ACT_TO_CARDEMU													\
	/* format */																\
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value }, // comments here*/								\
	{0x001F, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0},/*0x1F[7:0] = 0 turn off RF*/	\
	{0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT0|BIT1, 0}, /* 0x02[1:0] = 0	reset BB*/			\
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT1, BIT1}, /*0x04[9] = 1 turn off MAC by HW state machine*/	\
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_POLLING, BIT1, 0}, /*wait till 0x04[9] = 0 polling until return 0 to disable*/	\

#define RTL8195_TRANS_CARDEMU_TO_SUS													\
	/* format */																\
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value }, // comments here*/								\
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK|PWR_INTF_SDIO_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT3|BIT4, BIT3}, /*0x04[12:11] = 2b'01enable WL suspend*/	\
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT3|BIT4, BIT3|BIT4}, /*0x04[12:11] = 2b'11enable WL suspend for PCIe*/	\
	{0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,PWR_BASEADDR_SDIO,PWR_CMD_WRITE, BIT0, BIT0}, /*Set SDIO suspend local register*/	\
	{0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,PWR_BASEADDR_SDIO,PWR_CMD_POLLING, BIT1, 0}, /*wait power state to suspend*/

#define RTL8195_TRANS_SUS_TO_CARDEMU													\
	/* format */																\
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value }, // comments here*/								\
	{0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,PWR_BASEADDR_SDIO,PWR_CMD_WRITE, BIT0, 0}, /*Set SDIO suspend local register*/	\
	{0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,PWR_BASEADDR_SDIO,PWR_CMD_POLLING, BIT1, BIT1}, /*wait power state to suspend*/\
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT3|BIT4, 0}, /*0x04[12:11] = 2b'01enable WL suspend*/

#define RTL8195_TRANS_CARDEMU_TO_CARDDIS													\
	/* format */																\
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value }, // comments here*/								\
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK|PWR_INTF_SDIO_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT3|BIT4, BIT3}, /*0x04[12:11] = 2b'01enable WL suspend*/	\
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT2, BIT2}, /*0x04[10] = 2b'1*/	\
	{0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,PWR_BASEADDR_SDIO,PWR_CMD_WRITE, BIT0, BIT0}, /*Set SDIO suspend local register*/	\
	{0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,PWR_BASEADDR_SDIO,PWR_CMD_POLLING, BIT1, 0}, /*wait power state to suspend*/

#define RTL8195_TRANS_CARDDIS_TO_CARDEMU													\
	/* format */																\
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value }, // comments here*/								\
	{0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,PWR_BASEADDR_SDIO,PWR_CMD_WRITE, BIT0, 0}, /*Set SDIO suspend local register*/	\
	{0x0086, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,PWR_BASEADDR_SDIO,PWR_CMD_POLLING, BIT1, BIT1}, /*wait power state to suspend*/\
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT3|BIT4, 0}, /*0x04[12:11] = 2b'01enable WL suspend*/

#define RTL8195_TRANS_CARDEMU_TO_PDN												\
	/* format */																\
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value }, // comments here*/								\
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT7, BIT7},/* 0x04[15] = 1*/

#define RTL8195_TRANS_PDN_TO_CARDEMU												\
	/* format */																\
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value }, // comments here*/								\
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT7, 0},/* 0x04[15] = 0*/

#define RTL8195_TRANS_ACT_TO_LPS														\
	/* format */																\
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value }, // comments here*/								\
	{0x0522, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0xFF}, /*.	0x522[7:0] = 0xFF  TX pause*/\
	{0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT1|BIT0, BIT1}, /*.	0x02[1:0] = 2b'10	Reset BB TRX*/\
	{0x0100, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0x3F}, /*.	0x100[7:0] = 0x3F	 Reset MAC TRX*/\
	{0x0101, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT1, 0}, /*.	0x101[1] = 0	 check if removed later.*/\
	{0x0553, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT5, BIT5}, /*.	0x553[5] = 1	 respond TX ok to scheduler */\
	{0x0093, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0x14}, /*. 0x93[7:0] = 0xd4, 94, 14 configure LPS option, enable PFM, disable other Ana blocks*/\
	{0x0029, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT6|BIT7, BIT6|BIT7}, /*. 0x29[7:6] = 2b'11 gated BB clock*/\
	{0x0008, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT4, BIT4}, /*. 0x08[4] = 1	switch TSF clock to 32K*/\
	{0x0109, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_POLLING, BIT7, BIT7}, /*Polling 0x109[7]=1  TSF in 32K*/\
	{0x0090, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT0, BIT0}, /*. 0x90[0] = 1	enable WL_LPS_EN*/\
	{0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_DELAY, 0, PWRSEQ_DELAY_MS}, /*. delay_us(20)	delay, CPU may stock here when clock gated*/


#define RTL8195_TRANS_LPS_TO_ACT															\
	/* format */																\
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value }, // comments here*/								\
	{0x0080, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,PWR_BASEADDR_SDIO,PWR_CMD_WRITE, 0xFF, 0x84}, /*SDIO RPWM*/\
	{0xFE58, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0x84}, /*USB RPWM*/\
	{0x0361, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0x84}, /*PCIe RPWM*/\
	{0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_DELAY, 0, PWRSEQ_DELAY_MS}, /*Delay*/\
	{0x0008, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT4, 0}, /*.	0x08[4] = 0		 switch TSF to 40M*/\
	{0x0109, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_POLLING, BIT7, 0}, /*Polling 0x109[7]=0  TSF in 40M*/\
	{0x0029, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT6|BIT7, 0}, /*.	0x29[7:6] = 2b'00	 enable BB clock*/\
	{0x0101, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT1, BIT1}, /*.	0x101[1] = 1*/\
	{0x0100, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0xFF}, /*.	0x100[7:0] = 0xFF	 enable WMAC TRX*/\
	{0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT1|BIT0, BIT1|BIT0}, /*.	0x02[1:0] = 2b'11	 enable BB macro*/\
	{0x0522, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0}, /*.	0x522 = 0*/
 
#define RTL8195_TRANS_END															\
	/* format */																\
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value }, // comments here*/								\
	{0xFFFF, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,0,PWR_CMD_END, 0, 0}, //

BOOLEAN PWR_SEQ_PARSER(struct sdio_func *func, u8 CUT, u8 FAB, u8 INTF, WLAN_PWR_CFG PWR_SEQ_CFG[]);
extern WLAN_PWR_CFG rtl8195_power_on_flow[RTL8195_TRANS_CARDEMU_TO_ACT_STEPS+RTL8195_TRANS_END_STEPS];
//extern WLAN_PWR_CFG rtl8195_radio_off_flow[RTL8195_TRANS_ACT_TO_CARDEMU_STEPS+RTL8195_TRANS_END_STEPS];
//extern WLAN_PWR_CFG rtl8195_card_disable_flow[RTL8195_TRANS_ACT_TO_CARDEMU_STEPS+RTL8195_TRANS_CARDEMU_TO_PDN_STEPS+RTL8195_TRANS_END_STEPS];
//extern WLAN_PWR_CFG rtl8195_card_enable_flow[RTL8195_TRANS_ACT_TO_CARDEMU_STEPS+RTL8195_TRANS_CARDEMU_TO_PDN_STEPS+RTL8195_TRANS_END_STEPS];
//extern WLAN_PWR_CFG rtl8195_suspend_flow[RTL8195_TRANS_ACT_TO_CARDEMU_STEPS+RTL8195_TRANS_CARDEMU_TO_SUS_STEPS+RTL8195_TRANS_END_STEPS];
//extern WLAN_PWR_CFG rtl8195_resume_flow[RTL8195_TRANS_ACT_TO_CARDEMU_STEPS+RTL8195_TRANS_CARDEMU_TO_SUS_STEPS+RTL8195_TRANS_END_STEPS];
//extern WLAN_PWR_CFG rtl8195_hwpdn_flow[RTL8195_TRANS_ACT_TO_CARDEMU_STEPS+RTL8195_TRANS_CARDEMU_TO_PDN_STEPS+RTL8195_TRANS_END_STEPS];
//extern WLAN_PWR_CFG rtl8195_enter_lps_flow[RTL8195_TRANS_ACT_TO_LPS_STEPS+RTL8195_TRANS_END_STEPS];
//extern WLAN_PWR_CFG rtl8195_leave_lps_flow[RTL8195_TRANS_LPS_TO_ACT_STEPS+RTL8195_TRANS_END_STEPS];


