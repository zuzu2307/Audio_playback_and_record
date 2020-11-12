################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/project/STM32/MAD/workspace/Audio_playback_and_record/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.c \
D:/project/STM32/MAD/workspace/Audio_playback_and_record/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.c \
D:/project/STM32/MAD/workspace/Audio_playback_and_record/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.c \
D:/project/STM32/MAD/workspace/Audio_playback_and_record/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.c 

OBJS += \
./Middlewares/STM32_USBH_Library/Core/usbh_core.o \
./Middlewares/STM32_USBH_Library/Core/usbh_ctlreq.o \
./Middlewares/STM32_USBH_Library/Core/usbh_ioreq.o \
./Middlewares/STM32_USBH_Library/Core/usbh_pipes.o 

C_DEPS += \
./Middlewares/STM32_USBH_Library/Core/usbh_core.d \
./Middlewares/STM32_USBH_Library/Core/usbh_ctlreq.d \
./Middlewares/STM32_USBH_Library/Core/usbh_ioreq.d \
./Middlewares/STM32_USBH_Library/Core/usbh_pipes.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/STM32_USBH_Library/Core/usbh_core.o: D:/project/STM32/MAD/workspace/Audio_playback_and_record/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F746xx -DUSE_STM32746G_DISCO -DUSE_IOEXPANDER -DUSE_USB_FS -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../../../Drivers/STM32F7xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32746G-Discovery -I../../../Drivers/BSP/Components/Common -I../../../Utilities/Log -I../../../Utilities/Fonts -I../../../Utilities/CPU -I../../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../../Middlewares/Third_Party/FatFs/src -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/STM32_USBH_Library/Core/usbh_core.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/STM32_USBH_Library/Core/usbh_ctlreq.o: D:/project/STM32/MAD/workspace/Audio_playback_and_record/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F746xx -DUSE_STM32746G_DISCO -DUSE_IOEXPANDER -DUSE_USB_FS -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../../../Drivers/STM32F7xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32746G-Discovery -I../../../Drivers/BSP/Components/Common -I../../../Utilities/Log -I../../../Utilities/Fonts -I../../../Utilities/CPU -I../../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../../Middlewares/Third_Party/FatFs/src -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/STM32_USBH_Library/Core/usbh_ctlreq.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/STM32_USBH_Library/Core/usbh_ioreq.o: D:/project/STM32/MAD/workspace/Audio_playback_and_record/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F746xx -DUSE_STM32746G_DISCO -DUSE_IOEXPANDER -DUSE_USB_FS -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../../../Drivers/STM32F7xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32746G-Discovery -I../../../Drivers/BSP/Components/Common -I../../../Utilities/Log -I../../../Utilities/Fonts -I../../../Utilities/CPU -I../../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../../Middlewares/Third_Party/FatFs/src -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/STM32_USBH_Library/Core/usbh_ioreq.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/STM32_USBH_Library/Core/usbh_pipes.o: D:/project/STM32/MAD/workspace/Audio_playback_and_record/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F746xx -DUSE_STM32746G_DISCO -DUSE_IOEXPANDER -DUSE_USB_FS -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../../../Drivers/STM32F7xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32746G-Discovery -I../../../Drivers/BSP/Components/Common -I../../../Utilities/Log -I../../../Utilities/Fonts -I../../../Utilities/CPU -I../../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../../Middlewares/Third_Party/FatFs/src -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/STM32_USBH_Library/Core/usbh_pipes.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

