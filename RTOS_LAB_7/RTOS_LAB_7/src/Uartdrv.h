/*************************************************************
* Author: Michael Bottita
* Filename: Uartdrv.h
* Date Created: 2/6/23
**************************************************************/


#ifndef UARTDRV_H_
#define UARTDRV_H_

#define EDBG_UART                        UART0
#define UART_SERIAL_BAUDRATE             115200ul
#define UART_SERIAL_CHAR_LENGTH          US_MR_CHRL_8_BIT
#define UART_SERIAL_PARITY               US_MR_PAR_NO
#define UART_SERIAL_STOP_BIT             false
#define UART_MCK_DIV                     16
#define UART_MCK_DIV_MIN_FACTOR          1
#define UART_MCK_DIV_MAX_FACTOR          65535

#include <FreeRTOS.h>
#include <task.h>
#include <asf.h>


uint8_t initUART(Uart * pUart);
void UARTPutC(Uart * pUart, char data);
void UARTPutStr(Uart * pUart, char * data, uint8_t len);

#endif /* UARTDRV_H_ */