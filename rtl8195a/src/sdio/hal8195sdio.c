//#include "hal8195sdio.h"
//#include "../pwrseqcmd.h"
#include "../rtl8195_pwrseq.h"
#include "sdio_io.h"


/* HW Init Functions*/

BOOLEAN PWR_SEQ_PARSER(struct sdio_func *func, u8 CUT, u8 FAB, u8 INTF, WLAN_PWR_CFG PWR_SEQ_CFG[])
{
	u32 AryIdx=0;
	BOOLEAN PollingBit=FALSE;
	WLAN_PWR_CFG PWR_SEQ_CMD;
	u8 value;
	u32 PollingCount;
	u32 offset;
	
	do
	{
		PWR_SEQ_CMD=PWR_SEQ_CFG[AryIdx];

		//2 Only Handle the command whose FAB, CUT, and Interface are matched
		if((PWR_SEQ_CMD.fab_msk&FAB)&&(PWR_SEQ_CMD.cut_msk&CUT)&&(PWR_SEQ_CMD.interface_msk&INTF))
		{
			switch(PWR_SEQ_CMD.cmd)
			{
				case PWR_CMD_READ:
					break;

				case PWR_CMD_WRITE:
					//Add base offset for SDIO
					if(PWR_SEQ_CMD.base==PWR_BASEADDR_SDIO)
						offset = PWR_SEQ_CMD.offset|0x10250000;
					else
						offset = PWR_SEQ_CMD.offset;
					//Read Back the value
					value=IoRead8(func, offset);
					value=value&(~PWR_SEQ_CMD.msk);
					value=value|(PWR_SEQ_CMD.value&PWR_SEQ_CMD.msk);
					//Write Back the value
					IoWrite8(func, offset, value);
					break;

				case PWR_CMD_POLLING:
					PollingBit=FALSE;
					PollingCount = 0;
					if(PWR_SEQ_CMD.base==PWR_BASEADDR_SDIO)
						offset = PWR_SEQ_CMD.offset|0x10250000;
					else
						offset = PWR_SEQ_CMD.offset;
					do
					{
						PollingCount++;
						value=IoRead8(func, offset);
						value=value&PWR_SEQ_CMD.msk;
						if(value==(PWR_SEQ_CMD.value&PWR_SEQ_CMD.msk))
							PollingBit=TRUE;
						else
						{
							if(PollingCount>POLLING_READY_TIMEOUT_COUNT)
								return FALSE;
						//	else
						//	sleep(5);
						}
						
					}while(!PollingBit);
					break;

				case PWR_CMD_DELAY:
					//if(PWR_SEQ_CMD.value==PWRSEQ_DELAY_US)
					//	sleep(PWR_SEQ_CMD.offset/1000);
					//else 
					//	sleep(PWR_SEQ_CMD.offset);
					break; 

				case PWR_CMD_END:
					// When this command is parsed, end the process
					return TRUE;
					break;

				default:
					return FALSE;
					break;					
			}

		}
		AryIdx++;//Add Array Index
	}while(1);
	return TRUE;
}

u32 InitPowerHAL8195SDIO(struct sdio_func *func)
{

	u32	  value32=0x00000000;
	u16	  value16=0x0000;
	u8	  value8=0x00;
//	FILE      *fp=NULL;

	printk("InitPower8195SDIO=======>\n");

//	SDIOClearRx_seq();

	return PWR_SEQ_PARSER(func, PWR_CUT_TESTCHIP_MSK, PWR_FAB_TSMC_MSK, PWR_INTF_SDIO_MSK, rtl8195_power_on_flow);	;	
}

#if 0
u4Byte InitMACHAL8195SDIO(void)
{
	u1Byte	temp[1]={0x00};
	u4Byte l=0;
	u4Byte value32;
	u2Byte   value16;
	u1Byte     value8;
	FILE  *fp=NULL;
	u2Byte WriteValue16 = 0 ;

	printk("MACInit=============1111>\n");
     
	//Set TRXDMA Control Reg
	WriteValue16 |= 0x3 <<14; //TXDMA HIQ mapping to hi priority queue
	WriteValue16 |= 0x3 << 12; // TXDMA MGQ mapping to hi priority queue
	WriteValue16 |= 0x3 << 10;// TXDMA BKQ mapping to hi priority queue
	WriteValue16 |= 0x3 << 8;// TXDMA BEQ mapping to hi priority queue
	WriteValue16 |= 0x3 << 6;// TXDMA VIQ mapping to hi priority queue
	WriteValue16 |= 0x3 << 4;// TXDMA VOQ mapping to hi priority queue

					
	IoWrite16(TRX_DMA_CTRL,WriteValue16);

	
  	// MyPrintf("Set_SDIO_HIMR start !\n");
	//Set SDIO HIMR to 0; turn off HIMR
	//AfxMessageBox("Before set sdio HIMR", MB_ICONERROR | MB_OK);
	//Set_SDIO_HIMR(0);
	//IoWrite8(SDIO_HIMR, 0);

	IoRead32(SDIO_FREE_TXPG);
	IoRead32(0x1025001c);

	printk("init_LLT_table:\n");
   	value8=0x00;
	IoWrite8(REG_CR,value8);
	value8 = (HCI_TXDMA_EN | HCI_RXDMA_EN | TXDMA_EN | RXDMA_EN
		| PROTOCOL_EN | SCHEDULE_EN | MACTXEN | MACRXEN);
//	ASSERT(0xFF == value8);
	IoWrite8(REG_CR, value8);
    
	IoWrite16(REG_CR,IoRead16(REG_CR)|BIT9);   //MAC Security Enable

	//return TRUE;
//	init_LLT_table();

	// reset TSF timer  //KaiYuan added for 88e
	IoWrite8(0x0604, 0x01);
/*
	if ( UiSetting.MacSettingGen.test_option.lb_mode == LB_Disable) {
		value8 = _NPQ(NTWOMAC_PAGE_NUM_NPQ);
		value32 = _HPQ(NTWOMAC_PAGE_NUM_HPQ) | _LPQ(NTWOMAC_PAGE_NUM_LPQ)
				| _PUBQ(NTWOMAC_PAGE_NUM_PUBQ) | LD_RQPN;	
	}
	else {
		value8 = _NPQ(NLLB_PAGE_NUM_NPQ);
		value32 = _HPQ(NLLB_PAGE_NUM_HPQ) | _LPQ(NLLB_PAGE_NUM_LPQ)
				| _PUBQ(NLLB_PAGE_NUM_PUBQ) | LD_RQPN;	
	}
*/
	IoWrite8(REG_RQPN_NPQ, value8);

	IoWrite32(REG_RQPN, value32);


	value32 = _PUBQ(0x7f)|LD_RQPN;
	printk("REG 0x200:%x\n",value32);

#if 0
//init_ID
	   
	WriteUSBRegisterBYTE(REG_MACID, 6, MacAddr);
    WriteUSBRegisterBYTE(REG_MACID_2, 6,MacAddr2);
	WriteUSBRegisterBYTE(REG_BSSID, 6, BSSID1);
    WriteUSBRegisterBYTE(REG_BSSID_2, 6,BSSID2);

	// Set MAR
	IoWrite32(REG_MAR, 0xFFFFFFFF);
	IoWrite32((REG_MAR + 4), 0xFFFFFFFF);
#endif
	//KaiYuan added for 88e
	//set macid
	IoWrite32(REG_MACID, 0x456789aa);
	IoWrite16(0x614, 0x0123);
	//set macid
	IoWrite32(REG_BSSID, 0xcccccccc);
	IoWrite16(0x61C, 0xcccc);


	// init_page
	printk("init_page:\n");
	// Tx page boundary
#if LLT_HALF_PAGE_NUM
//KaiYuan removed
#else
	value8 = ( UiSetting.MacSettingGen.test_option.lb_mode == LB_Disable) ? TX_PAGE_BOUNDARY_NORMAL_MODE :
									TX_PAGE_BOUNDARY_LOOPBACK_MODE;

	IoWrite8(REG_TXPKTBUF_BCNQ_BDNY, value8);
	IoWrite8(REG_TXPKTBUF_MGQ_BDNY, value8);

	if ( UiSetting.MacSettingGen.test_option.lb_mode != LB_Disable)
	{
		//IoWrite8(REG_WMAC_HEADER, value8);
		IoWrite8(REG_WMAC_HEADER, 0x82); //KaiYuan modified for 88e
	}

	IoWrite8(REG_TDECTL+1, value8);

	//Rx page Boundary
	//IoWrite16(REG_RX_PGBNDY, 0x27FF);
	//IoWrite16(REG_RX_PGBNDY, 0x1FFF);//KaiYuan modified for 88e
	IoWrite16(REG_RX_PGBNDY, 0x18FF);//KaiYuan modified for 88e
#endif

	printk("init_page: BCNQ_BDNY:%x\n", value8);

	//init_dma_ctrl
	printk("init_dma_ctrl:\n");
	initQueuePrioritySDIO();
	
	//init_network_type
	printk("init_network_type:\n");

	value32 = IoRead32(REG_CR);
	value32 = value32 & ~MASK_NETTYPE;

	value32 = value32 | _NETTYPE(NT_LINK_AP);//KaiYuan added for 88e
	IoWrite32(REG_CR, value32);

	//set dur extra protect =0 //KaiYuan added for 88e
	IoWrite16(REG_TXPAUSE, 0x0000);

	//set slot time //KaiYuan added for 88e
	IoWrite8(REG_SLOT, 0x05);

	//shorten the waiting time for tx response BA  //KaiYuan added for 88e
	IoWrite16(REG_BACAMCMD, 0xc000);


	//set s2Byte GI/s2Byte preamble enable of Tx response  //KaiYuan added for 88e
	IoWrite32(REG_WMAC_TRXPTCL_CTL, 0x0e710000);


	//set basic/stbc response rate  //KaiYuan added for 88e
	IoWrite8(0x481, 0x05);

	//set basic/stbc response rate  //KaiYuan added for 88e
	IoWrite8(0x482, 0x0f);

	//set pifs //KaiYuan added for 88e
	IoWrite8(REG_PIFS, 0x19);

	//set HWSEQ_CTRL
	//if (Adapter1->protocol_setting.bHwCtrlSeq)
	//	IoWrite8(REG_HWSEQ_CTRL, 0x0);
	//else
	IoWrite8(REG_HWSEQ_CTRL, 0xFF);

	//set_page_size
	printk("set_page_size:\n");
	//value8 = _PSRX(PBP_128) | _PSTX(PBP_128);//KaiYuan marked for 88e
	value8 = _PSTX(PBP_128);//KaiYuan modified for 88e
	IoWrite8(REG_PAGE_SIZE, value8);

	//set_wmac
	printk("set_wmac:\n");	
	//value32 = AAP | APM | AM |AB  |ADD3|APWRMGT| APP_ICV | APP_MIC |APP_FCS|ACRC32|AICV|ADF |ACF|AMF|HTC_LOC_CTRL;
	//value32=0x40044a0f;	//KaiYuan modified for 88e
	value32=0xE0007B3E;	//KaiYuan modified for 88e
	IoWrite32(REG_RCR, value32);
	
	//init_adaptive_ctrl
	printk("init_adaptive_ctrl:\n");
	// Response Rate Set
	value32 = IoRead32(REG_RRSR);
	value32 |= RATE_BITMAP_ALL;
	IoWrite32(REG_RRSR, value32);

	// CF-END Threshold
	//IoWrite8(REG_CFEND_TH, 0x1);

	// SIFS
	value16 = _SPEC_SIFS_CCK(0x10) | _SPEC_SIFS_OFDM(0x10);
	IoWrite16(REG_SPEC_SIFS, value16);

	// Retry Limit
	value16 = _LRL(0x8) | _SRL(0x7);//KaiYuan modified for 88e
	//value16 = _LRL(0x30) | _SRL(0x30);
	IoWrite16(REG_RL, value16);

	// init_edca
	printk("init_edca:\n");
	//value16 = _SIFS_CCK_CTX(0x10) | _SIFS_CCK_TRX(0x10);
    	value16 = _SIFS_CCK_CTX(0x0A) | _SIFS_CCK_TRX(0x0A);
	IoWrite16(REG_SIFS_CCK, value16);

	value16 = _SIFS_OFDM_CTX(0x10) | _SIFS_OFDM_TRX(0x10);
	IoWrite16(REG_SIFS_OFDM, value16);

	value32=IoRead32(REG_EDCA_VO_PARAM);
	value32&=0x0000FFFF;
	IoWrite32(REG_EDCA_VO_PARAM,value32);

	printk("init_Retry function:\n");
	IoWrite32(REG_DARFRC, 0x00000000);
	IoWrite32(REG_DARFRC + 4, 0x06050401);
	IoWrite32(REG_RARFRC, 0x00000000);
	IoWrite32(REG_RARFRC+4, 0x06050401);

	// Set Data Auto Rate Fallback Reg.
	for(int i = 0 ; i < 4 ; i++){
		IoWrite32(REG_ARFR0+i*4, 0x1f0ffff0);
	}

	// Set ACK timeout
	IoWrite8(REG_ACKTO, 0x40);      

	printk("init Agg function:\n");
	IoWrite8(REG_TRX_DMA_CTRL, (IoRead8(REG_TRX_DMA_CTRL)&(~RXDMA_AGG_EN)));

	value16 = IoRead16(REG_TRX_DMA_CTRL);
	value16 = value16|0xfff0;	//KaiYuan modified for 88e
	IoWrite16(REG_TRX_DMA_CTRL, value16);

	value8 = 0x0b;
	IoWrite8(REG_CR+3, value8);

	//set sec register  //KaiYuan added for 88e
	IoWrite16(REG_SECCFG, 0x01cc);

	//set TCR register  //KaiYuan added for 88e
	IoWrite8(REG_TCR+1, 0x00);
	
	//KaiYuan added for 88e
	IoWrite8(REG_RXDMA_AGG_PG_TH,0x07);
	IoWrite8(REG_RXDMA_AGG_PG_TH+1,0x05);

	//set rx drive info size register  //KaiYuan added for 88e
	//IoWrite8(REG_RX_DRVINFO_SZ, 0x02);
	IoWrite8(REG_RX_DRVINFO_SZ, 0x00);

	//set response TX info  //KaiYuan added for 88e
	IoWrite32(REG_WMAC_RESP_TXINFO, 0x000a2483);

	//set VOQ TXOP limit  //KaiYuan added for 88e
	IoWrite16(0x502, 0x0186);

	//set VIQ TXOP limit  //KaiYuan added for 88e
	IoWrite16(0x506, 0x03bc);	

	//set NAV  //KaiYuan added for 88e
	IoWrite32(REG_RD_NAV_NXT, 0x001b0005);	

	//set stbc & ness  //KaiYuan added for 88e
	IoWrite8(REG_STBC_SETTING, 0x00);	
	
	//IoWrite8(REG_LBDLY, 0x4);//KaiYuan added for 88e

	//InitBeaconParameter();

	IoWrite8(0x605,IoRead8(0x605)|0x30);

	IoWrite8(0x55e,0x30);
	IoWrite8(0x55f,0x30);
	IoWrite8(0x606,0x30);
	IoWrite8(0x5e4,0x38);
	IoWrite8(0x523,0x10);

	//Set HIMR = 1
	value8 = ( RX_REQUEST_MSK); // turn on RX Request , Rx error Mask
	Set_SDIO_HIMR(value8);

	//Turn Off CF-end
	value8 = IoRead8(RD_CTRL+1);
	value8 |= 0x7;
	IoWrite8(RD_CTRL+1,value8);
	
	//Disable Control Frame Receiving
	
	value8  = IoRead8(RECIVE_CONF_REG+1);
	value8 &= ~(1<<4); 
	IoWrite8(RECIVE_CONF_REG +1 , value8);

	//KaiYuan Reinit Start for 88e

	// HISR - turn all off
	value32 = 0xffffffff;//KaiYuan modified for 88e
	IoWrite32(REG_HISR, value32);
	IoWrite32(REG_HIMR, value32);

	//set dur extra protect =0 //KaiYuan added for 88e
	IoWrite16(REG_TXPAUSE, 0x0000);

	//KaiYuan modified for 88e
	IoWrite16(REG_TRX_DMA_CTRL, 0xfff0);

	//set TCR register  //KaiYuan added for 88e
	IoWrite8(REG_TCR+1, 0x00);

	IoWrite32(0x10250000, 0x00000000);
	//KaiYuan Reinit End

	return TRUE;
}
#endif

