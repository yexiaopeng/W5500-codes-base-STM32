   
   /**
    ******************************************************************************
    * @file    nt_stm32f1hw_systick.c
    * @author  yexiaopeng
    * @version V1.0.0
    * @date    2017-11-27 
    * @brief   ϵͳ�δ�(SysTick)�м�� ʵ��ϵͳ�δ� API 
    ******************************************************************************
    * email: yexiaopeng1992@126.com
    * ˵����
    *    PXMODE(uint8_t pin,GPIOMode_TypeDef mode);{X = A��B��C��D....}
    *        ����GPIO��ģʽ��
    *             GPIO_Mode_AIN = 0x0,
    *              GPIO_Mode_IN_FLOATING = 0x04,
    *              GPIO_Mode_IPD = 0x28,
    *              GPIO_Mode_IPU = 0x48,
    *              GPIO_Mode_Out_OD = 0x14,
    *              GPIO_Mode_Out_PP = 0x10,
    *              GPIO_Mode_AF_OD = 0x1C,
    *              GPIO_Mode_AF_PP = 0x18
    *          
    *   void PXOUT(uint8_t pin,uint8_t portlevel);{X = A��B��C��D....}
    *        ��GPIO���ģʽ�£���������ĸߵ͵�ƽ
    *        pin:���ű��
    *            [0~15] ����ʹ��|�����ö�����ţ�һ������һ��ֻ�ܿ���һ������
    *        portlevel����ƽ
    *            [0,1]
    *   uint8_t PXINT(uint8_t pin);{X = A��B��C��D....}
    *        ��GPIO����ģʽ�£���ȡGPIO�ĸߵ͵�ƽ
    *        pin:���ű��
    *            [0~15] ����ʹ��|�����ö�����ţ�һ������һ��ֻ�ܿ���һ������
    *        return����ƽ
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
    * ����: ��ʼ��ϵͳ�δ������
    * ����: ��
    * ����: ��
    * ˵����AHBʱ��Ĭ��Ϊ72MHZ �ж�ʱ��Ϊ1us
    */
    extern void nthw_systick_init()
    {
        //1000000 1us
        //100000  10us
        //10000   100us
        //1000    1ms
        if( SysTick_Config( SystemCoreClock / 1000000 ) )
        {
            //���ò��ɹ�
            while(1);
        }
        //�ر�systick
        SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
    }

    /**
    * ����: ��ʱ ntime us
    * ����: uint32_t ntime
            ��ʱ��us
    * ����: ��
    * ˵����AHBʱ��Ĭ��Ϊ72MHZ �ж�ʱ��Ϊ1us
    */
    extern void nthw_systick_delay_us(uint32_t ntime)
    {
        TimingDelay = ntime;
        //����systick
        SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
        while(TimingDelay > 0);
        SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
    
    }

    extern void nthw_systick_delay_ms(uint16_t ntime)
    {
         TimingDelay = ntime * 1000;
        //����systick
        SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
        while(TimingDelay > 0);
        SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
    }
    
    
    /**
    * ����: systick �жϺ���
    * ����: ��
    * ����: ��
    * ˵�����ڴ˴����ã�����stm32f10x_it.c
    */
    void SysTick_Handler(void)
    {
        if( 0x00 != TimingDelay )
        {
            TimingDelay--;
        }
    }

