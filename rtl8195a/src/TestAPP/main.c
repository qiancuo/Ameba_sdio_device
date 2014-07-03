#include <stdio.h>

typedef struct _cmd_entry {
	char *command;
	void (*function)(int, char **);
} cmd_entry;
static const cmd_entry cmd_table[] = {
	{"wifi_connect", cmd_wifi_connect},
	{"wifi_disconnect", cmd_wifi_disconnect},
	{"wifi_info", cmd_wifi_info},
	{"wifi_on", cmd_wifi_on},
	{"wifi_off", cmd_wifi_off},
	{"wifi_ap", cmd_wifi_ap},
	{"wifi_scan", cmd_wifi_scan},
	{"wifi_get_rssi", cmd_wifi_get_rssi},
//	{"iwpriv", cmd_wifi_iwpriv},
//	{"promisc", cmd_promisc},
//	{"ttcp", cmd_ttcp},
	{"ping", cmd_ping},
	{"exit", cmd_exit},
	{"help", cmd_help}
};
static void cmd_help(int argc, char **argv)
{
	int i;

	printf("\n\rCOMMAND LIST:");
	printf("\n\r==============================");

	for(i = 0; i < sizeof(cmd_table) / sizeof(cmd_table[0]); i ++)
		printf("\n\r    %s", cmd_table[i].command);
}
static void cmd_wifi_connect(int argc, char **argv)
{
	printf("\n\rDo %s", __FUNCTION__);
	if((argc != 2) && (argc != 3) && (argc != 4)) {
		printf("\n\rUsage: wifi_connect SSID [WPA PASSWORD / (5 or 13) ASCII WEP KEY] [WEP KEY ID 0/1/2/3]");
		return;
	}
//todo: send relative data to Ameba
}
static void cmd_wifi_disconnect(int argc, char **argv)
{
	printf("\n\rDo %s", __FUNCTION__);
//todo: send relative data to Ameba
}

static void cmd_wifi_info(int argc, char **argv)
{
	printf("\n\rDo %s", __FUNCTION__);
//todo: send relative data to Ameba
}

static void cmd_wifi_on(int argc, char **argv)
{
	printf("\n\rDo %s", __FUNCTION__);
//todo: send relative data to Ameba
}

static void cmd_wifi_off(int argc, char **argv)
{
	printf("\n\rDo %s", __FUNCTION__);
//todo: send relative data to Ameba
}

static void cmd_wifi_ap(int argc, char **argv)
{
	printf("\n\rDo %s", __FUNCTION__);
//	WIFI_AP ap = {0};
	int timeout = 20, mode;
	unsigned char ssid[33];

	if((argc != 3) && (argc != 4)) {
		printf("\n\rUsage: wifi_ap SSID CHANNEL [PASSWORD]");
		return;
	}
}
static void cmd_wifi_scan(int argc, char **argv)
{
	printf("\n\rDo %s", __FUNCTION__);
	int scan_cnt = 0, add_cnt = 0;
	if(argc == 2 && argv[1]){
		//todo: send relative data to Ameba
	}
	else{
		printf("\n\rUsage: wifi_scan BUFFER_LENGTH");
	}
}

static void cmd_wifi_get_rssi(int argc, char **argv)
{
	printf("\n\rDo %s", __FUNCTION__);
	int rssi = 0;
//	wifi_get_rssi(&rssi);
//todo: send relative data to Ameba
	printf("\n\rwifi_get_rssi: rssi = %d", rssi);
}

static void cmd_ping(int argc, char **argv)
{
	if(argc == 2) {
//		do_ping_call(argv[1], 0, 5);	//Not loop, count=5
		//todo: send relative data to Ameba

	}
	else if(argc == 3) {
		if(strcmp(argv[2], "loop") == 0)
//			do_ping_call(argv[1], 1, 0);	//loop, no count
			//todo: send relative data to Ameba
		else
//			do_ping_call(argv[1], 0, atoi(argv[2]));	//Not loop, with count
			//todo: send relative data to Ameba
	}
	else {
		printf("\n\rUsage: ping IP [COUNT/loop]");
	}
}

int main(int argc, char **argv)
{
	return 0;
}

