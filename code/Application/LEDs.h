/**********************************************************************************
 * [FILE NAME]: LEDs.c
 *
 * [AUTHOR]: Toka Zakaria Mohamed Ramadan
 *
 * [DATE CREATED]: Jul 27, 2021
 *
 * [Description]:
 ***********************************************************************************/

#ifndef LEDS_H_
#define LEDS_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

#define NUMBER_OF_LEDS              2

#define POSITIVE                    1
#define NEGATIVE                    2


#if NUMBER_OF_LEDS == 1


#define LED1_DIRECTION_PORT         DDRD
#define LED1_DATA_PORT              PORTD
#define LED1_PIN_PORT               PIND
#define LED1_OUTPUT_PIN              PD5

#define LED1_LOGIC                POSITIVE


#elif NUMBER_OF_LEDS == 2

#define LED1_DIRECTION_PORT         DDRD
#define LED1_DATA_PORT              PORTD
#define LED1_PIN_PORT               PIND
#define LED1_OUTPUT_PIN              PD5

#define LED1_LOGIC                POSITIVE


#define LED2_DIRECTION_PORT         DDRD
#define LED2_DATA_PORT              PORTD
#define LED2_PIN_PORT               PIND
#define LED2_OUTPUT_PIN              PD6

#define LED2_LOGIC                POSITIVE

#elif  NUMBER_OF_LEDS == 3

#define LED1_DIRECTION_PORT         DDRA
#define LED1_DATA_PORT              PORTA
#define LED1_PIN_PORT               PINA
#define LED1_OUTPUT_PIN              PA0

#define LED1_LOGIC                POSITIVE


#define LED2_DIRECTION_PORT         DDRA
#define LED2_DATA_PORT              PORTA
#define LED2_PIN_PORT               PINA
#define LED2_OUTPUT_PIN              PA0

#define LED2_LOGIC                POSITIVE


#define LED3_DIRECTION_PORT         DDRA
#define LED3_DATA_PORT              PORTA
#define LED3_PIN_PORT               PINA
#define LED3_OUTPUT_PIN              PA0

#define LED3_LOGIC                POSITIVE

#endif



typedef enum
{
	LED1, LED2, LED3, LED4, LED5
}LedNumber;

/**********************************************************************************
 * [Function Name]: LED_Init
 *
 * [Description]: function to initialize LEDs to configure its pins as
 *                output pins
 *
 * [Args]:         NONE
 *
 * [In]:           NONE
 *
 * [Out]:          NONE
 *
 * [Returns]:      NONE
 **********************************************************************************/
void LED_Init(void);
/**********************************************************************************
 * [Function Name]:  LED_ON
 *
 * [Description]:    function to turn on the required LED
 *
 * [Args]:           uint8 ledNumber
 *
 * [In]:            ledNumber: to take the number of LED which
 *                             required to be turned ON
 *
 * [Out]:              NONE
 *
 * [Returns]:          NONE
 **********************************************************************************/
void LED_ON(uint8 ledNumber);
/**********************************************************************************
 * [Function Name]:  LED_ON
 *
 * [Description]:    function to turn on the required LED
 *
 * [Args]:           uint8 ledNumber
 *
 * [In]:            ledNumber: to take the number of LED which
 *                             required to be turned ON
 *
 * [Out]:              NONE
 *
 * [Returns]:          NONE
 **********************************************************************************/
void LED_OFF(uint8 ledNumber);
/**********************************************************************************/

#endif /* LEDS_H_ */
