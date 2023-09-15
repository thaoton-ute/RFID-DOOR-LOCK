################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Library/middleware/flash.c 

OBJS += \
./Core/Library/middleware/flash.o 

C_DEPS += \
./Core/Library/middleware/flash.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Library/middleware/%.o Core/Library/middleware/%.su Core/Library/middleware/%.cyclo: ../Core/Library/middleware/%.c Core/Library/middleware/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I"D:/STM32MySelf/Project_Intern/khoa2/07-2023-itr-intern-group-3/SMART_DOOR_CLOCK/test/Core/Library/api/inc" -I"D:/STM32MySelf/Project_Intern/khoa2/07-2023-itr-intern-group-3/SMART_DOOR_CLOCK/test/Core/Library/bsp/inc" -I"D:/STM32MySelf/Project_Intern/khoa2/07-2023-itr-intern-group-3/SMART_DOOR_CLOCK/test/Core/Library/driver/inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Admin/Desktop/Internship/07-2023-itr-intern-group-3/SMART_DOOR_CLOCK/test/Core/Library/driver/inc" -I"C:/Users/Admin/Desktop/Internship/07-2023-itr-intern-group-3/SMART_DOOR_CLOCK/test/Core/Library/bsp/inc" -I"C:/Users/Admin/Desktop/Internship/07-2023-itr-intern-group-3/SMART_DOOR_CLOCK/test/Core/Library/api/inc" -I"D:/Thao/nhap nhap/test/Core/Library/api/inc" -I"D:/Thao/nhap nhap/test/Core/Library/bsp/inc" -I"D:/Thao/nhap nhap/test/Core/Library/driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Library-2f-middleware

clean-Core-2f-Library-2f-middleware:
	-$(RM) ./Core/Library/middleware/flash.cyclo ./Core/Library/middleware/flash.d ./Core/Library/middleware/flash.o ./Core/Library/middleware/flash.su

.PHONY: clean-Core-2f-Library-2f-middleware

