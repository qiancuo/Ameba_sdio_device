#ifndef __HAL_DATA_H__
#define __HAL_DATA_H__
#include "autoconf.h"
#include <linux/mmc/sdio_func.h>
enum RTL871X_HCI_TYPE {
	RTW_PCIE	= BIT0,
	RTW_USB 	= BIT1,
	RTW_SDIO 	= BIT2,
	RTW_GSPI	= BIT3,
};
typedef struct hal_com_data
{
//	HAL_VERSION			VersionID;
//	RT_MULTI_FUNC		MultiFunc; // For multi-function consideration.
//	RT_POLARITY_CTL		PolarityCtl; // For Wifi PDn Polarity control.
//	RT_REGULATOR_MODE	RegulatorMode; // switching regulator or LDO

//		u16	FirmwareVersion;
//		u16	FirmwareVersionRev;
//		u16	FirmwareSubVersion;
//		u16	FirmwareSignature;

//	//current WIFI_PHY values
//	WIRELESS_MODE		CurrentWirelessMode;
//	CHANNEL_WIDTH	CurrentChannelBW;
//	BAND_TYPE			CurrentBandType;	//0:2.4G, 1:5G
//	BAND_TYPE			BandSet;
//		u8	CurrentChannel;
//		u8	CurrentCenterFrequencyIndex1;
//		u8	nCur40MhzPrimeSC;// Control channel sub-carrier
//		u8	nCur80MhzPrimeSC;   //used for primary 40MHz of 80MHz mode
//	
//		u16	CustomerID;
//		u16	BasicRateSet;
//		u16 ForcedDataRate;// Force Data Rate. 0: Auto, 0x02: 1M ~ 0x6C: 54M.
//		u32	ReceiveConfig;
//	
//		//rf_ctrl
//		u8	rf_chip;
//		u8	rf_type;
//		u8	PackageType;
//		u8	NumTotalRFPath;
//	
//		u8	InterfaceSel;
//		u8	framesync;
//		u32	framesyncC34;
//		u8	framesyncMonitor;
//		u8	DefaultInitialGain[4];
//		//
//		// EEPROM setting.
//		//
//		u16	EEPROMVID;
//		u16	EEPROMSVID;
//	#ifdef CONFIG_USB_HCI
//		u16	EEPROMPID;
//		u16	EEPROMSDID;
//	#endif
//	#ifdef CONFIG_PCI_HCI
//	 	u16	EEPROMDID;
//		u16	EEPROMSMID;	
//	#endif
//	
//		u8	EEPROMCustomerID;
//		u8	EEPROMSubCustomerID;
//		u8	EEPROMVersion;
//		u8	EEPROMRegulatory;
//		u8	EEPROMThermalMeter;
//		u8	EEPROMBluetoothCoexist;	
//		u8	EEPROMBluetoothType;
//		u8	EEPROMBluetoothAntNum;
//		u8	EEPROMBluetoothAntIsolation;
//		u8	EEPROMBluetoothRadioShared;
//		u8	bTXPowerDataReadFromEEPORM;
//		u8	bAPKThermalMeterIgnore;
//		u8	bDisableSWChannelPlan; // flag of disable software change channel plan
//	
//		BOOLEAN 		EepromOrEfuse;
//		u8				EfuseUsedPercentage;
//		u16				EfuseUsedBytes;
//		//u8				EfuseMap[2][HWSET_MAX_SIZE_JAGUAR];
//	//	EFUSE_HAL		EfuseHal;
//	
//		//---------------------------------------------------------------------------------//
	//3 [2.4G]
//	u8	Index24G_CCK_Base[MAX_RF_PATH][CHANNEL_MAX_NUMBER];
//	u8	Index24G_BW40_Base[MAX_RF_PATH][CHANNEL_MAX_NUMBER];
	//If only one tx, only BW20 and OFDM are used.
//	s8	CCK_24G_Diff[MAX_RF_PATH][MAX_TX_COUNT];	
//	s8	OFDM_24G_Diff[MAX_RF_PATH][MAX_TX_COUNT];
//	s8	BW20_24G_Diff[MAX_RF_PATH][MAX_TX_COUNT];
//	s8	BW40_24G_Diff[MAX_RF_PATH][MAX_TX_COUNT];
	//3 [5G]
//	u8	Index5G_BW40_Base[MAX_RF_PATH][CHANNEL_MAX_NUMBER];
//	u8	Index5G_BW80_Base[MAX_RF_PATH][CHANNEL_MAX_NUMBER_5G_80M];		
//	s8	OFDM_5G_Diff[MAX_RF_PATH][MAX_TX_COUNT];
//	s8	BW20_5G_Diff[MAX_RF_PATH][MAX_TX_COUNT];
//	s8	BW40_5G_Diff[MAX_RF_PATH][MAX_TX_COUNT];
//	s8	BW80_5G_Diff[MAX_RF_PATH][MAX_TX_COUNT];
//	
//		u8	Regulation2_4G;
//		u8	Regulation5G;
//	
//		u8	TxPwrInPercentage;
//	
//		u8	TxPwrCalibrateRate;
	//
	// TX power by rate table at most 4RF path.
	// The register is 
	//
	// VHT TX power by rate off setArray = 
	// Band:-2G&5G = 0 / 1
	// RF: at most 4*4 = ABCD=0/1/2/3
	// CCK=0 OFDM=1/2 HT-MCS 0-15=3/4/56 VHT=7/8/9/10/11			
	//
//		u8	TxPwrByRateTable;
//		u8	TxPwrByRateBand;
//	s8	TxPwrByRateOffset[TX_PWR_BY_RATE_NUM_BAND]
//						 [TX_PWR_BY_RATE_NUM_RF]
//						 [TX_PWR_BY_RATE_NUM_RF]
//						 [TX_PWR_BY_RATE_NUM_RATE];
	//---------------------------------------------------------------------------------//

	//2 Power Limit Table 
//	u8	TxPwrLevelCck[RF_PATH_MAX_92C_88E][CHANNEL_MAX_NUMBER];
//	u8	TxPwrLevelHT40_1S[RF_PATH_MAX_92C_88E][CHANNEL_MAX_NUMBER];	// For HT 40MHZ pwr
//	u8	TxPwrLevelHT40_2S[RF_PATH_MAX_92C_88E][CHANNEL_MAX_NUMBER];	// For HT 40MHZ pwr
//	u8	TxPwrHt20Diff[RF_PATH_MAX_92C_88E][CHANNEL_MAX_NUMBER];// HT 20<->40 Pwr diff
//	u8	TxPwrLegacyHtDiff[RF_PATH_MAX_92C_88E][CHANNEL_MAX_NUMBER];// For HT<->legacy pwr diff

	// Power Limit Table for 2.4G
//	u8	TxPwrLimit_2_4G[MAX_REGULATION_NUM]
//						[MAX_2_4G_BANDWITH_NUM]
//	                                [MAX_RATE_SECTION_NUM]
//	                                [CHANNEL_MAX_NUMBER_2G]
//						[MAX_RF_PATH_NUM];

	// Power Limit Table for 5G
//	u8	TxPwrLimit_5G[MAX_REGULATION_NUM]
//						[MAX_5G_BANDWITH_NUM]
//						[MAX_RATE_SECTION_NUM]
//						[CHANNEL_MAX_NUMBER_5G]
//						[MAX_RF_PATH_NUM];

	
	// Store the original power by rate value of the base of each rate section of rf path A & B
//		u8	TxPwrByRateBase2_4G[TX_PWR_BY_RATE_NUM_RF]
//							[TX_PWR_BY_RATE_NUM_RF]
//							[MAX_BASE_NUM_IN_PHY_REG_PG_2_4G];
//		u8	TxPwrByRateBase5G[TX_PWR_BY_RATE_NUM_RF]
//							[TX_PWR_BY_RATE_NUM_RF]
//							[MAX_BASE_NUM_IN_PHY_REG_PG_5G];

	// For power group
//		u8	PwrGroupHT20[RF_PATH_MAX_92C_88E][CHANNEL_MAX_NUMBER];
//		u8	PwrGroupHT40[RF_PATH_MAX_92C_88E][CHANNEL_MAX_NUMBER];
//	
//	
//		
//	
//		u8	PGMaxGroup;
//		u8	LegacyHTTxPowerDiff;// Legacy to HT rate power diff
	// The current Tx Power Level
//		u8	CurrentCckTxPwrIdx;
//		u8	CurrentOfdm24GTxPwrIdx;
//		u8	CurrentBW2024GTxPwrIdx;
//		u8	CurrentBW4024GTxPwrIdx;
	
	// Read/write are allow for following hardware information variables	
//		u8	pwrGroupCnt;
//		u32	MCSTxPowerLevelOriginalOffset[MAX_PG_GROUP][16];
//		u32	CCKTxPowerLevelOriginalOffset;
//	
//		u8	CrystalCap;
//		u32	AntennaTxPath;					// Antenna path Tx
//		u32	AntennaRxPath;					// Antenna path Rx
//	
//		u8	PAType_2G;
//		u8	PAType_5G;
//		u8	LNAType_2G;
//		u8	LNAType_5G;
//		u8	ExternalPA_2G;
//		u8	ExternalLNA_2G;
//		u8	ExternalPA_5G;
//		u8	ExternalLNA_5G;
//		u8	TypeGLNA;
//		u8	TypeGPA;
//		u8	TypeALNA;
//		u8	TypeAPA;
//		u8	RFEType;
//		u8	BoardType;
//		u8	ExternalPA;
//		u8	bIQKInitialized;
//		BOOLEAN		bLCKInProgress;
//	
//		BOOLEAN		bSwChnl;
//		BOOLEAN		bSetChnlBW;
//		BOOLEAN		bChnlBWInitialized;
//		BOOLEAN		bNeedIQK;
//	
//		u8	bLedOpenDrain; // Support Open-drain arrangement for controlling the LED. Added by Roger, 2009.10.16.
//		u8	TxPowerTrackControl; //for mp mode, turn off txpwrtracking as default
//		u8	b1x1RecvCombine;	// for 1T1R receive combining
//	
//		u32	AcParam_BE; //Original parameter for BE, use for EDCA turbo.	
//	
//		BB_REGISTER_DEFINITION_T	PHYRegDef[4];	//Radio A/B/C/D
//	
//		u32	RfRegChnlVal[2];
//	
//		//RDG enable
//		BOOLEAN	 bRDGEnable;
//	
//		//for host message to fw
//		u8	LastHMEBoxNum;
//	
//		u8	fw_ractrl;
//		u8	RegTxPause;
//		// Beacon function related global variable.
//		u8	RegBcnCtrlVal;
//		u8	RegFwHwTxQCtrl;
//		u8	RegReg542;
//		u8	RegCR_1;
//		u8	Reg837;
//		u8	RegRFPathS1;
//		u16	RegRRSR;
//	
//		u8	CurAntenna;
//		u8	AntDivCfg;
//		u8	AntDetection;
//		u8	TRxAntDivType;
//	
//		u8	u1ForcedIgiLb;			// forced IGI lower bound
//	
//		u8	bDumpRxPkt;//for debug
//		u8	bDumpTxPkt;//for debug
//		u8	FwRsvdPageStartOffset; //2010.06.23. Added by tynli. Reserve page start offset except beacon in TxQ.
//	
//		// 2010/08/09 MH Add CU power down mode.
//		BOOLEAN		pwrdown;
//	
//		// Add for dual MAC  0--Mac0 1--Mac1
//		u32	interfaceIndex;
//	
//		u8	OutEpQueueSel;
//		u8	OutEpNumber;

//		// 2010/12/10 MH Add for USB aggreation mode dynamic shceme.
//		BOOLEAN		UsbRxHighSpeedMode;
//	
//		// 2010/11/22 MH Add for slim combo debug mode selective.
//		// This is used for fix the drawback of CU TSMC-A/UMC-A cut. HW auto suspend ability. Close BT clock.
//		BOOLEAN		SlimComboDbg;

//	#ifdef CONFIG_P2P
//		u8	p2p_ps_offload;
//	#endif
//	
//		u8	AMPDUDensity;
//	
//		// Auto FSM to Turn On, include clock, isolation, power control for MAC only
//		u8	bMacPwrCtrlOn;
//	
//		u8	RegIQKFWOffload;
//		struct submit_ctx 	iqk_sctx;
//	
//		RT_AMPDU_BRUST		AMPDUBurstMode; //92C maybe not use, but for compile successfully

	//
	// For SDIO Interface HAL related
	//

	//
	// SDIO ISR Related
	//
//	u32			IntrMask[1];
//	u32			IntrMaskToSet[1];
//	LOG_INTERRUPT		InterruptLog;
	struct sdio_func *func;
	u32			sdio_himr;
	u32			sdio_hisr;

	//
	// SDIO Tx FIFO related.
	//
	// HIQ, MID, LOW, PUB free pages; padapter->xmitpriv.free_txpg
//	u8			SdioTxFIFOFreePage[SDIO_TX_FREE_PG_QUEUE];
//	_lock		SdioTxFIFOFreePageLock;
//	u8			SdioTxOQTMaxFreeSpace;
//	u8			SdioTxOQTFreeSpace;
	

	//
	// SDIO Rx FIFO related.
	//
	u8			SdioRxFIFOCnt;
	u16			SdioRxFIFOSize;

//	u32			sdio_tx_max_len[SDIO_MAX_TX_QUEUE];// H, N, L, used for sdio tx aggregation max length per queue

//	
//	#ifdef CONFIG_USB_HCI
//		u32	UsbBulkOutSize;
//		BOOLEAN		bSupportUSB3;
//	
//		// Interrupt relatd register information.
//		u32	IntArray[3];//HISR0,HISR1,HSISR
//		u32	IntrMask[3];
//		u8	C2hArray[16];
//		#ifdef CONFIG_USB_TX_AGGREGATION
//		u8	UsbTxAggMode;
//		u8	UsbTxAggDescNum;
//		#endif // CONFIG_USB_TX_AGGREGATION
//		
//		#ifdef CONFIG_USB_RX_AGGREGATION
//		u16	HwRxPageSize;				// Hardware setting
//		u32	MaxUsbRxAggBlock;
//	
//		USB_RX_AGG_MODE	UsbRxAggMode;
//		u8	UsbRxAggBlockCount;		//FOR USB Mode, USB Block count. Block size is 512-byte in hight speed and 64-byte in full speed
//		u8	UsbRxAggBlockTimeout;
//		u8	UsbRxAggPageCount;			//FOR DMA Mode, 8192C DMA page count
//		u8	UsbRxAggPageTimeout;
//	
//		u8	RegAcUsbDmaSize;
//		u8	RegAcUsbDmaTime;
//		#endif//CONFIG_USB_RX_AGGREGATION
//	#endif //CONFIG_USB_HCI
//	
//	
//	#ifdef CONFIG_PCI_HCI
//		//
//		// EEPROM setting.
//		//
//		u16	EEPROMChannelPlan;
//		
//		u8	EEPROMTSSI[2];
//		u8	EEPROMBoardType;
//		u32	TransmitConfig;	
//	
//		u32	IntrMaskToSet[2];
//		u32	IntArray[2];
//		u32	IntrMask[2];
//		u32	SysIntArray[1];
//		u32	SysIntrMask[1];
//		u32	IntrMaskReg[2];
//		u32	IntrMaskDefault[2];
//	
//		BOOLEAN	 bL1OffSupport;
//		BOOLEAN bSupportBackDoor;
//	
//		u8	bDefaultAntenna;
//		//u8	bIQKInitialized;
//		
//		u8	bInterruptMigration;
//		u8	bDisableTxInt;
//	#endif //CONFIG_PCI_HCI
//	
//		struct dm_priv	dmpriv;
//		DM_ODM_T 		odmpriv;
//	#ifdef DBG_CONFIG_ERROR_DETECT
//		struct sreset_priv srestpriv;
//	#endif //#ifdef DBG_CONFIG_ERROR_DETECT
//	
//	#ifdef CONFIG_BT_COEXIST
//		// For bluetooth co-existance
//		BT_COEXIST		bt_coexist;
//	#ifdef CONFIG_RTL8723A
//		u8				bAntennaDetected;
//	#endif // CONFIG_RTL8723A
//	#endif // CONFIG_BT_COEXIST
//	
//	#if defined(CONFIG_RTL8723A) || defined(CONFIG_RTL8723B)
//		#ifndef CONFIG_PCI_HCI	// mutual exclusive with PCI -- so they're SDIO and GSPI 
//		// Interrupt relatd register information.
//		u32			SysIntrStatus;
//		u32			SysIntrMask;
//		#endif
//	#endif //endif CONFIG_RTL8723A
//	
//		
//	#if defined(CONFIG_RTL8192C) ||defined(CONFIG_RTL8192D)
//		
//		u8	BluetoothCoexist;
//		
//		u8	EEPROMChnlAreaTxPwrCCK[2][3];	
//		u8	EEPROMChnlAreaTxPwrHT40_1S[2][3];	
//		u8	EEPROMChnlAreaTxPwrHT40_2SDiff[2][3];
//		u8	EEPROMPwrLimitHT20[3];
//		u8	EEPROMPwrLimitHT40[3];
//		#ifdef CONFIG_RTL8192D
//		MACPHY_MODE_8192D	MacPhyMode92D;
//		BAND_TYPE	CurrentBandType92D;	//0:2.4G, 1:5G
//		BAND_TYPE	BandSet92D;
//		BOOLEAN       bMasterOfDMSP;
//		BOOLEAN       bSlaveOfDMSP;
//	
//		IQK_MATRIX_REGS_SETTING IQKMatrixRegSetting[IQK_Matrix_Settings_NUM_92D];
//		#ifdef CONFIG_DUALMAC_CONCURRENT
//		BOOLEAN		bInModeSwitchProcess;
//		#endif
//		u8	AutoLoadStatusFor8192D;
//		u8	EEPROMC9;
//		u8	EEPROMCC;
//		u8	PAMode;
//		u8	InternalPA5G[2];	//pathA / pathB
//		BOOLEAN		bPhyValueInitReady;
//		BOOLEAN		bLoadIMRandIQKSettingFor2G;// True if IMR or IQK  have done  for 2.4G in scan progress
//		BOOLEAN		bNOPG;
//		BOOLEAN		bIsVS;
//		//Query RF by FW
//		BOOLEAN		bReadRFbyFW;
//		BOOLEAN		bEarlyModeEnable;
//		BOOLEAN		bSupportRemoteWakeUp;
//		BOOLEAN		bInSetPower;
//		u8	RTSInitRate;	 // 2010.11.24.by tynli.	
//		#endif //CONFIG_RTL8192D 
//	
//	#endif //defined(CONFIG_RTL8192C) ||defined(CONFIG_RTL8192D)
//	
//	#ifdef CONFIG_LOAD_PHY_PARA_FROM_FILE
//		char	para_file_buf[MAX_PARA_FILE_BUF_LEN];
//		char *mac_reg;
//		u32	mac_reg_len;
//		char *bb_phy_reg;
//		u32	bb_phy_reg_len;
//		char *bb_agc_tab;
//		u32	bb_agc_tab_len;
//		char *bb_phy_reg_pg;
//		u32	bb_phy_reg_pg_len;
//		char *bb_phy_reg_mp;
//		u32	bb_phy_reg_mp_len;
//		char *rf_radio_a;
//		u32	rf_radio_a_len;
//		char *rf_radio_b;
//		u32	rf_radio_b_len;
//		char *rf_tx_pwr_track;
//		u32	rf_tx_pwr_track_len;
//		char *rf_tx_pwr_lmt;
//		u32	rf_tx_pwr_lmt_len;
//	#endif
} HAL_DATA_COMMON, *PHAL_DATA_COMMON;

typedef struct hal_com_data HAL_DATA_TYPE, *PHAL_DATA_TYPE;

#endif

