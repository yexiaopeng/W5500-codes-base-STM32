    /**
    ********************************************************************************
    * @file    nt_stm32f1hw_GPIO.h
    * @author  yexiaopeng
    * @version V1.0.0
    * @date    2017-11-27 
    * @brief   GPIO中间件头文件
    ********************************************************************************
    * email: yexiaopeng1992@126.com
    * 说明：
    *    PXMODE(uint8_t pin,GPIOMode_TypeDef mode);{X = A、B、C、D....}
    *        配置GPIO的模式：
    *             GPIO_Mode_AIN = 0x0,
    *              GPIO_Mode_IN_FLOATING = 0x04,
    *              GPIO_Mode_IPD = 0x28,
    *              GPIO_Mode_IPU = 0x48,
    *              GPIO_Mode_Out_OD = 0x14,
    *              GPIO_Mode_Out_PP = 0x10,
    *              GPIO_Mode_AF_OD = 0x1C,
    *              GPIO_Mode_AF_PP = 0x18
    *          
    *   void PXOUT(uint8_t pin,uint8_t portlevel);{X = A、B、C、D....}
    *        在GPIO输出模式下，控制输出的高低电平
    *        pin:引脚编号
    *            [0~15] 不可使用|来配置多个引脚，一个函数一次只能控制一个引脚
    *        portlevel：电平
    *            [0,1]
    *   uint8_t PXINT(uint8_t pin);{X = A、B、C、D....}
    *        在GPIO输入模式下，读取GPIO的高低电平
    *        pin:引脚编号
    *            [0~15] 不可使用|来配置多个引脚，一个函数一次只能控制一个引脚
    *        return：电平
    *            [0,1]   
    *                                
    *
    ********************************************************************************
    */

    #ifndef __NT_STM32F1HW_GPIO_H
    #define __NT_STM32F1HW_GPIO_H
    
    #include "stdint.h"
    #include "stm32f10x_gpio.h"
    #ifdef __cplusplus
        extern "C" {
    #endif 
        extern void PAMODE(uint8_t pin,GPIOMode_TypeDef mode);
        extern void PBMODE(uint8_t pin,GPIOMode_TypeDef mode);
        extern void PCMODE(uint8_t pin,GPIOMode_TypeDef mode);
        extern void PDMODE(uint8_t pin,GPIOMode_TypeDef mode);
        extern void PEMODE(uint8_t pin,GPIOMode_TypeDef mode);
        extern void PFMODE(uint8_t pin,GPIOMode_TypeDef mode);
        extern void PGMODE(uint8_t pin,GPIOMode_TypeDef mode);
            
        extern void PAOUT(uint8_t pin,uint8_t portlevel);
        extern void PBOUT(uint8_t pin,uint8_t portlevel);
        extern void PCOUT(uint8_t pin,uint8_t portlevel);
        extern void PDOUT(uint8_t pin,uint8_t portlevel);
        extern void PEOUT(uint8_t pin,uint8_t portlevel);
        extern void PFOUT(uint8_t pin,uint8_t portlevel);
        extern void PGOUT(uint8_t pin,uint8_t portlevel);
        
        extern uint8_t PAINT(uint8_t pin);
        extern uint8_t PBINT(uint8_t pin);
        extern uint8_t PCINT(uint8_t pin);
        extern uint8_t PDINT(uint8_t pin);
        extern uint8_t PEINT(uint8_t pin);
        extern uint8_t PFINT(uint8_t pin);
        extern uint8_t PGINT(uint8_t pin);
            
    #ifdef __cplusplus
        }
    #endif

    #endif //__NT_STM32F1HW_SYSTICK_H
