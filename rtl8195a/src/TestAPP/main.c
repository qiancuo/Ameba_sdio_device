#include <stdio.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <string.h>
#include <sys/ioctl.h>

typedef struct _cmd_entry {
	char *command;
	void (*function)(int, char **);
} cmd_entry;

typedef struct _CMD_DESC{
//DWORD 0
unsigned int pktsize: 16; //=tx_desc.pktsize - cmd_desc.offset
unsigned int offset: 8; //cmd header size
unsigned int datatype: 8; // only first bit used, 0: data frame 1: management frame
//DWORD 1
unsigned char cmdtype[2]; //to call which API
unsigned int resv: 16;
}CMD_DESC, *PCMD_DESC;

typedef enum _WIFI_SECURITY_TYPE{
	WIFI_SECURITY_OPEN = 0,
	WIFI_SECURITY_WEP,
	WIFI_SECURITY_WPA,
	WIFI_SECURITY_WPA2,
	WIFI_SECURITY_MAX_NUM
}WIFI_SECURITY_TYPE;

typedef struct _WIFI_NETWORK{
	unsigned char 		*ssid;
	WIFI_SECURITY_TYPE	security_type;
	unsigned char 		*password;
	int 				ssid_len;
	int 				password_len;
	int					key_id;
}WIFI_NETWORK;

typedef struct _SDIO_CMDDATA{
	CMD_DESC cmd;
	char cmd_data[2040];
}SDIO_CMDDATA, *PSDIO_CMDDATA;

#define SDIO_CMD_wifi_connect 		"C0"
#define SDIO_CMD_wifi_disconnect 		"CD"
#define SDIO_CMD_wifi_on 			"P1"
#define SDIO_CMD_wifi_off 			"P0"
#define SDIO_CMD_wifi_ap 			"A0"
#define SDIO_CMD_wifi_scan 			"F0"
#define SDIO_CMD_wifi_get_rssi 		"CR"
#define SDIO_CMD_wifi_ping 			"T0"
#define SDIO_CMD_wifi_info 			"I?"
#define MNGMT_FRAME				1
#define DATA_FRAME					0

#define INIC_8195A "/dev/inic_8195a"
static int global_exit =1;
static int fd;
static char cmd_buf[2040] = {0};
static void cmd_help(int argc, char **argv);

static void cmd_wifi_connect(int argc, char **argv)
{
	CMD_DESC cmdDesc;
	SDIO_CMDDATA sdioData;
	WIFI_NETWORK wifi = {0};
	int timeout = 20, mode, i;
	unsigned char ssid[33];
	short cmdtype;
	printf("Do %s\n\r", __FUNCTION__);
	if((argc != 2) && (argc != 3) && (argc != 4)) {
		printf("Usage: wifi_connect SSID [WPA PASSWORD / (5 or 13) ASCII WEP KEY] [WEP KEY ID 0/1/2/3]\n\r");
		return;
	}
	
	printf("Joining BSS ...\n\r");	
//todo: send relative data to Ameba by using the module inic_8195a.ko
	strcpy(cmdDesc.cmdtype, SDIO_CMD_wifi_connect);	
	cmdDesc.datatype = MNGMT_FRAME;
	cmdDesc.offset = sizeof(CMD_DESC);
	cmdDesc.pktsize = strlen(cmd_buf)-strlen(argv[0])-1;

	sdioData.cmd = cmdDesc;
	printf("sdioData.cmd.cmdtype is: %s\n\r", sdioData.cmd.cmdtype);
	printf("sdioData.cmd.datatype is: %d\n\r", sdioData.cmd.datatype);
	printf("sdioData.cmd.offset is: %d\n\r", sdioData.cmd.offset);
	printf("sdioData.cmd.pktsize is: %d\n\r", sdioData.cmd.pktsize);
//	
//		printf("The command entered is : %s\n\r", cmd_buf);		
//		strcpy(sdioData.cmd_data, cmd_buf);
//		printf("sdioData->cmd_data: %s\n\r", sdioData.cmd_data);	
	strcpy(sdioData.cmd_data, (char *)(cmd_buf+strlen(argv[0])+1));
	printf("sdioData->cmd_data: %s\n\r", sdioData.cmd_data);
//todo: send sdioData to Ameba driver
	write(fd, &sdioData,sizeof(SDIO_CMDDATA));
}
static void cmd_wifi_disconnect(int argc, char **argv)
{
	CMD_DESC cmdDesc;
	SDIO_CMDDATA sdioData;
	printf("Do %s\n\r", __FUNCTION__);
	printf("Deassociating AP ...\n\r");
//todo: send relative data to Ameba
	strcpy(cmdDesc.cmdtype, SDIO_CMD_wifi_disconnect);	
	cmdDesc.datatype = MNGMT_FRAME;
	cmdDesc.offset = sizeof(CMD_DESC);
	cmdDesc.pktsize = strlen(cmd_buf)-strlen(argv[0]);

	sdioData.cmd = cmdDesc;
	memcpy(sdioData.cmd_data, (char *)(cmd_buf+strlen(argv[0])+1), cmdDesc.pktsize);
	write(fd, &sdioData,sizeof(SDIO_CMDDATA));
}

static void cmd_wifi_info(int argc, char **argv)
{
	CMD_DESC cmdDesc;
	SDIO_CMDDATA sdioData;
	printf("Do %s\n\r", __FUNCTION__);
//todo: send relative data to Ameba
	strcpy(cmdDesc.cmdtype, SDIO_CMD_wifi_info);	
	cmdDesc.datatype = MNGMT_FRAME;
	cmdDesc.offset = sizeof(CMD_DESC);
	cmdDesc.pktsize = strlen(cmd_buf)-strlen(argv[0]);
	sdioData.cmd = cmdDesc;
	memcpy(sdioData.cmd_data, (char *)(cmd_buf+strlen(argv[0])+1), cmdDesc.pktsize);
	write(fd, &sdioData,sizeof(SDIO_CMDDATA));
}

static void cmd_wifi_on(int argc, char **argv)
{
	CMD_DESC cmdDesc;
	SDIO_CMDDATA sdioData;
	printf("Do %s\n\r", __FUNCTION__);
//todo: send relative data to Ameba
	strcpy(cmdDesc.cmdtype, SDIO_CMD_wifi_on);	
	cmdDesc.datatype = MNGMT_FRAME;
	cmdDesc.offset = sizeof(CMD_DESC);
	cmdDesc.pktsize = strlen(cmd_buf)-strlen(argv[0]);
	sdioData.cmd = cmdDesc;
	memcpy(sdioData.cmd_data, (char *)(cmd_buf+strlen(argv[0])+1), cmdDesc.pktsize);
	write(fd, &sdioData,sizeof(SDIO_CMDDATA));
}

static void cmd_wifi_off(int argc, char **argv)
{
	CMD_DESC cmdDesc;
	SDIO_CMDDATA sdioData;
	printf("Do %s\n\r", __FUNCTION__);
//todo: send relative data to Ameba
	strcpy(cmdDesc.cmdtype, SDIO_CMD_wifi_off);	
	cmdDesc.datatype = MNGMT_FRAME;
	cmdDesc.offset = sizeof(CMD_DESC);
	cmdDesc.pktsize = strlen(cmd_buf)-strlen(argv[0]);
	sdioData.cmd = cmdDesc;
	memcpy(sdioData.cmd_data, (char *)(cmd_buf+strlen(argv[0])+1), cmdDesc.pktsize);
	write(fd, &sdioData,sizeof(SDIO_CMDDATA));
}

static void cmd_wifi_ap(int argc, char **argv)
{
	CMD_DESC cmdDesc;
	SDIO_CMDDATA sdioData;
	printf("Do %s\n\r", __FUNCTION__);
//	WIFI_AP ap = {0};
	int timeout = 20, mode;
	unsigned char ssid[33];

	if((argc != 3) && (argc != 4)) {
		printf("Usage: wifi_ap SSID CHANNEL [PASSWORD]\n\r");
		return;
	}
	strcpy(cmdDesc.cmdtype, SDIO_CMD_wifi_ap);	
	cmdDesc.datatype = MNGMT_FRAME;
	cmdDesc.offset = sizeof(CMD_DESC);
	cmdDesc.pktsize = strlen(cmd_buf)-strlen(argv[0])-1;
	sdioData.cmd = cmdDesc;
	memcpy(sdioData.cmd_data, (char *)(cmd_buf+strlen(argv[0])+1), cmdDesc.pktsize);
	write(fd, &sdioData,sizeof(SDIO_CMDDATA));
}
static void cmd_wifi_scan(int argc, char **argv)
{
	CMD_DESC cmdDesc;
	SDIO_CMDDATA sdioData;
	printf("Do %s\n\r", __FUNCTION__);
	int scan_cnt = 0, add_cnt = 0;
	if(argc == 2 && argv[1]){
	//todo: send relative data to Ameba
		strcpy(cmdDesc.cmdtype, SDIO_CMD_wifi_scan);	
		cmdDesc.datatype = MNGMT_FRAME;
		cmdDesc.offset = sizeof(CMD_DESC);
		cmdDesc.pktsize = strlen(cmd_buf)-strlen(argv[0])-1;
		sdioData.cmd = cmdDesc;
		memcpy(sdioData.cmd_data, (char *)(cmd_buf+strlen(argv[0])+1), cmdDesc.pktsize);
		write(fd, &sdioData,sizeof(SDIO_CMDDATA));
	}
	else{
		printf("Usage: wifi_scan BUFFER_LENGTH\n\r");
	}
}

static void cmd_wifi_get_rssi(int argc, char **argv)
{
	CMD_DESC cmdDesc;
	SDIO_CMDDATA sdioData;
	printf("Do %s\n\r", __FUNCTION__);
	int rssi = 0;
//	wifi_get_rssi(&rssi);
//todo: send relative data to Ameba
	strcpy(cmdDesc.cmdtype, SDIO_CMD_wifi_get_rssi);	
	cmdDesc.datatype = MNGMT_FRAME;
	cmdDesc.offset = sizeof(CMD_DESC);
	cmdDesc.pktsize = strlen(cmd_buf)-strlen(argv[0]);

	sdioData.cmd = cmdDesc;
	memcpy(sdioData.cmd_data, (char *)(cmd_buf+strlen(argv[0])+1), cmdDesc.pktsize);
	write(fd, &sdioData,sizeof(SDIO_CMDDATA));
	printf("wifi_get_rssi: rssi = %d\n\r", rssi);
}

static void cmd_ping(int argc, char **argv)
{
	CMD_DESC cmdDesc;
	SDIO_CMDDATA sdioData;
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
	char *argv[MAX_ARGC];
	int i, argc;
	char buf[2040];
	fd = open(INIC_8195A, O_RDWR);  
	if(fd < 0)  
	{  
	        printf("open file %s failed!\n", INIC_8195A);  
	        return -1;  
	}
	printf("\n\rEnter the interative mode, please make your command as follow.\n\n\r");
	for(i = 0; i < sizeof(cmd_table) / sizeof(cmd_table[0]); i ++)
		printf("\n\r    %s", cmd_table[i].command);
	printf("\n\n\r");

	do{
		printf("Wlan: ");
		gets(buf);
		printf("The command entered is : %s\n\r", buf);
		printf("buf size is : %d\n\r", sizeof(buf));
		strcpy(cmd_buf, buf);		
		if((argc = parse_cmd(buf, argv)) > 0) {
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
	close(fd);	
	return 0;
}

