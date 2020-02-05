################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/uart_module/subdir.mk
-include MCAL/timer_module/subdir.mk
-include MCAL/i2c/subdir.mk
-include MCAL/external_interrupt/subdir.mk
-include MCAL/dio_module/subdir.mk
-include MCAL/PWM_module/subdir.mk
-include HWAL/motor_module/subdir.mk
-include HWAL/lcd_module/subdir.mk
-include HWAL/keypad_module/subdir.mk
-include HWAL/eeprom_module/subdir.mk
-include APP_layer/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
CTRL.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: CTRL.elf secondary-outputs

# Tool invocations
CTRL.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,CTRL.map -mmcu=atmega16 -o "CTRL.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

CTRL.lss: CTRL.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S CTRL.elf  >"CTRL.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: CTRL.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega16 CTRL.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) CTRL.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
