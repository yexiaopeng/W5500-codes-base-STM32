/*
 * bsp_led.h
 *
 *  Created on: 2017Äê12ÔÂ9ÈÕ
 *      Author: Yexiaopeng
 */

#ifndef BSP_LED_H_HARD_DRIVER_INC
#define BSP_LED_H_HARD_DRIVER_INC

//LED PC13
#include "nt_stm32f1hw_gpio.h"

#define LED_INIT()    do{ \
							PCMODE(13,GPIO_Mode_Out_PP); \
							PCOUT(13,1);\
						}while(0)


#define LED_ON()    PCOUT(13,0)
#define LED_OFF()   PCOUT(13,1)



#endif /* BSP_LED_H_HARD_DRIVER_INC */
