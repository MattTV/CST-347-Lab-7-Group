/*************************************************************
* Author: Michael Bottita
* Filename: myTasks.c
* Date Created: 2/6/23
**************************************************************/
#include <asf.h>
#include <stdbool.h>
#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include <queue.h>
#include <semphr.h>
#include <string.h>
#include "OITExpansionBoard.h"
#include "led_driver.h"
#include "Uartdrv.h"
#include "myTasks.h"
#include "helperFunctions.h"
#include "controlCLI.h"
#include "FreeRTOS_CLI.h"

/**********************************************************************
* Purpose: This task handles all the information to be send to the UART
*
* Precondition:
*     None
*
* Postcondition:
*      sends correct info to the UART
*
************************************************************************/
void TxTask (void * pvParameters)
{	
	char messageTx[MAX_MESSAGE];
	
	while (true)
	{
		//Wait for a message to be received and send the message
		if (xQueueReceive(TxQueue, &messageTx, portMAX_DELAY) == pdTRUE)
		{
			UARTPutStr(EDBG_UART,messageTx,strlen(messageTx));
		}
	}
}

/**********************************************************************
* Purpose: This task handles all the information being recieved from the UART
*
* Precondition:
*     None
*
* Postcondition:
*      sends correct information to the LEDQueue and TxQueue
*
************************************************************************/
void RxTask (void * pvParameters)
{			
	static char bufferCLI[MAX_CLI_MESSAGE];
	char tempTxBuff[MAX_MESSAGE];
	static char message[MAX_MESSAGE];
		message[1] = '\0';
	
	char msgToEcho[2];
	char endCmd[] = {'\n','\r','\0'};
	
	uint8_t cmdIndex = 0;
	
	while (true)
	{	
		//Wait for a queue message from the UART ISR
		if (xQueueReceive(RxQueue,&message[cmdIndex],portMAX_DELAY) == pdTRUE)
		{	
			if (message[cmdIndex] == '\r')
			{
				//message[cmdIndex] = '\0';
				xQueueSendToBack(TxQueue,&endCmd,portMAX_DELAY);
				
				//Check for specific elevator keys
				uint8_t EleCheckInputs = checkElevatorInputs(message[cmdIndex]);
				if (EleCheckInputs != -1)
				{
					ElevatorInfo_s tempEleInfo = {-1,EleCheckInputs};
					xQueueSendToBack(ElevatorQueue,&tempEleInfo,portMAX_DELAY);
				}
				else
				{
					FreeRTOS_CLIProcessCommand(message,bufferCLI,MAX_CLI_MESSAGE);
				
					for(int i = 0; i < MAX_CLI_MESSAGE/MAX_MESSAGE; ++i)
					{
						strncpy(tempTxBuff,bufferCLI+i*(MAX_MESSAGE-1),MAX_MESSAGE-1);
						tempTxBuff[MAX_MESSAGE-1] = '\0';
						xQueueSendToBack(TxQueue,&tempTxBuff,portMAX_DELAY);
					}

					cmdIndex = 0;
					memset(bufferCLI,0x00,MAX_CLI_MESSAGE);
					memset(tempTxBuff,0x00,MAX_MESSAGE);
				}
			}
			else if (message[cmdIndex] == 127) //DEL
			{
				msgToEcho[0] = message[cmdIndex];
				msgToEcho[1] = '\0';
				xQueueSendToBack(TxQueue,&msgToEcho,portMAX_DELAY);
				cmdIndex = cmdIndex-1 < 0 ? 0 : cmdIndex-1;
			}
			else //Handle echo
			{
				msgToEcho[0] = message[cmdIndex];
				msgToEcho[1] = '\0';

				xQueueSendToBack(TxQueue,&msgToEcho,portMAX_DELAY);
				cmdIndex++;
			}
		}
	}
}

void ElevatorTask(void * pvParameters)
{
	ElevatorInfo_s tempElevatorInfo;
	while(1)
	{
		xQueueReceive(ElevatorQueue,&tempElevatorInfo,portMAX_DELAY);
		
		switch(tempElevatorInfo.EL_instruct)
		{
			case CHANGE_MAX_SPEED :
				MaxSpeed = tempElevatorInfo.EL_helperVar;
				break;
			case CHANGE_ACCEL	  :
				Acceleration = tempElevatorInfo.EL_helperVar;
				break;
			case SEND_TO_FLOOR    :
				break;
			case EM_STOP          :
				break;
			case EM_CLEAR         :
				break;
			case GD_FLOOR_CALL    :
				break;
			case P1_DN_CALL       :
				break;
			case P1_UP_CALL       :
				break;
			case P2_CALL          :
				break;
		}
		
	}
}

/**********************************************************************
* Purpose: This function calls other helper functions to toggle the current LED
*
* Precondition:
*     Take pvParameters which is a struct containing info about the LED
*
* Postcondition:
*      Reads from a queue to control the speed of the current LED
*
************************************************************************/
void toggleLED(void * pvParameters)
{	
	int ledNumCopy = LEDStructInfo.LedNum;
	uint ledDelayCopy = LEDStructInfo.Delay;
	
	LEDStructInfo.LedNum = 0;
	LEDStructInfo.Delay = 0;
	
	xQueueHandle currQueue;
	BaseType_t currLed;
	switch(ledNumCopy)
	{
		case 1: 
			currLed=EXT1_LED_1_PIN;
			currQueue = Led1Queue;
			break;
		case 2:
			currLed=EXT1_LED_2_PIN;
			currQueue = Led2Queue;
			break;
		case 3:
			currLed=EXT1_LED_3_PIN;
			currQueue = Led3Queue;
			break;
		default:
			currLed=0;
	}
	
	while (true)
	{	
		ioport_toggle_pin_level(currLed);
		
		if (uxQueueMessagesWaiting(currQueue) == pdTRUE)
		{
			xQueueReceive(currQueue,&ledDelayCopy,0);
		}
		vTaskDelay(ledDelayCopy/portTICK_PERIOD_MS);
	}
}

/**********************************************************************
* Purpose: This function blinks an on-board LED
*
* Precondition:
*     None
*
* Postcondition:
*      None
*
************************************************************************/
void taskHeartbeat (void * pvParameters)
{
	const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
	
	while (true)
	{
		ioport_set_pin_level(LED_0_PIN, LED_0_ACTIVE);
		vTaskDelay(xDelay);
		
		ioport_set_pin_level(LED_0_PIN, LED_0_INACTIVE);
		vTaskDelay(xDelay);
		
	}
}
