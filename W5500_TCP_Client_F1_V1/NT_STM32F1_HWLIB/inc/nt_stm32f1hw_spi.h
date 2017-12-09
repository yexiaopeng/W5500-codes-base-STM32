/*
 * nt_stm32f1hw_spi.h
 *
 *  Created on: 2017Äê12ÔÂ9ÈÕ
 *      Author: Yexiaopeng
 */

#ifndef NT_STM32F1HW_SPI_H_
#define NT_STM32F1HW_SPI_H_

#include "stm32f10x_spi.h"

extern void nthw_sp1_config(void);
extern uint8_t nthw_sp1_ReadByte(void);
extern void nthw_sp1__WriteByte(uint8_t TxData);
extern void SPI_CrisEnter(void);
extern void SPI_CrisExit(void);

#endif /* NT_STM32F1HW_SPI_H_ */
