    /**
    ********************************************************************************
    * @file    nt_stm32f1hw_usart.h
    * @author  yexiaopeng
    * @version V1.0.0
    * @date    2017-11-30 
    * @brief   USART中间件头文件
    ********************************************************************************
    * email: yexiaopeng1992@126.com
    * 说明：             
    *
    ********************************************************************************
    */
    #ifndef __NT_STM32F1HW_USART_H
    #define __NT_STM32F1HW_USART_H
    
    #include "stm32f10x.h"
    #include "stm32f10x_usart.h"
        
    extern uint8_t nthw_usart_init(USART_TypeDef* USARTx, uint32_t USART_BaudRate,uint16_t USART_Mode);
    
    extern void nthw_usart_PutChar(USART_TypeDef* USARTx,uint8_t data);
    
    extern void nthw_usart_PutStr(USART_TypeDef* USARTx,uint8_t * str);
    
    extern void nthw_usart_1_rxen_cbfunc(void (*func)(uint16_t data));
    
    extern void nthw_usart_1_itle_cbfunc(void (*func)(void));
    
    extern void nthw_usart_2_rxen_cbfunc(void (*func)(uint16_t data));
    
    extern void nthw_usart_2_itle_cbfunc(void (*func)(void));
    
    #endif
    
    
    
    