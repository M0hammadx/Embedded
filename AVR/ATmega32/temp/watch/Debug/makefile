################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
<<<<<<< HEAD
-include SERVICE/subdir.mk
-include HAL/UART/subdir.mk
-include HAL/TIMER/subdir.mk
-include HAL/I2C/subdir.mk
-include HAL/DIO/subdir.mk
=======
-include hal/UART/subdir.mk
-include hal/TIMER/subdir.mk
-include hal/I2C/subdir.mk
-include hal/DIO/subdir.mk
-include SERVICE/subdir.mk
>>>>>>> 4dc176ffe1bb20ece6c6e4ada9dacf7df24a391d
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
AVR_SDK.lss \

FLASH_IMAGE += \
AVR_SDK.hex \

EEPROM_IMAGE += \
AVR_SDK.eep \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: AVR_SDK.elf secondary-outputs

# Tool invocations
AVR_SDK.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-g++ -Wl,-Map,AVR_SDK.map,--cref -mrelax -Wl,--gc-sections -mmcu=atmega32 -o "AVR_SDK.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

AVR_SDK.lss: AVR_SDK.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S AVR_SDK.elf  >"AVR_SDK.lss"
	@echo 'Finished building: $@'
	@echo ' '

AVR_SDK.hex: AVR_SDK.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex AVR_SDK.elf  "AVR_SDK.hex"
	@echo 'Finished building: $@'
	@echo ' '

AVR_SDK.eep: AVR_SDK.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex AVR_SDK.elf  "AVR_SDK.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: AVR_SDK.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 AVR_SDK.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: AVR_SDK.elf
	@echo 'Invoking: AVRDude'
	D:\eclipse\Embedded\WinAVR-20100110\bin\avrdude -pm32 -Uflash:w:AVR_SDK.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(AVRDUDEDUMMY)$(S_DEPS)$(LSS)$(C_DEPS)$(FLASH_IMAGE)$(CC_DEPS)$(ELFS)$(C++_DEPS)$(OBJS)$(CXX_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(SIZEDUMMY)$(S_UPPER_DEPS)$(CPP_DEPS) AVR_SDK.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
