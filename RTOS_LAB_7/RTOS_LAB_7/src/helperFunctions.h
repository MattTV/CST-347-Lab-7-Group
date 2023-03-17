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
uint8_t checkElevatorInputs(char charRx);

#endif /* HELPERFUNCTIONS_H_ */