/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f10x.h"
			
//system include
#include "stdio.h"


// nt_hw lib
#include "nt_stm32f1hw_usart.h"
#include "nt_stm32f1hw_spi.h"
#include "nt_stm32f1hw_systick.h"

//hard_driver include
#include "bsp_led.h"
#include "bsp_w5500.h"

//W5500 INCLUDE
#include "wizchip_conf.h"
#include "dhcp.h"
#include "socket.h"

//dhcp socket�ı��
static const uint8_t dhcp_socket = 0;


static void setup(void)
{
    //systick��ʼ��
    nthw_systick_init();
    //LED��ʼ��
    LED_INIT();
    //��ʼ������USART1��Ϊ���Խӿ�
    //�޸�syscall.c�е�write����ʵ��printf
    nthw_usart_init(USART1,115200,USART_Mode_Rx| USART_Mode_Tx);

}

static void loop(void)
{
	int ret;
	//����LED
	LED_ON();
	printf("===========================\r\n");
	//w5500�ĳ�ʼ��
	//����IO�����ã�SPI��CS
	//w5500��PYH����
	bsp_w5500_init();
	//����dhcp����
	//ѡ��ͨ��dhcp_socket��0��������Դ���5
	if( 1 == bsp_w5500_dhcp(dhcp_socket,5))
	{
		printf("=============DHCP SUCCEED==============\r\n");
	}else
	{
		printf("=============DHCP FAILURE==============\r\n");
	}
	//����socket
	ret = socket(dhcp_socket,Sn_MR_TCP,21688,0x00);
	if(ret != dhcp_socket){
		printf("%d:Socket Error\r\n",dhcp_socket);
		while(1);
	}else{
		printf("%d:Opened\r\n",dhcp_socket);
	}
	printf("=============socket ok ==============\r\n");

	uint8_t DstIP[]={192,168,9,75};
	ret = connect(dhcp_socket,DstIP,31688);
	if(ret != SOCK_OK){
		printf("%d:Socket Connect Error\r\n",dhcp_socket);
		while(1);
	}
	printf("=============connect %s:%d ok ==============\r\n",DstIP,31688);


	while(1)
	{
		//����TCP���������͵�����
		memset(gDATABUF,'\0',1024);
		ret = recv(dhcp_socket,gDATABUF,1024);
		if(ret <= 0){
			continue;
		}
		//�����յ�����ԭ�����ظ�TCP������
		printf("=============recv %s ==============\r\n",gDATABUF);
		ret = send(dhcp_socket,gDATABUF,ret);
	}
}

int main(void)
{

	setup();
	loop();
	for(;;);
}
