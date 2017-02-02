################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../calendar/get_calendar.c 

OBJS += \
./calendar/get_calendar.o 

C_DEPS += \
./calendar/get_calendar.d 


# Each subdirectory must supply rules for building sources it contributes
calendar/%.o: ../calendar/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


