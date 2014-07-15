#ifndef __DRV_TYPE_H__
#define __DRV_TYPE_H__
#include "basic_types.h"
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

	PVOID			HalData;
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
	

	void (*intf_start)(_adapter * adapter);
	void (*intf_stop)(_adapter * adapter);

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
	_adapter *pbuddy_adapter;

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
typedef struct _ADAPTER _adapter, ADAPTER,*PADAPTER;
struct dvobj_priv{
};
#endif