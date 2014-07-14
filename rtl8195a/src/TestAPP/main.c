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
typedef enum _WIFI_MODE_TYPE{
	WIFI_MODE_STA = 0,
	WIFI_MODE_AP
}WIFI_MODE_TYPE;
typedef struct _WIFI_SETTING{
	unsigned char		mode;
	unsigned char 		ssid[33];
	unsigned char		channel;
	unsigned char	security_type;
	unsigned char 		password[33];
}WIFI_SETTING;
struct net_device_stats {
	unsigned long   rx_packets;             /* total packets received       */
	unsigned long   tx_packets;             /* total packets transmitted    */
	unsigned long   rx_dropped;             /* no space in linux buffers    */
	unsigned long   tx_dropped;             /* no space available in linux  */
	unsigned long   rx_bytes;               /* total bytes received         */
	unsigned long   tx_bytes;               /* total bytes transmitted      */
};
typedef struct _AT_WIFI_INFO{
	struct net_device_stats stats;
	int running;
	int min_free_heap_size;
	int max_skbbuf_used_num;
	int skbbuf_used_num;
	int max_skbdata_used_num;
	int skbdata_used_num;
	int max_timer_used_num;
	WIFI_SETTING setting;
	unsigned char mac[6];
	unsigned char ip[4];
	unsigned char gw[4];
}AT_WIFI_INFO, PAT_WIFI_INFO;
typedef struct _SDIO_CMDDATA{
	CMD_DESC cmd;
	unsigned char cmd_data[2040];
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
static char cmd_buf[2040] = {0};
static void cmd_help(int argc, char **argv);


void DumpForOneBytes(unsigned char *pData, unsigned char Len)
{
	unsigned char *pSbuf = pData;	
	char Length=Len;

	char LineIndex=0,BytesIndex,Offset;
	printf("\r [Addr]   .0 .1 .2 .3 .4 .5 .6 .7 .8 .9 .A .B .C .D .E .F\r\n" );

	while( LineIndex< Length)
	{		
			printf("%08x: ", (unsigned int)(pSbuf+LineIndex));

			if(LineIndex+16 < Length)
				Offset=16;
			else			
				Offset=Length-LineIndex;
			

			for(BytesIndex=0; BytesIndex<Offset; BytesIndex++)
				printf("%02x ", pSbuf[LineIndex+BytesIndex]);	

			for(BytesIndex=0;BytesIndex<16-Offset;BytesIndex++)	//a last line
    			printf("   ");


			printf("    ");		//between byte and char
			
			for(BytesIndex=0;  BytesIndex<Offset; BytesIndex++) {
                
				if( ' ' <= pSbuf[LineIndex+BytesIndex]  && pSbuf[LineIndex+BytesIndex] <= '~')
					printf("%c", pSbuf[LineIndex+BytesIndex]);
				else
					printf(".");
			}
            
			printf("\n\r");
			LineIndex += 16;
	}
	
}
int wifi_show_setting(WIFI_SETTING *pSetting)
{
	int ret = 0;
	printf("\n\r\nWIFI Setting:");
	printf("\n\r==============================");

	switch(pSetting->mode) {
		case WIFI_MODE_AP:
			printf("\n\r      MODE => AP");
			break;
		case WIFI_MODE_STA:
			printf("\n\r      MODE => STATION");
			break;
		default:
			printf("\n\r      MODE => UNKNOWN");
	}

	printf("\n\r      SSID => %s", pSetting->ssid);
	printf("\n\r   CHANNEL => %d", pSetting->channel);

	switch(pSetting->security_type) {
		case WIFI_SECURITY_OPEN:
			printf("\n\r  SECURITY => OPEN");
			break;
		case WIFI_SECURITY_WEP:
			printf("\n\r  SECURITY => WEP");
			break;
		case WIFI_SECURITY_WPA:
			printf("\n\r  SECURITY => WPA");
			break;
		case WIFI_SECURITY_WPA2:
			printf("\n\r  SECURITY => WPA2");
			break;
		default:
			printf("\n\r  SECURITY => UNKNOWN");
	}

	printf("\n\r  PASSWORD => %s", pSetting->password);
	printf("\n\r");

	return ret;
}
static CMD_DESC CmdDescGen()
{
	CMD_DESC cmdDesc;

}

static void cmd_wifi_connect(int argc, char **argv)
{
	static int fd;
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
	strcpy(sdioData.cmd_data, (unsigned char *)(cmd_buf+strlen(argv[0])+1));
	printf("sdioData->cmd_data: %s\n\r", sdioData.cmd_data);
//todo: send sdioData to Ameba driver
	fd = open(INIC_8195A, O_RDWR);  
	if(fd < 0)  
	{  
	        printf("open file %s failed!\n", INIC_8195A);  
	        return;  
	}
	write(fd, &sdioData,sizeof(SDIO_CMDDATA));
	close(fd);
}
static void cmd_wifi_disconnect(int argc, char **argv)
{
	static int fd;
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
	fd = open(INIC_8195A, O_RDWR);  
	if(fd < 0)  
	{  
	        printf("open file %s failed!\n", INIC_8195A);  
	        return;  
	}
	write(fd, &sdioData,sizeof(SDIO_CMDDATA));
	close(fd);
}

static void cmd_wifi_info(int argc, char **argv)
{
	static int fd;
	CMD_DESC cmdDesc;
	PCMD_DESC pDesc;
	AT_WIFI_INFO *pWifiInfo;
//	WIFI_SETTING *pWifiSet;
	SDIO_CMDDATA sdioData;
	int read_bytes, i;
	unsigned char buf[2048];
	printf("Do %s\n\r", __FUNCTION__);
//todo: send relative data to Ameba
	strcpy(cmdDesc.cmdtype, SDIO_CMD_wifi_info);	
	cmdDesc.datatype = MNGMT_FRAME;
	cmdDesc.offset = sizeof(CMD_DESC);
	cmdDesc.pktsize = strlen(cmd_buf)-strlen(argv[0]);
	sdioData.cmd = cmdDesc;
	memcpy(sdioData.cmd_data, (char *)(cmd_buf+strlen(argv[0])+1), cmdDesc.pktsize);
	fd = open(INIC_8195A, O_RDWR);  
	if(fd < 0)  
	{  
	        printf("open file %s failed!\n", INIC_8195A);  
	        return;  
	}
	write(fd, &sdioData,sizeof(SDIO_CMDDATA));
	for(i=0;i<1000000000;i++);
	read_bytes = read(fd, buf, sizeof(buf));
	if(read_bytes < 0)
	{
		printf("read wifi_info failed!\n");
		return;
	}
	close(fd);
	printf("size of CMD_DESC = %d\n\r", sizeof(CMD_DESC));
	pDesc = (PCMD_DESC)buf;
	printf("pDesc->cmdtype: %s\n\r", pDesc->cmdtype);
	printf("pDesc->datatype: %d\n\r", pDesc->datatype);
	printf("pDesc->offset: %d\n\r", pDesc->offset);
	printf("pDesc->pktsize: %d\n\r", pDesc->pktsize);
	
	pWifiInfo = (AT_WIFI_INFO *)(buf+sizeof(CMD_DESC));
	wifi_show_setting(&(pWifiInfo->setting));
	printf("WIFI Status (%s)\n\r", (pWifiInfo->running == 1) ? "Running" : "Stopped");
	printf("==============================\n\r");
	
	printf("\n\r[rltk_wlan_statistic]min_free_heap_size=%d, current heap free size=", pWifiInfo->min_free_heap_size);
	printf("\n\r[rltk_wlan_statistic]max_skbbuf_used_num=%d, skbbuf_used_num=%d", pWifiInfo->max_skbbuf_used_num, pWifiInfo->skbbuf_used_num);
	printf("\n\r[rltk_wlan_statistic]max_skbdata_used_num=%d, skbdata_used_num=%d", pWifiInfo->max_skbdata_used_num, pWifiInfo->skbdata_used_num);
	printf("\n\r[rltk_wlan_statistic]max_timer_used_num=%d", pWifiInfo->max_timer_used_num);
	
	printf("\n\r  MAC => %02x:%02x:%02x:%02x:%02x:%02x", pWifiInfo->mac[0], pWifiInfo->mac[1], pWifiInfo->mac[2], pWifiInfo->mac[3], pWifiInfo->mac[4], pWifiInfo->mac[5]) ;
	printf("\n\r  IP  => %d.%d.%d.%d", pWifiInfo->ip[0], pWifiInfo->ip[1], pWifiInfo->ip[2], pWifiInfo->ip[3]);
	printf("\n\r  GW  => %d.%d.%d.%d\n\r", pWifiInfo->gw[0], pWifiInfo->gw[1], pWifiInfo->gw[2], pWifiInfo->gw[3]);
}

static void cmd_wifi_on(int argc, char **argv)
{
	static int fd;
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
	fd = open(INIC_8195A, O_RDWR);  
	if(fd < 0)  
	{  
	        printf("open file %s failed!\n", INIC_8195A);  
	        return;  
	}
	write(fd, &sdioData,sizeof(SDIO_CMDDATA));
	close(fd);
}

static void cmd_wifi_off(int argc, char **argv)
{
	static int fd;
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
	fd = open(INIC_8195A, O_RDWR);  
	if(fd < 0)  
	{  
	        printf("open file %s failed!\n", INIC_8195A);  
	        return;  
	}
	write(fd, &sdioData,sizeof(SDIO_CMDDATA));
	close(fd);
}

static void cmd_wifi_ap(int argc, char **argv)
{
	static int fd;
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
	fd = open(INIC_8195A, O_RDWR);  
	if(fd < 0)  
	{  
	        printf("open file %s failed!\n", INIC_8195A);  
	        return;  
	}
	write(fd, &sdioData,sizeof(SDIO_CMDDATA));
	close(fd);
}
static void cmd_wifi_scan(int argc, char **argv)
{
	static int fd;
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
		fd = open(INIC_8195A, O_RDWR);  
		if(fd < 0)  
		{  
		        printf("open file %s failed!\n", INIC_8195A);  
		        return;  
		}
		write(fd, &sdioData,sizeof(SDIO_CMDDATA));
		close(fd);
	}
	else{
		printf("Usage: wifi_scan BUFFER_LENGTH\n\r");
	}
}

static void cmd_wifi_get_rssi(int argc, char **argv)
{
	static int fd;
	CMD_DESC cmdDesc;
	PCMD_DESC pDesc;
	SDIO_CMDDATA sdioData;
	printf("Do %s\n\r", __FUNCTION__);
	int read_bytes, i;
	unsigned char buf[2048];
	int *rssi ;
//	wifi_get_rssi(&rssi);
//todo: send relative data to Ameba
	strcpy(cmdDesc.cmdtype, SDIO_CMD_wifi_get_rssi);	
	cmdDesc.datatype = MNGMT_FRAME;
	cmdDesc.offset = sizeof(CMD_DESC);
	cmdDesc.pktsize = strlen(cmd_buf)-strlen(argv[0]);

	sdioData.cmd = cmdDesc;
	memcpy(sdioData.cmd_data, (char *)(cmd_buf+strlen(argv[0])+1), cmdDesc.pktsize);
	fd = open(INIC_8195A, O_RDWR);  
	if(fd < 0)  
	{  
	        printf("open file %s failed!\n", INIC_8195A);  
	        return;  
	}
	write(fd, &sdioData,sizeof(SDIO_CMDDATA));
	for(i=0;i<100000;i++);
	read_bytes = read(fd, buf, sizeof(buf));
	if(read_bytes < 0)
	{
		printf("read wifi_info failed!\n");
		return;
	}
	close(fd);
	printf("size of CMD_DESC = %d\n\r", sizeof(CMD_DESC));
	pDesc = (PCMD_DESC)buf;
	printf("pDesc->cmdtype: %s\n\r", pDesc->cmdtype);
	printf("pDesc->datatype: %d\n\r", pDesc->datatype);
	printf("pDesc->offset: %d\n\r", pDesc->offset);
	printf("pDesc->pktsize: %d\n\r", pDesc->pktsize);
	rssi = (int *)(buf+sizeof(CMD_DESC));
	printf("wifi_get_rssi: rssi = %d\n\r", *rssi);
}

static void cmd_ping(int argc, char **argv)
{
	static int fd;
	CMD_DESC cmdDesc;
	SDIO_CMDDATA sdioData;
	printf("Do %s\n\r", __FUNCTION__);
	if((argc!=2)&&(argc!=3))
	{
		printf("Usage: ping IP [COUNT/loop]\n\r");
	}
	strcpy(cmdDesc.cmdtype, SDIO_CMD_wifi_ping);	
	cmdDesc.datatype = MNGMT_FRAME;
	cmdDesc.offset = sizeof(CMD_DESC);
	cmdDesc.pktsize = strlen(cmd_buf)-strlen(argv[0])-1;

	sdioData.cmd = cmdDesc;
//	memcpy(sdioData.cmd_data, (char *)(cmd_buf+strlen(argv[0])+1), cmdDesc.pktsize);
	strcpy(sdioData.cmd_data, (char *)(cmd_buf+strlen(argv[0])+1));
	fd = open(INIC_8195A, O_RDWR);  
	if(fd < 0)  
	{  
	        printf("open file %s failed!\n", INIC_8195A);  
	        return;  
	}
//		printf("sdioData.cmd.cmdtype is: %s\n\r", sdioData.cmd.cmdtype);
//		printf("sdioData.cmd.datatype is: %d\n\r", sdioData.cmd.datatype);
//		printf("sdioData.cmd.offset is: %d\n\r", sdioData.cmd.offset);
//		printf("sdioData.cmd.pktsize is: %d\n\r", sdioData.cmd.pktsize);
//		
//		printf("sdioData->cmd_data: %s\n\r", sdioData.cmd_data);
	printf("CMD Desc: \n");
	DumpForOneBytes ((unsigned char *)&sdioData.cmd, sizeof(CMD_DESC));
	printf("WLAN Payload: \n");
	DumpForOneBytes ((unsigned char *)(&sdioData.cmd_data), sdioData.cmd.pktsize);
	write(fd, &sdioData,sizeof(SDIO_CMDDATA));
	close(fd);
}

static void cmd_exit(int argc, char **argv)
{
	printf("Do %s\n\r", __FUNCTION__);
	printf("Leave INTERACTIVE MODE\n\r");
	global_exit = 0;
}
#define wlanpktsize 282
static void cmd_wifi_send_data(int argc, char **argv)
{
	static int fd;
	CMD_DESC cmdDesc;
	SDIO_CMDDATA sdioData;
	int i, payload_len;
	unsigned char wlan_header[26];
	payload_len = wlanpktsize-sizeof(wlan_header);
	unsigned char payload[payload_len];	
	printf("Do %s\n\r", __FUNCTION__);
	wlan_header[0]=0x88;
	wlan_header[1]=0x01;
	wlan_header[2]=0x00;
	wlan_header[3]=0x00;
//destination address
	wlan_header[4]=0xff;
	wlan_header[5]=0xff;
	wlan_header[6]=0xff;
	wlan_header[7]=0xff;
	wlan_header[8]=0xff;
	wlan_header[9]=0xff;
//source address
	wlan_header[10]=0x00;
	wlan_header[11]=0x00;
	wlan_header[12]=0x00;
	wlan_header[13]=0x00;
	wlan_header[14]=0x00;
	wlan_header[15]=0x02;
//BSSID	
	wlan_header[16]=0x00;
	wlan_header[17]=0x00;
	wlan_header[18]=0x00;
	wlan_header[19]=0x00;
	wlan_header[20]=0x00;
	wlan_header[21]=0x01;
//SEQ control	
	wlan_header[22]=0x00;
	wlan_header[23]=0x00;
//QoS control
	wlan_header[24]=0x06;
	wlan_header[25]=0x00;
	for(i=0; i<payload_len; i++)
		payload[i] = 0x3e;

	cmdDesc.datatype = DATA_FRAME;
	cmdDesc.offset = sizeof(CMD_DESC);
	cmdDesc.pktsize = wlanpktsize;

	sdioData.cmd = cmdDesc;

	memcpy(sdioData.cmd_data, wlan_header, sizeof(wlan_header));
	memcpy(sdioData.cmd_data+sizeof(wlan_header), payload, payload_len);
	for(i=0;i<wlanpktsize;i++)
		printf("wlanpkt[%d] = 0x%02x\n", i, sdioData.cmd_data[i]);
	fd = open(INIC_8195A, O_RDWR);  
	if(fd < 0)  
	{  
	        printf("open file %s failed!\n", INIC_8195A);  
	        return;  
	}
	write(fd, &sdioData,sizeof(SDIO_CMDDATA));
	close(fd);
}

static void cmd_wifi_recv_data(int argc, char **argv)
{
	static int fd;
	unsigned char buf[2048];
	PCMD_DESC pCmdDesc;
	int read_bytes, i;
	printf("Do %s\n\r", __FUNCTION__);
	fd = open(INIC_8195A, O_RDWR);  
	if(fd < 0)  
	{  
	        printf("open file %s failed!\n", INIC_8195A);  
	        return;  
	}
	read_bytes = read(fd, buf, sizeof(buf));
	close(fd);
	if(read_bytes < 0)
	{
		printf("read from 8195a failed!\n");
		return;
	}
//		for(i=0;i<50;i++)
//			printf("buf_read[%d] = 0x%02x\n", i, buf[i]);
	pCmdDesc = (PCMD_DESC)buf;
	printf("CMD Desc: \n");
	DumpForOneBytes ((unsigned char *)pCmdDesc, sizeof(CMD_DESC));
	printf("WLAN Payload: \n");
	DumpForOneBytes ((unsigned char *)(buf+sizeof(CMD_DESC)), pCmdDesc->pktsize);
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
	{"help", cmd_help},
	{"wifi_send_pkt", cmd_wifi_send_data},
	{"wifi_recv_pkt", cmd_wifi_recv_data}
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

	printf("\n\rEnter the interative mode, please make your command as follow.\n\n\r");
	for(i = 0; i < sizeof(cmd_table) / sizeof(cmd_table[0]); i ++)
		printf("\n\r    %s", cmd_table[i].command);
	printf("\n\n\r");

	do{
		printf("Wlan: ");
		gets(buf);
		printf("The command entered is : %s\n\r", buf);

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
	return 0;
}

