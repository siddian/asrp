################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/LSM303.cpp 

OBJS += \
./src/LSM303.o 

CPP_DEPS += \
./src/LSM303.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/home/siddian/Dropbox/ArduinoWorkspace/arduino_core/src" -I"/home/siddian/Dropbox/ArduinoWorkspace/arduino_core/pins_arduino_328P_16MHz" -I"/home/siddian/Dropbox/ArduinoWorkspace/Wire/src" -I"/home/siddian/Dropbox/ArduinoWorkspace/Wire/utility" -Wall -g2 -gstabs -Os -ffunction-sections -fdata-sections -fno-exceptions -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


