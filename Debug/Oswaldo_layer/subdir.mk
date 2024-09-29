################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Oswaldo_layer/practice1.c \
../Oswaldo_layer/practice_app.c 

C_DEPS += \
./Oswaldo_layer/practice1.d \
./Oswaldo_layer/practice_app.d 

OBJS += \
./Oswaldo_layer/practice1.o \
./Oswaldo_layer/practice_app.o 


# Each subdirectory must supply rules for building sources it contributes
Oswaldo_layer/%.o: ../Oswaldo_layer/%.c Oswaldo_layer/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practica1Oswaldo_aes_crc32_txrx_transfer3\board" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practica1Oswaldo_aes_crc32_txrx_transfer3\source" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practica1Oswaldo_aes_crc32_txrx_transfer3\drivers" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practica1Oswaldo_aes_crc32_txrx_transfer3\device" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practica1Oswaldo_aes_crc32_txrx_transfer3\CMSIS" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practica1Oswaldo_aes_crc32_txrx_transfer3\utilities" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practica1Oswaldo_aes_crc32_txrx_transfer3\component\serial_manager" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practica1Oswaldo_aes_crc32_txrx_transfer3\component\uart" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practica1Oswaldo_aes_crc32_txrx_transfer3\component\lists" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Oswaldo_layer

clean-Oswaldo_layer:
	-$(RM) ./Oswaldo_layer/practice1.d ./Oswaldo_layer/practice1.o ./Oswaldo_layer/practice_app.d ./Oswaldo_layer/practice_app.o

.PHONY: clean-Oswaldo_layer

