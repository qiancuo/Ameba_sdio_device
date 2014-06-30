
#if 0
//-----------------------------------------------------
//
//	0x0000h ~ 0x00FFh	System Configuration
//
//-----------------------------------------------------
#define REG_SYS_ISO_CTRL		0x0000
#define REG_SYS_FUNC_EN			0x0002
#define REG_APS_FSMCO			0x0004
#define REG_PSC_FSM				0x0004
#define REG_SYS_CLKR			0x0008
#define REG_9346CR				0x000A
#define REG_EE_VPD				0x000C
#define REG_AFE_MISC			0x0010
#define REG_SPS0_CTRL			0x0011
#define REG_SPS1_CTRL			0x0018
#define REG_SPS_OCP_CFG			0x0018
#define REG_RSV_CTRL			0x001C
#define REG_RF_CTRL				0x001F
#define REG_LDOA15_CTRL			0x0020
#define REG_LDOV12D_CTRL		0x0021
#define REG_LDOHCI12_CTRL		0x0022
#define REG_LPLDO_CTRL			0x0023
#define REG_AFE_XTAL_CTRL		0x0024
#define REG_AFE_PLL_CTRL		0x0028
#define REG_EFUSE_CTRL			0x0030
#define REG_EFUSE_TEST			0x0034
#define REG_PWR_DATA			0x0038
#define REG_CAL_TIMER			0x003C
#define REG_ACLK_MON			0x003E
#define REG_GPIO_MUXCFG			0x0040
#define REG_GPIO_PIN_CTRL		0x0044
#define REG_GPIO_INTM			0x0048
#define REG_LEDCFG				0x004C
#define REG_FSIMR				0x0050
#define REG_FSISR				0x0054

#define REG_8051FWDL			0x0080
#define REG_RPWM				0x0083
#define REG_BIST_SCAN			0x00D0
#define REG_BIST_RPT			0x00D4
#define REG_BIST_ROM_RPT		0x00D8
#define REG_USB_SIE_INTF		0x00E0
#define REG_PCIE_MIO_INTF		0x00E4
#define REG_PCIE_MIO_INTD		0x00E8
#define REG_HPON_FSM			0x00EC
#define REG_SYS_CFG				0x00F0
#define REG_MAC_PHY_CONFG       0x00F8
//-----------------------------------------------------
//
//	0x0100h ~ 0x01FFh	MACTOP General Configuration
//
//-----------------------------------------------------
#define REG_FUNC_ENABLE			0x0100
#define REG_CR					0x0100
#define REG_PAGE_SIZE			0x0104
#define REG_TRX_DMA_CTRL		0x010C
#define REG_TX_PGBNDY			0x0114
#define REG_RX_PGBNDY			0x0116
#define REG_TRXFF_STATUS		0x0118
#define REG_RXFF_PTR			0x011C
#define REG_HIMR				0x0120
#define REG_HISR				0x0124
#define REG_HIMRE				0x0128
#define REG_HISRE				0x012C
#define REG_CPWM				0x012F
#define REG_FWIMR				0x0130
#define REG_FWISR				0x0134
#define REG_PKTBUF_DBG_CTRL		0x0140
#define REG_PKTBUF_DBG_DATA_L	0x0144
#define REG_PKTBUF_DBG_DATA_H	0x0148

#define REG_TC0_CTRL			0x0150
#define REG_TC1_CTRL			0x0154
#define REG_TC2_CTRL			0x0158
#define REG_TC3_CTRL			0x015C
#define REG_TC4_CTRL			0x0160
#define REG_TCUNIT_BASE			0x0164
#define REG_MBIST_START			0x0174
#define REG_MBIST_DONE			0x0178
#define REG_MBIST_FAIL			0x017C
#define REG_FMETHR				0x01C8
#define REG_HMETFR				0x01CC
#define REG_HMEBOX_0			0x01D0
#define REG_HMEBOX_1			0x01D4
#define REG_HMEBOX_2			0x01D8
#define REG_HMEBOX_3			0x01DC

#define REG_LLT_INIT			0x01E0
#define REG_BB_ACCEESS_CTRL		0x01E8
#define REG_BB_ACCESS_DATA		0x01EC

#define REG_LLT 0x01E0

//-----------------------------------------------------
//
//	0x0200h ~ 0x027Fh	TXDMA Configuration
//
//-----------------------------------------------------
#define REG_RQPN				0x0200
#define REG_FIFOPAGE			0x0204
#define REG_TDECTL				0x0208
#define REG_TXDMA_OFFSET_CHECK	0x020C
#define REG_TXDMA_STATUS		0x0210
#define REG_RQPN_NPQ			0x0214

//-----------------------------------------------------
//
//	0x0280h ~ 0x02FFh	RXDMA Configuration
//
//-----------------------------------------------------
#define REG_RXDMA_AGG_PG_TH		0x0280
#define REG_RXPKT_NUM			0x0284
#define REG_RXDMA_STATUS		0x0288
#define REG_RXDMA_PRO			0x0290

//-----------------------------------------------------
//
//	0x0300h ~ 0x03FFh	PCIe
//
//-----------------------------------------------------
#define REG_TPPoll  0x300


// spec version 11
//-----------------------------------------------------
//
//	0x0400h ~ 0x047Fh	Protocol Configuration
//
//-----------------------------------------------------
#define REG_VOQ_INFORMATION		0x0400
#define REG_VIQ_INFORMATION		0x0404
#define REG_BEQ_INFORMATION		0x0408
#define REG_BKQ_INFORMATION		0x040C
#define REG_MGQ_INFORMATION		0x0410
#define REG_HGQ_INFORMATION		0x0414
#define REG_BCNQ_INFORMATION	0x0418


#define REG_CPU_MGQ_INFORMATION	0x041C
#define REG_FUNCTION_ENABLE		0x0420
#define REG_FWHW_TXQ_CTRL		0x0420
#define REG_HWSEQ_CTRL			0x0423
#define REG_TXPKTBUF_BCNQ_BDNY	0x0424
#define REG_TXPKTBUF_MGQ_BDNY	0x0425
#define REG_MULTI_BCNQ_ENABLE	0x0426
#define REG_MULTI_BCNQ_OFFSET	0x0427
#define REG_SPEC_SIFS			0x0428
#define REG_RL					0x042A
#define REG_DARFRC				0x0430
#define REG_RARFRC				0x0438
#define REG_RRSR				0x0440
#define REG_ARFR0				0x0444
#define REG_ARFR1				0x0448
#define REG_ARFR2				0x044C
#define REG_ARFR3				0x0450
#define REG_AGGLEN_LMT			0x0458
#define REG_AMPDU_MIN_SPACE	0x045C
#define REG_WMAC_HEADER		0x045D
#define REG_FAST_EDCA_CTRL		0x0460
#define REG_RD_RESP_PKT_TH		0x0463
#define REG_INIRTS_RATE_SEL		0x0480
#define REG_INIDATA_RATE_SEL	0x0484
#define REG_POWER_STATUS		0x04A4
#define REG_POWER_STAGE1		0x04B4
#define REG_POWER_STAGE2		0x04B8
#define REG_PKT_LIFE_TIME		0x04C0
#define REG_STBC_SETTING		0x04C4
#define REG_PROT_MODE_CTRL		0x04C8
#define REG_BAR_MODE_CTRL		0x04CC
#define REG_RA_TRY_RATE_AGG_LMT	0x04CF
#define REG_EARLY_MODE_CTRL	0x04D0
#define REG_NQOS_SEQ			0x04DC
#define REG_QOS_SEQ				0x04DE
#define REG_NEED_CPU_HANDLE		0x04E0
#define REG_PKT_LOSE_RPT		0x04E1
#define REG_PTCL_ERR_STATUS		0x04E2
#define REG_DUMMY				0x04FC



//-----------------------------------------------------
//
//	0x0500h ~ 0x05FFh	EDCA Configuration
//
//-----------------------------------------------------

#define REG_EDCA_VO_PARAM		0x0500
#define REG_EDCA_VI_PARAM		0x0504
#define REG_EDCA_BE_PARAM		0x0508
#define REG_EDCA_BK_PARAM		0x050C
#define REG_BCNTCFG				0x0510
#define REG_PIFS				0x0512
#define REG_RDG_PIFS			0x0513
#define REG_SIFS_CCK			0x0514
#define REG_SIFS_OFDM			0x0516
#define REG_AGGR_BREAK_TIME		0x051A
#define REG_SLOT				0x051B
#define REG_TX_PTCL_CTRL		0x0520
#define REG_TXPAUSE				0x0522
#define REG_DIS_TXREQ_CLR		0x0523
#define REG_RD_CTRL				0x0524
#define REG_TBTT_PROHIBIT		0x0540
#define REG_RD_NAV_NXT			0x0544
#define REG_NAV_PROT_LEN		0x0546
#define REG_BCN_CTRL			0x0550
#define REG_USTIME_TSF			0x0551
#define REG_MBID_NUM			0x0552
#define REG_MBSSID_BCN_SPACE	0x0554
#define REG_DRVERLYINT			0x0558
#define REG_BCNDMATIM			0x0559
#define REG_ATIMWND				0x055A
#define REG_BCN_MAX_ERR			0x055D
#define REG_RXTSF_OFFSET_CCK	0x055E
#define REG_RXTSF_OFFSET_OFDM	0x055F	
#define REG_TSFTR				0x0560
#define REG_TSFTR1				0x0568
#define REG_INIT_TSFTR			0x0560
#define REG_INIT_TSFTR1			0x0568
#define REG_PSTIMER				0x0580
#define REG_TIMER0				0x0584
#define REG_TIMER1				0x0588
#define REG_ACMHWCTRL			0x05C0
#define REG_ACMRSTCTRL			0x05C1
#define REG_ACMAVG				0x05C2
#define REG_VO_ADMTIME			0x05C4
#define REG_VI_ADMTIME			0x05C6
#define REG_BE_ADMTIME			0x05C8
#define REG_EDCA_RANDOM_GEN		0x05CC
#define REG_SCH_TXCMD			0x05D0


//-----------------------------------------------------
//
//	0x0600h ~ 0x07FFh	WMAC Configuration
//
//-----------------------------------------------------
#define REG_APSD_CTRL			0x0600
#define REG_BWOPMODE			0x0603
#define REG_TCR					0x0604
#define REG_RCR					0x0608
#define REG_RX_PKT_LIMIT		0x060C
#define REG_RX_DLK_TIME			0x060D
#define REG_MBIDCTRL			0x060E
#define REG_MACID				0x0610
#define REG_MACID_2				0x0700
#define REG_BSSID				0x0618
#define REG_BSSID_2				0x0708
#define REG_MAR					0x0620
#define REG_MBIDCAMCFG			0x0628
#define REG_RX_DRVINFO_SZ		0x060F

#define REG_USTIME_EDCA			0x0638
//#define REG_SPEC_SIFS			0x063A
#define REG_RESP_SIFS_CCK		0x063C
#define REG_RESP_SIFS_OFDM		0x063E
#define REG_ACKTO				0x0640
#define REG_CTS2TO				0x0641
#define REG_EIFS				0x0642


//WMA, BA, CCX
#define REG_NAV_CTRL			0x0650
#define REG_BACAMCMD			0x0654
#define REG_BACAMCONTENT		0x0658
#define REG_LBDLY				0x0660
#define REG_FWDLY				0x0661
#define REG_RXERR_RPT			0x0664
#define REG_WMAC_TRXPTCL_CTL	0x0668


// Security
#define REG_CAMCMD				0x0670
#define REG_CAMWRITE			0x0674
#define REG_CAMREAD				0x0678
#define REG_CAMDBG				0x067C
#define REG_SECCFG				0x0680

// Power
#define REG_WOW_CTRL			0x0690
#define REG_PSSTATUS			0x0691
#define REG_PS_RX_INFO			0x0692
#define REG_LPNAV_CTRL			0x0694
#define REG_WKFMCAM_CMD			0x0698
#define REG_WKFMCAM_RWD			0x069C
#define REG_RXFLTMAP0			0x06A0
#define REG_RXFLTMAP1			0x06A2
#define REG_RXFLTMAP2			0x06A4
#define REG_BCN_PSR_RPT			0x06A8
#define REG_CALB32K_CTRL		0x06AC
#define REG_PKT_MON_CTRL		0x06B4
#define REG_BT_COEX_TABLE		0x06C0
#define REG_WMAC_RESP_TXINFO	0x06D8


// Baseband 
#define REGA0_RFMOD              			0x800  //RF mode & CCK TxSC
#define REGA0_TxInfo             			0x804
#define REGA0_TxGainStage        			0x80c
#define REGA0_XA_RFTiming        			0x810
#define REGA0_XB_RFTiming        			0x814
#define REGA0_XC_RFTiming        			0x818
#define REGA0_XD_RFTiming        			0x81c
#define REGA0_XA_HSSIParameter1  		0x820
#define REGA0_XA_HSSIParameter2  		0x824
#define REGA0_XB_HSSIParameter1  		0x828
#define REGA0_XB_HSSIParameter2  		0x82c
#define REGA0_XC_HSSIParameter1  		0x830
#define REGA0_XC_HSSIParameter2  		0x834
#define REGA0_XD_HSSIParameter1  		0x838
#define REGA0_XD_HSSIParameter2  		0x83c
#define REGA0_XA_LSSIParameter   		0x840
#define REGA0_XB_LSSIParameter   		0x844
#define REGA0_XC_LSSIParameter   		0x848
#define REGA0_XD_LSSIParameter   		0x84c
#define REGA0_RFWakeUpParameter  		0x850
#define REGA0_RFSleepUpParameter 		0x854
#define REGA0_XAB_SwitchControl  		0x858
#define REGA0_XCD_SwitchControl  		0x85c
#define REGA0_XA_RFInterfaceOE   		0x860
#define REGA0_XB_RFInterfaceOE   		0x864
#define REGA0_XC_RFInterfaceOE   		0x868
#define REGA0_XD_RFInterfaceOE   		0x86c
#define REGA0_XAB_RFInterfaceSW  		0x870
#define REGA0_XCD_RFInterfaceSW  		0x874
#define REGA0_XAB_RFParameter    		0x878 
#define REGA0_XCD_RFParameter    		0x87c 
#define REGA0_AnalogParameter1   		0x880
#define REGA0_AnalogParameter2   		0x884
#define REGA0_AnalogParameter3   		0x888
#define REGA0_anaparpsTRX		  		0x88c
#define REGA0_XA_LSSIReadBack    		0x8a0
#define REGA0_XB_LSSIReadBack    		0x8a4
#define REGA0_XC_LSSIReadBack    		0x8a8
#define REGA0_XD_LSSIReadBack    		0x8ac
#define REGA0_XA_LSSIReadBack_PI 		0x8b8
#define REGA0_XB_LSSIReadBack_PI 		0x8bC
#define REGA0_XAB_RFInterfaceRB  		0x8e0
#define REGA0_XCD_RFInterfaceRB  		0x8e4

//page 9
#define REGA1_RFMOD              			0x900  //RF mode & OFDM TxSC
#define REGA1_TxBlock            			0x904
#define REGA1_DebugSelect        			0x908
#define REGA1_TxInfo             				0x90c

//page a
#define RECCK0_System              			0xa00
#define RECCK0_AFESetting          			0xa04
#define RECCK0_CCA                 			0xa08
#define RECCK0_RxAGC1              			0xa0c  //AGC default value, saturation level
#define RECCK0_RxAGC2              			0xa10  //AGC & DAGC
#define RECCK0_RxHP                			0xa14
#define RECCK0_DSPParameter1       		0xa18  //Timing recovery & Channel estimation threshold
#define RECCK0_DSPParameter2       		0xa1c  //SQ threshold
#define RECCK0_TxFilter1           			0xa20
#define RECCK0_TxFilter2           			0xa24
#define RECCK0_DebugPort           			0xa28  //debug port and Tx filter3
#define RECCK0_RxReport            			0xa54  //0xa57
#define RECCK0_FACounterLower      		0xa58  //0xa5b
#define RECCK0_FACounterUpper      		0xa5c  //0xa5c

//page c
#define REOFDM0_LSTF               			0xc00
#define REOFDM0_TRxPathEnable      		0xc04
#define REOFDM0_XARxAFE            			0xc10  //RxIQ DC offset, Rx digital filter, DC notch filter
#define REOFDM0_XARxIQImbalance    		0xc14  //RxIQ imblance matrix
#define REOFDM0_XBRxAFE            			0xc18
#define REOFDM0_XBRxIQImbalance    		0xc1c
#define REOFDM0_XCRxAFE            			0xc20
#define REOFDM0_XCRxIQImbalance    		0xc24
#define REOFDM0_XDRxAFE            			0xc28
#define REOFDM0_XDRxIQImbalance    		0xc2c
#define REOFDM0_RxDetector1        		0xc30  //PD,BW & SBD
#define REOFDM0_RxDetector2        		0xc34  //SBD & Fame Sync.
#define REOFDM0_RxDetector3        		0xc38  //Frame Sync.
#define REOFDM0_RxDetector4        		0xc3c  //PD, SBD, Frame Sync & Short-GI
#define REOFDM0_RxDSP              			0xc40  //Rx Sync Path
#define REOFDM0_CFOandDAGC         		0xc44  //CFO & DAGC
#define REOFDM0_CCADropThreshold   		0xc48 //CCA Drop threshold
#define REOFDM0_ECCAThreshold      		0xc4c // energy CCA
#define REOFDM0_XAAGCCore1         		0xc50
#define REOFDM0_XAAGCCore2         		0xc54
#define REOFDM0_XBAGCCore1         		0xc58
#define REOFDM0_XBAGCCore2         		0xc5c
#define REOFDM0_XCAGCCore1         		0xc60
#define REOFDM0_XCAGCCore2         		0xc64
#define REOFDM0_XDAGCCore1         		0xc68
#define REOFDM0_XDAGCCore2         		0xc6c
#define REOFDM0_AGCParameter1     		0xc70
#define REOFDM0_AGCTRSWTHRESHOLD  	0xc72
#define REOFDM0_AGCParameter2      		0xc74
#define REOFDM0_AGCRSSITable       		0xc78 //rssi_table_select
#define REOFDM0_HTSTFAGC           		0xc7c
#define REOFDM0_XATxIQImbalance    		0xc80
#define REOFDM0_XATxAFE            			0xc84
#define REOFDM0_XBTxIQImbalance    		0xc88
#define REOFDM0_XBTxAFE            			0xc8c
#define REOFDM0_XCTxIQImbalance    		0xc90
#define REOFDM0_XCTxAFE            			0xc94
#define REOFDM0_XDTxIQImbalance    		0xc98
#define REOFDM0_XDTxAFE            			0xc9c
#define REOFDM0_FrameSync         		0xcf0
#define REOFDM0_RxHPParameter      		0xce0

//page d
#define REOFDM1_LSTF               			0xd00
#define REOFDM1_TRxPathEnable      		0xd04
#define REOFDM1_CFO                			0xd08
#define REOFDM1_CSI1               			0xd10
#define REOFDM1_SBD                			0xd14
#define REOFDM1_CSI2               			0xd18
#define REOFDM1_CFOTracking        		0xd2c
#define REOFDM1_TRxMesaure1        		0xd34
#define REOFDM_PHYCounter1         		0xda0  //cca, parity fail
#define REOFDM_PHYCounter2         		0xda4  //rate illegal, crc8 fail
#define REOFDM_PHYCounter3         		0xda8  //MCS not support
#define REOFDM_ShortCFOAB          		0xdac
#define REOFDM_ShortCFOCD          		0xdb0
#define REOFDM_LongCFOAB           		0xdb4
#define REOFDM_LongCFOCD           		0xdb8
#define REOFDM_TailCFOAB           			0xdbc
#define REOFDM_TailCFOCD           			0xdc0
#define REOFDM_PWMeasure1          		0xdc4
#define REOFDM_PWMeasure2          		0xdc8
#define REOFDM_BWReport            			0xdcc
#define REOFDM_AGCReport           			0xdd0
#define REOFDM_RxSNR               			0xdd4
#define REOFDM_RxEVMCSI            			0xdd8
#define REOFDM_SIGReport           			0xddc

//-----------------------------------------------------
//
//	0xFE00h ~ 0xFE55h	USB Configuration
//
//-----------------------------------------------------
#define REG_USB_INFO				0xFE17
#define REG_USB_TXQS				0xFE48
#define REG_USB_SPECIAL_OPTION	0xFE55
#define REG_USB_HRPWM				0xFE58
#define REG_USB_DMA_AGG_TO		0xFE5B
#define REG_USB_AGG_TO				0xFE5C
#define REG_USB_AGG_TH				0xFE5D

#define REG_USB_VID					0xFE60
#define REG_USB_PID					0xFE62
#define REG_USB_OPTIONAL			0xFE64

//Test chip
#define REG_USB_CHIRP_K			0xFE65
#define REG_USB_PHY				0xFE66

//Normal chip
#define REG_USB_EP_SETTING			0xFE65 // FE65~FE67
#define REG_USB_NORMAL_PHY		0xFE68

#define REG_USB_MAC_ADDR			0xFE70

//------------------------
//
// Extra
//
//------------------------
//#define EDCA_VI_PARAM		0x0504  //added
//#define EDCA_BE_PARAM		0x0508  //added
//#define EDCA_BK_PARAM		0x050C  //added
#define BcnTCfg         			0x0510  //Beacon Time Configuration added by zhaoxx
//#define PIFS					0x0512	//0x0090
#define RDG_PIFS			0x0513	//added
//#define SIFS_CCK				0x0514  
//#define SIFS_OFDM			0x0516  
#define TX_SIFS_TIME		0x0518  //added
#define AGGR_BREAK_TIME	0x051a  //added
//#define SLOT 				0x051b	//modify
#define FUNCTION_ENABLE_P5	0x0520 //added //??????????
//#define TXPAUSE				0x0523  //modify
#define BKF_SEL				0x0524  //added
#define DUALMACMAC_CTL		0x0526  //added
#define TBTT_PROHIBIT		0x0540  //added
#define RDG_NEXT_PKT_TIME	0x0544  //added
#define TXOP_NEXT_PKT_TIME	0x0546  //added
#define BCN_CTRL				0x0550  //added
#define BCN_US_SETTING          	0x0551  //added
#define MULTI_BCN_NUMBER	0x0552  //added
#define DUAL_TSF_RST		0x0553
#define BCN_SPACE			0x0554  //added
#define BCN_EARLY_INT		0x0558  //added
#define BCN_DMA_INT			0x0559  //added
#define BCN_ATIM				0x055a  //added
#define BCN_MAX_ERROR		0x055d  //added
#define UDATE_CCK_RXTSF_OFFSET		0x055E //added
#define UDATE_OFDM_RXTSF_OFFSET	0x055F //added
//#define TSFTR					0x0560	//0x0080 //richard 0424

#define REG_CTWINDOW		0x0572	// Only exist 8723 Normal Chip
#define TIMER1_INT			0x0580  //added
#define ACMRSTCTRL			0x05C1  //added
//#define ACMAVG				0x05C2  //added
//#define VO_ADMTIME			0x05C4  //added
//#define VI_ADMTIME			0x05C6  //added
//#define BE_ADMTIME			0x05C8  //added
//#define EDCA_RANDOM_GEN	0x05CC  //added
#define NoAElemSelect		0x05CF

#define NoADuration			0x05E0
#define NoAInterval			0x05E4
#define NoAStartTime			0x05E8
#define NoACount				0x05EC
#define NoASubElement		0x05ED



/******************************************/
	/* Include file*/
/******************************************/

/******************************************/
	/* Macro*/
/******************************************/
#define RF_PATH_A 0x00000000
#define RF_PATH_B 0x00010000

#define IOREG_BASE        0x0000

#define PAGE_NUM_HPQ	0x1C
#define PAGE_NUM_NPQ	0x0E
#define PAGE_NUM_LPQ	0x0E
#define PAGE_NUM_PUBQ	0xC0

//SYSCGF registers
#define SYS_ISO_CTRL		0x0000
#define SYS_FUNC_EN			0x0002
#define PSC_FSM				0x0004
#define SYS_CLKR				0x0008
#define CR9346				0x000A
#define EE_VPD				0x000C
#define AFE_MISC			0x0010
#define SPS0_CTRL			0x0011
#define SPS1_CTRL			0x0018
#define RF_CTRL				0x001F
#define LDOA15_CTRL			0x0020
#define LDOV12D_CTRL		0x0021
#define LDOHCI12_CTRL		0x0022
#define LDO_USB_SDIO		0x0023
#define EE_PON				0x0024
#define AFE_XTAL_CTRL		0x0026
#define AFE_PLL_CTRL		0x0028
#define EFUSE_CTRL			0x0030	
#define EFUSE_TEST			0x0034
#define PWR_DATA			0x0038
#define DPS_TIMER			0x003C
#define RCLK_MON			0x003E
//Define IO registers
#define CR					0x0040
#define TXPAUSE				0x0042
#define LBKMD				0x0043  //added
#define TCR					0x0044
#define RCR					0x0048
#define MSR					0x004C
#define SYSF_CFG			0x004D
#define RX_PKT_LIMIT		0x004E	//added
#define MBIDCTRL			0x004F	//added
#define MACID				0x0050
#define BSSID				0x0058
#define MBIDCAMCFG			0x005E  //added
#define MAR					0x0060
#define MBIDCAMCONTENT		0x0068  //added
#define BUILDUSER   		0x0070  //added
#define BUILDTIME   		0x0078  //added
#define TSFTR				0x0080
#define USTIME				0x0088
#define SLOT 				0x0089
#define TUBASE				0x008A
#define SIFS_CCK			0x008C //added
#define SIFS_OFDM			0x008E //added
#define PIFS					0x0090
#define ACKTO				0x0091
#define EIFS					0x0092
#define BCNITBV				0x0094
#define ATIMWND				0x0096
#define DRVERLYINT			0x0098 //added
#define BCNDMATIM			0x009A
#define BCNERRTH			0x009C //added
#define MLT					0x009D
#define MBSSID_BCN_SPACE    0x009E
#define RQPN					0x00A0
#define RXFF_BNDY			0x00AC
#define RXRPT_BNDY			0x00B0
#define TXPKTBUF_PGBNDY	0x00B4
#define PBP					0x00B5
#define DRVINFO_SZ			0x00B6
#define TXFF_STATUS			0x00B7
#define RXFF_STATUS			0x00B8
#define TXFF_EMPTY_TH		0x00B9  //added
#define SDIO_RX_BLKSZ		0x00BC  //added
#define RXDMA				0x00BD
#define RXPKT_NUM			0x00BE
#define C2HCMD_UDT_SIZE		0x00C0  //added
#define C2HCMD_UDT_ADDR		0x00C2  //added
#define FIFOPAGE2   		0x00C4  //added
#define FIFOPAGE1   		0x00C8  //added
#define FW_RSVD_PG_CTRL		0x00D8  //added
#define RXDMA_AGG_PG_TH	0x00D9
#define TXDESC_MSK	    	0x00DC  //added
#define C2HFF_RDPTR	    	0x00E8  //added
#define C2HFF_WTPTR	    	0x00EC  //added
#define RXFF0_RDPTR	    	0x00F0  //added
#define RXFF0_WTPTR	    	0x00F4  //added
#define RXFF1_RDPTR	    	0x00F8  //added
#define RXFF1_WTPTR	    	0x00FC  //added
#define RXRPT0_RDPTR	    0x0100  //added
#define RXRPT0_WTPTR	    0x0104  //added
#define RXRPT1_RDPTR	    0x0108  //added
#define RXRPT1_WTPTR	    0x010C  //added
#define RX0_UDT_SIZE	    0x0110  //added
#define RXFLTMAP0	        0x0116  //added
#define RXFLTMAP1	        0x0118  //added
#define RXFLTMAP2	        0x011A  //added
#define RXFLTMAP3	        0x011C  //added
#define BCNQ_CTRL	        0x0120  //added
#define MGTQ_CTRL	        0x0124  //added
#define HIQ_CTRL	        0x0128  //added
#define VOQ1_CTRL	        0x012C  //added
#define VOQ0_CTRL	        0x0130  //added
#define VIQ1_CTRL	        0x0134  //added
#define VIQ0_CTRL	        0x0138  //added
#define BEQ1_CTRL	        0x013C  //added
#define BEQ0_CTRL	        0x0140  //added
#define BKQ1_CTRL	        0x0144  //added
#define BKQ0_CTRL	        0x0148  //added
#define CMDQ_CTRL	        0x014C  //added
#define TXPKT_NUM_CTRL      0x0150  //added
#define TXQ_PGADD           0x0152  //added
#define TXFF_PG_NUM         0x0154  //added
#define TRXDMA_STATUS       0x0156  //added
#define INIMCS_SEL          0x0160  //added
#define INIRTSMCS_SEL       0x0180  //added
#define RRSR					0x0181
#define ARFR0   			0x0184	//added
#define ARFR1   			0x0188	//added
#define ARFR2   			0x018C	//added
#define ARFR3   			0x0190	//added
#define ARFR4   			0x0194	//added
#define ARFR5   			0x0198	//added
#define ARFR6   			0x019C	//added
#define ARFR7   			0x01A0	//added
#define AGGLEN_LMT_H		0x01A7	//added
#define AGGLEN_LMT_L		0x01A8	//added
#define DARFRC      		0x01B0	//added
#define RARFRC      		0x01B8	//added
#define MCS_TXAGC      		0x01C0	//added
#define CCK_TXAGC      		0x01C8	//added
#define EDCA_VO_PARAM  		0x01D0	//added
#define EDCA_VI_PARAM  		0x01D4	//added
#define EDCA_BE_PARAM  		0x01D8	//added
#define EDCA_BK_PARAM  		0x01DC	//added
#define BCNTCFG     		0x01E0	//added
#define CWRR        		0x01E2	//added
#define ACMAVG       		0x01E4	//added
#define ACMHWCTRL      		0x01E7	//added
#define VO_ADMTIME     		0x01E8	//added
#define VI_ADMTIME     		0x01EC	//added
#define BE_ADMTIME     		0x01F0	//added
#define RL		     		0x01F4	//added
#define MAX_MCS_AVAL   		0x01F6	//added
#define EDCA_RANDOM_GEN		0x01F8	//added

#define NAV_CTRL			0x0200	//added
#define BWOPMODE			0x0203	//added
#define BACAMCMD			0x0204	//added
#define BACAMCONTENT		0x0208	//added
#define LBDLY				0x0210	//added
#define FWDLY				0x0211	//added
#define HWPC_RX_CTRL		0x0218	//added
#define MQ          		0x0220	//added
#define MA          		0x0222	//added
#define MS          		0x0224	//added
#define RXERR_RPT      		0x0230	//added
#define NAV_PROT_LEN   		0x0234	//added

#define CFEND_TH			0x0236
#define AMPDU_MIN_SPACE	0x0237
#define TXOP_STALL_CTRL		0x0238
#define CAM_CMD				0x0240
#define CAM_Write			0x0244
#define CAM_Read			0x0248
#define CAMDBG  			0x024C	//added
#define SECCFG				0x0250

#define WOW_CTRL			0x0260	//added
#define PSSTATUS			0x0261	//added
#define PSSWITCH			0x0262	//added
#define MIMOPS_WAIT_PERIOD	0x0263	//added
#define LPNAV_CTRL			0x0264	//added
#define WFM0				0x0270	//added
#define WFM1				0x0280	//added
#define WFM2				0x0290	//added
#define WFM3				0x02A0	//added
#define WFM4				0x02B0	//added
#define WFM5				0x02C0	//added

#define WFCRC				0x02D0	//added
#define RPWM				0x02DC	//added
#define CPWM				0x02DD	//added

#define PSTIMER				0x02E0	//added
#define TIMER0				0x02E4	//added
#define TIMER1				0x02E8	//added
#define GPIO_CTRL			0x02EC	//added
#define GPIO_INTCTRL		0x02F0	//added
#define MAC_PINMUX_CFG		0x02F1	//added
#define LEDCFG				0x02F2	//added
#define PHY_REG_RPT			0x02F3	//added
#define PHY_REG_DATA		0x02F4	//added
#define EFUSE_CLK_CTRL		0x02F8	//added

#define HIMR				0x0300	//added
#define HISR				0x0308	//added

#define BIST				0x0310	//added
#define LMS					0x0315	//added
#define CPUINST				0x0318	//added
#define CPUCAUSE			0x031C	//added
#define LBUS_ERR_ADDR		0x0320	//added
#define LBUS_ERR_CMD		0x0324	//added
#define LBUS_ERR_DATA_L		0x0328	//added
#define LBUS_ERR_DATA_H		0x032C	//added
#define WDG_CTRL			0x0334	//added
#define FDLOCKTURN0			0x033C	//added
#define FDLOCKTURN1			0x033D	//added
#define FDLOCKFLAG0			0x033E	//added
#define FDLOCKFLAG1			0x033F	//added

#define TRXPKTBUF_DBG_DATA	0x0340
#define TRXPKTBUF_DBG_CTRL		0x0348

#define DPLL_MON			0x034A	//added
#define CBUS_ERR_ADDR		0x0350	//added
#define CBUS_ERR_CMD		0x0354	//added
#define CBUS_ERR_DATA_L		0x0358	//added
#define CBUS_ERR_DATA_H		0x035C	//added
#define USB_SIE_INTF_ADDR	0x0360	//added
#define USB_SIE_INTF_WD 	0x0361	//added
#define USB_SIE_INTF_RD 	0x0362	//added
#define USB_SIE_INTF_CTRL 	0x0363	//added

#define LBUS_MON_ADDR	 	0x0364	//added
#define LBUS_ADDR_MSK	 	0x0368	//added
#define LBUS_MON_DATA_L	 	0x036C	//added
#define LBUS_MON_DATA_H	 	0x0370	//added
#define LBUS_MSK_DATA_L	 	0x0374	//added
#define LBUS_MSK_DATA_H	 	0x0378	//added

/******************************************/
	/* Structure Declaration*/
/******************************************/


enum{
	NTWOMAC_PAGE_NUM_HPQ			= 0x00,
	NTWOMAC_PAGE_NUM_NPQ			= 0x00,
	NTWOMAC_PAGE_NUM_LPQ			= 0x00,
	NTWOMAC_PAGE_NUM_PUBQ			= 0xF9,		
	TX_PAGE_BOUNDARY_NORMAL_MODE	= 252,//KaiYuan modified for 88e		
};

enum{
	NLLB_PAGE_NUM_HPQ				= 0x20,
	NLLB_PAGE_NUM_NPQ				= 0x20,
	NLLB_PAGE_NUM_LPQ				= 0x20,
	NLLB_PAGE_NUM_PUBQ				= 0x20,	
	TX_PAGE_BOUNDARY_LOOPBACK_MODE	= 130,//KaiYuan modified for 88e	
};
/******************************************/
	/* Exported Function*/
/******************************************/




//2 8051FWDL
#define FW8051DWL_EN			BIT(0)
#define FW8051DWL_RDY			BIT(1)

// FW download range
#define FW_SIZE					0xc000
#define FW_START_ADDRESS		0x1000
#define FW_END_ADDRESS		0x3FFF
#define MIN_BLOCK_SIZE			8
#define FW_BLOCK_SIZE			64
#define FW_PAGE_SIZE			0x1000
#define FW_BLOCKNUM_ONE_PAGE	(FW_PAGE_SIZE/FW_BLOCK_SIZE)	//be careful, it is neccessary  to be divided with no remainder 
#define FW_WRITE_UNIT 			8
#define FW_DOWNLOAD_BEACON_MODE 1

// Add by Guo.Mingzhi 2009-07-30
#define DUAL_MAC_EN             0x01
#define DUAL_PHY_EN             0x02
#define SUPER_MAC_EN            0x04

#define TXPKTBUF_BLOCK_SIZE		8


//2 8051FWDL
#define FW8051DWL_EN			BIT(0)
#define FW8051DWL_RDY			BIT(1)

#define ROM_DLEN				BIT(3)

//=========================================////
//	0x0000h ~ 0x00FFh	System Configuration
//=========================================//
//2 //2 9346CR
#define EEDO					BIT(0)
#define EEDI					BIT(1)
#define EESK					BIT(2)
#define EECS					BIT(3)
#define EERPROMSEL				BIT(4)
#define EEPROM_EN				BIT(5)
#define EEM0					BIT(6)
#define EEM1					BIT(7)


//2 SYS_ISO_CTRL
#define ISO_MD2PP				BIT(0)
#define ISO_UD2PP				BIT(1)
#define ISO_UA2USB				BIT(2)
#define ISO_PA2PCIE				BIT(3)
#define ISO_PLL2MD				BIT(4)
#define ISO_RF2MD				BIT(5)
#define ISO_DIOP				BIT(6)
#define ISO_DIOE				BIT(7)
#define ISO_LDR2RP				BIT(8)
#define ISO_I12RP				BIT(9)
#define ISO_I22RP				BIT(10)
#define PWC_DV2RP				BIT(11)
#define PWC_RV2RP				BIT(12)
#define PWC_RP2IM1				BIT(13)
#define PWC_RP2IM2				BIT(14)
#define PWC_RV2LDR				BIT(15)


//2 SYS_FUNC_EN
#define FEN_BBRSTB				BIT(0)
#define FEN_BB_GLB_RSTn			BIT(1)
#define FEN_USBA				BIT(2)
#define FEN_UPLL				BIT(3)
#define FEN_USBD				BIT(4)
#define FEN_DIO_PCIE			BIT(5)
#define FEN_PCIEA				BIT(6)
#define FEN_PPLL				BIT(7)
#define FEN_PCIED				BIT(8)
#define FEN_DIOE				BIT(9)
#define FEN_CPUEN				BIT(10)
#define FEN_DCORE				BIT(11)
#define FEN_ELDR				BIT(12)
#define PWC_DV2LDR				BIT(13)
#define FEN_HWPDN				BIT(14)
#define FEN_MREGEN				BIT(15)


//2 SYS_CLKR
#define PS_CLKSEL				BIT(1)
#define INT32K_EN				BIT(3)
#define MACSLP					BIT(4)
#define EFUSE_CLK_EN			BIT(5)
#define EFUSE_CLK_SEL			BIT(6)
#define _80M_SSC_DIS			BIT(7)
#define _80M_SSC_EN_HO			BIT(8)
#define PHY_SSC_RSTB			BIT(9)
#define SEC_CLK_EN				BIT(10)
#define MAC_CLK_EN				BIT(11)
#define SYS_CLK_EN				BIT(12)
#define RING_CLK_EN				BIT(13)
#define SWHW_SEL				BIT(14)
#define FWHW_SEL				BIT(15)


//2 SPS1_CTRL
#define SW12_LDEN				BIT(0)
#define SW12_SWEN				BIT(1)
#define SW12_VOL				BIT(2)

// SW12_STD
#define SW12_STD_80US			0x0
#define SW12_STD_160US			0x1
#define SW12_STD_640US			0x2
#define SW12_STD_2560US			0x3


// TODO:
// SW12_IN 

#define SW12_FDUAL				BIT(11)
#define SW12_FPWM				BIT(12)
#define SW12_SFREQC				BIT(13)

// SW12_SFREQ
// SW12_TBOX
#define SW12_LDO_R				BIT(18)
#define SW12_SD					BIT(19)
#define SW12_AREN				BIT(20)


//2 RF_CTRL
#define RF_EN						BIT(0)
#define RF_RSTB						BIT(1)
#define RF_SDMRSTB					BIT(2)


//2 AFE_MISC
#define AFE_BGEN				BIT(0)
#define AFE_MBEN				BIT(1)
#define AFE_E32K_EN				BIT(2)
#define AFE_I32K_EN				BIT(3)
#define USB_BGEN				BIT(4)
#define USB_MBEN				BIT(5)
#define XTAL_UDLY				BIT(6)
#define XTAL_ADLY				BIT(7)


//2 LDOA15_CTRL
#define LDA15_EN				BIT(0)
#define LDA15_STBY				BIT(1)
#define LDA15_OBUF				BIT(2)
#define _LDA15_VOADJ(x)			(((x) & 0x7) << 4)


//2 LDOV12D_CTRL
#define LDV12_EN				BIT(0)
#define LDV12_SDBY				BIT(1)
#define LPLDO_HSM				BIT(2)
#define LPLDO_LSM_DIS			BIT(3)
#define _LDV12_VADJ(x)			(((x) & 0xF) << 4)


//2 AFE_XTAL_CTRL
#define XTAL_EN					BIT(0)
#define XTAL_BSEL				BIT(1)
#define _XTAL_BOSC(x)			(((x) & 0x3) << 2)
#define _XTAL_CADJ(x)			(((x) & 0xF) << 4)
#define XTAL_GATE_USB			BIT(8)
#define _XTAL_USB_DRV(x)		(((x) & 0x3) << 9)
#define XTAL_GATE_AFE			BIT(11)
#define _XTAL_AFE_DRV(x)		(((x) & 0x3) << 12)
#define XTAL_RF_GATE			BIT(14)
#define _XTAL_RF_DRV(x)			(((x) & 0x3) << 15)
#define XTAL_GATE_DIG			BIT(17)
#define _XTAL_DIG_DRV			(((x) & 0x3) << 18)
#define XTAL_BT_GATE			BIT(20)
#define _XTAL_BT_DRV			(((x) & 0x3) << 21)
#define _XTAL_GPIO(x)			(((x) & 0x7) << 23)


#define CKDLY_AFE				BIT(26)
#define CKDLY_USB				BIT(27)
#define CKDLY_DIG				BIT(28)
#define CKDLY_BT				BIT(29)

//#define XTAL_MOST_CURRENT		0x3
//#define XTAL_LESS_CURRENT		0x0



//2 AFE_PLL_CTRL
#define APLL_EN					BIT(0)

#define APLL_REF_CLK_13MHZ		0x1
#define APLL_REF_CLK_19_2MHZ	0x2
#define APLL_REF_CLK_20MHZ		0x3
#define APLL_REF_CLK_25MHZ		0x4
#define APLL_REF_CLK_26MHZ		0x5
#define APLL_REF_CLK_38_4MHZ	0x6
#define APLL_REF_CLK_40MHZ		0x7

#define APLL_CPU_EN				BIT(4)
//APLL_CPUDPLL_SEL
#define APLL_80M_EN				BIT(8)
#define APLL_WDOGB				BIT(9)

// TODO:


//2 8051FWDL
#define FW8051DWL_EN			BIT(0)
#define FW8051DWL_RDY			BIT(1)

// FW download range
#define TESTCHIP_FW_SIZE		0x3000
#define NORMALCHIP_FW_SIZE	0x4000
#define FW_START_ADDRESS		0x1000
#define FW_END_ADDRESS		0x3FFF
#define FW_BLOCK_SIZE			64
#define FW_PAGE_SIZE			0x1000
#define FW_BLOCKNUM_ONE_PAGE	(FW_PAGE_SIZE/FW_BLOCK_SIZE)	//be careful, it is neccessary  to be divided with no remainder 


// Add by Guo.Mingzhi 2009-07-30
#define DUAL_MAC_EN             0x01
#define DUAL_PHY_EN             0x02
#define SUPER_MAC_EN            0x04


//RPWM
#define 	PS_DPS				BIT(0)
#define 	PS_LCLK				(PS_DPS)
#define	PS_RF_OFF			BIT(1)
#define	PS_ALL_ON			BIT(2)
#define	PS_ST_ACTIVE		BIT(3)
#define	PS_LP				BIT(4)	// low performance
#define	PS_ACK				BIT(6)
#define	PS_TOGGLE			BIT(7)


//=========================================////
//	0x0100h ~ 0x01FFh	MACTOP General Configuration
//=========================================////

//2 
//2 Function Enable Registers

#define REG_LBMODE						(REG_CR + 3)


#define HCI_TXDMA_EN					BIT(0)
#define HCI_RXDMA_EN					BIT(1)
#define TXDMA_EN						BIT(2)
#define RXDMA_EN						BIT(3)
#define PROTOCOL_EN						BIT(4)
#define SCHEDULE_EN						BIT(5)
#define MACTXEN							BIT(6)
#define MACRXEN							BIT(7)
#define ENSEC							BIT(9)
#define IC_MACPHY_MODE					BIT(28)

// Network type
#define _NETTYPE(x)						(((x) & 0x3) << 16)
#define MASK_NETTYPE					0x30000
#define NT_NO_LINK						0x0
#define NT_LINK_AD_HOC					0x1
#define NT_LINK_AP						0x2
#define NT_AS_AP						0x3

#define _LBMODE(x)						(((x) & 0xF) << 24)
#define MASK_LBMODE						0xF000000
#define LOOPBACK_NORMAL					0x0
#define LOOPBACK_IMMEDIATELY			0xB
#define LOOPBACK_MAC_DELAY				0x3
#define LOOPBACK_PHY					0x1
#define LOOPBACK_DMA					0x7


//2 PBP - Page Size Register
#define GET_RX_PAGE_SIZE(value)			((value) & 0xF)
#define GET_TX_PAGE_SIZE(value)			(((value) & 0xF0) >> 4)
#define _PSRX_MASK						0xF
#define _PSTX_MASK						0xF0
#define _PSRX(x)						(x)
#define _PSTX(x)						((x) << 4)

#define PBP_64							0x0
#define PBP_128							0x1
#define PBP_256							0x2
#define PBP_512							0x3
#define PBP_1024						0x4

//2 BCN_RST

//2 TX/RXDMA
#define RXDMA_ARBBW_EN					BIT(0)
//#define RXSHFT_EN						BIT(1)
#define RXDMA_AGG_EN					BIT(2)

//test chip definition
#define QS_VO_QUEUE					BIT(8)
#define QS_VI_QUEUE						BIT(9)
#define QS_BE_QUEUE					BIT(10)
#define QS_BK_QUEUE					BIT(11)
#define QS_MANAGER_QUEUE				BIT(12)
#define QS_HIGH_QUEUE					BIT(13)

//normal chip definition
#define _TXDMA_HIQ_MAP(x) 	 ((x) << 14)
#define _TXDMA_MGQ_MAP(x) 	 ((x) << 12)
#define _TXDMA_BKQ_MAP(x) 	 ((x) << 10)		
#define _TXDMA_BEQ_MAP(x) 	 ((x) << 8 )
#define _TXDMA_VIQ_MAP(x) 	 ((x) << 6 )
#define _TXDMA_VOQ_MAP(x) 	 ((x) << 4 )

#define LOW_QUEUE 		1 
#define NORMAL_QUEUE    2
#define HI_QUEUE 		3


//2 PKTBUF_DBG_CTRL
#define TXPKTBUF_DBG					BIT(13)
#define RXPKTBUF_DBG					BIT(14)
#define TXLLT_INI						BIT(15)


//2 FFBND
#define _RXFF0_BND(x)					((x) << 16)
#define _TXPKTBUF_PG_BNDY(x)			(x)



//2 LLT_INIT
#define _LLT_NO_ACTIVE					0x0
#define _LLT_WRITE_ACCESS				0x1
#define _LLT_READ_ACCESS				0x2

#define _LLT_INIT_DATA(x)				((x) & 0xFF)
#define _LLT_INIT_ADDR(x)				(((x) & 0xFF) << 8)
#define _LLT_OP(x)						(((x) & 0x3) << 30)
#define _LLT_OP_VALUE(x)				(((x) >> 30) & 0x3)


//2 HISR (0x0124)
#define	BCNMDA_INT0	BIT(13)

//2 HISRE (0x012C)
#define	CPWM_INT	BIT(8)




//=========================================//
//    EDCA  BIT DEFINITION
//=========================================//
//2 //2 EDCA_VO_PARAM
#define _AIFS(x)				(x)
#define _ECW_MAX_MIN(x)			((x) << 8)
#define _TXOP_LIMIT(x)			((x) << 16)


#define _BCNIFS(x)				((x) & 0xFF)
#define _BCNECW(x)				(((x) & 0xF))<< 8)


#define _LRL(x)					((x) & 0x3F)
#define _SRL(x)					(((x) & 0x3F) << 8)


//2 SIFS_CCK
#define _SIFS_CCK_CTX(x)		((x) & 0xFF)
#define _SIFS_CCK_TRX(x)		(((x) & 0xFF) << 8);


//2 SIFS_OFDM
#define _SIFS_OFDM_CTX(x)		((x) & 0xFF)
#define _SIFS_OFDM_TRX(x)		(((x) & 0xFF) << 8);


//2 RESP SIF

#define _SIFS_R2T_CCK(x)          ((x) & 0xff)
#define _SIFS_R2T_OFDM(x)          (((x) & 0xff) << 8)

//2 TST SIFS

#define _SIFS_T2T_CCK(x)          ((x) & 0xff)
#define _SIFS_T2T_OFDM(x)          (((x) & 0xff) << 8)


//2 TBTT PROHIBIT
#define _TBTT_PROHIBIT_HOLD(x)	(((x) & 0xFF) << 8)


//2 BCN_CTRL
#define _BCN_TXBCN_RPT			BIT(2)
#define _BCN_FUNC_ENABLE		BIT(3)



//=========================================//
//    PROTOCOL  BIT DEFINITION
//=========================================//
//2 //2 INIRTSMCS_SEL
#define _INIRTSMCS_SEL(x)			((x) & 0x3F)


//2 SPEC SIFS
#define _SPEC_SIFS_CCK(x)			((x) & 0xFF)
#define _SPEC_SIFS_OFDM(x)			(((x) & 0xFF) << 8)


//2 RRSR

//1 NOTE: Make sure these definition suit for all registers
#define RATE_1M						BIT(0)
#define RATE_2M						BIT(1)
#define RATE_5_5M					BIT(2)
#define RATE_11M					BIT(3)
#define RATE_6M						BIT(4)
#define RATE_9M						BIT(5)
#define RATE_12M					BIT(6)
#define RATE_18M					BIT(7)
#define RATE_24M					BIT(8)
#define RATE_36M					BIT(9)
#define RATE_48M					BIT(10)
#define RATE_54M					BIT(11)
#define RATE_MCS0					BIT(12)
#define RATE_MCS1					BIT(13)
#define RATE_MCS2					BIT(14)
#define RATE_MCS3					BIT(15)
#define RATE_MCS4					BIT(16)
#define RATE_MCS5					BIT(17)
#define RATE_MCS6					BIT(18)
#define RATE_MCS7					BIT(19)

#define RATE_BITMAP_ALL				0xFFFFF

#define _RRSC_BITMAP(x)				((x) & 0xFFFFF)

#define _RRSR_RSC(x)				(((x) & 0x3) << 21)
#define RRSR_RSC_RESERVED			0x0
#define RRSR_RSC_UPPER_SUBCHANNEL	0x1
#define RRSR_RSC_LOWER_SUBCHANNEL	0x2
#define RRSR_RSC_DUPLICATE_MODE		0x3
#define RRSR_SHORT					BIT(23)


//2 ARFR
#define USE_SHORT_G1				BIT(20)

//2 AGGLEN_LMT_L
#define _AGGLMT_MCS0(x)				((x) & 0xF)
#define _AGGLMT_MCS1(x)				(((x) & 0xF) << 4)
#define _AGGLMT_MCS2(x)				(((x) & 0xF) << 8)
#define _AGGLMT_MCS3(x)				(((x) & 0xF) << 12)
#define _AGGLMT_MCS4(x)				(((x) & 0xF) << 16)
#define _AGGLMT_MCS5(x)				(((x) & 0xF) << 20)
#define _AGGLMT_MCS6(x)				(((x) & 0xF) << 24)
#define _AGGLMT_MCS7(x)				(((x) & 0xF) << 28)


//2 DARFRC
#define _DARF_RC1(x)				((x) & 0x1F)
#define _DARF_RC2(x)				(((x) & 0x1F) << 8)
#define _DARF_RC3(x)				(((x) & 0x1F) << 16)
#define _DARF_RC4(x)				(((x) & 0x1F) << 24)
// NOTE: shift starting from address (DARFRC + 4)
#define _DARF_RC5(x)				((x) & 0x1F)
#define _DARF_RC6(x)				(((x) & 0x1F) << 8)
#define _DARF_RC7(x)				(((x) & 0x1F) << 16)
#define _DARF_RC8(x)				(((x) & 0x1F) << 24)


//2 RARFRC
#define _RARF_RC1(x)				((x) & 0x1F)
#define _RARF_RC2(x)				(((x) & 0x1F) << 8)
#define _RARF_RC3(x)				(((x) & 0x1F) << 16)
#define _RARF_RC4(x)				(((x) & 0x1F) << 24)
// NOTE: shift starting from address (RARFRC + 4)
#define _RARF_RC5(x)				((x) & 0x1F)
#define _RARF_RC6(x)				(((x) & 0x1F) << 8)
#define _RARF_RC7(x)				(((x) & 0x1F) << 16)
#define _RARF_RC8(x)				(((x) & 0x1F) << 24)




//=========================================//
//    SECURITY  BIT DEFINITION
//=========================================//
//2 //2 CAMCMD
#define SECCAM_POLLING		BIT(31)
#define SECCAN_CLR			BIT(30)
#define SECCAM_WE			BIT(16)
#define SECCAM_ADDR_MASK	0xFF


//2 CAMDBG

//2 SECCFG
#define TXUSEDK				BIT(0)
#define RXUSEDK				BIT(1)
#define TXENC				BIT(2)
#define RXDEC				BIT(3)
#define SKBYA2				BIT(4)
#define NOSKMC				BIT(5)


//=========================================//
//    TXDMA  BIT DEFINITION
//=========================================//
//2 //2 RQPN
#define _HPQ(x)					(x)
#define _LPQ(x)					((x) << 8)
#define _PUBQ(x)				((x) << 16)

#define HPQ_PUBLIC_DIS			BIT(24)
#define LPQ_PUBLIC_DIS			BIT(25)
#define LD_RQPN					BIT(31)

//8195 normal chip
#define	_NPQ(x)				(x)



//2 TDECTL
#define BLK_DESC_NUM_SHIFT		4
#define BLK_DESC_NUM_MASK		0xF

//=========================================//
//    USB  BIT DEFINITION
//=========================================//
//2 //2 USB Information (0xFE17)
#define USB_IS_HIGH_SPEED		0
#define USB_IS_FULL_SPEED		1
#define USB_SPEED_MASK			BIT(5)


//2 Special Option
#define USB_AGG_EN				BIT(3)

//=========================================//
// 0x0600h ~ 0x07FFh	WMAC Configuration
//=========================================//
//2 CR
#define APSDOFF					BIT(6)
#define APSDOFF_STATUS			BIT(7)


//2 BWOPMODE
#define BW_20MHZ				BIT(2)

//2 TCR
#define TSFRST					BIT(0)
#define CRC						BIT(8)
#define CFENDFORM				BIT(9)
#define ICV						BIT(10)
#define DIS_TXPL_PREFETCH		BIT(11)
#define ONLY_TKIPWEP_AGG_WDPTH	BIT(13)
#define DIS_WDPTH				BIT(14)


//2 RCR
#define AAP						BIT(0)
#define APM						BIT(1)
#define AM						BIT(2)
#define AB						BIT(3)
#define ADD3					BIT(4)
#define APWRMGT					BIT(5)

//filen: test chip
//#define CBSSID						BIT(6)   	

//filen: below two belong to normal chip
#define CBSSID_DATA					BIT(6)
#define CBSSID_BCN				BIT(7)

#define ACRC32					BIT(8)
#define AICV					BIT(9)
#define ADF						BIT(11)
#define ACF						BIT(12)
#define AMF						BIT(13)
#define HTC_LOC_CTRL			BIT(14)
#define MFBEN					BIT(22)
#define LSIGEN					BIT(23)
#define EnMBID					BIT(24)
#define APP_BASSN				BIT(27)
#define APP_PHYSTS				BIT(28)
#define APP_ICV					BIT(29)
#define APP_MIC					BIT(30)
#define APP_FCS					BIT(31)

//2 NAV_CTRL
#define _RTSRST(x)				((x) & 0xFF)
#define _NAV_UPPER(x)			(((x) & 0xFF) << 8)


//2 AMPDU_MIN_SPACE
#define _MIN_SPACE(x)			((x) & 0x7)
#define _SHORT_GI_PADDING(x)	(((x) & 0x1F) << 3)


//2 RXERR_RPT
#define RXERR_TYPE_OFDM_PPDU		0
#define RXERR_TYPE_OFDM_FALSE_ALARM	1
#define	RXERR_TYPE_OFDM_MPDU_OK		2
#define RXERR_TYPE_OFDM_MPDU_FAIL	3
#define RXERR_TYPE_CCK_PPDU			4
#define RXERR_TYPE_CCK_FALSE_ALARM	5
#define RXERR_TYPE_CCK_MPDU_OK		6
#define RXERR_TYPE_CCK_MPDU_FAIL	7
#define RXERR_TYPE_HT_PPDU			8
#define RXERR_TYPE_HT_FALSE_ALARM	9
#define RXERR_TYPE_HT_MPDU_TOTAL	10
#define RXERR_TYPE_HT_MPDU_OK		11
#define RXERR_TYPE_HT_MPDU_FAIL		12
#define RXERR_TYPE_RX_FULL_DROP		15

#define RXERR_COUNTER_MASK			0xFFFFF
#define RXERR_RPT_RST				BIT(27)
#define _RXERR_RPT_SEL(type)		((type) << 28)

#endif


