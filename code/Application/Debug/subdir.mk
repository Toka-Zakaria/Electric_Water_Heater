################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DCmotor.c \
../LEDs.c \
../adc.c \
../application_functions.c \
../external_eeprom.c \
../external_interrupts.c \
../i2c.c \
../main.c \
../timers.c 

OBJS += \
./DCmotor.o \
./LEDs.o \
./adc.o \
./application_functions.o \
./external_eeprom.o \
./external_interrupts.o \
./i2c.o \
./main.o \
./timers.o 

C_DEPS += \
./DCmotor.d \
./LEDs.d \
./adc.d \
./application_functions.d \
./external_eeprom.d \
./external_interrupts.d \
./i2c.d \
./main.d \
./timers.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


