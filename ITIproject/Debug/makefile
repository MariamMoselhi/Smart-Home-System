################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
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
ITIproject.lss \

FLASH_IMAGE += \
ITIproject.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: ITIproject.elf secondary-outputs

# Tool invocations
ITIproject.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ITIproject.map -mmcu=atmega32 -o "ITIproject.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ITIproject.lss: ITIproject.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ITIproject.elf  >"ITIproject.lss"
	@echo 'Finished building: $@'
	@echo ' '

ITIproject.hex: ITIproject.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex ITIproject.elf  "ITIproject.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ITIproject.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 ITIproject.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) ITIproject.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
