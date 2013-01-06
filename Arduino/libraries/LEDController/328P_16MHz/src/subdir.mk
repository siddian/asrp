################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/LedControl.cpp 

OBJS += \
./src/LedControl.o 

CPP_DEPS += \
./src/LedControl.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/home/siddian/Dropbox/ArduinoWorkspace/arduino_core/src" -I"/home/siddian/Dropbox/ArduinoWorkspace/arduino_core/pins_arduino_328P_16MHz" -Wall -g2 -gstabs -Os -ffunction-sections -fdata-sections -fno-exceptions -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


