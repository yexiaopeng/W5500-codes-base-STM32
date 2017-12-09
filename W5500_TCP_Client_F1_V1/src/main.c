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

static const uint8_t dhcp_socket = 0;

static void setup(void)
{
	nthw_systick_init();
	LED_INIT();
	nthw_usart_init(USART1,115200,USART_Mode_Rx| USART_Mode_Tx);

}

static void loop(void)
{
	LED_ON();
	printf("===========================\r\n");
	bsp_w5500_init();
	if( 1 == bsp_w5500_dhcp(dhcp_socket,5))
	{
		printf("=============DHCP SUCCEED==============\r\n");
	}else
	{
		printf("=============DHCP FAILURE==============\r\n");
	}
}





int main(void)
{

	setup();
	loop();
	for(;;);
}
