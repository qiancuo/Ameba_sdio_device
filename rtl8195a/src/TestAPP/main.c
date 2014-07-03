#include <stdio.h>

typedef struct _cmd_entry {
	char *command;
	void (*function)(int, char **);
} cmd_entry;

static int global_exit =1;
static void cmd_help(int argc, char **argv);

static void cmd_wifi_connect(int argc, char **argv)
{
	printf("Do %s\n\r", __FUNCTION__);
	if((argc != 2) && (argc != 3) && (argc != 4)) {
		printf("Usage: wifi_connect SSID [WPA PASSWORD / (5 or 13) ASCII WEP KEY] [WEP KEY ID 0/1/2/3]\n\r");
		return;
	}
//todo: send relative data to Ameba
}
static void cmd_wifi_disconnect(int argc, char **argv)
{
	printf("Do %s\n\r", __FUNCTION__);;
//todo: send relative data to Ameba
}

static void cmd_wifi_info(int argc, char **argv)
{
	printf("Do %s\n\r", __FUNCTION__);
//todo: send relative data to Ameba
}

static void cmd_wifi_on(int argc, char **argv)
{
	printf("Do %s\n\r", __FUNCTION__);
//todo: send relative data to Ameba
}

static void cmd_wifi_off(int argc, char **argv)
{
	printf("Do %s\n\r", __FUNCTION__);
//todo: send relative data to Ameba
}

static void cmd_wifi_ap(int argc, char **argv)
{
	printf("Do %s\n\r", __FUNCTION__);
//	WIFI_AP ap = {0};
	int timeout = 20, mode;
	unsigned char ssid[33];

	if((argc != 3) && (argc != 4)) {
		printf("Usage: wifi_ap SSID CHANNEL [PASSWORD]\n\r");
		return;
	}
}
static void cmd_wifi_scan(int argc, char **argv)
{
	printf("Do %s\n\r", __FUNCTION__);
	int scan_cnt = 0, add_cnt = 0;
	if(argc == 2 && argv[1]){
		//todo: send relative data to Ameba
	}
	else{
		printf("Usage: wifi_scan BUFFER_LENGTH\n\r");
	}
}

static void cmd_wifi_get_rssi(int argc, char **argv)
{
	printf("Do %s\n\r", __FUNCTION__);
	int rssi = 0;
//	wifi_get_rssi(&rssi);
//todo: send relative data to Ameba
	printf("wifi_get_rssi: rssi = %d\n\r", rssi);
}

static void cmd_ping(int argc, char **argv)
{
	printf("Do %s\n\r", __FUNCTION__);
	if(argc == 2) {
//		do_ping_call(argv[1], 0, 5);	//Not loop, count=5
		//todo: send relative data to Ameba

	}
	else if(argc == 3) {
		if(strcmp(argv[2], "loop") == 0)
			{
//			do_ping_call(argv[1], 1, 0);	//loop, no count
			//todo: send relative data to Ameba
			}
		else
			{
//			do_ping_call(argv[1], 0, atoi(argv[2]));	//Not loop, with count
			//todo: send relative data to Ameba
			}
	}
	else {
		printf("Usage: ping IP [COUNT/loop]\n\r");
	}
}

static void cmd_exit(int argc, char **argv)
{
	printf("Do %s\n\r", __FUNCTION__);
	printf("Leave INTERACTIVE MODE\n\r");
	global_exit = 0;
}

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

	printf("COMMAND LIST:\n\r");
	printf("==============================\n\r");

	for(i = 0; i < sizeof(cmd_table) / sizeof(cmd_table[0]); i ++)
		printf("    %s\n\r", cmd_table[i].command);
}

#define MAX_ARGC 5
static int parse_cmd(char *buf, char **argv)
{
	int argc = 0;

	while((argc < MAX_ARGC) && (*buf != '\0')) {
		argv[argc] = buf;
		argc ++;
		buf ++;

		while((*buf != ' ') && (*buf != '\0'))
			buf ++;

		while(*buf == ' ') {
			*buf = '\0';
			buf ++;
		}
		// Don't replace space
		if(argc == 1){
			if(strcmp(argv[0], "iwpriv") == 0){
				if(*buf != '\0'){
					argv[1] = buf;
					argc ++;
				}
				break;
			}
		}
	}

	return argc;
}


int main(void)
{
	char cmd[64] = {0};
	char *argv[MAX_ARGC];
	int i, argc;
	printf("\n\rEnter the interative mode, please make your command as follow.\n\n\r");
	for(i = 0; i < sizeof(cmd_table) / sizeof(cmd_table[0]); i ++)
		printf("\n\r    %s", cmd_table[i].command);
	printf("\n\n\r");

	do{
		printf("Wlan: ");
		gets(cmd);
		printf("The command entered is : %s\n\r", cmd);
		if((argc = parse_cmd(cmd, argv)) > 0) {
			int found = 0;

			for(i = 0; i < sizeof(cmd_table) / sizeof(cmd_table[0]); i ++) {
				if(strcmp((const char *)argv[0], (const char *)(cmd_table[i].command)) == 0) {
					cmd_table[i].function(argc, argv);
					found = 1;
					break;
				}
			}

			if(!found)
				printf("unknown command '%s'\n\r", argv[0]);
		}
	}while(global_exit);
	return 0;
}

