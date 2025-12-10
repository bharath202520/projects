################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/str/subdir.mk
-include utilities/debug_console/subdir.mk
-include utilities/subdir.mk
-include usb/host/class/subdir.mk
-include usb/host/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include mbedtls/port/pkc/subdir.mk
-include mbedtls/port/els/subdir.mk
-include mbedtls/library/subdir.mk
-include littlefs/subdir.mk
-include freertos/freertos-kernel/portable/MemMang/subdir.mk
-include freertos/freertos-kernel/portable/GCC/ARM_CM33_NTZ/non_secure/subdir.mk
-include freertos/freertos-kernel/subdir.mk
-include framework/services/LowPower/subdir.mk
-include framework/platform/rw61x/subdir.mk
-include flash_config/subdir.mk
-include flash/mflash/frdmrw612/subdir.mk
-include flash/mflash/subdir.mk
-include fatfs/source/fsl_usb_disk/subdir.mk
-include fatfs/source/subdir.mk
-include edgefast/bluetooth/source/services/subdir.mk
-include edgefast/bluetooth/source/porting/work/subdir.mk
-include edgefast/bluetooth/source/porting/thread/subdir.mk
-include edgefast/bluetooth/source/porting/slist/subdir.mk
-include edgefast/bluetooth/source/porting/slab/subdir.mk
-include edgefast/bluetooth/source/porting/sem/subdir.mk
-include edgefast/bluetooth/source/porting/queue/subdir.mk
-include edgefast/bluetooth/source/porting/poll/subdir.mk
-include edgefast/bluetooth/source/porting/net/subdir.mk
-include edgefast/bluetooth/source/porting/lifo/subdir.mk
-include edgefast/bluetooth/source/porting/fifo/subdir.mk
-include edgefast/bluetooth/source/porting/subdir.mk
-include edgefast/bluetooth/source/impl/ethermind/host/subdir.mk
-include edgefast/bluetooth/source/impl/ethermind/crypto/subdir.mk
-include edgefast/bluetooth/source/impl/ethermind/common/subdir.mk
-include edgefast/bluetooth/porting/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include component/uart/subdir.mk
-include component/timer_manager/subdir.mk
-include component/timer/subdir.mk
-include component/time_stamp/subdir.mk
-include component/serial_manager/subdir.mk
-include component/rng/subdir.mk
-include component/power_manager/subdir.mk
-include component/osa/subdir.mk
-include component/messaging/subdir.mk
-include component/mem_manager/subdir.mk
-include component/log/subdir.mk
-include component/lists/subdir.mk
-include component/imu_adapter/subdir.mk
-include component/els_pkc/src/platforms/rw61x/subdir.mk
-include component/els_pkc/src/comps/mcuxCsslParamIntegrity/src/subdir.mk
-include component/els_pkc/src/comps/mcuxCsslMemory/src/subdir.mk
-include component/els_pkc/src/comps/mcuxClTrng/src/subdir.mk
-include component/els_pkc/src/comps/mcuxClSession/src/subdir.mk
-include component/els_pkc/src/comps/mcuxClRsa/src/subdir.mk
-include component/els_pkc/src/comps/mcuxClRandomModes/src/subdir.mk
-include component/els_pkc/src/comps/mcuxClRandom/src/subdir.mk
-include component/els_pkc/src/comps/mcuxClPrng/src/subdir.mk
-include component/els_pkc/src/comps/mcuxClPkc/src/subdir.mk
-include component/els_pkc/src/comps/mcuxClPadding/src/subdir.mk
-include component/els_pkc/src/comps/mcuxClMemory/src/subdir.mk
-include component/els_pkc/src/comps/mcuxClMath/src/subdir.mk
-include component/els_pkc/src/comps/mcuxClMacModes/src/subdir.mk
-include component/els_pkc/src/comps/mcuxClMac/src/subdir.mk
-include component/els_pkc/src/comps/mcuxClKey/src/subdir.mk
-include component/els_pkc/src/comps/mcuxClHmac/src/subdir.mk
-include component/els_pkc/src/comps/mcuxClHashModes/src/subdir.mk
-include component/els_pkc/src/comps/mcuxClHash/src/subdir.mk
-include component/els_pkc/src/comps/mcuxClEls/src/subdir.mk
-include component/els_pkc/src/comps/mcuxClEcc/src/subdir.mk
-include component/els_pkc/src/comps/mcuxClCipherModes/src/subdir.mk
-include component/els_pkc/src/comps/mcuxClCipher/src/subdir.mk
-include component/els_pkc/src/comps/mcuxClBuffer/src/subdir.mk
-include component/els_pkc/src/comps/mcuxClAes/src/subdir.mk
-include component/els_pkc/src/comps/mcuxClAeadModes/src/subdir.mk
-include component/els_pkc/src/comps/mcuxClAead/src/subdir.mk
-include component/devices/RW612/subdir.mk
-include component/conn_fwloader/fw_bin/rw61x/subdir.mk
-include component/conn_fwloader/subdir.mk
-include bt_ble/source/impl/ethermind/platform/subdir.mk
-include bt_ble/source/impl/ethermind/subdir.mk
-include bt_ble/port/pal/mcux/toolspec/mcuxpresso/subdir.mk
-include bt_ble/port/pal/mcux/ethal/subdir.mk
-include bt_ble/port/pal/mcux/bluetooth/controller/subdir.mk
-include bt_ble/port/pal/mcux/bluetooth/subdir.mk
-include bt_ble/port/pal/mcux/subdir.mk
-include bt_ble/port/osal/src/freertos/subdir.mk
-include bt_ble/bluetooth/export/vendor/subdir.mk
-include bt_ble/bluetooth/export/extension/subdir.mk
-include board/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := bluetooth
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: bluetooth.axf

# Tool invocations
bluetooth.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\admin\Documents\MCUXpressoIDE_25.6.136\workspace\bluetooth\component\els_pkc\static_library\rw61x" -L"C:\Users\admin\Documents\MCUXpressoIDE_25.6.136\workspace\bluetooth\bt_ble\bluetooth\private\lib" -Xlinker -no-warn-rwx-segments -Xlinker -Map="bluetooth.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m33+nodsp -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -T bluetooth_Debug.ld -o "bluetooth.axf" $(OBJS) $(USER_OBJS) $(LIBS) -Wl,--start-group -lclns -lethermind_ble_core -lethermind_ble_gatt -lethermind_ble_protocol -lethermind_ble_util -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) bluetooth.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "bluetooth.axf"; # arm-none-eabi-objcopy -v -O binary "bluetooth.axf" "bluetooth.bin" ; # checksum -p RW612 -d "bluetooth.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
