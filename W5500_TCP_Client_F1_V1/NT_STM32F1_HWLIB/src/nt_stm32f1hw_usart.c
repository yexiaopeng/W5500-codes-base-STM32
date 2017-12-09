    /* Includes ------------------------------------------------------------------*/
    #include "nt_stm32f1hw_usart.h"
    #include "nt_stm32f1hw_gpio.h"
    
    #include "stddef.h"
    
   
    
    
    
    /* Private variables ---------------------------------------------------------*/
    static USART_InitTypeDef USART_InitStructure;
	static NVIC_InitTypeDef NVIC_InitStructure;
    
    /* Private function prototypes -----------------------------------------------*/  
    static void nthw_usart_config_USART1(uint32_t USART_BaudRate,uint16_t USART_Mode);
    static void nthw_usart_config_USART2(uint32_t USART_BaudRate,uint16_t USART_Mode);
    static void nthw_usart_config_USART3(uint32_t USART_BaudRate,uint16_t USART_Mode);
    static void nthw_usart_config_UART4(uint32_t USART_BaudRate,uint16_t USART_Mode);
    
    static void (* usart_1_rxen_fun)(uint16_t) = NULL;
    static void (* usart_1_idle_fun)(void) = NULL;
    
    static void (* usart_2_rxen_fun)(uint16_t) = NULL;
    static void (* usart_2_idle_fun)(void) = NULL;
    /* Public function -----------------------------------------------------------*/ 
   
    
    extern uint8_t nthw_usart_init(USART_TypeDef* USARTx, 
                                   uint32_t USART_BaudRate,
                                   uint16_t USART_Mode)
    {
        if( USARTx == USART1 )
        {
            nthw_usart_config_USART1(USART_BaudRate,USART_Mode);
            return 1;
        }else if(USARTx == USART2)
        {
            nthw_usart_config_USART2(USART_BaudRate,USART_Mode);
            return 1;
        }else if(USARTx == USART3)
        {
            nthw_usart_config_USART3(USART_BaudRate,USART_Mode);
            return 1;
        }else if(USARTx == UART4)
        {
            nthw_usart_config_UART4(USART_BaudRate,USART_Mode);
            return 1;
        }else{
            return 0;
        }
    }
    
    extern void nthw_usart_PutChar(USART_TypeDef* USARTx,uint8_t data)
    {
         USART_SendData(USARTx, data);
         while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){}
    }
    extern void nthw_usart_PutStr(USART_TypeDef* USARTx,uint8_t * str)
    {
         while (0 != *str)
        {
             nthw_usart_PutChar(USARTx,*str);
            str++;
        }
    }
    
    extern void nthw_usart_1_rxen_cbfunc(void (*func)(uint16_t))
    {
        usart_1_rxen_fun = func;
    }
    
    extern void nthw_usart_1_itle_cbfunc(void (*func)(void))
    {
        usart_1_idle_fun = func;
    }
    
    extern void nthw_usart_2_rxen_cbfunc(void (*func)(uint16_t))
    {
        usart_2_rxen_fun = func;
    }
    
    extern void nthw_usart_2_itle_cbfunc(void (*func)(void))
    {
        usart_2_idle_fun = func;
    }
    
    /* Private function ---------- -----------------------------------------------*/
    static void nthw_usart_config_USART1(uint32_t USART_BaudRate,uint16_t USART_Mode)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
        //PA9 PA10
        PAMODE(9,GPIO_Mode_AF_PP);
        PAMODE(10,GPIO_Mode_IN_FLOATING);
        
        /* USART������������ */
        /* USART������:115200 */
        USART_InitStructure.USART_BaudRate = USART_BaudRate;
        /* USART�ֳ�(��Чλ)��8λ */
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        /* USARTֹͣλ��1λ */
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
        /* USARTУ��λ���� */
        USART_InitStructure.USART_Parity = USART_Parity_No ;
        /* USARTӲ������������(Ӳ���źſ��ƴ���ֹͣ)���� */
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        /* USART����ģʽʹ�ܣ�������պͷ��� */
        USART_InitStructure.USART_Mode = USART_Mode;
        /* ��ʼ��USART */
        USART_Init(USART1, &USART_InitStructure);
        
        /* Ƕ�������жϿ�������ѡ�� */
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
        /* ����USARTΪ�ж�Դ */
        NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
        /* �������ȼ�Ϊ0 */
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
        /* �����ȼ�Ϊ1 */
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
        /* ʹ���ж� */
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        /* ��ʼ������NVIC */
        NVIC_Init(&NVIC_InitStructure);

         /* ʹ�ܽ����ж� */
        USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//RXEN�ж�
        USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//�����ж�
        /* ʹ��USART */
        USART_Cmd(USART1, ENABLE);

        /* ���������ɱ�־ */
        USART_ClearFlag(USART1, USART_FLAG_TC|USART_FLAG_TXE|USART_FLAG_RXNE);    

        usart_1_rxen_fun = NULL;
    }
       
    static void nthw_usart_config_USART2(uint32_t USART_BaudRate,uint16_t USART_Mode)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
        //PA2 PA3
        PAMODE(2,GPIO_Mode_AF_PP);
        PAMODE(3,GPIO_Mode_IN_FLOATING);
        
        /* USART������������ */
        /* USART������:115200 */
        USART_InitStructure.USART_BaudRate = USART_BaudRate;
        /* USART�ֳ�(��Чλ)��8λ */
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        /* USARTֹͣλ��1λ */
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
        /* USARTУ��λ���� */
        USART_InitStructure.USART_Parity = USART_Parity_No ;
        /* USARTӲ������������(Ӳ���źſ��ƴ���ֹͣ)���� */
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        /* USART����ģʽʹ�ܣ�������պͷ��� */
        USART_InitStructure.USART_Mode = USART_Mode;
        /* ��ʼ��USART */
        USART_Init(USART2, &USART_InitStructure);
        
        /* Ƕ�������жϿ�������ѡ�� */
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
        /* ����USARTΪ�ж�Դ */
        NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
        /* �������ȼ�Ϊ0 */
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
        /* �����ȼ�Ϊ1 */
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
        /* ʹ���ж� */
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        /* ��ʼ������NVIC */
        NVIC_Init(&NVIC_InitStructure);

         /* ʹ�ܽ����ж� */
        USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//RXEN�ж�
        USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);//�����ж�
        /* ʹ��USART */
        USART_Cmd(USART2, ENABLE);

        /* ���������ɱ�־ */
        USART_ClearFlag(USART2, USART_FLAG_TC|USART_FLAG_TXE|USART_FLAG_RXNE); 
    }
    
    static void nthw_usart_config_USART3(uint32_t USART_BaudRate,uint16_t USART_Mode)
    {
    }
    
    static void nthw_usart_config_UART4(uint32_t USART_BaudRate,uint16_t USART_Mode)
    {
    
    }
    

    
    /* Interrupt function ---------- -----------------------------------------------*/
    /**
    * @name: DEBUG_USARTX_IRQHANDLER
    * @brief: USARTX Inputerrupt USARTX_IRQHandler
    * @Auttor:yexiaopeng
    * @param:Void
    * @retval:None
    * @output:None
    */
    void USART1_IRQHandler(void)
    {
        uint8_t clear = clear;
        if( USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
        {
            clear = USART_ReceiveData(USART1);
            if(usart_1_rxen_fun == NULL){
                
                return;
            }
                
            usart_1_rxen_fun(clear);
        }

        if(USART_GetITStatus(USART1,USART_IT_IDLE) != RESET)
        {

            clear = USART1->SR;
            clear = USART1->DR;
            //TODO ���Ӳ������õĴ���
            if( usart_1_idle_fun == NULL ) return;
            usart_1_idle_fun();

        }
    }
    
    void USART2_IRQHandler(void)
    {
        uint8_t clear = clear;
        if( USART_GetITStatus(USART2,USART_IT_RXNE) != RESET)
        {
            if(usart_2_rxen_fun == NULL){
                USART_ReceiveData(USART2);
                return;
            }
                
            usart_2_rxen_fun(USART_ReceiveData(USART2));
        }

        if(USART_GetITStatus(USART2,USART_IT_IDLE) != RESET)
        {

            clear = USART2->SR;
            clear = USART2->DR;
            //TODO ���Ӳ������õĴ���

        }
    }
    
    
    
    
