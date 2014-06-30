#include "rtl8195_pwrseq.h"

/* 
    drivers should parse below arrays and do the corresponding actions
*/
//3 Power on  Array
WLAN_PWR_CFG rtl8195_power_on_flow[RTL8195_TRANS_CARDEMU_TO_ACT_STEPS+RTL8195_TRANS_END_STEPS]=
{
	RTL8195_TRANS_CARDEMU_TO_ACT
	RTL8195_TRANS_END
};

//3Radio off GPIO Array
WLAN_PWR_CFG rtl8195_radio_off_flow[RTL8195_TRANS_ACT_TO_CARDEMU_STEPS+RTL8195_TRANS_END_STEPS]=
{
	RTL8195_TRANS_ACT_TO_CARDEMU
	RTL8195_TRANS_END
};

//3Card Disable Array
WLAN_PWR_CFG rtl8195_card_disable_flow[RTL8195_TRANS_ACT_TO_CARDEMU_STEPS+RTL8195_TRANS_CARDEMU_TO_PDN_STEPS+RTL8195_TRANS_END_STEPS]=
{
	RTL8195_TRANS_ACT_TO_CARDEMU
	RTL8195_TRANS_CARDEMU_TO_CARDDIS
	RTL8195_TRANS_END
};

//3 Card Enable Array
WLAN_PWR_CFG rtl8195_card_enable_flow[RTL8195_TRANS_ACT_TO_CARDEMU_STEPS+RTL8195_TRANS_CARDEMU_TO_PDN_STEPS+RTL8195_TRANS_END_STEPS]=
{
	RTL8195_TRANS_CARDDIS_TO_CARDEMU
	RTL8195_TRANS_CARDEMU_TO_ACT		
	RTL8195_TRANS_END
};

//3Suspend Array
WLAN_PWR_CFG rtl8195_suspend_flow[RTL8195_TRANS_ACT_TO_CARDEMU_STEPS+RTL8195_TRANS_CARDEMU_TO_SUS_STEPS+RTL8195_TRANS_END_STEPS]=
{
	RTL8195_TRANS_ACT_TO_CARDEMU
	RTL8195_TRANS_CARDEMU_TO_SUS
	RTL8195_TRANS_END
};

//3 Resume Array
WLAN_PWR_CFG rtl8195_resume_flow[RTL8195_TRANS_ACT_TO_CARDEMU_STEPS+RTL8195_TRANS_CARDEMU_TO_SUS_STEPS+RTL8195_TRANS_END_STEPS]=
{
	RTL8195_TRANS_SUS_TO_CARDEMU
	RTL8195_TRANS_CARDEMU_TO_ACT
	RTL8195_TRANS_END
};



//3HWPDN Array
WLAN_PWR_CFG rtl8195_hwpdn_flow[RTL8195_TRANS_ACT_TO_CARDEMU_STEPS+RTL8195_TRANS_CARDEMU_TO_PDN_STEPS+RTL8195_TRANS_END_STEPS]=
{
	//TRANS_ACT_TO_CARDEMU
	//TRANS_CARDEMU_TO_PDN		
	//HW behavior
	RTL8195_TRANS_END
};

//3 Enter LPS 
WLAN_PWR_CFG rtl8195_enter_lps_flow[RTL8195_TRANS_ACT_TO_LPS_STEPS+RTL8195_TRANS_END_STEPS]=
{
	//FW behavior
	RTL8195_TRANS_ACT_TO_LPS	
	RTL8195_TRANS_END
};

//3 Leave LPS 
WLAN_PWR_CFG rtl8195_leave_lps_flow[RTL8195_TRANS_LPS_TO_ACT_STEPS+RTL8195_TRANS_END_STEPS]=
{
	//FW behavior
	RTL8195_TRANS_LPS_TO_ACT
	RTL8195_TRANS_END
};


