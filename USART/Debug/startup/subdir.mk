################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32.s 

OBJS += \
./startup/startup_stm32.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo %cd%
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -I"C:/Users/UMK-Fizyka/Documents/STM32/Kurs_5/inc" -I"C:/Users/UMK-Fizyka/Documents/STM32/Kurs_5/CMSIS/core" -I"C:/Users/UMK-Fizyka/Documents/STM32/Kurs_5/CMSIS/device" -I"C:/Users/UMK-Fizyka/Documents/STM32/Kurs_5/StdPeriph_Driver/inc" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


