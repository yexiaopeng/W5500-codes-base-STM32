   
   /**
    ******************************************************************************
    * @file    nt_stm32f1hw_systick.c
    * @author  yexiaopeng
    * @version V1.0.0
    * @date    2017-11-27 
    * @brief   系统滴答(SysTick)中间件 实现系统滴答 API 
    ******************************************************************************
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
    ******************************************************************************
    */
    
    /* Includes ------------------------------------------------------------------*/
    #include "nt_stm32f1hw_systick.h"
    
    #include "stm32f10x.h"

    static __IO uint32_t TimingDelay;
    
    /**
    * 描述: 初始化系统滴答计数器
    * 参数: 无
    * 返回: 无
    * 说明：AHB时钟默认为72MHZ 中断时间为1us
    */
    extern void nthw_systick_init()
    {
        //1000000 1us
        //100000  10us
        //10000   100us
        //1000    1ms
        if( SysTick_Config( SystemCoreClock / 1000000 ) )
        {
            //设置不成功
            while(1);
        }
        //关闭systick
        SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
    }

    /**
    * 描述: 延时 ntime us
    * 参数: uint32_t ntime
            延时的us
    * 返回: 无
    * 说明：AHB时钟默认为72MHZ 中断时间为1us
    */
    extern void nthw_systick_delay_us(uint32_t ntime)
    {
        TimingDelay = ntime;
        //开启systick
        SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
        while(TimingDelay > 0);
        SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
    
    }

    extern void nthw_systick_delay_ms(uint16_t ntime)
    {
         TimingDelay = ntime * 1000;
        //开启systick
        SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
        while(TimingDelay > 0);
        SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
    }
    
    
    /**
    * 描述: systick 中断函数
    * 参数: 无
    * 返回: 无
    * 说明：在此处调用，不在stm32f10x_it.c
    */
    void SysTick_Handler(void)
    {
        if( 0x00 != TimingDelay )
        {
            TimingDelay--;
        }
    }

