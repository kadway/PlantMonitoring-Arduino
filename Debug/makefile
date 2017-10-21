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
SensorSide.lss \

FLASH_IMAGE += \
SensorSide.hex \

EEPROM_IMAGE += \
SensorSide.eep \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: SensorSide.elf secondary-outputs

# Tool invocations
SensorSide.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,SensorSide.map -mmcu=atmega328p -o "SensorSide.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

SensorSide.lss: SensorSide.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S SensorSide.elf  >"SensorSide.lss"
	@echo 'Finished building: $@'
	@echo ' '

SensorSide.hex: SensorSide.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex SensorSide.elf  "SensorSide.hex"
	@echo 'Finished building: $@'
	@echo ' '

SensorSide.eep: SensorSide.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex SensorSide.elf  "SensorSide.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: SensorSide.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p SensorSide.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: SensorSide.elf
	@echo 'Invoking: AVRDude'
	/usr/bin/avrdude -pm328p -carduino -P/dev/ttyUSB1 -b115200 -Uflash:w:SensorSide.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) SensorSide.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
