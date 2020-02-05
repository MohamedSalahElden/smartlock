################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP_layer/HMI_main.c \
../APP_layer/HMI_utility_functions.c \
../APP_layer/HW_config.c 

OBJS += \
./APP_layer/HMI_main.o \
./APP_layer/HMI_utility_functions.o \
./APP_layer/HW_config.o 

C_DEPS += \
./APP_layer/HMI_main.d \
./APP_layer/HMI_utility_functions.d \
./APP_layer/HW_config.d 


# Each subdirectory must supply rules for building sources it contributes
APP_layer/%.o: ../APP_layer/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O3 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


