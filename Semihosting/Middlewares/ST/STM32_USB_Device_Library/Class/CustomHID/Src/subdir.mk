################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Src/usbd_customhid.c 

OBJS += \
./Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Src/usbd_customhid.o 

C_DEPS += \
./Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Src/usbd_customhid.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Src/usbd_customhid.o: ../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Src/usbd_customhid.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F072xB -DDEBUG -D__DEBUG_PRINTF__ -c -I../USB_DEVICE/Target -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../USB_DEVICE/App -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Src/usbd_customhid.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

