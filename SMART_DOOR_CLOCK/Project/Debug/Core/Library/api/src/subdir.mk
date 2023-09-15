################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Library/api/src/api_flash.c \
../Core/Library/api/src/api_handle_display.c \
../Core/Library/api/src/api_keypad.c \
../Core/Library/api/src/api_rc522.c 

OBJS += \
./Core/Library/api/src/api_flash.o \
./Core/Library/api/src/api_handle_display.o \
./Core/Library/api/src/api_keypad.o \
./Core/Library/api/src/api_rc522.o 

C_DEPS += \
./Core/Library/api/src/api_flash.d \
./Core/Library/api/src/api_handle_display.d \
./Core/Library/api/src/api_keypad.d \
./Core/Library/api/src/api_rc522.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Library/api/src/%.o Core/Library/api/src/%.su Core/Library/api/src/%.cyclo: ../Core/Library/api/src/%.c Core/Library/api/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I"D:/STM32MySelf/Project_Intern/khoa2/07-2023-itr-intern-group-3/SMART_DOOR_CLOCK/test/Core/Library/api/inc" -I"D:/STM32MySelf/Project_Intern/khoa2/07-2023-itr-intern-group-3/SMART_DOOR_CLOCK/test/Core/Library/bsp/inc" -I"D:/STM32MySelf/Project_Intern/khoa2/07-2023-itr-intern-group-3/SMART_DOOR_CLOCK/test/Core/Library/driver/inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Admin/Desktop/Internship/07-2023-itr-intern-group-3/SMART_DOOR_CLOCK/test/Core/Library/driver/inc" -I"C:/Users/Admin/Desktop/Internship/07-2023-itr-intern-group-3/SMART_DOOR_CLOCK/test/Core/Library/bsp/inc" -I"C:/Users/Admin/Desktop/Internship/07-2023-itr-intern-group-3/SMART_DOOR_CLOCK/test/Core/Library/api/inc" -I"D:/Thao/nhap nhap/test/Core/Library/api/inc" -I"D:/Thao/nhap nhap/test/Core/Library/bsp/inc" -I"D:/Thao/nhap nhap/test/Core/Library/driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Library-2f-api-2f-src

clean-Core-2f-Library-2f-api-2f-src:
	-$(RM) ./Core/Library/api/src/api_flash.cyclo ./Core/Library/api/src/api_flash.d ./Core/Library/api/src/api_flash.o ./Core/Library/api/src/api_flash.su ./Core/Library/api/src/api_handle_display.cyclo ./Core/Library/api/src/api_handle_display.d ./Core/Library/api/src/api_handle_display.o ./Core/Library/api/src/api_handle_display.su ./Core/Library/api/src/api_keypad.cyclo ./Core/Library/api/src/api_keypad.d ./Core/Library/api/src/api_keypad.o ./Core/Library/api/src/api_keypad.su ./Core/Library/api/src/api_rc522.cyclo ./Core/Library/api/src/api_rc522.d ./Core/Library/api/src/api_rc522.o ./Core/Library/api/src/api_rc522.su

.PHONY: clean-Core-2f-Library-2f-api-2f-src

