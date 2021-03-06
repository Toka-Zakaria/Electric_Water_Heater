/**********************************************************************************
 * [FILE NAME]: application_functions.c
 *
 * [AUTHOR]: Toka Zakaria Mohamed Ramadan
 *
 * [DATE CREATED]: Jul 27, 2021
 *
 * [Description]: Functions will be used in the Applications in MCU
 ***********************************************************************************/

#include"application_functions.h"

/***********************************************************************************
 *                             Application_Functions
 ***********************************************************************************/

/**********************************************************************************
 * [Function Name]: read_currentTemperature
 *
 * [Description]:  function to read the current temperature from ADC channel
 *
 * [Args]:         NONE
 *
 * [In]:           NONE
 *
 * [Out]:          uint32 temp
 *
 * [Returns]:      the value of the current temperature which is read from
 *                 temperature sensor
 **********************************************************************************/
uint32 read_currentTemperature(void)
{
	uint32 temp;

	/*
	 * Read channel two where the temperature sensor is connect
	 * the current value of the water temperature
	 */
	temp = ADC_readChannel(CHANNEL_NUMBER);
	/*
	 * Calculate the temperature from the ADC value
	 */
	temp = (uint32)((temp*150*5)/(1023*1.5));

	return temp;

}/*end of read temperature function*/
/**********************************************************************************
 * [Function Name]:     displayTemperature
 *
 * [Description]:      function to display the passed temperature to the
 *                     function on the 7-Segments
 *
 * [Args]:              uint32 currentTemp
 *
 * [In]:                currentTemp: to carry the value of the temperature
 *                                   which  wanted to display on 7-Segment
 *
 * [Out]:                NONE
 *
 * [Returns]:            NONE
 **********************************************************************************/
void displayTemperature(uint32 currentTemp)
{
	/*
	 * Enable Control selection lines of the segments
	 */
	SEGMENTS_CTRL_PORT_REG = (SEGMENTS_CTRL_PORT_REG & SEGMENTS_CTRL_MASK) | FIRST_SEGMENT_ENABLE_CTRL;
	SEGMENTS_PORT_REG =   (SEGMENTS_PORT_REG & SEGMENTS_MASK) | (((uint32)(currentTemp))%10);
	_delay_ms(SEGMENTS_CTRL_TIME);

	SEGMENTS_CTRL_PORT_REG = (SEGMENTS_CTRL_PORT_REG & SEGMENTS_CTRL_MASK) | SECOND_SEGMENT_ENABLE_CTRL;
	SEGMENTS_PORT_REG =   (SEGMENTS_PORT_REG & SEGMENTS_MASK) | (((uint32)(currentTemp))/10);
	_delay_ms(SEGMENTS_CTRL_TIME);

}/*End of display temperature function*/

/**********************************************************************************
 * [Function Name]:  disableSegments
 *
 * [Description]:    function to disable the 7-segments and turn it off
 *
 * [Args]:       NONE
 *
 * [In]:         NONE
 *
 * [Out]:        NONE
 *
 * [Returns]:    NONE
 **********************************************************************************/
void disableSegments(void)
{
	SEGMENTS_CTRL_PORT_REG = SEGMENTS_CTRL_PORT_REG & SEGMENTS_CTRL_MASK;
}
/**********************************************************************************
 * [Function Name]:   FlashingSegments
 *
 * [Description]:    function to flash the value of temperature on the 7-segments
 *
 * [Args]:           uint32 temperature
 *
 * [In]:             temperature: to carry the value of the temperature
 *                                which  wanted to flash on 7-Segment
 *
 * [Out]:            NONE
 *
 * [Returns]:        NONE
 **********************************************************************************/
void FlashingSegments(uint32 temperature)
{
	/*
	 * display the temperature
	 */
	displayTemperature(temperature);
	/*
	 * disable the temperature
	 */
	disableSegments();

	_delay_ms(FLASHING_TIME);
}
/**********************************************************************************
 * [Function Name]:   upFunc
 *
 * [Description]: function to be call back function for interrupt 0
 *
 * [Args]:            NONE
 *
 * [In]:              NONE
 *
 * [Out]:             NONE
 *
 * [Returns]:         NONE
 **********************************************************************************/
void upFunc(void)
{
	/*
	 * Change the state of g_upInterrupt_SWflag to be TRUE
	 * to inform the system that UP interrupt has occurred
	 */
	g_upInterrupt_SWflag = TRUE;
	/*
	 * return g_tick to its initial value be ready to
	 * count another MAXIMUM_NUMBER_OF_SECONDS to start seconds
	 * of displaying set temperature from initial value
	 */
	g_tick = INITIAL_VALUE;

	if(g_firstClick == FALSE)
	{
		/*
		 * Change the state of g_firstClick to be true to display the
		 * Initial set temperature value one time only in the begin of the
		 * program
		 */
		g_firstClick = TRUE;
	}
	else
	{
		/*
		 * Increasing the value of the temperature by INCREASE_VALUE
		 * every click on UP button
		 */
		g_setTemprature = g_setTemprature + INCREASE_VALUE;

		/*
		 * return the set temperature to its initial value
		 * when the increasing of set temperature exceed
		 * the MAXIMUM_SET_TEMPERATURE
		 */
		if(g_setTemprature > MAXIMUM_SET_TEMPERATURE)
		{
			g_setTemprature = INITIAL_SET_TEMPERATURE;
		}
	}
}
/**********************************************************************************
 * [Function Name]:   downFunc
 *
 * [Description]: function to be call back function for interrupt 1
 *
 * [Args]:            NONE
 *
 * [In]:              NONE
 *
 * [Out]:             NONE
 *
 * [Returns]:         NONE
 **********************************************************************************/
void downFunc(void)
{
	/*
	 * Change the state of g_downInterrupt_SWflag to be TRUE
	 * to inform the system that Down interrupt has occurred
	 */
	g_downInterrupt_SWflag = TRUE;
	/*
	 * return g_tick to its initial value be ready to
	 * count another MAXIMUM_NUMBER_OF_SECONDS
	 */
	g_tick = INITIAL_VALUE;

	if(g_firstClick == FALSE)
	{
		/*
		 * Change the state of g_firstClick to be true to display the
		 * Initial set temperature value one time only in the begin of the
		 * program
		 */
		g_firstClick = TRUE;
	}
	else
	{
		/*
		 * Decreasing the value of the temperature by DECREASE_VALUE
		 * every click on Down button
		 */
		g_setTemprature = g_setTemprature - DECREASE_VALUE;

		/*
		 * return the set temperature to its initial value
		 * when the decreasing of set temperature is below
		 * the MINIMUM_SET_TEMPERATURE
		 */
		if(g_setTemprature < MINIMUM_SET_TEMPERATURE)
		{
			g_setTemprature = INITIAL_SET_TEMPERATURE;
		}
	}
}
/**********************************************************************************
 * [Function Name]:  flashingTime
 *
 * [Description]:   function to be call back function for timer1
 *
 * [Args]:           NONE
 *
 * [In]:             NONE
 *
 * [Out]:            NONE
 *
 * [Returns]:        NONE
 **********************************************************************************/
void flashingTime(void)
{
	g_tick++;
}
/**********************************************************************************
 * [Function Name]: store_inMemory
 *
 * [Description]:   function to store the passed temperature to the
 *                  function in the external memory
 *
 * [Args]:           uint32 temperature
 *
 * [In]:             temperature: to carry the value of the temperature which
 *                                is required to store in external memory
 * [Out]:             NONE
 *
 * [Returns]:         NONE
 **********************************************************************************/
void store_inMemory(uint32 temperature)
{
	/*
	 * write the first digit of the temperature in
	 * the external memory
	 */
	EEPROM_writeByte(FIRST_ADDRESS_TO_STORE, temperature%10);
	/*
	 * wait some seconds to give the memory time to write
	 */
	_delay_ms(EEPROM_WRITE_DELAY_VALUE);
	/*
	 * write the second digit of the temperature in
	 * the external memory
	 */
	EEPROM_writeByte(SECOND_ADDRESS_TO_STORE, temperature/10);
	/*
	 * wait some seconds to give the memory time to write
	 */
	_delay_ms(EEPROM_WRITE_DELAY_VALUE);
}
/**********************************************************************************/
