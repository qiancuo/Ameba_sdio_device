#ifndef __8195_DESC_H__
#define __8195_DESC_H__

typedef struct _RTL8195A_ATCMD_DESC{
//DWORD 0
unsigned int pktsize: 16; //=tx_desc.pktsize - cmd_desc.offset
unsigned int offset: 8; //cmd header size
unsigned int resv: 7;
unsigned int datatype: 1; // only one bit used, 0: data frame 1: management frame
}RTL8195A_ATCMD_DESC, *PRTL8195A_ATCMD_DESC;

typedef struct _TX_DESC{
	// DWORD 0
	unsigned int	txpktsize:16;
	unsigned int	offset:8;
	unsigned int	bmc:1;
	unsigned int	htc:1;
	unsigned int	ls:1;
	unsigned int	fs:1;
	unsigned int	linip:1;
	unsigned int	noacm:1;
	unsigned int	gf:1;            //Green Field enable
	unsigned int	own:1;           //When set, this bit indicates that the descriptor is owned by NIC
	
	// DWORD 1
	unsigned int	macid:5;			
	unsigned int	agg_en:1;
	unsigned int	bk:1;
	unsigned int	rdg_en:1;

	unsigned int	qsel:5;
	unsigned int    rdg_nav_ext:1;
	unsigned int	lsig_txop_en:1;	
	unsigned int	pifs:1;

	unsigned int	rate_id:4;
	unsigned int	navusehdr:1;
	unsigned int	en_desc_id:1;
	unsigned int	sectype:2;

	unsigned int	rsvd2:2;
	unsigned int	pkt_offset:5;
	unsigned int	rsvd3:1;
	
	// DWORD 2
	unsigned int    rts_rc:6;
	unsigned int    data_rc:6;
	unsigned int    rsvd8:2;	
	unsigned int	bar_rty_th:2;

	unsigned int    rsvd4:1;
	unsigned int	morefrag:1;
	unsigned int    raw:1;
	unsigned int    ccx:1;
	unsigned int    ampdu_density:3;
	unsigned int    rsvd5:1;
	
	unsigned int    antsel_a:1;
	unsigned int    antsel_b:1;
	unsigned int    tx_ant_cck:2;
	unsigned int	tx_antl:2;
	unsigned int    tx_antht:2;
	
	// DWORD 3
	unsigned int	nextheadpage:8;
	unsigned int	tailpage:8;
	unsigned int	seq:12;
	unsigned int	pkt_id:4;
	
	// DWORD 4
	unsigned int	rtsrate:5;
	unsigned int    ap_dcfe:1;
	unsigned int    qos: 1;
	unsigned int    hwseq_en:1;
	
	unsigned int	userate:1;
	unsigned int	disrtsfb:1;
	unsigned int	disdatafb:1;
	unsigned int	cts2self:1;
	unsigned int	rtsen:1;
	unsigned int	hw_rts_en:1;
	unsigned int	port_toggle:1;
	unsigned int    rsvd6:1;
	
	unsigned int    rsvd7:2;
	unsigned int	wait_dcts:1;
	unsigned int	cts2ap_en:1;
	unsigned int	data_txsc:2;
	unsigned int	data_stbc:2;
	
	unsigned int	data_short:1;
	unsigned int	databw:1;
	unsigned int	rts_short:1;
	unsigned int	rtsbw:1;
	unsigned int	rts_sc:2;
	unsigned int	vcs_stbc:2;

	// DWORD 5
	unsigned int	datarate:8;

	unsigned int	data_ratefb_lmt:5;
	unsigned int	rts_ratefb_lmt:4;
	unsigned int	rty_en:1;
	unsigned int	data_rt_lmt:6;

	unsigned int	usb_txagg_num:8;
	
	// DWORD 6
	unsigned int	txagc_a:5;
	unsigned int	txagc_b:5;
	unsigned int	use_max_len:1;
	unsigned int	max_agg_num:5;
	unsigned int	mcsg1_max_len:4;
	unsigned int	mcsg2_max_len:4;
	unsigned int	mcsg3_max_len:4;
	unsigned int	mcsg7_max_len:4;

	// DWORD 7
unsigned int	txbuffsize:16;		//PCIe
unsigned int	mcsg4_max_len:4;
unsigned int	mcsg5_max_len:4;
unsigned int	mcsg6_max_len:4;
unsigned int	mcsg15_max_len:4;
}TX_DESC, *PTX_DESC;
#define	SIZE_TX_DESC_8195a	(sizeof(TX_DESC))
typedef struct _TX_DESC TXDESC_8195A, *PTXDESC_8195A;
typedef struct _TX_EXTEND_DESC{
	unsigned int       Pkt_num:4;
	unsigned int       Len0:12;
	unsigned int       Len1:12;
	unsigned int       Len2_p1:4;
	unsigned int       Len2_p2:8;
	unsigned int       Len3:12;
	unsigned int       Len4:12;
	
}TX_EXTEND_DESC, *PTX_EXTEND_DESC;

typedef struct _RX_DESC{
	// DWORD 0
	unsigned int	pkt_len:14;
	unsigned int	crc32:1;
	unsigned int	icverr:1;
	unsigned int	drv_info_size:4;
	unsigned int	security:3;
	unsigned int	qos:1;
	unsigned int	shift:2;
	unsigned int	physt:1;
	unsigned int	swdec:1;
	unsigned int	ls:1;
	unsigned int	fs:1;
	unsigned int	eor:1;
	unsigned int	own:1;

	// DWORD 1
	unsigned int	macid:5;			
	unsigned int	tid:4;
	unsigned int	hwrsvd:4;
	unsigned int	amsdu:1;
	unsigned int	paggr:1;
	unsigned int	faggr:1;
	unsigned int	a1_fit:4;
	unsigned int	a2_fit:4;
	unsigned int	pam:1;
	unsigned int	pwr:1;
	unsigned int	md:1;
	unsigned int	mf:1;
	unsigned int	type:2;
	unsigned int	mc:1;
	unsigned int	bc:1;
	
	// DWORD 2
	unsigned int	seq:12;
	unsigned int	frag:4;
	unsigned int	usb_agg_pkt_num:8;
	unsigned int	rsvd1:6;
	unsigned int	next_ind:1;
	unsigned int	rsvd2:1;
	
	// DWORD 3
	unsigned int	rxmcs:6;			
	unsigned int	rxht:1;
	unsigned int	gf:1;
	unsigned int	splcp:1;
	unsigned int	bw:1;
	unsigned int	htc:1;
	unsigned int	eosp:1;
	unsigned int	bssid_fit:2;
	unsigned int	hwpc_err:1;
	unsigned int	hwpc_ind:1;
	unsigned int	iv1:16;
	
	// DWORD 4
	unsigned int	iv;

	// DWORD 5
	unsigned int	tsfl;
} RX_DESC, *PRX_DESC;
#define	SIZE_RX_DESC_8195a	(sizeof(RX_DESC))

typedef struct _FIFO_INFO{

	unsigned char	tx_pub_page;
	unsigned char	tx_hi_page;
	unsigned char	tx_mid_page;
	unsigned char	tx_low_page;

	unsigned char	 HISR_L;
	unsigned char	 HISR_R;
	unsigned short	rx_agg_len;	

}FIFO_INFO, *PFIFO_INFO;

#define	SIZE_RX_DESC_8192C	24

// Tx QSEL
enum _QSEL {
	QSEL_TID0 = 0,
	QSEL_TID1,
	QSEL_TID2,
	QSEL_TID3,
	QSEL_TID4,
	QSEL_TID5,
	QSEL_TID6,
	QSEL_TID7,
	QSEL_TID8,
	QSEL_TID9,			
	QSEL_TIDA,
	QSEL_TIDB,
	QSEL_TIDC,
	QSEL_TIDD,
	QSEL_TIDE,
	QSEL_TIDF,

	QSEL_BEACON	= 0x10,
	QSEL_HIGH		= 0x11,
	QSEL_MGT		= 0x12,
	QSEL_CMD		= 0x13	// deprecated in 8191C
};

typedef struct _TX_QUEUE_MAPPING
{

      unsigned char HIQueueToPriorty;
      unsigned char MGQueueToPriorty;
      unsigned char BEQueueToPriorty;
      unsigned char BKQueueToPriorty;
      unsigned char VIQueueToPriorty;
      unsigned char VOQueueToPriorty;
	 

}TX_QUEUE_MAPPING,*PTX_QUEUE_MAPPING;

#define VO_Q QSEL_TID6
#define VI_Q  QSEL_TID4
#define BE_Q  QSEL_TID0
#define BK_Q  QSEL_TID1
#define BCN_Q QSEL_BEACON
#define CMD_Q QSEL_CMD

// Tx descriptor security type
#define TXDESC_SECTYPE_NO			0x0
#define TXDESC_SECTYPE_WEP			0x1
#define TXDESC_SECTYPE_TKIP			0x1
#define TXDESC_SECTYPE_WAPI			0x2
#define TXDESC_SECTYPE_AES			0x3


// Rx descriptor security type
#define RXDESC_SECTYPE_NO			0x0
#define RXDESC_SECTYPE_WEP40		0x1
#define RXDESC_SECTYPE_WEP104		0x5
#define RXDESC_SECTYPE_TKIP_WO_MIC	0x2
#define RXDESC_SECTYPE_TKIP_WT_MIC	0x3
#define RXDESC_SECTYPE_AES			0x4

#endif