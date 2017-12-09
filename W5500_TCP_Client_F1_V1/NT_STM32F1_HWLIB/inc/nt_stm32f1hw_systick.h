    /**
    ******************************************************************************
    * @file    nt_stm32f1hw_systick.h
    * @author  yexiaopeng
    * @version V1.0.0
    * @date    2017-11-27 
    * @brief   系统滴答(SysTick)中间件头文件
    ******************************************************************************
    * email: yexiaopeng1992@126.com
    *                 
    *                                
    *
    ******************************************************************************
    */
    
    #ifndef __NT_STM32F1HW_SYSTICK_H
    #define __NT_STM32F1HW_SYSTICK_H
    
    #include "stdint.h"
    
    #ifdef __cplusplus
        extern "C" {
    #endif 
        
        extern void nthw_systick_init(void);
        
        extern void nthw_systick_delay_us(uint32_t ntime);
            
        extern void nthw_systick_delay_ms(uint16_t ntime);
            
    #ifdef __cplusplus
        }
    #endif

    #endif //__NT_STM32F1HW_SYSTICK_H

