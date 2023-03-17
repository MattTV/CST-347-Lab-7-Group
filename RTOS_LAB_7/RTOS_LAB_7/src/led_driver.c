/*************************************************************
* Author: Michael Bottita
* Filename: led_driver.c
* Date Created: 2/6/23
**************************************************************/

#include <asf.h>
#include <stdbool.h>
#include "myTasks.h"
#include "FreeRTOS.h"
#include "task.h"
#include "OITExpansionBoard.h"
#include "OITExpansionBoardDefines.h"
#include "led_driver.h"
#include "helperFunctions.h"

/**********************************************************************
* Purpose: This function initializes the LEDs
*
* Precondition:
*     None
*
* Postcondition:
*      None
*
************************************************************************/
void initializeLEDDriver(void)
{
	ioport_set_pin_dir(EXT1_LED_1_PIN,IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(EXT1_LED_2_PIN,IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(EXT1_LED_3_PIN,IOPORT_DIR_OUTPUT);
	
	ioport_set_pin_level(EXT1_LED_1_PIN, EXT1_LED_1_INACTIVE);
	ioport_set_pin_level(EXT1_LED_2_PIN, EXT1_LED_2_INACTIVE);
	ioport_set_pin_level(EXT1_LED_3_PIN, EXT1_LED_3_INACTIVE);
}

/**********************************************************************
* Purpose: This function reads the status of the current GPIO
*
* Precondition:
*     Takes a number that corresponds to an LED
*
* Postcondition:
*      Returns true or false
*
************************************************************************/
uint8_t readLED(uint8_t uiLedNum)
{
	uint8_t curr_state = 0;
	switch (uiLedNum)
	{
		case 0:
			curr_state = ioport_get_pin_level(LED_0_PIN);
			break;
			
		case 1:
			curr_state = ioport_get_pin_level(EXT1_LED_1_PIN);
			break;
			
		case 2:
			curr_state = ioport_get_pin_level(EXT1_LED_2_PIN);
			break;
			
		case 3:
			curr_state = ioport_get_pin_level(EXT1_LED_3_PIN);
			break;
			
		default:
			break;
	}
	return curr_state;
}

/**********************************************************************
* Purpose: This function sets the status of the current GPIO
*
* Precondition:
*     Takes a number that corresponds to an LED and a valu
*
* Postcondition:
*      Sets the GPIO to the current uiLedValue
*
************************************************************************/
uint8_t setLED(uint8_t uiLedNum, uint8_t uiLedValue)
{
	bool level = uiLedValue;
	
	switch (uiLedNum)
	{
		case 1:
			ioport_set_pin_level(EXT1_LED_1_PIN, level);
			break;
		
		case 2:
			ioport_set_pin_level(EXT1_LED_2_PIN, level);
			break;
		
		case 3:
			ioport_set_pin_level(EXT1_LED_3_PIN, level);
			break;
			
		default:
			break;
	}
	
	return 0;
}