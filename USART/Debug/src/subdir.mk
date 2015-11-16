################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/syscalls.c \
../src/system_stm32f30x.c 

OBJS += \
./src/main.o \
./src/syscalls.o \
./src/system_stm32f30x.o 

C_DEPS += \
./src/main.d \
./src/syscalls.d \
./src/system_stm32f30x.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -DSTM32F30 -DNUCLEO_F303RE -DSTM32F3 -DSTM32F303RETx -DSTM32 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F303xE -I"C:/Users/UMK-Fizyka/Documents/STM32/Kurs_5/inc" -I"C:/Users/UMK-Fizyka/Documents/STM32/Kurs_5/CMSIS/core" -I"C:/Users/UMK-Fizyka/Documents/STM32/Kurs_5/CMSIS/device" -I"C:/Users/UMK-Fizyka/Documents/STM32/Kurs_5/StdPeriph_Driver/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


