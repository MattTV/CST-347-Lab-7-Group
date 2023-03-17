/*************************************************************
* Author: Michael Bottita
* Filename: helperFunctions.c
* Date Created: 2/21/23
**************************************************************/

//Includes
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
* Purpose: This function initializes the tasks and queues
*
* Precondition:
*     None
*
* Postcondition:
*      Creates tasks, queues, and stores all the handles
*
************************************************************************/
void initializeTasksAndQueues(void)
{
	//Define global values
	MaxSpeed = 20;
	Acceleration = 2;
	
	// Initialize Queues and Queue Handles
	TxQueue = xQueueCreate(20,MAX_MESSAGE);
	RxQueue = xQueueCreate(20,1);
	
	ElevatorQueue = xQueueCreate(20,sizeof(ElevatorInfo_s*));
	
	xTaskCreate(TxTask,			// Function Called by task
	"TX Task",					// Task Name
	configMINIMAL_STACK_SIZE,	// Task Stack Size
	NULL,						// Any Parameters Passed to Task
	3,							// Task Priority
	NULL);						// Place to store Task Handle
	
	xTaskCreate(RxTask,			// Function Called by task
	"RX Task",					// Task Name
	(configMINIMAL_STACK_SIZE*2),	// Task Stack Size
	NULL,						// Any Parameters Passed to Task
	4,							// Task Priority
	NULL);						// Place to store Task Handle
	
	xTaskCreate(taskHeartbeat,	// Function Called by task
	"Heartbeat",			    // Task Name
	configMINIMAL_STACK_SIZE,	// Task Stack Size
	NULL,						// Any Parameters Passed to Task
	1,							// Task Priority
	NULL);						// Place to store Task Handle
	
	//Initialize the UART
	initUART(EDBG_UART);
	
}

uint8_t checkElevatorInputs(char charRx)
{
	uint8_t ElevatorNum = -1;
	switch(charRx)
	{
		case 'z':
			ElevatorNum = GD_FLOOR_CALL;
			break;
		case 'x':
			ElevatorNum = P1_DN_CALL;
			break;
		case 'c':
			ElevatorNum = P1_UP_CALL;
			break;
		case 'v':
			ElevatorNum = P2_CALL;
			break;
		case 'b':
			ElevatorNum = EM_STOP;
			break;
		case 'n':
			ElevatorNum = EM_CLEAR;
			break;	
	}
	return ElevatorNum;
}