################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/aes.c \
../source/fsl_enet_cmsis.c \
../source/fsl_enet_mdio.c \
../source/fsl_enet_phy_cmsis.c \
../source/fsl_phyksz8081.c \
../source/fsl_sysmpu.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/aes.d \
./source/fsl_enet_cmsis.d \
./source/fsl_enet_mdio.d \
./source/fsl_enet_phy_cmsis.d \
./source/fsl_phyksz8081.d \
./source/fsl_sysmpu.d \
./source/semihost_hardfault.d 

OBJS += \
./source/aes.o \
./source/fsl_enet_cmsis.o \
./source/fsl_enet_mdio.o \
./source/fsl_enet_phy_cmsis.o \
./source/fsl_phyksz8081.o \
./source/fsl_sysmpu.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practica1Oswaldo_aes_crc32_txrx_transfer3\board" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practica1Oswaldo_aes_crc32_txrx_transfer3\source" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practica1Oswaldo_aes_crc32_txrx_transfer3\drivers" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practica1Oswaldo_aes_crc32_txrx_transfer3\device" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practica1Oswaldo_aes_crc32_txrx_transfer3\CMSIS" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practica1Oswaldo_aes_crc32_txrx_transfer3\utilities" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practica1Oswaldo_aes_crc32_txrx_transfer3\component\serial_manager" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practica1Oswaldo_aes_crc32_txrx_transfer3\component\uart" -I"C:\Users\tiori\Documents\MCUXpressoIDE_11.10.0_3148\workspace\Practica1Oswaldo_aes_crc32_txrx_transfer3\component\lists" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/aes.d ./source/aes.o ./source/fsl_enet_cmsis.d ./source/fsl_enet_cmsis.o ./source/fsl_enet_mdio.d ./source/fsl_enet_mdio.o ./source/fsl_enet_phy_cmsis.d ./source/fsl_enet_phy_cmsis.o ./source/fsl_phyksz8081.d ./source/fsl_phyksz8081.o ./source/fsl_sysmpu.d ./source/fsl_sysmpu.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

