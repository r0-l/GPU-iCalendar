################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cookies/get_cookie_value.c 

OBJS += \
./cookies/get_cookie_value.o 

C_DEPS += \
./cookies/get_cookie_value.d 


# Each subdirectory must supply rules for building sources it contributes
cookies/%.o: ../cookies/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


