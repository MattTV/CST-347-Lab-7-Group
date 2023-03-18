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
	Elevator.max_speed = 20; //feet/s
	Elevator.acceleration = 2; //feet/s^2
	Elevator.speed = 0; //feet/s
	Elevator.height = 0; //feet
	Elevator.max_height = P2;
	Elevator.isMoving = false;
	Elevator.movingUp = false;
	Elevator.doorOpen = false;
	Elevator.eStop = false;
	
	// Initialize Queues and Queue Handles
	TxQueue = xQueueCreate(20,MAX_MESSAGE);
	RxQueue = xQueueCreate(20,1);	
	ElevatorQueue = xQueueCreate(20,sizeof(ElevatorInfo_s));
	
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
	
	xTaskCreate(ElevatorTask,	// Function Called by task
	"Elevator Task",			    // Task Name
	(configMINIMAL_STACK_SIZE*2),	// Task Stack Size
	NULL,						// Any Parameters Passed to Task
	5,							// Task Priority
	NULL);						// Place to store Task Handle
	
	xTaskCreate(DisplayElevatorStatus,	// Function Called by task
	"Elevator Task Status",			    // Task Name
	(configMINIMAL_STACK_SIZE*2),	// Task Stack Size
	NULL,						// Any Parameters Passed to Task
	5,							// Task Priority
	NULL);						// Place to store Task Handle
	
	xTaskCreate(MotorFreq,	// Function Called by task
	"LED Speed Indicator",			    // Task Name
	(configMINIMAL_STACK_SIZE*2),	// Task Stack Size
	NULL,						// Any Parameters Passed to Task
	1,							// Task Priority
	NULL);						// Place to store Task Handle
	
	xTaskCreate(dirTask,	// Function Called by task
	"LED Dir Indicator",			    // Task Name
	(configMINIMAL_STACK_SIZE*2),	// Task Stack Size
	NULL,						// Any Parameters Passed to Task
	1,							// Task Priority
	NULL);						// Place to store Task Handle
	
	//Initialize the UART
	initUART(EDBG_UART);
	
}

int checkElevatorInputs(char charRx)
{
	int ElevatorNum = -1;
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

void ElevatorStatusUpdate(void)
{
	char FloorIndicator[MAX_MESSAGE] = "Floor:";

	char stoppedIndicator[MAX_MESSAGE] = " Status: Stopped\n\r\0";
	char movingIndicator[MAX_MESSAGE] = " Status: Moving\n\r\0";
	
	char heightIndicator[MAX_MESSAGE] = " Height: \0";

	char speedIndicator[MAX_MESSAGE] = " Speed (ft/s): \0";
	
	//Height\floor update
	switch(Elevator.height)
	{
		case GND:
			strcat(FloorIndicator," GND\0");
			xQueueSendToBack(TxQueue,&FloorIndicator,portMAX_DELAY);
			break;
		case P1:
			strcat(FloorIndicator," P1\0");
			xQueueSendToBack(TxQueue,&FloorIndicator,portMAX_DELAY);
			break;
		case P2:
			strcat(FloorIndicator," P2\0");
			xQueueSendToBack(TxQueue,&FloorIndicator,portMAX_DELAY);
			break;
	}
	
	//Send speed update
	char tempSpeed[MAX_MESSAGE];
	itoa(Elevator.speed,tempSpeed,10);
	strcat(tempSpeed,"\0");
	xQueueSendToBack(TxQueue,&speedIndicator,portMAX_DELAY);
	xQueueSendToBack(TxQueue,&tempSpeed,portMAX_DELAY);
	
	//Height update
	char tempHeight[MAX_MESSAGE];
	itoa(Elevator.height,tempHeight,10);
	strcat(tempHeight,"\0");
	xQueueSendToBack(TxQueue,&heightIndicator,portMAX_DELAY);
	xQueueSendToBack(TxQueue,&tempHeight,portMAX_DELAY);
	
	//isMoving
	if (Elevator.isMoving)
		xQueueSendToBack(TxQueue,&movingIndicator,portMAX_DELAY);
	else
		xQueueSendToBack(TxQueue,&stoppedIndicator,portMAX_DELAY);
}

/**********************************************************************
* Purpose: This function flashes LED6 at 1Hz for every 10 ft/s the elevator is traveling.
*
* Precondition:
*
*
* Postcondition: flashes an LED
*
*
************************************************************************/

void MotorFreq (void)
{
	TickType_t xDelay = (1000 / portTICK_PERIOD_MS); // 1 second delay
	
	while(1)
	{
		uint8_t count = abs(Elevator.speed) / 10;
	
		toggleLED(6);
		vTaskDelay(xDelay/count);
		
	}
	
}

/**********************************************************************
* Purpose: This function simulates an elevator door closing
*
* Precondition:
*
*
* Postcondition:
*
*
************************************************************************/

void elevatorDoorClose(void)
{
	const TickType_t xDelay3 = 300 / portTICK_PERIOD_MS; // .3 second delay
	if (Elevator.doorOpen)
	{
		toggleLED(1);
		vTaskDelay(xDelay3);
		toggleLED(2);
		vTaskDelay(xDelay3);
		toggleLED(3);
	}
}

/**********************************************************************
* Purpose: This function simulates an elevator door opening
*
* Precondition:
*
*
* Postcondition:
*
*
************************************************************************/

void elevatorDoorOpen(void)
{
	const TickType_t xDelay3 = 300 / portTICK_PERIOD_MS; //.3 second delay

	if (!Elevator.doorOpen)
	{
		toggleLED(3);
		vTaskDelay(xDelay3);
		toggleLED(2);
		vTaskDelay(xDelay3);
		toggleLED(1);
	}
}

void ReachedDest(void)
{
	if (Elevator.isMoving)
	{
		Elevator.speed = 0;
		Elevator.isMoving = 0;
		Elevator.height = Elevator.destination;
		elevatorDoorOpen();
		vTaskDelay(5000/portTICK_PERIOD_MS);
		elevatorDoorClose();
	}
}