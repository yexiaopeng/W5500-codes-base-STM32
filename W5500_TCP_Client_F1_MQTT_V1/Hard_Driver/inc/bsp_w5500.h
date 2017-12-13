/*
 * bsp_w5500.h
 *
 *  Created on: 2017��12��9��
 *      Author: Yexiaopeng
 */

#ifndef BSP_W5500_H_HARD_DRIVER_INC
#define BSP_W5500_H_HARD_DRIVER_INC

#include "nt_stm32f1hw_spi.h"
#include "nt_stm32f1hw_gpio.h"


extern uint8_t gDATABUF[1024];

// SPI1 + CS(PA4)

//W5500��ʼ������
extern void bsp_w5500_init(void);
//W5500ͨ��dhcp��ȡip
extern uint8_t bsp_w5500_dhcp(uint8_t sock,uint8_t max_dhcp_retry);

#endif /* BSP_W5500_H_HARD_DRIVER_INC */
