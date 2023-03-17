/*
 * controlCLI.c
 *
 * Created: 2/22/2023 1:02:13 PM
 *  Author: michael.bottita
 */ 

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

//CLI helper info
static const char taskListHdr[] = "Name\t\t\tStat\tPri\tS/Space\tTCB\r\n";

//Definitions for CLI commands
static const CLI_Command_Definition_t xTaskStatsCommand = {"task-stats",
			"\r\ntask-stats: Displays a table of task state information\r\n",
            (pdCOMMAND_LINE_CALLBACK)prvTaskStatsCommand,
            0};

static const CLI_Command_Definition_t xChangeMaxSpeed = {"S",
			"\r\nS <speed>: Change Maximum Speed in ft/s.\r\n",
			(pdCOMMAND_LINE_CALLBACK)prvChangeMaxSpeed,
			1};
	
static const CLI_Command_Definition_t xChangeAcceleration = {"AP",
			"\r\nAP <acceleration>: Change Acceleration in ft/s^2.\r\n",
			(pdCOMMAND_LINE_CALLBACK)prvChangeAcceleration,
			1};

static const CLI_Command_Definition_t xSendFloor = {"SF",
			"\r\nSF <floor_num>: Send to floor.\r\n",
			(pdCOMMAND_LINE_CALLBACK)prvSendToFloor,
			1};
			
static const CLI_Command_Definition_t xEmergStop = {"ES",
			"\r\nES: Emergency Stop.\r\n",
			(pdCOMMAND_LINE_CALLBACK)prvEmergencyStop,
			0};

static const CLI_Command_Definition_t xEmergClear = {"ER",
			"\r\nER: Emergency Clear.\r\n",
			(pdCOMMAND_LINE_CALLBACK)prvEmergencyClear,
			0};

//Function definitions for CMD functionality
portBASE_TYPE prvTaskStatsCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString)
{
    sprintf(pcWriteBuffer, taskListHdr);
    pcWriteBuffer += strlen(taskListHdr);
    vTaskList(pcWriteBuffer);
	xQueueSendToBack(TxQueue,&pcWriteBuffer,portMAX_DELAY);
    return pdFALSE;
}

portBASE_TYPE prvChangeMaxSpeed(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString)
{
	char *maxSpeedRx;
	BaseType_t maxSpeedRxStringLength;
	
	maxSpeedRx = FreeRTOS_CLIGetParameter(pcCommandString, 1, &maxSpeedRxStringLength);
	
	maxSpeedRx[maxSpeedRxStringLength] = '\0';
	
	MaxSpeed = atoi(maxSpeedRx);
	
	return pdFALSE;
}

portBASE_TYPE prvChangeAcceleration(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString)
{
	char *accelRx;
	BaseType_t accelRxStringLength;
	
	accelRx = FreeRTOS_CLIGetParameter(pcCommandString, 1, &accelRxStringLength);
	
	accelRx[accelRxStringLength] = '\0';
	
	Acceleration = atoi(accelRx);
	
	return pdFALSE;
}

portBASE_TYPE prvSendToFloor(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString)
{
	char *floorNumRx;
	BaseType_t floorNumRxStringLength;
	
	floorNumRx = FreeRTOS_CLIGetParameter(pcCommandString, 1, &floorNumRxStringLength);
	
	floorNumRx[floorNumRxStringLength] = '\0';
	
	int floorNum = atoi(floorNumRx);
	
	ElevatorInfo_s tempElevatorInfo = {floorNum,SEND_TO_FLOOR};
	
	xQueueSendToBack(ElevatorQueue,&tempElevatorInfo,portMAX_DELAY);
	
	return pdFALSE;
}

portBASE_TYPE prvEmergencyStop(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString)
{
	ElevatorInfo_s testElevatorInfo = {0,EM_STOP};
	xQueueSendToBack(ElevatorQueue,&testElevatorInfo,portMAX_DELAY);	
	return pdFALSE;
}

portBASE_TYPE prvEmergencyClear(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString)
{
	ElevatorInfo_s testElevatorInfo = {0,EM_CLEAR};
	xQueueSendToBack(ElevatorQueue,&testElevatorInfo,portMAX_DELAY);
	return pdFALSE;
}

void RegisterCommands()
{
	FreeRTOS_CLIRegisterCommand(&xTaskStatsCommand);
	FreeRTOS_CLIRegisterCommand(&xChangeMaxSpeed);
	FreeRTOS_CLIRegisterCommand(&xChangeAcceleration);
	FreeRTOS_CLIRegisterCommand(&xSendFloor);
	FreeRTOS_CLIRegisterCommand(&xEmergStop);
	FreeRTOS_CLIRegisterCommand(&xEmergClear);
}