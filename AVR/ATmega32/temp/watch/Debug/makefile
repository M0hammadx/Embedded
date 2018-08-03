################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include HAL/UART/subdir.mk
-include HAL/TIMER/subdir.mk
-include HAL/I2C/subdir.mk
-include HAL/DIO/subdir.mk
-include ECU/E2PROM/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
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
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
watch.lss \

FLASH_IMAGE += \
watch.hex \

EEPROM_IMAGE += \
watch.eep \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: watch.elf secondary-outputs

# Tool invocations
watch.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-g++ -Wl,-Map,watch.map,--cref -mrelax -Wl,--gc-sections -mmcu=atmega32 -o "watch.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

watch.lss: watch.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S watch.elf  >"watch.lss"
	@echo 'Finished building: $@'
	@echo ' '

watch.hex: watch.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex watch.elf  "watch.hex"
	@echo 'Finished building: $@'
	@echo ' '

watch.eep: watch.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex watch.elf  "watch.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: watch.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 watch.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: watch.elf
	@echo 'Invoking: AVRDude'
	E:\eclipse\Embedded\WinAVR-20100110\bin\avrdude -pm32 -Uflash:w:watch.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(AVRDUDEDUMMY)$(S_DEPS)$(LSS)$(C_DEPS)$(FLASH_IMAGE)$(CC_DEPS)$(ELFS)$(C++_DEPS)$(OBJS)$(CXX_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(SIZEDUMMY)$(S_UPPER_DEPS)$(CPP_DEPS) watch.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
