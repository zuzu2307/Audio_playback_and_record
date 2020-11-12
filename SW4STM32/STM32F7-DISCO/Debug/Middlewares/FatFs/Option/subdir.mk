################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/project/STM32/MAD/workspace/Audio_playback_and_record/Middlewares/Third_Party/FatFs/src/option/syscall.c \
D:/project/STM32/MAD/workspace/Audio_playback_and_record/Middlewares/Third_Party/FatFs/src/option/unicode.c 

OBJS += \
./Middlewares/FatFs/Option/syscall.o \
./Middlewares/FatFs/Option/unicode.o 

C_DEPS += \
./Middlewares/FatFs/Option/syscall.d \
./Middlewares/FatFs/Option/unicode.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FatFs/Option/syscall.o: D:/project/STM32/MAD/workspace/Audio_playback_and_record/Middlewares/Third_Party/FatFs/src/option/syscall.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F746xx -DUSE_STM32746G_DISCO -DUSE_IOEXPANDER -DUSE_USB_FS -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../../../Drivers/STM32F7xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32746G-Discovery -I../../../Drivers/BSP/Components/Common -I../../../Utilities/Log -I../../../Utilities/Fonts -I../../../Utilities/CPU -I../../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../../Middlewares/Third_Party/FatFs/src -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FatFs/Option/syscall.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FatFs/Option/unicode.o: D:/project/STM32/MAD/workspace/Audio_playback_and_record/Middlewares/Third_Party/FatFs/src/option/unicode.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F746xx -DUSE_STM32746G_DISCO -DUSE_IOEXPANDER -DUSE_USB_FS -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../../../Drivers/STM32F7xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32746G-Discovery -I../../../Drivers/BSP/Components/Common -I../../../Utilities/Log -I../../../Utilities/Fonts -I../../../Utilities/CPU -I../../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../../Middlewares/Third_Party/FatFs/src -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FatFs/Option/unicode.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

