################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Drivers/HMC5883L_4_NUCLEO_64.c \
../Core/Src/Drivers/JDY18_4_NUCLEO_64.c \
../Core/Src/Drivers/L293D4NUCLEO_64.c 

OBJS += \
./Core/Src/Drivers/HMC5883L_4_NUCLEO_64.o \
./Core/Src/Drivers/JDY18_4_NUCLEO_64.o \
./Core/Src/Drivers/L293D4NUCLEO_64.o 

C_DEPS += \
./Core/Src/Drivers/HMC5883L_4_NUCLEO_64.d \
./Core/Src/Drivers/JDY18_4_NUCLEO_64.d \
./Core/Src/Drivers/L293D4NUCLEO_64.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Drivers/%.o Core/Src/Drivers/%.su Core/Src/Drivers/%.cyclo: ../Core/Src/Drivers/%.c Core/Src/Drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Drivers

clean-Core-2f-Src-2f-Drivers:
	-$(RM) ./Core/Src/Drivers/HMC5883L_4_NUCLEO_64.cyclo ./Core/Src/Drivers/HMC5883L_4_NUCLEO_64.d ./Core/Src/Drivers/HMC5883L_4_NUCLEO_64.o ./Core/Src/Drivers/HMC5883L_4_NUCLEO_64.su ./Core/Src/Drivers/JDY18_4_NUCLEO_64.cyclo ./Core/Src/Drivers/JDY18_4_NUCLEO_64.d ./Core/Src/Drivers/JDY18_4_NUCLEO_64.o ./Core/Src/Drivers/JDY18_4_NUCLEO_64.su ./Core/Src/Drivers/L293D4NUCLEO_64.cyclo ./Core/Src/Drivers/L293D4NUCLEO_64.d ./Core/Src/Drivers/L293D4NUCLEO_64.o ./Core/Src/Drivers/L293D4NUCLEO_64.su

.PHONY: clean-Core-2f-Src-2f-Drivers

