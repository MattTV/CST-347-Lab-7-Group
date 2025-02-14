/*************************************************************
* Author: Michael Bottita
* Filename: myTasks.h
* Date Created: 2/6/23
**************************************************************/


#ifndef MYTASKS_H_
#define MYTASKS_H_

#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include <queue.h>
#include <semphr.h>

#define MAX_MESSAGE 50
#define MAX_CLI_MESSAGE 300

#define CHANGE_MAX_SPEED 0
#define CHANGE_ACCEL	 1
#define SEND_TO_FLOOR    2
#define EM_STOP			 3
#define EM_CLEAR		 4
#define GD_FLOOR_CALL	 5
#define P1_DN_CALL		 6
#define P1_UP_CALL		 7
#define P2_CALL			 8

#define GND				 0
#define P1				 500
#define P2				 510

xQueueHandle QueueUart;
xQueueHandle Led1Queue1;
xQueueHandle Led2Queue1;
xQueueHandle Led3Queue1;
xQueueHandle Led1Queue3;
xQueueHandle Led2Queue3;
xQueueHandle Led3Queue3;

TaskHandle_t Led1TaskHandle;
TaskHandle_t Led2TaskHandle;
TaskHandle_t Led3TaskHandle;

int buttonState;

//Structure to hold Queue number, Led number, and the next task handle number
typedef struct {
	uint LEDnum;
	uint newDelay;
	} changeInfo_s;

typedef struct {
	uint8_t LedNum;
	uint8_t Delay;
} ToggleInfo_s;

typedef struct {
	int EL_helperVar;
	int EL_instruct;
	} ElevatorInfo_s;

typedef struct {
	int speed;
	int acceleration;
	int max_speed;
	int height;
	int max_height;
	int destination;
	bool isMoving;
	bool movingUp;
	bool doorOpen;
	bool eStop;
	} Elevator_s;

Elevator_s Elevator; 

//Function declarations
void TxTask (void * pvParameters);
void RxTask (void * pvParameters);
void UartTask (void * pvParameters);
void ElevatorTask (void * pvParameters);
void ButtonTask (void * pvParameters);
void taskLEDToggle (void * pvParameters);
void DisplayElevatorStatus(void);
void dirTask(void * pvParameters);

void taskHeartbeat (void * pvParameters);
#endif /* MYTASKS_H_ */