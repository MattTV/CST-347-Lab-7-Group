/*************************************************************
*
* Lab/Assignment: Lab 5 � Led Control with Interrupts
*
* Overview:
* This program toggles leds based on UART control
*
* Input:
* The input is controlled by the UART and the output is
* on the UART screen
*
************************************************************/

//system includes
#include <asf.h>
#include <stdint.h>
#include <stdbool.h>

// FreeRTOS Includes
#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include <queue.h>
#include <semphr.h>

// My Includes
#include "OITExpansionBoard.h"
#include "myTasks.h"
#include "led_driver.h"
#include "helperFunctions.h"
#include "controlCLI.h"

// Defines
#if( BOARD == SAM4E_XPLAINED_PRO )
	// Used to place the heap
	#define mainHEAP_START		_estack
	#define mainRAM_LENGTH		0x00020000	/* 128 KB of internal SRAM. */
	#define mainRAM_START		0x20000000	/* at 0x20000000 */
	/* The SAM4E Xplained board has 2 banks of external SRAM, each one 512KB. */
	#define mainEXTERNAL_SRAM_SIZE		( 512ul * 1024ul )
#else
	#error Define memory regions here.
#endif /* SAM4E_XPLAINED_PRO */

// Function prototypes
static void prvMiscInitialisation( void );
static void prvInitialiseHeap( void );

// Used to place the heap
extern char _estack;

/**********************************************************************
* Purpose: This function is the main control for the program
*
************************************************************************/
int main ( void )
{
	// Initialize The Board
	prvMiscInitialisation();
	
	//Init all tasks and queues
	initializeTasksAndQueues();
	
	//Register Commands
	RegisterCommands();
	
	// Start The Scheduler
	vTaskStartScheduler();
	
	while( true )
	{
		elevatorDoorOpen();
		elevatorDoorClose();
	}
}

static void prvMiscInitialisation( void )
{
	/* Initialize the SAM system */
	sysclk_init();
	board_init();
	prvInitialiseHeap();
	
	pmc_enable_periph_clk(ID_PIOA);
	pmc_enable_periph_clk(ID_PIOB);
	
	OITExpansionBoardInit();
	initializeLEDDriver();
}

static void prvInitialiseHeap( )
{
	uint32_t ulHeapSize;
	uint8_t *pucHeapStart, *pucHeapEnd;

	pucHeapStart = ( uint8_t * ) ( ( ( ( uint32_t ) &mainHEAP_START ) + 7 ) & ~0x07ul );
	pucHeapEnd = ( uint8_t * ) ( mainRAM_START + mainRAM_LENGTH );

	ulHeapSize = ( uint32_t ) ( ( uint32_t ) pucHeapEnd - ( uint32_t ) &mainHEAP_START );
	ulHeapSize &= ~0x07ul;
	ulHeapSize -= 1024;

	HeapRegion_t xHeapRegions[] = {
		{ ( unsigned char *) pucHeapStart, ulHeapSize },
		{ ( unsigned char *) SRAM_BASE_ADDRESS, mainEXTERNAL_SRAM_SIZE },
		{ ( unsigned char *) SRAM_BASE_ADDRESS_2ND, mainEXTERNAL_SRAM_SIZE },
		{ NULL, 0 }
	};

	vPortDefineHeapRegions( xHeapRegions );
}

void vAssertCalled( const char *pcFile, uint32_t ulLine )
{
	volatile uint32_t ulBlockVariable = 0UL;
	
	/* Setting ulBlockVariable to a non-zero value in the debugger will allow
	this function to be exited. */
	taskDISABLE_INTERRUPTS();
	{
		while( ulBlockVariable == 0UL )
		{
			__asm volatile( "NOP" );
		}
	}
	taskENABLE_INTERRUPTS();
}

void vApplicationMallocFailedHook( void )
{
	/* Called if a call to pvPortMalloc() fails because there is insufficient
	free memory available in the FreeRTOS heap.  pvPortMalloc() is called
	internally by FreeRTOS API functions that create tasks, queues, software
	timers, and semaphores.  The size of the FreeRTOS heap is set by the
	configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
	vAssertCalled( __FILE__, __LINE__ );
}

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}