################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../driver/Lights.c \
../driver/adc.c \
../driver/gpio.c \
../driver/timer32.c 

OBJS += \
./driver/Lights.o \
./driver/adc.o \
./driver/gpio.o \
./driver/timer32.o 

C_DEPS += \
./driver/Lights.d \
./driver/adc.d \
./driver/gpio.d \
./driver/timer32.d 


# Each subdirectory must supply rules for building sources it contributes
driver/%.o: ../driver/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c11 -D__REDLIB__ -D__USE_CMSIS -DDEBUG -D__CODE_RED -I"C:\Users\ethan\Documents\LPC\Workspace\TVlight\cmsis" -I"C:\Users\ethan\Documents\LPC\Workspace\TVlight\config" -I"C:\Users\ethan\Documents\LPC\Workspace\TVlight\driver" -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

