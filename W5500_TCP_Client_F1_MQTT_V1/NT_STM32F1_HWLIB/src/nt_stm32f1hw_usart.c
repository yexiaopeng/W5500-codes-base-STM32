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
        
        /* USART工作环境配置 */
        /* USART波特率:115200 */
        USART_InitStructure.USART_BaudRate = USART_BaudRate;
        /* USART字长(有效位)：8位 */
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        /* USART停止位：1位 */
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
        /* USART校验位：无 */
        USART_InitStructure.USART_Parity = USART_Parity_No ;
        /* USART硬件数据流控制(硬件信号控制传输停止)：无 */
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        /* USART工作模式使能：允许接收和发送 */
        USART_InitStructure.USART_Mode = USART_Mode;
        /* 初始化USART */
        USART_Init(USART1, &USART_InitStructure);
        
        /* 嵌套向量中断控制器组选择 */
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
        /* 配置USART为中断源 */
        NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
        /* 抢断优先级为0 */
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
        /* 子优先级为1 */
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
        /* 使能中断 */
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        /* 初始化配置NVIC */
        NVIC_Init(&NVIC_InitStructure);

         /* 使能接收中断 */
        USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//RXEN中断
        USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//空闲中断
        /* 使能USART */
        USART_Cmd(USART1, ENABLE);

        /* 清除发送完成标志 */
        USART_ClearFlag(USART1, USART_FLAG_TC|USART_FLAG_TXE|USART_FLAG_RXNE);    

        usart_1_rxen_fun = NULL;
    }
       
    static void nthw_usart_config_USART2(uint32_t USART_BaudRate,uint16_t USART_Mode)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
        //PA2 PA3
        PAMODE(2,GPIO_Mode_AF_PP);
        PAMODE(3,GPIO_Mode_IN_FLOATING);
        
        /* USART工作环境配置 */
        /* USART波特率:115200 */
        USART_InitStructure.USART_BaudRate = USART_BaudRate;
        /* USART字长(有效位)：8位 */
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        /* USART停止位：1位 */
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
        /* USART校验位：无 */
        USART_InitStructure.USART_Parity = USART_Parity_No ;
        /* USART硬件数据流控制(硬件信号控制传输停止)：无 */
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        /* USART工作模式使能：允许接收和发送 */
        USART_InitStructure.USART_Mode = USART_Mode;
        /* 初始化USART */
        USART_Init(USART2, &USART_InitStructure);
        
        /* 嵌套向量中断控制器组选择 */
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
        /* 配置USART为中断源 */
        NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
        /* 抢断优先级为0 */
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
        /* 子优先级为1 */
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
        /* 使能中断 */
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        /* 初始化配置NVIC */
        NVIC_Init(&NVIC_InitStructure);

         /* 使能接收中断 */
        USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//RXEN中断
        USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);//空闲中断
        /* 使能USART */
        USART_Cmd(USART2, ENABLE);

        /* 清除发送完成标志 */
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
            //TODO 增加参数配置的处理
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
            //TODO 增加参数配置的处理

        }
    }
    
    
    
    
