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
	// EXT 1
	ioport_set_pin_dir(EXT1_LED_1_PIN,IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(EXT1_LED_2_PIN,IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(EXT1_LED_3_PIN,IOPORT_DIR_OUTPUT);
	
	// EXT 3
	ioport_set_pin_dir(EXT3_LED_1_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(EXT3_LED_2_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(EXT3_LED_3_PIN, IOPORT_DIR_OUTPUT);
	
	// EXT 1
	ioport_set_pin_level(EXT1_LED_1_PIN, EXT1_LED_1_ACTIVE);
	ioport_set_pin_level(EXT1_LED_2_PIN, EXT1_LED_2_ACTIVE);
	ioport_set_pin_level(EXT1_LED_3_PIN, EXT1_LED_3_ACTIVE);
	
	// EXT 3
	ioport_set_pin_level(EXT3_LED_1_PIN, EXT3_LED_1_INACTIVE);
	ioport_set_pin_level(EXT3_LED_2_PIN, EXT3_LED_2_INACTIVE);
	ioport_set_pin_level(EXT3_LED_3_PIN, EXT3_LED_3_INACTIVE);
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
		
		
		case 4:
		curr_state = ioport_get_pin_level(EXT3_LED_1_PIN);
		break;
		case 5:
		curr_state = ioport_get_pin_level(EXT3_LED_2_PIN);
		break;
		case 6:
		curr_state = ioport_get_pin_level(EXT3_LED_3_PIN);
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
*     Takes a number that corresponds to an LED and a value
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
		// EXT 1
		case 1:
		ioport_set_pin_level(EXT1_LED_1_PIN, level);
		break;
		
		case 2:
		ioport_set_pin_level(EXT1_LED_2_PIN, level);
		break;
		
		case 3:
		ioport_set_pin_level(EXT1_LED_3_PIN, level);
		break;
		
		// EXT 3
		case 4:
		ioport_set_pin_level(EXT3_LED_1_PIN, level);
		break;
		
		case 5:
		ioport_set_pin_level(EXT3_LED_2_PIN, level);
		break;
		
		case 6:
		ioport_set_pin_level(EXT3_LED_3_PIN, level);
		break;
		
		default:
		break;
	}
	
	return 0;
}

uint8_t toggleLED(uint8_t uiLedNum)
{
    switch(uiLedNum)
    {
        case 0:
            if(ioport_get_pin_level(LED_0_PIN) == LED_0_ACTIVE)
                ioport_set_pin_level(LED_0_PIN, LED_0_INACTIVE);
            else
                ioport_set_pin_level(LED_0_PIN, LED_0_ACTIVE);
            break;
        case 1:
            if(ioport_get_pin_level(EXT1_LED1_GPIO) == EXT1_LED1_ACTIVE_LEVEL)
                ioport_set_pin_level(EXT1_LED1_GPIO, EXT1_LED1_INACTIVE_LEVEL);
            else
                ioport_set_pin_level(EXT1_LED1_GPIO, EXT1_LED1_ACTIVE_LEVEL);
            break;
        case 2:
            if(ioport_get_pin_level(EXT1_LED2_GPIO) == EXT1_LED2_ACTIVE_LEVEL)
                ioport_set_pin_level(EXT1_LED2_GPIO, EXT1_LED2_INACTIVE_LEVEL);
            else
                ioport_set_pin_level(EXT1_LED2_GPIO, EXT1_LED2_ACTIVE_LEVEL);            
            break;
        case 3:
            if(ioport_get_pin_level(EXT1_LED3_GPIO) == EXT1_LED3_ACTIVE_LEVEL)
                ioport_set_pin_level(EXT1_LED3_GPIO, EXT1_LED3_INACTIVE_LEVEL);
            else
                ioport_set_pin_level(EXT1_LED3_GPIO, EXT1_LED3_ACTIVE_LEVEL);            
            break;    
        case 4:
            if(ioport_get_pin_level(EXT3_LED1_GPIO) == EXT3_LED1_ACTIVE_LEVEL)
                ioport_set_pin_level(EXT3_LED1_GPIO, EXT3_LED1_INACTIVE_LEVEL);
            else
                ioport_set_pin_level(EXT3_LED1_GPIO, EXT3_LED1_ACTIVE_LEVEL);
            break;
        case 5:
            if(ioport_get_pin_level(EXT3_LED2_GPIO) == EXT3_LED2_ACTIVE_LEVEL)
                ioport_set_pin_level(EXT3_LED2_GPIO, EXT3_LED3_INACTIVE_LEVEL);
            else
                ioport_set_pin_level(EXT3_LED2_GPIO, EXT3_LED2_ACTIVE_LEVEL);
            break;
        case 6:
            if(ioport_get_pin_level(EXT3_LED3_GPIO) == EXT3_LED3_ACTIVE_LEVEL)
                ioport_set_pin_level(EXT3_LED3_GPIO, EXT3_LED3_INACTIVE_LEVEL);
            else
                ioport_set_pin_level(EXT3_LED3_GPIO, EXT3_LED3_ACTIVE_LEVEL);
        break;
        
            default:
                return -1;
    }    
    return 0;
}