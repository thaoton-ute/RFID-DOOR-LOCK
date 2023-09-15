################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Library/driver/src/driver_delay.c \
../Core/Library/driver/src/driver_ds1307.c \
../Core/Library/driver/src/driver_i2c_lcd.c \
../Core/Library/driver/src/driver_keypad.c \
../Core/Library/driver/src/driver_rc522.c \
../Core/Library/driver/src/driver_uart.c 

OBJS += \
./Core/Library/driver/src/driver_delay.o \
./Core/Library/driver/src/driver_ds1307.o \
./Core/Library/driver/src/driver_i2c_lcd.o \
./Core/Library/driver/src/driver_keypad.o \
./Core/Library/driver/src/driver_rc522.o \
./Core/Library/driver/src/driver_uart.o 

C_DEPS += \
./Core/Library/driver/src/driver_delay.d \
./Core/Library/driver/src/driver_ds1307.d \
./Core/Library/driver/src/driver_i2c_lcd.d \
./Core/Library/driver/src/driver_keypad.d \
./Core/Library/driver/src/driver_rc522.d \
./Core/Library/driver/src/driver_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Library/driver/src/%.o Core/Library/driver/src/%.su Core/Library/driver/src/%.cyclo: ../Core/Library/driver/src/%.c Core/Library/driver/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I"D:/STM32MySelf/Project_Intern/khoa2/07-2023-itr-intern-group-3/SMART_DOOR_CLOCK/test/Core/Library/api/inc" -I"D:/STM32MySelf/Project_Intern/khoa2/07-2023-itr-intern-group-3/SMART_DOOR_CLOCK/test/Core/Library/bsp/inc" -I"D:/STM32MySelf/Project_Intern/khoa2/07-2023-itr-intern-group-3/SMART_DOOR_CLOCK/test/Core/Library/driver/inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Admin/Desktop/Internship/07-2023-itr-intern-group-3/SMART_DOOR_CLOCK/test/Core/Library/driver/inc" -I"C:/Users/Admin/Desktop/Internship/07-2023-itr-intern-group-3/SMART_DOOR_CLOCK/test/Core/Library/bsp/inc" -I"C:/Users/Admin/Desktop/Internship/07-2023-itr-intern-group-3/SMART_DOOR_CLOCK/test/Core/Library/api/inc" -I"D:/Thao/nhap nhap/test/Core/Library/api/inc" -I"D:/Thao/nhap nhap/test/Core/Library/bsp/inc" -I"D:/Thao/nhap nhap/test/Core/Library/driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Library-2f-driver-2f-src

clean-Core-2f-Library-2f-driver-2f-src:
	-$(RM) ./Core/Library/driver/src/driver_delay.cyclo ./Core/Library/driver/src/driver_delay.d ./Core/Library/driver/src/driver_delay.o ./Core/Library/driver/src/driver_delay.su ./Core/Library/driver/src/driver_ds1307.cyclo ./Core/Library/driver/src/driver_ds1307.d ./Core/Library/driver/src/driver_ds1307.o ./Core/Library/driver/src/driver_ds1307.su ./Core/Library/driver/src/driver_i2c_lcd.cyclo ./Core/Library/driver/src/driver_i2c_lcd.d ./Core/Library/driver/src/driver_i2c_lcd.o ./Core/Library/driver/src/driver_i2c_lcd.su ./Core/Library/driver/src/driver_keypad.cyclo ./Core/Library/driver/src/driver_keypad.d ./Core/Library/driver/src/driver_keypad.o ./Core/Library/driver/src/driver_keypad.su ./Core/Library/driver/src/driver_rc522.cyclo ./Core/Library/driver/src/driver_rc522.d ./Core/Library/driver/src/driver_rc522.o ./Core/Library/driver/src/driver_rc522.su ./Core/Library/driver/src/driver_uart.cyclo ./Core/Library/driver/src/driver_uart.d ./Core/Library/driver/src/driver_uart.o ./Core/Library/driver/src/driver_uart.su

.PHONY: clean-Core-2f-Library-2f-driver-2f-src

