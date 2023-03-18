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
				message[cmdIndex] = '\0';
				xQueueSendToBack(TxQueue,&endCmd,portMAX_DELAY);
				
				//Check for specific elevator keys
				int EleCheckInputs = checkElevatorInputs(message[0]);
				if (EleCheckInputs != -1)
				{
					ElevatorInfo_s tempEleInfo = {-1,EleCheckInputs};
					
					if (!Elevator.eStop)
						xQueueSendToBack(ElevatorQueue,&tempEleInfo,portMAX_DELAY);
					else if (EleCheckInputs == EM_CLEAR)
						xQueueSendToBack(ElevatorQueue,&tempEleInfo,portMAX_DELAY);
						
					memset(message,0x00,MAX_MESSAGE);
					cmdIndex = 0;
				}
				else
				{
					BaseType_t moreMSG = 0;
					do 
					{
						moreMSG = FreeRTOS_CLIProcessCommand(message,bufferCLI,MAX_CLI_MESSAGE);
				
						for(int i = 0; i < MAX_CLI_MESSAGE/MAX_MESSAGE; ++i)
						{
							strncpy(tempTxBuff,bufferCLI+i*(MAX_MESSAGE-1),MAX_MESSAGE-1);
							tempTxBuff[MAX_MESSAGE-1] = '\0';
							xQueueSendToBack(TxQueue,&tempTxBuff,portMAX_DELAY);
						}
						
					} while(moreMSG == pdTRUE);
					
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
		if (xQueueReceive(ElevatorQueue,&tempElevatorInfo,0) == pdTRUE)
		{
			switch(tempElevatorInfo.EL_instruct)
			{
				case CHANGE_MAX_SPEED:
					Elevator.max_speed = tempElevatorInfo.EL_helperVar;
					break;
					
				case CHANGE_ACCEL:
					Elevator.acceleration = tempElevatorInfo.EL_helperVar;
					break;
					
				case SEND_TO_FLOOR:
					Elevator.isMoving = true;
					Elevator.destination = tempElevatorInfo.EL_helperVar;
					
					if (Elevator.height > Elevator.destination)
						Elevator.movingUp = false;
						
					else if (Elevator.height < Elevator.destination)
						Elevator.movingUp = true;
						
					break;
					
				case EM_STOP:
					Elevator.eStop = true;
					Elevator.isMoving = true;
					Elevator.movingUp = false;
					Elevator.destination = GND;
					break;
					
				case EM_CLEAR:
					Elevator.eStop = false;
					break;
					
				case GD_FLOOR_CALL:
					Elevator.isMoving = true;
					Elevator.movingUp = false;
					Elevator.destination = GND;
					break;
					
				case P1_DN_CALL:
				
					Elevator.isMoving = true;
					Elevator.destination = P1;
					
					if (Elevator.height > Elevator.destination)
						Elevator.movingUp = false;
						
					else if (Elevator.height < Elevator.destination)
						Elevator.movingUp = true;
							
					break;
					
				case P1_UP_CALL:
					Elevator.isMoving = true;
					Elevator.destination = P1;
					
					if (Elevator.height > Elevator.destination)
						Elevator.movingUp = false;
						
					else if (Elevator.height < Elevator.destination)
						Elevator.movingUp = true;
					break;
					
				case P2_CALL:
					Elevator.isMoving = true;
					Elevator.destination = P2;
					
					if (Elevator.height > Elevator.destination)
						Elevator.movingUp = false;
					
					else if (Elevator.height < Elevator.destination)
						Elevator.movingUp = true;
					break;
			}
		}
		
		if (Elevator.isMoving && (abs(Elevator.speed) < Elevator.max_speed))
		{
			Elevator.speed += Elevator.movingUp ? Elevator.acceleration : (-1 * Elevator.acceleration);
		}
		
		if(Elevator.isMoving)
			Elevator.height += Elevator.speed;

		if (Elevator.height < 0)
			Elevator.height = 0;

		else if (Elevator.height >= Elevator.max_height)
		{
			Elevator.height = Elevator.max_height;
			Elevator.isMoving = false;
		}
		
		if (Elevator.movingUp && (Elevator.height >= Elevator.destination) \
		|| (!Elevator.movingUp) && (Elevator.height <= Elevator.destination))
			ReachedDest();

		vTaskDelay(1000/portTICK_PERIOD_MS);
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

void DisplayElevatorStatus()
{
	while(1)
	{
		ElevatorStatusUpdate();
		vTaskDelay(500/portTICK_PERIOD_MS);
	}
}

void dirTask(void * pvParameters)
{    
    while (true)
    {
        if (Elevator.movingUp && Elevator.isMoving)
        {
            setLED(4, 1);
            setLED(5, 0);
        }
        else if (!Elevator.movingUp && Elevator.isMoving)
        {
            setLED(5, 1);
            setLED(4, 0);
        }
        else
        {
            setLED(4, 0);
            setLED(5, 0);
        }
		vTaskDelay(1/portTICK_PERIOD_MS);
    }
}