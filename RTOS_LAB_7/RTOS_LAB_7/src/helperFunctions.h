/*
 * helperFunctions.h
 *
 * Created: 2/7/2023 8:58:15 AM
 *  Author: michael.bottita
 */ 

#ifndef HELPERFUNCTIONS_H_
#define HELPERFUNCTIONS_H_

xQueueHandle TxQueue;
xQueueHandle RxQueue;
xQueueHandle ElevatorQueue;

TaskHandle_t buttonTaskHandle;

void initializeTasksAndQueues(void);
int checkElevatorInputs(char charRx);
void ElevatorStatusUpdate(void);
void elevatorDoorOpen(void);
void elevatorDoorClose(void);
void MotorFreq (void);
void ReachedDest(void);

#endif /* HELPERFUNCTIONS_H_ */