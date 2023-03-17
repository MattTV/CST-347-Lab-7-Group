/*************************************************************
* Author: Michael Bottita
* Filename: led_driver.h
* Date Created: 2/6/23
**************************************************************/

#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

void initializeLEDDriver(void);
uint8_t readLED(uint8_t uiLedNum);
uint8_t setLED(uint8_t uiLedNum, uint8_t uiLedValue);
void toggleLED(void * pvParameters);


#endif /* LED_DRIVER_H_ */