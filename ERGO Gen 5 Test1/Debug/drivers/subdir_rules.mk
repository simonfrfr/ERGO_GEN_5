################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
drivers/formike240x320x16_ili9320.obj: C:/StellarisWare/boards/rdk-idm/drivers/formike240x320x16_ili9320.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti2/ccsv5/tools/compiler/arm_5.0.1/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me -O2 -g --include_path="C:/ti2/ccsv5/tools/compiler/arm_5.0.1/include" --include_path="C:/Users/Simon/ERGO UNIT/ERGO Gen 5 Test1" --include_path="C:/StellarisWare/boards/rdk-idm" --include_path="C:/StellarisWare" --include_path="C:/StellarisWare/third_party" --include_path="C:/StellarisWare/third_party/lwip-1.3.2/src/include" --include_path="C:/StellarisWare/third_party/lwip-1.3.2/src/include/ipv4" --include_path="C:/StellarisWare/third_party/lwip-1.3.2/ports/stellaris/include" --gcc --define=ccs="ccs" --define=PART_LM3S6918 --define=UART_BUFFERED --diag_warning=225 --display_error_number --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="drivers/formike240x320x16_ili9320.pp" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/touch.obj: C:/StellarisWare/boards/rdk-idm/drivers/touch.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti2/ccsv5/tools/compiler/arm_5.0.1/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me -O2 -g --include_path="C:/ti2/ccsv5/tools/compiler/arm_5.0.1/include" --include_path="C:/Users/Simon/ERGO UNIT/ERGO Gen 5 Test1" --include_path="C:/StellarisWare/boards/rdk-idm" --include_path="C:/StellarisWare" --include_path="C:/StellarisWare/third_party" --include_path="C:/StellarisWare/third_party/lwip-1.3.2/src/include" --include_path="C:/StellarisWare/third_party/lwip-1.3.2/src/include/ipv4" --include_path="C:/StellarisWare/third_party/lwip-1.3.2/ports/stellaris/include" --gcc --define=ccs="ccs" --define=PART_LM3S6918 --define=UART_BUFFERED --diag_warning=225 --display_error_number --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="drivers/touch.pp" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


