################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
MinIMU9AHRS.lss \

FLASH_IMAGE += \
MinIMU9AHRS.hex \


# All Target
all: MinIMU9AHRS.elf secondary-outputs

# Tool invocations
MinIMU9AHRS.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-g++ -Wl,-Map,MinIMU9AHRS.map,--cref -lm -L"/home/siddian/Dropbox/ArduinoWorkspace/arduino_core/328P_16MHz" -L"/home/siddian/Dropbox/ArduinoWorkspace/Wire/328P_16MHz" -L"/home/siddian/src/asrp/Arduino/libraries/L3G/Debug" -L"/home/siddian/src/asrp/Arduino/libraries/LSM303/328P_16MHz" -mmcu=atmega328p -o "MinIMU9AHRS.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

MinIMU9AHRS.lss: MinIMU9AHRS.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S MinIMU9AHRS.elf  >"MinIMU9AHRS.lss"
	@echo 'Finished building: $@'
	@echo ' '

MinIMU9AHRS.hex: MinIMU9AHRS.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex MinIMU9AHRS.elf  "MinIMU9AHRS.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(CPP_DEPS)$(C_UPPER_DEPS) MinIMU9AHRS.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
