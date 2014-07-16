#ifndef __DRV_TYPE_H__
#define __DRV_TYPE_H__

#include "autoconf.h"
#include "basic_types.h"
#include "sta_info.h"
#include "if_ether.h"
#include "rtw_xmit.h"


#ifdef CONFIG_SDIO_HCI
#include "drv_types_sdio.h"
#define INTF_DATA SDIO_DATA
#elif defined(CONFIG_GSPI_HCI)
#include <drv_types_gspi.h>
#define INTF_DATA GSPI_DATA
#elif defined(CONFIG_PCI_HCI)
#include <drv_types_pci.h>
#endif

#define ETH_ALEN 6 //6 octets for 
struct cam_entry_cache {
	u16 ctrl;
	u8 mac[ETH_ALEN];
	u8 key[16];
};
enum _IFACE_ID {
	IFACE_ID0, //maping to PRIMARY_ADAPTER
	IFACE_ID1, //maping to SECONDARY_ADAPTER
	IFACE_ID2,
	IFACE_ID3,
	IFACE_ID_MAX,
};
struct debug_priv {
	u32 dbg_sdio_free_irq_error_cnt;
	u32 dbg_sdio_alloc_irq_error_cnt;
	u32 dbg_sdio_free_irq_cnt;
	u32 dbg_sdio_alloc_irq_cnt;
	u32 dbg_sdio_deinit_error_cnt;
	u32 dbg_sdio_init_error_cnt;
	u32 dbg_suspend_error_cnt;
	u32 dbg_suspend_cnt;
	u32 dbg_resume_cnt;
	u32 dbg_resume_error_cnt;
	u32 dbg_deinit_fail_cnt;
	u32 dbg_carddisable_cnt;
	u32 dbg_carddisable_error_cnt;
	u32 dbg_ps_insuspend_cnt;
	u32	dbg_dev_unload_inIPS_cnt;
	u32 dbg_wow_leave_ps_fail_cnt;
	u32 dbg_scan_pwr_state_cnt;
	u32 dbg_downloadfw_pwr_state_cnt;
	u32 dbg_fw_read_ps_state_fail_cnt;
	u32 dbg_leave_ips_fail_cnt;
	u32 dbg_leave_lps_fail_cnt;
	u32 dbg_h2c_leave32k_fail_cnt;
	u32 dbg_diswow_dload_fw_fail_cnt;
	u32 dbg_enwow_dload_fw_fail_cnt;
	u32 dbg_ips_drvopen_fail_cnt;
	u32 dbg_poll_fail_cnt;
	u32 dbg_rpwm_toogle_cnt;
	u32 dbg_rpwm_timeout_fail_cnt;
	u32 dbg_sreset_cnt;
	u64 dbg_rx_fifo_last_overflow;
	u64 dbg_rx_fifo_curr_overflow;
	u64 dbg_rx_fifo_diff_overflow;
	u64 dbg_rx_ampdu_drop_count;
	u64 dbg_rx_ampdu_forced_indicate_count;
	u64 dbg_rx_ampdu_loss_count;
	u64 dbg_rx_dup_mgt_frame_drop_count;
	u64 dbg_rx_ampdu_window_shift_cnt;
};

struct _ADAPTER{
	int	DriverState;// for disable driver using module, use dongle to replace module.
	int	pid[3];//process id from UI, 0:wps, 1:hostapd, 2:dhcpcd
	int	bDongle;//build-in module or external dongle
	u16 	chip_type;
	u16	HardwareType;
	u16	interface_type;//USB,SDIO,SPI,PCI

	struct dvobj_priv *dvobj;
//		struct	mlme_priv mlmepriv;
//		struct	mlme_ext_priv mlmeextpriv;
//		struct	cmd_priv	cmdpriv;
//		struct	evt_priv	evtpriv;
//		//struct	io_queue	*pio_queue;
//		struct 	io_priv	iopriv;
//		struct	xmit_priv	xmitpriv;
//		struct	recv_priv	recvpriv;
//		struct	sta_priv	stapriv;
//		struct	security_priv	securitypriv;
//		_lock   security_key_mutex; // add for CONFIG_IEEE80211W, none 11w also can use
//		struct	registry_priv	registrypriv;
//		struct 	eeprom_priv eeprompriv;
//		struct	led_priv	ledpriv;
//	
//	#ifdef CONFIG_MP_INCLUDED
//	       struct	mp_priv	mppriv;
//	#endif
//	
//	#ifdef CONFIG_DRVEXT_MODULE
//		struct	drvext_priv	drvextpriv;
//	#endif
//	
//	#ifdef CONFIG_AP_MODE
//		struct	hostapd_priv	*phostapdpriv;
//	#endif
//	
//	#ifdef CONFIG_IOCTL_CFG80211
//	#ifdef CONFIG_P2P
//		struct cfg80211_wifidirect_info	cfg80211_wdinfo;
//	#endif //CONFIG_P2P
//	#endif //CONFIG_IOCTL_CFG80211
//		u32	setband;
//	#ifdef CONFIG_P2P
//		struct wifidirect_info	wdinfo;
//	#endif //CONFIG_P2P
//	
//	#ifdef CONFIG_TDLS
//		struct tdls_info	tdlsinfo;
//	#endif //CONFIG_TDLS
//	
//	#ifdef CONFIG_WAPI_SUPPORT
//		u8	WapiSupport;
//		RT_WAPI_T	wapiInfo;
//	#endif
//	
//	
//	#ifdef CONFIG_WFD
//		struct wifi_display_info wfd_info;
//	#endif //CONFIG_WFD

	void *		HalData;
	u32 hal_data_sz;
//	struct hal_ops	HalFunc;

	s32	bDriverStopped;
	s32	bSurpriseRemoved;
	s32  bCardDisableWOHSM;

	u32	IsrContent;
	u32	ImrContent;

	u8	EepromAddressSize;
	u8	hw_init_completed;
	u8	bDriverIsGoingToUnload;
	u8	init_adpt_in_progress;
	u8	bHaltInProgress;

//		_thread_hdl_ cmdThread;
//		_thread_hdl_ evtThread;
//		_thread_hdl_ xmitThread;
//		_thread_hdl_ recvThread;

#ifndef PLATFORM_LINUX
//	NDIS_STATUS (*dvobj_init)(struct dvobj_priv *dvobj);
	void (*dvobj_deinit)(struct dvobj_priv *dvobj);
#endif

 	u32 (*intf_init)(struct dvobj_priv *dvobj);
	void (*intf_deinit)(struct dvobj_priv *dvobj);
	int (*intf_alloc_irq)(struct dvobj_priv *dvobj);
	void (*intf_free_irq)(struct dvobj_priv *dvobj);
	

//	void (*intf_start)(_adapter *adapter);
//	void (*intf_stop)(_adapter *adapter);

#ifdef PLATFORM_WINDOWS
	_nic_hdl		hndis_adapter;//hNdisAdapter(NDISMiniportAdapterHandle);
	_nic_hdl		hndis_config;//hNdisConfiguration;
	NDIS_STRING fw_img;

	u32	NdisPacketFilter;
	u8	MCList[MAX_MCAST_LIST_NUM][6];
	u32	MCAddrCount;
#endif //end of PLATFORM_WINDOWS


#ifdef PLATFORM_LINUX
//	_nic_hdl pnetdev;
	char old_ifname[IFNAMSIZ];

	// used by rtw_rereg_nd_name related function
//		struct rereg_nd_name_data {
//			_nic_hdl old_pnetdev;
//			char old_ifname[IFNAMSIZ];
//			u8 old_ips_mode;
//			u8 old_bRegUseLed;
//		} rereg_nd_name_priv;

	int bup;
//		struct net_device_stats stats;
//		struct iw_statistics iwstats;
//		struct proc_dir_entry *dir_dev;// for proc directory
//		struct proc_dir_entry *dir_odm;

#ifdef CONFIG_IOCTL_CFG80211
	struct wireless_dev *rtw_wdev;
	struct rtw_wdev_priv wdev_data;
#endif //CONFIG_IOCTL_CFG80211

#endif //end of PLATFORM_LINUX

#ifdef PLATFORM_FREEBSD
	_nic_hdl pifp;
	int bup;
	_lock glock;
#endif //PLATFORM_FREEBSD
	int net_closed;
	
	u8 netif_up;

	u8 bFWReady;
	u8 bBTFWReady;
	u8 bLinkInfoDump;
	u8 bRxRSSIDisplay;
	//	Added by Albert 2012/10/26
	//	The driver will show up the desired channel number when this flag is 1.
	u8 bNotifyChannelChange;
#ifdef CONFIG_P2P
	//	Added by Albert 2012/12/06
	//	The driver will show the current P2P status when the upper application reads it.
	u8 bShowGetP2PState;
#endif
#ifdef CONFIG_AUTOSUSPEND
	u8	bDisableAutosuspend;
#endif

	//pbuddy_adapter is used only in  two inteface case, (iface_nums=2 in struct dvobj_priv)
	//PRIMARY_ADAPTER's buddy is SECONDARY_ADAPTER
	//SECONDARY_ADAPTER's buddy is PRIMARY_ADAPTER
	//for iface_id > SECONDARY_ADAPTER(IFACE_ID1), refer to padapters[iface_id]  in struct dvobj_priv
	//and their pbuddy_adapter is PRIMARY_ADAPTER.
	//for PRIMARY_ADAPTER(IFACE_ID0) can directly refer to if1 in struct dvobj_priv
//	_adapter *pbuddy_adapter;

#if defined(CONFIG_CONCURRENT_MODE) || defined(CONFIG_DUALMAC_CONCURRENT)
	u8 isprimary; //is primary adapter or not
	//notes:
	// if isprimary is true, the adapter_type value is 0, iface_id is IFACE_ID0 for PRIMARY_ADAPTER
	// if isprimary is false, the adapter_type value is 1, iface_id is IFACE_ID1 for SECONDARY_ADAPTER
	// refer to iface_id if iface_nums>2 and isprimary is false and the adapter_type value is 0xff.
	u8 adapter_type;//used only in  two inteface case(PRIMARY_ADAPTER and SECONDARY_ADAPTER) .
	u8 iface_type; //interface port type, it depends on HW port
#endif //CONFIG_CONCURRENT_MODE || CONFIG_DUALMAC_CONCURRENT

	//extend to support multi interface
       //IFACE_ID0 is equals to PRIMARY_ADAPTER
       //IFACE_ID1 is equals to SECONDARY_ADAPTER
	u8 iface_id;

#ifdef CONFIG_DUALMAC_CONCURRENT
	u8 DualMacConcurrent; // 1: DMSP 0:DMDP
#endif

#ifdef CONFIG_BR_EXT
	_lock					br_ext_lock;
	//unsigned int			macclone_completed;
	struct nat25_network_db_entry	*nethash[NAT25_HASH_SIZE];
	int				pppoe_connection_in_progress;
	unsigned char			pppoe_addr[MACADDRLEN];
	unsigned char			scdb_mac[MACADDRLEN];
	unsigned char			scdb_ip[4];
	struct nat25_network_db_entry	*scdb_entry;
	unsigned char			br_mac[MACADDRLEN];
	unsigned char			br_ip[4];

	struct br_ext_info		ethBrExtInfo;
#endif	// CONFIG_BR_EXT

#ifdef CONFIG_INTEL_PROXIM
	/* intel Proximity, should be alloc mem
	 * in intel Proximity module and can only
	 * be used in intel Proximity mode */
	struct proxim proximity;
#endif	//CONFIG_INTEL_PROXIM

#ifdef CONFIG_MAC_LOOPBACK_DRIVER
	PLOOPBACKDATA ploopback;
#endif

	u8 fix_rate;

	unsigned char     in_cta_test;
};
typedef struct _ADAPTER _adapter, ADAPTER, *PADAPTER;
struct dvobj_priv{
	/*-------- below is common data --------*/	
	_adapter *if1; //PRIMARY_ADAPTER
	_adapter *if2; //SECONDARY_ADAPTER

	s32	processing_dev_remove;

	struct debug_priv drv_dbg;

	//for local/global synchronization
	//
	_lock	lock;
	int macid[NUM_STA];

	_mutex hw_init_mutex;
	_mutex h2c_fwcmd_mutex;
	_mutex setch_mutex;
	_mutex setbw_mutex;

	unsigned char	oper_channel; //saved channel info when call set_channel_bw
	unsigned char	oper_bwmode;
	unsigned char	oper_ch_offset;//PRIME_CHNL_OFFSET
	u32 on_oper_ch_time;

	//extend to support mulitu interface
	//padapters[IFACE_ID0] == if1
	//padapters[IFACE_ID1] == if2
	_adapter *padapters[IFACE_ID_MAX];
	u8 iface_nums; // total number of ifaces used runtime

	struct cam_entry_cache cam_cache[32];

	//For 92D, DMDP have 2 interface.
	u8	InterfaceNumber;
	u8	NumInterfaces;

	//In /Out Pipe information
	int	RtInPipe[2];
	int	RtOutPipe[4];
	u8	Queue2Pipe[HW_QUEUE_ENTRY];//for out pipe mapping

	u8	irq_alloc;
	ATOMIC_T continual_io_error;

	ATOMIC_T disable_func;

//	struct pwrctrl_priv pwrctl_priv;

//	struct rtw_traffic_statistics	traffic_stat;

/*-------- below is for SDIO INTERFACE --------*/

#ifdef INTF_DATA
	INTF_DATA intf_data;
#endif
};

#endif
