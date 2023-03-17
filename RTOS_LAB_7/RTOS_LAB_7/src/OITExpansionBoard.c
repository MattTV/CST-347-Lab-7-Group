/*************************************************************
* Author: Michael Bottita
* Filename: OITExpansionBoard.c
* Date Created: 2/6/23
**************************************************************/
#include <asf.h>
#include "OITExpansionBoard.h"

#ifdef OIT_LED_FULL_BOARD_EXT1
static void InitLEDFullBoardExt1(void);
#endif
#ifdef OIT_LED_FULL_BOARD_EXT3
static void InitLEDFullBoardExt3(void);
#endif
#ifdef OIT_BTN_FULL_BAORD_EXT1
static void InitBtnFullBoardExt1(void);
#endif
#ifdef OIT_BTN_FULL_BAORD_EXT3
static void InitBtnFullBoardExt3(void);
#endif
#ifdef OIT_5LED_4BTN_BOARD_EXT1
static void Init5Led4BtnBoardExt1(void);
#endif
#ifdef OIT_5LED_4BTN_BOARD_EXT3
static void Init5Led4BtnBoardExt3(void);
#endif
#ifdef OIT_4LED_5BTN_BOARD_EXT1
static void Init4Led5BtnBoardExt1(void);
#endif
#ifdef OIT_4LED_5BTN_BOARD_EXT3
static void Init4Led5BtnBoardExt3(void);
#endif


/**
 * \brief Set input mode for one single IOPORT pin.
 * It will configure port mode and disable pin mode (but enable peripheral).
 * \param pin IOPORT pin to configure
 * \param mode Mode masks to configure for the specified pin (\ref ioport_modes)
 * \param sense Sense for interrupt detection (\ref ioport_sense)
 */
#define ioport_set_pin_input_mode(pin, mode, sense) \
	do {\
		ioport_set_pin_dir(pin, IOPORT_DIR_INPUT);\
		ioport_set_pin_mode(pin, mode);\
		ioport_set_pin_sense_mode(pin, sense);\
	} while (0)


void OITExpansionBoardInit(void)
{
#ifdef OIT_LED_FULL_BOARD_EXT1
	InitLEDFullBoardExt1();
#endif
	
#ifdef OIT_LED_FULL_BOARD_EXT3
	InitLEDFullBoardExt3();
#endif
	
#ifdef OIT_BTN_FULL_BAORD_EXT1
	InitLEDFullBoardExt1();
#endif
	
#ifdef OIT_BTN_FULL_BAORD_EXT3
	InitLEDFullBoardExt3();
#endif
#ifdef OIT_5LED_4BTN_BOARD_EXT1
	Init5Led4BtnBoardExt1();
#endif
#ifdef OIT_5LED_4BTN_BOARD_EXT3
	Init5Led4BtnBoardExt3();
#endif
#ifdef OIT_4LED_5BTN_BOARD_EXT1
	Init4Led5BtnBoardExt1();
#endif
#ifdef OIT_4LED_5BTN_BOARD_EXT3
	Init4Led5BtnBoardExt3();
#endif
}

#ifdef OIT_LED_FULL_BOARD_EXT1
static void InitLEDFullBoardExt1(void)
{
	ioport_set_pin_dir(EXT1_LED1_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT1_LED1_GPIO, EXT1_LED1_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT1_LED2_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT1_LED2_GPIO, EXT1_LED2_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT1_LED3_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT1_LED3_GPIO, EXT1_LED3_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT1_LED4_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT1_LED4_GPIO, EXT1_LED4_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT1_LED5_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT1_LED5_GPIO, EXT1_LED5_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT1_LED6_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT1_LED6_GPIO, EXT1_LED6_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT1_LED7_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT1_LED7_GPIO, EXT1_LED7_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT1_LED8_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT1_LED8_GPIO, EXT1_LED8_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT1_LED9_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT1_LED9_GPIO, EXT1_LED9_INACTIVE_LEVEL);	
}
#endif

#ifdef OIT_LED_FULL_BOARD_EXT3
static void InitLEDFullBoardExt3(void)
{
	ioport_set_pin_dir(EXT3_LED1_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT3_LED1_GPIO, EXT3_LED1_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT3_LED2_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT3_LED2_GPIO, EXT3_LED2_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT3_LED3_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT3_LED3_GPIO, EXT3_LED3_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT3_LED4_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT3_LED4_GPIO, EXT3_LED4_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT3_LED5_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT3_LED5_GPIO, EXT3_LED5_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT3_LED6_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT3_LED6_GPIO, EXT3_LED6_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT3_LED7_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT3_LED7_GPIO, EXT3_LED7_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT3_LED8_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT3_LED8_GPIO, EXT3_LED8_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT3_LED9_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT3_LED9_GPIO, EXT3_LED9_INACTIVE_LEVEL);
}
#endif

#ifdef OIT_BTN_FULL_BAORD_EXT1
static void InitBtnFullBoardExt1(void)
{
	ioport_set_pin_input_mode(EXT1_PUSH_BUTTON_1, EXT1_PUSH_BUTTON_1_FLAGS, EXT1_PUSH_BUTTON_1_SENSE);
	ioport_set_pin_input_mode(EXT1_PUSH_BUTTON_2, EXT1_PUSH_BUTTON_2_FLAGS, EXT1_PUSH_BUTTON_2_SENSE);
	ioport_set_pin_input_mode(EXT1_PUSH_BUTTON_3, EXT1_PUSH_BUTTON_3_FLAGS, EXT1_PUSH_BUTTON_3_SENSE);
	ioport_set_pin_input_mode(EXT1_PUSH_BUTTON_4, EXT1_PUSH_BUTTON_4_FLAGS, EXT1_PUSH_BUTTON_4_SENSE);
	ioport_set_pin_input_mode(EXT1_PUSH_BUTTON_5, EXT1_PUSH_BUTTON_5_FLAGS, EXT1_PUSH_BUTTON_5_SENSE);
	ioport_set_pin_input_mode(EXT1_PUSH_BUTTON_6, EXT1_PUSH_BUTTON_6_FLAGS, EXT1_PUSH_BUTTON_6_SENSE);
	ioport_set_pin_input_mode(EXT1_PUSH_BUTTON_7, EXT1_PUSH_BUTTON_7_FLAGS, EXT1_PUSH_BUTTON_7_SENSE);
	ioport_set_pin_input_mode(EXT1_PUSH_BUTTON_8, EXT1_PUSH_BUTTON_8_FLAGS, EXT1_PUSH_BUTTON_8_SENSE);
	ioport_set_pin_input_mode(EXT1_PUSH_BUTTON_9, EXT1_PUSH_BUTTON_9_FLAGS, EXT1_PUSH_BUTTON_9_SENSE);
}
#endif

#ifdef OIT_BTN_FULL_BAORD_EXT3
static void InitBtnFullBoardExt3(void)
{
	ioport_set_pin_input_mode(EXT3_PUSH_BUTTON_1, EXT3_PUSH_BUTTON_1_FLAGS, EXT3_PUSH_BUTTON_1_SENSE);
	ioport_set_pin_input_mode(EXT3_PUSH_BUTTON_2, EXT3_PUSH_BUTTON_2_FLAGS, EXT3_PUSH_BUTTON_2_SENSE);
	ioport_set_pin_input_mode(EXT3_PUSH_BUTTON_3, EXT3_PUSH_BUTTON_3_FLAGS, EXT3_PUSH_BUTTON_3_SENSE);
	ioport_set_pin_input_mode(EXT3_PUSH_BUTTON_4, EXT3_PUSH_BUTTON_4_FLAGS, EXT3_PUSH_BUTTON_4_SENSE);
	ioport_set_pin_input_mode(EXT3_PUSH_BUTTON_5, EXT3_PUSH_BUTTON_5_FLAGS, EXT3_PUSH_BUTTON_5_SENSE);
	ioport_set_pin_input_mode(EXT3_PUSH_BUTTON_6, EXT3_PUSH_BUTTON_6_FLAGS, EXT3_PUSH_BUTTON_6_SENSE);
	ioport_set_pin_input_mode(EXT3_PUSH_BUTTON_7, EXT3_PUSH_BUTTON_7_FLAGS, EXT3_PUSH_BUTTON_7_SENSE);
	ioport_set_pin_input_mode(EXT3_PUSH_BUTTON_8, EXT3_PUSH_BUTTON_8_FLAGS, EXT3_PUSH_BUTTON_8_SENSE);
	ioport_set_pin_input_mode(EXT3_PUSH_BUTTON_9, EXT3_PUSH_BUTTON_9_FLAGS, EXT3_PUSH_BUTTON_9_SENSE);
}
#endif

#ifdef OIT_5LED_4BTN_BOARD_EXT1
static void Init5Led4BtnBoardExt1(void)
{
	ioport_set_pin_dir(EXT1_LED1_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT1_LED1_GPIO, EXT1_LED1_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT1_LED2_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT1_LED2_GPIO, EXT1_LED2_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT1_LED3_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT1_LED3_GPIO, EXT1_LED3_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT1_LED4_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT1_LED4_GPIO, EXT1_LED4_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT1_LED5_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT1_LED5_GPIO, EXT1_LED5_INACTIVE_LEVEL);
	
	ioport_set_pin_input_mode(EXT1_PUSH_BUTTON_6, EXT1_PUSH_BUTTON_6_FLAGS, EXT1_PUSH_BUTTON_6_SENSE);
	ioport_set_pin_input_mode(EXT1_PUSH_BUTTON_7, EXT1_PUSH_BUTTON_7_FLAGS, EXT1_PUSH_BUTTON_7_SENSE);
	ioport_set_pin_input_mode(EXT1_PUSH_BUTTON_8, EXT1_PUSH_BUTTON_8_FLAGS, EXT1_PUSH_BUTTON_8_SENSE);
	ioport_set_pin_input_mode(EXT1_PUSH_BUTTON_9, EXT1_PUSH_BUTTON_9_FLAGS, EXT1_PUSH_BUTTON_9_SENSE);
}
#endif

#ifdef OIT_5LED_4BTN_BOARD_EXT3
static void Init5Led4BtnBoardExt3(void)
{
	ioport_set_pin_dir(EXT3_LED1_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT3_LED1_GPIO, EXT3_LED1_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT3_LED2_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT3_LED2_GPIO, EXT3_LED2_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT3_LED3_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT3_LED3_GPIO, EXT3_LED3_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT3_LED4_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT3_LED4_GPIO, EXT3_LED4_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT3_LED5_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT3_LED5_GPIO, EXT3_LED5_INACTIVE_LEVEL);
	
	ioport_set_pin_input_mode(EXT3_PUSH_BUTTON_6, EXT3_PUSH_BUTTON_6_FLAGS, EXT3_PUSH_BUTTON_6_SENSE);
	ioport_set_pin_input_mode(EXT3_PUSH_BUTTON_7, EXT3_PUSH_BUTTON_7_FLAGS, EXT3_PUSH_BUTTON_7_SENSE);
	ioport_set_pin_input_mode(EXT3_PUSH_BUTTON_8, EXT3_PUSH_BUTTON_8_FLAGS, EXT3_PUSH_BUTTON_8_SENSE);
	ioport_set_pin_input_mode(EXT3_PUSH_BUTTON_9, EXT3_PUSH_BUTTON_9_FLAGS, EXT3_PUSH_BUTTON_9_SENSE);
}
#endif

#ifdef OIT_4LED_5BTN_BOARD_EXT1
static void Init4Led5BtnBoardExt1(void)
{
	ioport_set_pin_dir(EXT1_LED1_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT1_LED1_GPIO, EXT1_LED1_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT1_LED2_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT1_LED2_GPIO, EXT1_LED2_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT1_LED3_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT1_LED3_GPIO, EXT1_LED3_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT1_LED4_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT1_LED4_GPIO, EXT1_LED4_INACTIVE_LEVEL);
	
	ioport_set_pin_input_mode(EXT1_PUSH_BUTTON_5, EXT1_PUSH_BUTTON_5_FLAGS, EXT1_PUSH_BUTTON_5_SENSE);
	ioport_set_pin_input_mode(EXT1_PUSH_BUTTON_6, EXT1_PUSH_BUTTON_6_FLAGS, EXT1_PUSH_BUTTON_6_SENSE);
	ioport_set_pin_input_mode(EXT1_PUSH_BUTTON_7, EXT1_PUSH_BUTTON_7_FLAGS, EXT1_PUSH_BUTTON_7_SENSE);
	ioport_set_pin_input_mode(EXT1_PUSH_BUTTON_8, EXT1_PUSH_BUTTON_8_FLAGS, EXT1_PUSH_BUTTON_8_SENSE);
	ioport_set_pin_input_mode(EXT1_PUSH_BUTTON_9, EXT1_PUSH_BUTTON_9_FLAGS, EXT1_PUSH_BUTTON_9_SENSE);
}
#endif

#ifdef OIT_4LED_5BTN_BOARD_EXT3
static void Init4Led5BtnBoardExt3(void)
{
	ioport_set_pin_dir(EXT3_LED1_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT3_LED1_GPIO, EXT3_LED1_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT3_LED2_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT3_LED2_GPIO, EXT3_LED2_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT3_LED3_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT3_LED3_GPIO, EXT3_LED3_INACTIVE_LEVEL);
	
	ioport_set_pin_dir(EXT3_LED4_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(EXT3_LED4_GPIO, EXT3_LED4_INACTIVE_LEVEL);
	
	ioport_set_pin_input_mode(EXT3_PUSH_BUTTON_5, EXT3_PUSH_BUTTON_5_FLAGS, EXT3_PUSH_BUTTON_5_SENSE);
	ioport_set_pin_input_mode(EXT3_PUSH_BUTTON_6, EXT3_PUSH_BUTTON_6_FLAGS, EXT3_PUSH_BUTTON_6_SENSE);
	ioport_set_pin_input_mode(EXT3_PUSH_BUTTON_7, EXT3_PUSH_BUTTON_7_FLAGS, EXT3_PUSH_BUTTON_7_SENSE);
	ioport_set_pin_input_mode(EXT3_PUSH_BUTTON_8, EXT3_PUSH_BUTTON_8_FLAGS, EXT3_PUSH_BUTTON_8_SENSE);
	ioport_set_pin_input_mode(EXT3_PUSH_BUTTON_9, EXT3_PUSH_BUTTON_9_FLAGS, EXT3_PUSH_BUTTON_9_SENSE);
}
#endif