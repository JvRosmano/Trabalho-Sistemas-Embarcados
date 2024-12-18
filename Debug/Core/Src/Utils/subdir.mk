################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Utils/Position.c \
../Core/Src/Utils/Position_Filter.c 

OBJS += \
./Core/Src/Utils/Position.o \
./Core/Src/Utils/Position_Filter.o 

C_DEPS += \
./Core/Src/Utils/Position.d \
./Core/Src/Utils/Position_Filter.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Utils/%.o Core/Src/Utils/%.su Core/Src/Utils/%.cyclo: ../Core/Src/Utils/%.c Core/Src/Utils/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Utils

clean-Core-2f-Src-2f-Utils:
	-$(RM) ./Core/Src/Utils/Position.cyclo ./Core/Src/Utils/Position.d ./Core/Src/Utils/Position.o ./Core/Src/Utils/Position.su ./Core/Src/Utils/Position_Filter.cyclo ./Core/Src/Utils/Position_Filter.d ./Core/Src/Utils/Position_Filter.o ./Core/Src/Utils/Position_Filter.su

.PHONY: clean-Core-2f-Src-2f-Utils

