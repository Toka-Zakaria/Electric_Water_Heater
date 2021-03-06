/**********************************************************************************
 * [FILE NAME]: main.c
 *
 * [AUTHOR]: Toka Zakaria Mohamed Ramadan
 *
 * [DATE CREATED]: Jul 27, 2021
 *
 * [Description]:
 ***********************************************************************************/

#include"application_functions.h"

/*
 * Variable to use it to store the value of the temperature
 * in the setting temperature mode, global to be able to
 *  use it in interrupt functions in another file
 */
uint32 g_setTemprature= INITIAL_SET_TEMPERATURE;

/*
 * Variable to use in timer interrupt function
 * it that every increment act as on second, global to be
 *  able to use it in interrupt functions in another file
 */
uint8 g_tick = INITIAL_VALUE;
/*
 * Variable to check if it is the first time to
 * press on down or up buttons or notglobal to be
 *  able to use it in interrupt functions in another file
 */
bool g_firstClick = FALSE;
/*
 * Variable to check if the set callback function of
 * UP button interrupt called or not, global to be
 *  able to use it in interrupt functions in another file
 */
bool g_upInterrupt_SWflag = FALSE;
/*
 * Variable to check if the set callback function of
 * down button interrupt called or not, global to be
 *  able to use it in interrupt functions in another file
 */
bool g_downInterrupt_SWflag= FALSE;

int main()
{
	/*******************************************************************************
	 *                    Variable Declaration and Definitions                     *
	 *******************************************************************************/
	/*
	 * local variable to check if the current press is On or off
	 */
	uint8 OnOff_ModeCheck = OFF_STATE;
	/*
	 * local variable to use it with on/off button to make sure that the
	 * functionality is done one time while pressing the button
	 */
	uint8 OnOFF_swFlag = FALSE_STATE;
	/*
	 * Variable to carry the value of zeros of the
	 * stored temperature after reading it from EEPROM
	 */
	uint8 temperatureZero = INITIAL_VALUE;
	/*
	 * Variable to carry the value of tens of the
	 * stored temperature after reading it from EEPROM
	 */
	uint8 temperatureTens = INITIAL_VALUE;
	/*
	 * Variable to carry the value of the
	 * stored temperature after reading it from EEPROM and after
	 * calculates it from temperatureZero and temperatureTens
	 */
	uint32 storedTemperature = INITIAL_VALUE;
	/*
	 * Variable to use it to manage displaying the
	 * stored temperature to be one time only
	 * in the first of ON State
	 */
	bool eepromFlag = FALSE;
	/*
	 * Variable to carry the current temperature which
	 * be read from Temperature sensor
	 */
	uint32 current_temperature = INITIAL_VALUE;
	/*
	 * Define a structure to configure the timer module to be
	 * able to count
	 */
	Timer_ConfigType time = {INITIAL_VALUE,COMPARE_VALUE,NONE, Timer1, F_CPU_1024, Compare, Disconnected, ChannelA};
	/*
	 * Configure the Callback function of timer to do
	 * a specific functionality every interrupt occurrence
	 */
	Timer_setCallBack(flashingTime, Timer1);
	/*
	 * Define a structure to configure the interrupt0
	 * module to be able to count
	 */
	External_Interrupt_ConfigType up = {INTERRUPT0, Falling};
	/*
	 * Define a structure to configure the interrupt1
	 * module to be able to count
	 */
	External_Interrupt_ConfigType down = {INTERRUPT1, Falling};
	/*
	 * Configure the Callback function of interrupt 0 to do
	 * a specific functionality every interrupt occurrence
	 */
	Interrupt_setCallBack(upFunc, INTERRUPT0);
	/*
	 * Configure the Callback function of interrupt 1 to do
	 * a specific functionality every interrupt occurrence
	 */
	Interrupt_setCallBack(downFunc, INTERRUPT1);
	/*******************************************************************************
	 *                             Modules Initialization                          *
	 *******************************************************************************/
	/*
	 *Configure ON OFF button as input pin
	 */
	ON_OFF_BUTTON_DIRECTION_REG = CLEAR_BIT(ON_OFF_BUTTON_DIRECTION_REG, ON_OFF_BUTTON_INPUT_PIN);
	/*
	 * Enable PULL Up for ON/OFF Button
	 */
	ON_OFF_BUTTON_PORT_REG = SET_BIT(ON_OFF_BUTTON_PORT_REG, ON_OFF_BUTTON_INPUT_PIN);
	/*
	 *Configure 7-segments pins as output pins
	 */
	SEGMENTS_DIRECTION_REG |=  SEGMENTS_MASK_TO_BE_OUTPUT;
	/*
	 * Configure Control selection lines of the segments as output pins
	 */
	SEGMENTS_CTRL_DIRECTION_REG |= SGMENTS_CTRL_MASK_TO_BE_OUTPUT;
	/*
	 * Disable Control selection lines of the segments at the beginning of the program to make segments off
	 */
	SEGMENTS_CTRL_PORT_REG &= SEGMENTS_CTRL_MASK;
	/*
	 * Set the first value on the segments by 0
	 */
	SEGMENTS_PORT_REG &=  SEGMENTS_MASK;
	/*
	 * Configure the pin of the temperature sensor  as input pin
	 */
	TEMP_SENSOR_DIRECTION_REG = SET_BIT(TEMP_SENSOR_DIRECTION_REG, TEMP_SENSOR_INPUT_PIN);
	/**************************************************************************************/
	/*
	 * Initialize the External EEPROM to be ready to work
	 */
	EEPROM_init();
	/*
	 * Initialize Analog to Digital Converter to be ready to work
	 */
	ADC_init();
	/*
	 * Initialize DC motor to be ready to work
	 */
	DC_motor_Init();
	/*
	 * Initialize LEDs to be ready to work
	 */
	LED_Init();
	/*
	 * Initialize Interrupt 0 to be ready to work
	 */
	External_Interrupt_init(&up);
	/*
	 * Initialize Interrupt 1 to be ready to work
	 */
	External_Interrupt_init(&down);
	/*
	 * Initialize timer 1 to be ready to work
	 */
	Timer_init(&time);
	/*
	 * Stop the clock of the timer
	 */
	Timer_stop(Timer1);
	/*
	 * Enable Global Interrupt
	 */
	SREG = SET_BIT(SREG, I_BIT);

	/*******************************************************************************
	 *                             Initial Start mode                               *
	 *******************************************************************************/
	/*
	 * stop the motor in the start of the program
	 */
	DC_motor_on_Stop();
	/*
	 * Turn OFF cooling LED in the begin of the program
	 */
	LED_OFF(LED1);
	/*
	 * Turn OFF heating LED in the begin of the program
	 */
	LED_OFF(LED2);
	/*******************************************************************************
	 *                             Main Application                                *
	 *******************************************************************************/
	while(1)
	{
		/*
		 * receive current temperature of water from temperature sensor
		 */
		current_temperature = read_currentTemperature();

		/**************************************************************************
		 *                              ON/OFF Button
		 **************************************************************************/
		if(  BIT_IS_CLEAR(ON_OFF_BUTTON_PIN_REG , ON_OFF_BUTTON_INPUT_PIN)  )
		{
			/*
			 * wait some seconds due to bouncing of the button
			 */
			_delay_ms(DEBOUNCE_TIME);
			/*
			 * Ask again to make sure it is a real push on the button
			 */
			if(  BIT_IS_CLEAR(ON_OFF_BUTTON_PIN_REG , ON_OFF_BUTTON_INPUT_PIN)  )
			{
				/*
				 * Ask about the SW flag of ON/OFF button to make sure it will do
				 *the functionality one time only
				 */
				if(OnOFF_swFlag == FALSE_STATE)
				{
					/*
					 * Change the state of the ON/OFF button to prevent the program
					 * to enter this area of condition to avoid multiple of this action
					 * during continuous press
					 */
					OnOFF_swFlag = TRUE_STATE;
					/*
					 * increment the variable which responsible for checking
					 * if this current press on the on/off button express on mode or off mode
					 */
					OnOff_ModeCheck++;
				}
			}
		}
		else
		{
			/*
			 * Change the state of the ON/OFF button to enable the program
			 * to enter the area of condition once again after releasing the button
			 */
			OnOFF_swFlag = FALSE_STATE;
		}

		/**************************************************************************
		 *                              (1) ON  STATE
		 **************************************************************************/
		if( MOD_BY_TWO(OnOff_ModeCheck) == ON_STATE)
		{
			/*
			 * read the first digit of the temperature from
			 * the external memory and store it in a variable
			 */
			EEPROM_readByte(FIRST_ADDRESS_TO_STORE, &temperatureZero);
			/*
			 * wait some seconds to give the memory time to read
			 */
			_delay_ms(EEPROM_READ_DELAY_VALUE);
			/*
			 * read the second digit of the temperature from
			 * the external memory and store it in a variable
			 */
			EEPROM_readByte(SECOND_ADDRESS_TO_STORE, &temperatureTens);
			/*
			 * wait some seconds to give the memory time to read
			 */
			_delay_ms(EEPROM_READ_DELAY_VALUE);
			/*
			 * Calculate the Stored temperature after getting
			 * the first and second digit from external memory
			 */
			storedTemperature = (temperatureTens*10) + temperatureZero;

			/**************************************************************************
			 *                 (1-1) HEATING-COOLING ELEMENT CHECK
			 **************************************************************************/

			/*Condition of Turn on Cooling Element*/
			if( (current_temperature ) > (storedTemperature + DIFFERANCE_VALUE) )
			{
				/*
				 * Turn on the motor to work on Clock wise direction
				 * to act as Fan for cooling
				 */
				DC_motor_on_ClockWise();
				/*
				 * Turn on the Cooling LED
				 */
				LED_ON(LED1);
				/*
				 * Turn off the heating LED
				 */
				LED_OFF(LED2);

			}
			/*Condition of Turn on Heating Element*/
			else if( (current_temperature ) < (storedTemperature - DIFFERANCE_VALUE) )
			{
				/*
				 * Turn on  the heating element
				 */
				LED_ON(LED2);
				/*
				 * Turn off the cooling element
				 */
				LED_OFF(LED1);
				/*
				 * force the motor to stop
				 */
				DC_motor_on_Stop();
			}
			else
			{
				/*
				 * force the motor to stop
				 */
				DC_motor_on_Stop();
				/*
				 * Turn off the cooling element
				 */
				LED_OFF(LED1);
				/*
				 * Turn off the heating element
				 */
				LED_OFF(LED2);
			}
			/**************************************************************************
			 *     (1-2)  DISPLAYING STORED TEMPERATURE AT FIRST OF ON STATE STAGE    *
			 **************************************************************************/
			if(eepromFlag == TRUE)
			{
				/*
				 *Start the timer to count seconds
				 */
				Timer_start(Timer1, F_CPU_1024);

				if(g_tick < MAXIMUM_NUMBER_OF_SECONDS)
				{
					/*
					 * displaying the set temperature in flashing mode
					 */
					FlashingSegments(storedTemperature);
				}
				else
				{
					/*
					 * stop the timer from count
					 */
					Timer_stop(Timer1);

					/*
					 * return g_tick to its initial value be ready to
					 * count another MAXIMUM_NUMBER_OF_SECONDS
					 */
					g_tick = INITIAL_VALUE;
					/*
					 * Change the state of eepromFlag to TRUE
					 * to prevent displaying flashing stored temperature
					 * from occurrence more than one time in ON-State
					 */
					eepromFlag = FALSE;
				}
			}
			/**************************************************************************
			 *                     (1-3)  UP BUTTON STAGE                             *
			 **************************************************************************/
			else if(g_upInterrupt_SWflag == TRUE)
			{
				/*
				 * Store the value of the set temperature in
				 * the external memory every UP occurrence
				 */
				store_inMemory(g_setTemprature);
				/*
				 *Start the timer to count seconds
				 */
				Timer_start(Timer1, F_CPU_1024);

				if(g_tick < MAXIMUM_NUMBER_OF_SECONDS)
				{
					/*
					 * displaying the set temperature in flashing mode
					 */
					FlashingSegments(g_setTemprature);
				}
				else
				{
					/*
					 * stop the timer from count
					 */
					Timer_stop(Timer1);
					/*
					 * return g_tick to its initial value be ready to
					 * count another MAXIMUM_NUMBER_OF_SECONDS
					 */
					g_tick = INITIAL_VALUE;
					/*
					 * Change the g_upInterrupt_SWflag to FALSE again
					 * to be ready to get UP interrupt again and
					 * stop increasing Set temperature
					 */
					g_upInterrupt_SWflag = FALSE;
				}

			}
			/**************************************************************************
			 *                     (1-3)  Down BUTTON STAGE                           *
			 **************************************************************************/
			else if(g_downInterrupt_SWflag == TRUE)
			{
				/*
				 * Store the value of the set temperature in
				 * the external memory every UP occurrence
				 */
				store_inMemory(g_setTemprature);
				/*
				 *Start the timer to count seconds
				 */
				Timer_start(Timer1, F_CPU_1024);

				if(g_tick < MAXIMUM_NUMBER_OF_SECONDS)
				{
					/*
					 * displaying the set temperature in flashing mode
					 */
					FlashingSegments(g_setTemprature);
				}
				else
				{
					/*
					 * stop the timer from count
					 */
					Timer_stop(Timer1);
					/*
					 * return g_tick to its initial value be ready to
					 * count another MAXIMUM_NUMBER_OF_SECONDS
					 */
					g_tick = INITIAL_VALUE;
					/*
					 * Change the g_downInterrupt_SWflag to FALSE again
					 * to be ready to get UP interrupt again and
					 * stop decreasing Set temperature
					 */
					g_downInterrupt_SWflag = FALSE;
				}
			}
			/**************************************************************************
			 *                       (1-4)  Default STAGE                             *
			 **************************************************************************/
			else
			{
				/*
				 * display current temperature of the sensor on 7-segments
				 */
				displayTemperature(current_temperature);

			}/*End of default stage*/

		}/*End of ON_OFF button in ON state*/
		/**************************************************************************
		 *                            (2)  OFF STATE                              *
		 **************************************************************************/
		else if( MOD_BY_TWO(OnOff_ModeCheck) == OFF_STATE )
		{
			/*
			 * Close the 7-Segments in OFF_STATE
			 */
			disableSegments();
			/*
			 * force the motor to stop
			 */
			DC_motor_on_Stop();
			/*
			 * Turn off the cooling element
			 */
			LED_OFF(LED1);
			/*
			 * Turn off the heating element
			 */
			LED_OFF(LED2);
			/*
			 * to prevent UP interrupt from occurrence in the OFF state
			 */
			g_upInterrupt_SWflag = FALSE;
			/*
			 * to prevent UDown interrupt from occurrence in the OFF state
			 */
			g_downInterrupt_SWflag = FALSE;
			/*
			 * Change the state of eepromFlag to TRUE
			 * to prevent displaying flashing stored temperature
			 * from occurrence more than one time in ON-State
			 */
			eepromFlag= TRUE;
			/*
			 * return g_tick to its initial value be ready to
			 * count another MAXIMUM_NUMBER_OF_SECONDS to start seconds
			 * of displaying stored temperature from initial value
			 */
			g_tick = INITIAL_VALUE;
		}/*End of ON_OFF button off state*/

	}/*End of super loop*/

	return 0;
}/*end of main function*/
