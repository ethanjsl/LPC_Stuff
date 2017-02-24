################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../driver/ADC.c \
../driver/Lights.c \
../driver/PWM.c \
../driver/localInput.c 

OBJS += \
./driver/ADC.o \
./driver/Lights.o \
./driver/PWM.o \
./driver/localInput.o 

C_DEPS += \
./driver/ADC.d \
./driver/Lights.d \
./driver/PWM.d \
./driver/localInput.d 


# Each subdirectory must supply rules for building sources it contributes
driver/%.o: ../driver/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c11 -D__REDLIB__ -D__USE_CMSIS -DDEBUG -D__CODE_RED -I"C:\Users\ethan\git\LPC_Stuff\TVlight\cmsis" -I"C:\Users\ethan\git\LPC_Stuff\TVlight\config" -I"C:\Users\ethan\git\LPC_Stuff\TVlight\driver" -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


