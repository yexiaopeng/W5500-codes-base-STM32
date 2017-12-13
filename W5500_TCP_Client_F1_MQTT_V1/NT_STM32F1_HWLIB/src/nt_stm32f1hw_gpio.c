      
    /**
    ******************************************************************************
    * @file    nt_stm32f1hw_gpio.c
    * @author  yexiaopeng
    * @version V1.0.0
    * @date    2017-11-27 
    * @brief   GPIO中间件 实现GPIO 的模式配置 和输入输出控制 API 
    ******************************************************************************
    * email: yexiaopeng1992@126.com
    *                 
    *                                
    *
    ******************************************************************************
    */
    
    #include "nt_stm32f1hw_gpio.h"
    
    #include "stm32f10x.h"
    #include "stm32f10x_rcc.h"
    
    static GPIO_InitTypeDef gpio_initStruct;
    
    /** GPIO 模式配置函数 */
    extern void PAMODE(uint8_t pin,GPIOMode_TypeDef mode)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
        gpio_initStruct.GPIO_Pin =  (uint16_t)(0x0001 << pin);
        gpio_initStruct.GPIO_Speed = GPIO_Speed_10MHz;
        gpio_initStruct.GPIO_Mode = mode;
        GPIO_Init(GPIOA,&gpio_initStruct);
    }

    extern void PBMODE(uint8_t pin,GPIOMode_TypeDef mode)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
        gpio_initStruct.GPIO_Pin =  (uint16_t)(0x0001 << pin);
        gpio_initStruct.GPIO_Speed = GPIO_Speed_10MHz;
        gpio_initStruct.GPIO_Mode = mode;
        GPIO_Init(GPIOB,&gpio_initStruct);
    }

    extern void PCMODE(uint8_t pin,GPIOMode_TypeDef mode)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
        gpio_initStruct.GPIO_Pin =  (uint16_t)(0x0001 << pin);
        gpio_initStruct.GPIO_Speed = GPIO_Speed_10MHz;
        gpio_initStruct.GPIO_Mode = mode;
        GPIO_Init(GPIOC,&gpio_initStruct);
    }

    extern void PDMODE(uint8_t pin,GPIOMode_TypeDef mode)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
        gpio_initStruct.GPIO_Pin =  (uint16_t)(0x0001 << pin);
        gpio_initStruct.GPIO_Speed = GPIO_Speed_10MHz;
        gpio_initStruct.GPIO_Mode = mode;
        GPIO_Init(GPIOD,&gpio_initStruct);
    }

    extern void PEMODE(uint8_t pin,GPIOMode_TypeDef mode)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
        gpio_initStruct.GPIO_Pin =  (uint16_t)(0x0001 << pin);
        gpio_initStruct.GPIO_Speed = GPIO_Speed_10MHz;
        gpio_initStruct.GPIO_Mode = mode;
        GPIO_Init(GPIOE,&gpio_initStruct);
    }

    extern void PFMODE(uint8_t pin,GPIOMode_TypeDef mode)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);
        gpio_initStruct.GPIO_Pin =  (uint16_t)(0x0001 << pin);
        gpio_initStruct.GPIO_Speed = GPIO_Speed_10MHz;
        gpio_initStruct.GPIO_Mode = mode;
        GPIO_Init(GPIOF,&gpio_initStruct);
    }

    extern void PGMODE(uint8_t pin,GPIOMode_TypeDef mode)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);
        gpio_initStruct.GPIO_Pin =  (uint16_t)(0x0001 << pin);
        gpio_initStruct.GPIO_Speed = GPIO_Speed_10MHz;
        gpio_initStruct.GPIO_Mode = mode;
        GPIO_Init(GPIOG
        ,&gpio_initStruct);
    }

    /** GPIO 输出函数*/
    extern void PAOUT(uint8_t pin,uint8_t portlevel)
    {
        if(portlevel == 0)
        {
            GPIO_ResetBits(GPIOA,(uint16_t)(0x0001 << pin));
        }else{
            GPIO_SetBits(GPIOA,(uint16_t)(0x0001 << pin));
        }
    }

    extern void PBOUT(uint8_t pin,uint8_t portlevel)
    {
        if(portlevel == 0)
        {
            GPIO_ResetBits(GPIOB,(uint16_t)(0x0001 << pin));
        }else{
            GPIO_SetBits(GPIOB,(uint16_t)(0x0001 << pin));
        }
    }

    extern void PCOUT(uint8_t pin,uint8_t portlevel)
    {
        if(portlevel == 0)
        {
            GPIO_ResetBits(GPIOC,(uint16_t)(0x0001 << pin));
        }else{
            GPIO_SetBits(GPIOC,(uint16_t)(0x0001 << pin));
        }
    }

    extern void PDOUT(uint8_t pin,uint8_t portlevel)
    {
        if(portlevel == 0)
        {
            GPIO_ResetBits(GPIOD,(uint16_t)(0x0001 << pin));
        }else{
            GPIO_SetBits(GPIOD,(uint16_t)(0x0001 << pin));
        }
    }

    extern void PEOUT(uint8_t pin,uint8_t portlevel)
    {
        if(portlevel == 0)
        {
            GPIO_ResetBits(GPIOE,(uint16_t)(0x0001 << pin));
        }else{
            GPIO_SetBits(GPIOE,(uint16_t)(0x0001 << pin));
        }
    }

    extern void PFOUT(uint8_t pin,uint8_t portlevel)
    {
        if(portlevel == 0)
        {
            GPIO_ResetBits(GPIOF,(uint16_t)(0x0001 << pin));
        }else{
            GPIO_SetBits(GPIOF,(uint16_t)(0x0001 << pin));
        }
    }

    extern void PGOUT(uint8_t pin,uint8_t portlevel)
    {
        if(portlevel == 0)
        {
            GPIO_ResetBits(GPIOG,(uint16_t)(0x0001 << pin));
        }else{
            GPIO_SetBits(GPIOG,(uint16_t)(0x0001 << pin));
        }
    }
    
    /** GPIO 输入检测函数*/
    extern uint8_t PAINT(uint8_t pin)
    {
        return GPIO_ReadInputDataBit(GPIOA,(uint16_t)(0x0001 << pin));
    }
        
    extern uint8_t PBINT(uint8_t pin)
    {
        return GPIO_ReadInputDataBit(GPIOB,(uint16_t)(0x0001 << pin));
    }
        
    extern uint8_t PCINT(uint8_t pin)
    {
        return GPIO_ReadInputDataBit(GPIOC,(uint16_t)(0x0001 << pin));
    }
        
    extern uint8_t PDINT(uint8_t pin)
    {
        return GPIO_ReadInputDataBit(GPIOD,(uint16_t)(0x0001 << pin));
    }
        
    extern uint8_t PEINT(uint8_t pin)
    {
        return GPIO_ReadInputDataBit(GPIOE,(uint16_t)(0x0001 << pin));
    }
        
    extern uint8_t PFINT(uint8_t pin)
    {
        return GPIO_ReadInputDataBit(GPIOF,(uint16_t)(0x0001 << pin));
    }
        
    extern uint8_t PGINT(uint8_t pin)
    {
        return GPIO_ReadInputDataBit(GPIOG,(uint16_t)(0x0001 << pin));
    }
