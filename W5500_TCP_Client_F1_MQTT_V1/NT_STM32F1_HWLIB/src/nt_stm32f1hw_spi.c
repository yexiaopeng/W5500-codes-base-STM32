/*
 * nt_stm32f1hw_spi.c
 *
 *  Created on: 2017��12��9��
 *      Author: Yexiaopeng
 */

#include "nt_stm32f1hw_spi.h"

extern void nthw_sp1_config(void)
{
	SPI_InitTypeDef SPI_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;

	//��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_SPI1,ENABLE);
	//������PA5->SCK,PA6->MISO,PA7->MOSI
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_5 | GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	//spi����
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStruct.SPI_Direction= SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1,&SPI_InitStruct);
	SPI_SSOutputCmd(SPI1, ENABLE);
	SPI_Cmd(SPI1, ENABLE);
}
extern uint8_t nthw_sp1_ReadByte(void)
{
	while((SPI1->SR&SPI_I2S_FLAG_TXE)==0);	//�ȴ���������
	SPI1->DR=0xFF;	 	  										//����һ�������ݲ����������ݵ�ʱ��
	while((SPI1->SR&SPI_I2S_FLAG_RXNE)==0); //�ȴ�������һ��byte
	return SPI1->DR;
}
extern void nthw_sp1__WriteByte(uint8_t TxData)
{
	while((SPI1->SR&SPI_I2S_FLAG_TXE)==0);	//�ȴ���������
	SPI1->DR=TxData;	 	  									//����һ��byte
	while((SPI1->SR&SPI_I2S_FLAG_RXNE)==0); //�ȴ�������һ��byte
	SPI1->DR;
}

/**
  * @brief  �����ٽ���
  * @retval None
  */
extern void SPI_CrisEnter(void)
{
	__set_PRIMASK(1);
}
/**
  * @brief  �˳��ٽ���
  * @retval None
  */
extern void SPI_CrisExit(void)
{
	__set_PRIMASK(0);
}
