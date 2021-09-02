/**********************************************************************************
 * [FILE NAME]: i2c.c
 *
 * [AUTHOR]: Toka Zakaria Mohamed Ramadan
 *
 * [DATE CREATED]: Nov 5, 2020
 *
 * [Description]: Function to initialize i2c driver
 *
 ***********************************************************************************/
 

#include "i2c.h"


void TWI_init(const TWI_ConfigType * Config_ptr)
{
    /* Bit Rate: 400.000 kbps using zero pre-scaler TWPS=00 and F_CPU=8Mhz */

    TWBR = Config_ptr->rateRegister;

	TWSR = ( TWSR & (0XFC) ) | (Config_ptr->prescaler);
	
    /* Two Wire Bus address my address if any master device want to call me: 0x1 (used in case this MC is a slave device)
       General Call Recognition: Off */
	/*shift left to use as address is 7 bit only*/
    TWAR =  ( (Config_ptr->address)<< 1 );  //0b00000010; // my address = 0x01 :)
	
    TWCR = (1<<TWEN); /* enable TWI */
}



void TWI_start(void)
{
    /* 
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    
    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

void TWI_stop(void)
{
    /* 
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_write(uint8 data)
{
    /* Put data On TWI data Register */
    TWDR = data;
    /* 
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */ 
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 TWI_readWithACK(void)
{
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1 
	 */ 
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

uint8 TWI_readWithNACK(void)
{
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

uint8 TWI_getStatus(void)
{
    uint8 status;
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    status = TWSR & 0xF8;
    return status;
}
