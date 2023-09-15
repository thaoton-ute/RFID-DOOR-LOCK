################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Library/bsp/src/bsp_delay.c \
../Core/Library/bsp/src/bsp_flash.c \
../Core/Library/bsp/src/bsp_gpio.c \
../Core/Library/bsp/src/bsp_i2c.c \
../Core/Library/bsp/src/bsp_i2c_1.c \
../Core/Library/bsp/src/bsp_spi.c \
../Core/Library/bsp/src/bsp_uart.c 

OBJS += \
./Core/Library/bsp/src/bsp_delay.o \
./Core/Library/bsp/src/bsp_flash.o \
./Core/Library/bsp/src/bsp_gpio.o \
./Core/Library/bsp/src/bsp_i2c.o \
./Core/Library/bsp/src/bsp_i2c_1.o \
./Core/Library/bsp/src/bsp_spi.o \
./Core/Library/bsp/src/bsp_uart.o 

C_DEPS += \
./Core/Library/bsp/src/bsp_delay.d \
./Core/Library/bsp/src/bsp_flash.d \
./Core/Library/bsp/src/bsp_gpio.d \
./Core/Library/bsp/src/bsp_i2c.d \
./Core/Library/bsp/src/bsp_i2c_1.d \
./Core/Library/bsp/src/bsp_spi.d \
./Core/Library/bsp/src/bsp_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Library/bsp/src/%.o Core/Library/bsp/src/%.su Core/Library/bsp/src/%.cyclo: ../Core/Library/bsp/src/%.c Core/Library/bsp/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I"D:/STM32MySelf/Project_Intern/khoa2/07-2023-itr-intern-group-3/SMART_DOOR_CLOCK/test/Core/Library/api/inc" -I"D:/STM32MySelf/Project_Intern/khoa2/07-2023-itr-intern-group-3/SMART_DOOR_CLOCK/test/Core/Library/bsp/inc" -I"D:/STM32MySelf/Project_Intern/khoa2/07-2023-itr-intern-group-3/SMART_DOOR_CLOCK/test/Core/Library/driver/inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Admin/Desktop/Internship/07-2023-itr-intern-group-3/SMART_DOOR_CLOCK/test/Core/Library/driver/inc" -I"C:/Users/Admin/Desktop/Internship/07-2023-itr-intern-group-3/SMART_DOOR_CLOCK/test/Core/Library/bsp/inc" -I"C:/Users/Admin/Desktop/Internship/07-2023-itr-intern-group-3/SMART_DOOR_CLOCK/test/Core/Library/api/inc" -I"D:/Thao/nhap nhap/test/Core/Library/api/inc" -I"D:/Thao/nhap nhap/test/Core/Library/bsp/inc" -I"D:/Thao/nhap nhap/test/Core/Library/driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Library-2f-bsp-2f-src

clean-Core-2f-Library-2f-bsp-2f-src:
	-$(RM) ./Core/Library/bsp/src/bsp_delay.cyclo ./Core/Library/bsp/src/bsp_delay.d ./Core/Library/bsp/src/bsp_delay.o ./Core/Library/bsp/src/bsp_delay.su ./Core/Library/bsp/src/bsp_flash.cyclo ./Core/Library/bsp/src/bsp_flash.d ./Core/Library/bsp/src/bsp_flash.o ./Core/Library/bsp/src/bsp_flash.su ./Core/Library/bsp/src/bsp_gpio.cyclo ./Core/Library/bsp/src/bsp_gpio.d ./Core/Library/bsp/src/bsp_gpio.o ./Core/Library/bsp/src/bsp_gpio.su ./Core/Library/bsp/src/bsp_i2c.cyclo ./Core/Library/bsp/src/bsp_i2c.d ./Core/Library/bsp/src/bsp_i2c.o ./Core/Library/bsp/src/bsp_i2c.su ./Core/Library/bsp/src/bsp_i2c_1.cyclo ./Core/Library/bsp/src/bsp_i2c_1.d ./Core/Library/bsp/src/bsp_i2c_1.o ./Core/Library/bsp/src/bsp_i2c_1.su ./Core/Library/bsp/src/bsp_spi.cyclo ./Core/Library/bsp/src/bsp_spi.d ./Core/Library/bsp/src/bsp_spi.o ./Core/Library/bsp/src/bsp_spi.su ./Core/Library/bsp/src/bsp_uart.cyclo ./Core/Library/bsp/src/bsp_uart.d ./Core/Library/bsp/src/bsp_uart.o ./Core/Library/bsp/src/bsp_uart.su

.PHONY: clean-Core-2f-Library-2f-bsp-2f-src

