/*
 * bsp_w5500.c
 *
 *  Created on: 2017年12月9日
 *      Author: Yexiaopeng
 */

#include "bsp_w5500.h"
#include "wizchip_conf.h"
#include "dhcp.h"
#include "socket.h"
//
#include "stdio.h"

//
#include "nt_stm32f1hw_systick.h"

#define bsp_w5500_delayms nthw_systick_delay_ms
//#define SOCKET_DHCP   0

#define DATA_BUF_SIZE   1024

#define bsp_w5500_log(x)     printf("============%s============\r\n",x);
#define bsp_w5500_log_message  printf

#define DEBUG 1





static uint8_t tmp;
static uint8_t memsize[2][8] = { {1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1}};
static uint8_t tmp;
static 	uint8_t my_dhcp_retry = 0;


uint8_t gDATABUF[DATA_BUF_SIZE];

static wiz_NetInfo gWIZNETINFO = { .mac = {0x00, 0x08, 0xdc,0x00, 0x01, 0x25},
        .ip = {192, 168, 1, 123},
        .sn = {255,255,255,0},
        .gw = {192, 168, 1, 1},
        .dns = {0,0,0,0},
        .dhcp = NETINFO_STATIC };


static void bsp_w5500_network_init(void);

static void bsp_w5500_spi_cs_select(void)
{
	PAOUT(4,0);
}

static void bsp_w5500_spi_cs_deselect(void)
{
	PAOUT(4,1);
}

static void bsp_w5500_ip_conflict(void)
{
	bsp_w5500_log("CONFLICT IP from DHCP\r\n");
	//halt or reset or any...
	while(1); // this example is halt.
}

static void bsp_w5500_ip_assign(void)
{

	getIPfromDHCP(gWIZNETINFO.ip);
	getGWfromDHCP(gWIZNETINFO.gw);
	getSNfromDHCP(gWIZNETINFO.sn);
	getDNSfromDHCP(gWIZNETINFO.dns);
	gWIZNETINFO.dhcp = NETINFO_DHCP;
	/* Network initialization */
	bsp_w5500_network_init();      // apply from dhcp
	bsp_w5500_log_message("DHCP LEASED TIME : %d Sec.\r\n",(int) getDHCPLeasetime());
}

static void bsp_w5500_network_init(void)
{
	uint8_t tmpstr[6] = {0};
	wiz_NetInfo netinfo;

	bsp_w5500_log("3/3DHCP Over");
	// Set Network information from netinfo structure
	ctlnetwork(CN_SET_NETINFO, (void*)&gWIZNETINFO);

	// Get Network information
	ctlnetwork(CN_GET_NETINFO, (void*)&netinfo);

	// Display Network Information
	ctlwizchip(CW_GET_ID,(void*)tmpstr);

	if(netinfo.dhcp == NETINFO_DHCP) bsp_w5500_log_message("\r\n=== %s NET CONF : DHCP ===\r\n",(char*)tmpstr);
	else bsp_w5500_log_message("\r\n=== %s NET CONF : Static ===\r\n",(char*)tmpstr);

	bsp_w5500_log_message("MAC: %02X:%02X:%02X:%02X:%02X:%02X\r\n",netinfo.mac[0],netinfo.mac[1],netinfo.mac[2],
			netinfo.mac[3],netinfo.mac[4],netinfo.mac[5]);
	bsp_w5500_log_message("SIP: %d.%d.%d.%d\r\n", netinfo.ip[0],netinfo.ip[1],netinfo.ip[2],netinfo.ip[3]);
	bsp_w5500_log_message("GAR: %d.%d.%d.%d\r\n", netinfo.gw[0],netinfo.gw[1],netinfo.gw[2],netinfo.gw[3]);
	bsp_w5500_log_message("SUB: %d.%d.%d.%d\r\n", netinfo.sn[0],netinfo.sn[1],netinfo.sn[2],netinfo.sn[3]);
	bsp_w5500_log_message("DNS: %d.%d.%d.%d\r\n", netinfo.dns[0],netinfo.dns[1],netinfo.dns[2],netinfo.dns[3]);
	bsp_w5500_log_message("===========================\r\n");
}

extern void bsp_w5500_init(void)
{
	bsp_w5500_log("bsp_w5500_init");

	nthw_sp1_config();
	PAMODE(4,GPIO_Mode_Out_PP);
	PAOUT(4,1);

	bsp_w5500_log("1/4初始化注册函数");
	reg_wizchip_cris_cbfunc(SPI_CrisEnter, SPI_CrisExit);	//注册临界区函数
	reg_wizchip_cs_cbfunc(bsp_w5500_spi_cs_select, bsp_w5500_spi_cs_deselect);//注册SPI片选信号函数
	reg_wizchip_spi_cbfunc(nthw_sp1_ReadByte, nthw_sp1__WriteByte);	//注册读写函数


	bsp_w5500_log("2/4WIZCHIP SOCKET缓存区初始化");
	if(ctlwizchip(CW_INIT_WIZCHIP,(void*)memsize) == -1)
	{
		bsp_w5500_log("WIZCHIP Initialized fail");
		while(1);
	}
	bsp_w5500_log("3/4PHY物理层连接状态检查");
	/* PHY link status check */
	do{
		 if(ctlwizchip(CW_GET_PHYLINK, (void*)&tmp) == -1)
		 {
			 bsp_w5500_log("Unknown PHY Link stauts");
		 }
	}while(tmp == PHY_LINK_OFF);

	bsp_w5500_log("4/4设置MAC");
	// must be set the default mac before DHCP started.
	setSHAR(gWIZNETINFO.mac);

}

//返回 1 -- 成功
// 2 -- 最大次数内失败
extern uint8_t bsp_w5500_dhcp(uint8_t sock,uint8_t max_dhcp_retry)
{
	uint8_t isOverDhcp = 0;
	bsp_w5500_log("bsp_w5500_dhcp");


	bsp_w5500_log("1/3DHCP_init");
	DHCP_init(sock, gDATABUF);
	reg_dhcp_cbfunc(bsp_w5500_ip_assign, bsp_w5500_ip_assign, bsp_w5500_ip_conflict);//注册DHCP回调函数

	//DHCP_run
	//先 DHCP_RUNNING循环直到成功或失败
	//成功后执行dhcp_cbfunc
	//再DHCP_RUNNING
	//然后DHCP_IP_LEASED
	//若不退出while 一直DHCP_IP_LEASED
	while(0 == isOverDhcp)
		{
			tmp = DHCP_run();
			switch(tmp)
			{
				case DHCP_IP_ASSIGN:
				case DHCP_IP_CHANGED:
					/* If this block empty, act with default_ip_assign & default_ip_update */
					//
					// This example calls my_ip_assign in the two case.
					//
					// Add to ...
					//
					break;
				case DHCP_IP_LEASED:
					//
					// TO DO YOUR NETWORK APPs.
					// TODO 完成DHCP后，在此作循环
					//先跳转到成功的回调函数
					//然后DHCP_RUNNING
					//再执行此处
					isOverDhcp = 1;//成功退出
					bsp_w5500_log("DHCP_IP_LEASED\r\n");
					break;
				case DHCP_FAILED:
					/* ===== Example pseudo code =====  */
					// The below code can be replaced your code or omitted.
					// if omitted, retry to process DHCP
					my_dhcp_retry++;
					if(my_dhcp_retry > max_dhcp_retry)
					{
						bsp_w5500_log("DHCP %d Failed");
						my_dhcp_retry = 0;
						DHCP_stop();      // if restart, recall DHCP_init()
						isOverDhcp = 2;//失败退出
						//bsp_w5500_network_init();   // apply the default static network and print out netinfo to serial
					}
					break;
				case DHCP_RUNNING:
					bsp_w5500_log("2/3DHCP Running");
					break;
				default:
					bsp_w5500_log("Unknown return");
					break;
			}
			bsp_w5500_delayms(100);
		}

	return isOverDhcp;
}
