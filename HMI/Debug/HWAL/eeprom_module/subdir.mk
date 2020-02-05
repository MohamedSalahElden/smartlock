################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HWAL/eeprom_module/eeprom.c 

OBJS += \
./HWAL/eeprom_module/eeprom.o 

C_DEPS += \
./HWAL/eeprom_module/eeprom.d 


# Each subdirectory must supply rules for building sources it contributes
HWAL/eeprom_module/%.o: ../HWAL/eeprom_module/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O3 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


