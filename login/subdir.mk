################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../login/get_index.c \
../login/post_login.c 

OBJS += \
./login/get_index.o \
./login/post_login.o 

C_DEPS += \
./login/get_index.d \
./login/post_login.d 


# Each subdirectory must supply rules for building sources it contributes
login/%.o: ../login/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


