include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#								VARIABLES	                              #
#*****************************************************************************#
#LWIPDIR = $(ROOTDIR)/../../../../sw/lib/sw_lib/network/lwip/lwip_v1.3.2
#RT_WLAN_DIR = $(ROOTDIR)/../../../../sw/lib/hw_lib/devs/wlan/realtek/v3_0
#API = $(ROOTDIR)/../../../../sw/lib/sw_lib/api
#NETWORK = $(ROOTDIR)/../../../../sw/lib/sw_lib/network
#TEST = $(ROOTDIR)/../../../../sw/lib/sw_lib/test
#
#MODULE_IFLAGS = -I../include -I$(LWIPDIR)/src/include -I$(LWIPDIR)/src/include/lwip \		
#				-I$(LWIPDIR)/src/include/netif -I$(LWIPDIR)/src/include/ipv4 \		
#				-I$(LWIPDIR)/port/realtek -I$(LWIPDIR)/port/realtek/freertos \		
#				-I$(RT_WLAN_DIR)/include \		
#				-I$(API) \		
#				-I$(NETWORK) \		
#				-I$(TEST)
				
#GLOBAL_CFLAGS += -DCONFIG_PLATFORM_8195A


#*****************************************************************************#
#								Source FILE LIST                              #
#*****************************************************************************#
CSRC        = main.c 
#		ping_test.c rtl8195a_it.c ttcp.c \		
#		$(addprefix $(API)/, wifi_interactive_mode.c lwip_netconf.c) \		
#		$(addprefix $(API)/wifi/, wifi_util.c wifi_conf.c wifi_promisc.c) \		
#		$(addprefix $(NETWORK)/dhcp/, dhcps.c) \		
#		$(addprefix $(LWIPDIR)/src/core/, dhcp.c dns.c init.c mem.c memp.c netif.c pbuf.c raw.c stats.c sys.c tcp.c tcp_in.c tcp_out.c udp.c ) \		
#		$(addprefix $(LWIPDIR)/src/core/ipv4/, autoip.c icmp.c igmp.c inet.c inet_chksum.c ip.c ip_addr.c ip_frag.c) \		
#		$(addprefix $(LWIPDIR)/src/api/, api_lib.c api_msg.c err.c netbuf.c netdb.c netifapi.c sockets.c tcpip.c) \		
#		$(addprefix $(LWIPDIR)/src/netif/, etharp.c) \		
#		$(addprefix $(LWIPDIR)/port/realtek/freertos/, ethernetif.c sys_arch.c)		

#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS        = $(CSRC:.c=.o)

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#
# Define the Rules to build the core targets
all: CORE_TARGETS COPY_RAM_OBJS	

#*****************************************************************************#
#              GENERATE OBJECT FILE 
#*****************************************************************************#

CORE_TARGETS:	$(OBJS)