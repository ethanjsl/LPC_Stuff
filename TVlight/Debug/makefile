################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include src/subdir.mk
-include driver/subdir.mk
-include cmsis/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: TVlight.axf

dependents:
	-cd C:/Users/ethan/git/LPC_Stuff/TVlight/Release && $(MAKE) all

# Tool invocations
TVlight.axf: $(OBJS) $(USER_OBJS) C:/Users/ethan/git/LPC_Stuff/TVlight/Release/TVlight.axf
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map=TVlight.map -Xlinker --gc-sections -mcpu=cortex-m0 -mthumb -T "../linker/lpc1114_flash_crp.ld" -o "TVlight.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) TVlight.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size TVlight.axf; arm-none-eabi-objcopy -O binary TVlight.axf TVlight.bin ; checksum -p LPC1114_301 -d TVlight.bin;
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
C:/Users/ethan/git/LPC_Stuff/TVlight/Release/TVlight.axf:

-include ../makefile.targets
