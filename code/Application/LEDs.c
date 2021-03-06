/**********************************************************************************
 * [FILE NAME]: LEDs.c
 *
 * [AUTHOR]: Toka Zakaria Mohamed Ramadan
 *
 * [DATE CREATED]: Jul 27, 2021
 *
 * [Description]: File contains the configuration of LEDs module
 ***********************************************************************************/



#include"LEDS.h"

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
void LED_Init(void)
{

#if NUMBER_OF_LEDS == 1

	/*configure the led as output pin*/
	LED1_DIRECTION_PORT = SET_BIT(LED1_DIRECTION_PORT, LED1_OUTPUT_PIN);


#elif NUMBER_OF_LEDS == 2

	/*configure the led as output pin*/
	LED1_DIRECTION_PORT = SET_BIT(LED1_DIRECTION_PORT, LED1_OUTPUT_PIN);
	/*configure the led as output pin*/
	LED2_DIRECTION_PORT = SET_BIT(LED2_DIRECTION_PORT, LED2_OUTPUT_PIN);


#elif NUMBER_OF_LEDS == 3

	/*configure the led as output pin*/
	LED1_DIRECTION_PORT = SET_BIT(LED1_DIRECTION_PORT, LED1_OUTPUT_PIN);
	/*configure the led as output pin*/
	LED2_DIRECTION_PORT = SET_BIT(LED2_DIRECTION_PORT, LED2_OUTPUT_PIN);
	/*configure the led as output pin*/
	LED3_DIRECTION_PORT = SET_BIT(LED3_DIRECTION_PORT, LED3_OUTPUT_PIN);

#endif

}/*end of Led_Init*/

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
void LED_ON(uint8 ledNumber)
{

	switch (ledNumber)
	{

#if NUMBER_OF_LEDS == 1

	case LED1:

#if LED1_LOGIC == POSITIVE

		LED1_DATA_PORT = SET_BIT(LED1_DATA_PORT, LED1_OUTPUT_PIN);
#else
		LED1_DATA_PORT = CLEAR_BIT(LED1_DATA_PORT, LED1_OUTPUT_PIN);

#endif
		break;

#elif NUMBER_OF_LEDS == 2

	case LED1:

#if LED1_LOGIC == POSITIVE

		LED1_DATA_PORT = SET_BIT(LED1_DATA_PORT, LED1_OUTPUT_PIN);
#else
		LED1_DATA_PORT = CLEAR_BIT(LED1_DATA_PORT, LED1_OUTPUT_PIN);

#endif
		break;

	case LED2:
#if LED2_LOGIC == POSITIVE

		LED2_DATA_PORT = SET_BIT(LED2_DATA_PORT, LED2_OUTPUT_PIN);
#else
		LED2_DATA_PORT = CLEAR_BIT(LED2_DATA_PORT, LED2_OUTPUT_PIN);

#endif
		break;



#elif NUMBER_OF_LEDS == 3

	case LED1:

#if LED1_LOGIC == POSITIVE

		LED1_DATA_PORT = SET_BIT(LED1_DATA_PORT, LED1_OUTPUT_PIN);
#else
		LED1_DATA_PORT = CLEAR_BIT(LED1_DATA_PORT, LED1_OUTPUT_PIN);

#endif
		break;

	case LED2:
#if LED2_LOGIC == POSITIVE

		LED2_DATA_PORT = SET_BIT(LED2_DATA_PORT, LED2_OUTPUT_PIN);
#else
		LED2_DATA_PORT = CLEAR_BIT(LED2_DATA_PORT, LED2_OUTPUT_PIN);

#endif
		break;

	case LED3:
#if LED3_LOGIC == POSITIVE

		LED3_DATA_PORT = SET_BIT(LED3_DATA_PORT, LED3_OUTPUT_PIN);
#else
		LED3_DATA_PORT = CLEAR_BIT(LED3_DATA_PORT, LED3_OUTPUT_PIN);

#endif
		break;
#endif

	}/*end of switch code*/
}/*end of LED_ON function*/


/**********************************************************************************
 * [Function Name]:  LED_ON
 *
 * [Description]:    function to turn on the required LED
 *
 * [Args]:           uint8 ledNumber
 *
 * [In]:            ledNumber: to take the number of LED which
 *                             required to be turned OFF
 *
 * [Out]:              NONE
 *
 * [Returns]:          NONE
 **********************************************************************************/
void LED_OFF(uint8 ledNumber)
{

	switch (ledNumber)
	{

#if NUMBER_OF_LEDS == 1

	case LED1:

#if LED1_LOGIC == POSITIVE

		LED1_DATA_PORT = CLEAR_BIT(LED1_DATA_PORT, LED1_OUTPUT_PIN);
#else
		LED1_DATA_PORT = SET_BIT(LED1_DATA_PORT, LED1_OUTPUT_PIN);

#endif
		break;

#elif NUMBER_OF_LEDS == 2

	case LED1:

#if LED1_LOGIC == POSITIVE

		LED1_DATA_PORT = CLEAR_BIT(LED1_DATA_PORT, LED1_OUTPUT_PIN);
#else
		LED1_DATA_PORT = SET_BIT(LED1_DATA_PORT, LED1_OUTPUT_PIN);

#endif
		break;

	case LED2:
#if LED2_LOGIC == POSITIVE

		LED2_DATA_PORT = CLEAR_BIT(LED2_DATA_PORT, LED2_OUTPUT_PIN);
#else
		LED2_DATA_PORT = SET_BIT(LED2_DATA_PORT, LED2_OUTPUT_PIN);

#endif
		break;

#elif NUMBER_OF_LEDS == 3

	case LED1:

#if LED1_LOGIC == POSITIVE

		LED1_DATA_PORT = CLEAR_BIT(LED1_DATA_PORT, LED1_OUTPUT_PIN);
#else
		LED1_DATA_PORT = SET_BIT(LED1_DATA_PORT, LED1_OUTPUT_PIN);

#endif
		break;

	case LED2:
#if LED2_LOGIC == POSITIVE

		LED2_DATA_PORT = CLEAR_BIT(LED2_DATA_PORT, LED2_OUTPUT_PIN);
#else
		LED2_DATA_PORT = SET_BIT(LED2_DATA_PORT, LED2_OUTPUT_PIN);

#endif
		break;

	case LED3:
#if LED3_LOGIC == POSITIVE

		LED3_DATA_PORT = CLEAR_BIT(LED3_DATA_PORT, LED3_OUTPUT_PIN);
#else
		LED3_DATA_PORT = SET_BIT(LED3_DATA_PORT, LED3_OUTPUT_PIN);

#endif
		break;
#endif

	}/*end of switch code*/
}/*end of LED_ON function*/










