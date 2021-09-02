/**********************************************************************************
 * [FILE NAME]: application_functions.h
 *
 * [AUTHOR]: Toka Zakaria Mohamed Ramadan
 *
 * [DATE CREATED]: Jul 27, 2021
 *
 * [Description]: File of All types Declaration and Functions prototypes of MCU
 ***********************************************************************************/

#ifndef APPLICATION_FUNCTIONS_H_
#define APPLICATION_FUNCTIONS_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"
#include"external_eeprom.h"
#include"timers.h"
#include"external_interrupts.h"
#include"adc.h"
#include"DCmotor.h"
#include"LEDs.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

#define MOD_BY_TWO(VARIABLE)                         (VARIABLE%2)

#define I_BIT                                               7
#define FALSE_STATE                                         0
#define TRUE_STATE                                          1
#define ON_STATE                                            1
#define OFF_STATE                                           0

#define COMPARE_VALUE                                     7000
#define NONE                                               0

#define ON_OFF_BUTTON_PORT_REG                            PORTD
#define ON_OFF_BUTTON_DIRECTION_REG                       DDRD
#define ON_OFF_BUTTON_PIN_REG                             PIND
#define ON_OFF_BUTTON_INPUT_PIN                           PD4

#define TEMP_SENSOR_DIRECTION_REG                         DDRA
#define TEMP_SENSOR_PORT_REG                              PORTA
#define TEMP_SENSOR_PIN_REG                               PINA
#define TEMP_SENSOR_INPUT_PIN                             PA0

#define SEGMENTS_DIRECTION_REG                            DDRB
#define SEGMENTS_PORT_REG                                 PORTB
#define SEGMENTS_PIN_REG                                  PINB

#define SEGMENTS_CTRL_DIRECTION_REG                       DDRD
#define SEGMENTS_CTRL_PORT_REG                            PORTD
#define SEGMENTS_CTRL_PIN_REG                             PIND

#define SEGMENTS_MASK_TO_BE_OUTPUT                        0X0F
#define SGMENTS_CTRL_MASK_TO_BE_OUTPUT                    0X03

#define SEGMENTS_CTRL_MASK                                0XFC
#define SEGMENTS_MASK                                     0XF0

#define SEGMENTS_CTRL_TIME                                 12
#define FIRST_SEGMENT_ENABLE_CTRL                          0X01
#define SECOND_SEGMENT_ENABLE_CTRL                         0X02

#define FLASHING_TIME                                      500


#define INITIAL_VALUE                                      0

#define INITIAL_SET_TEMPERATURE                           60
#define MINIMUM_SET_TEMPERATURE                           35
#define MAXIMUM_SET_TEMPERATURE                           75
#define INCREASE_VALUE                                     5
#define DECREASE_VALUE                                     5
#define DIFFERANCE_VALUE                                   5

#define MAXIMUM_NUMBER_OF_SECONDS                          5

#define FIRST_ADDRESS_TO_STORE                             0X0100
#define SECOND_ADDRESS_TO_STORE                            0X0101
#define EEPROM_WRITE_DELAY_VALUE                           80
#define EEPROM_READ_DELAY_VALUE                            80

#define DEBOUNCE_TIME                                      240
#define CHANNEL_NUMBER                                      0

/*******************************************************************************
 *                         extern variables                                    *
 *******************************************************************************/

extern uint32 g_setTemprature;

extern uint8 g_firstClick;

extern bool g_upInterrupt_SWflag;

extern bool g_downInterrupt_SWflag;

extern bool g_tick;

/*******************************************************************************
 *                           Functions Prototypes                              *
 *******************************************************************************/

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
uint32 read_currentTemperature(void);
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
void displayTemperature(uint32 currentTemp);
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
void disableSegments(void);
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
void upFunc(void);
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
void downFunc(void);
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
void flashingTime(void);
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
void FlashingSegments(uint32 temperature);
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
void store_inMemory(uint32 temperature);
/**********************************************************************************/


#endif /* APPLICATION_FUNCTIONS_H_ */
