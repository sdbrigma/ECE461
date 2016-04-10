################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
MSP_EXP432P401R.obj: ../MSP_EXP432P401R.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"/Applications/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="/Applications/ti/ccsv6/ccs_base/arm/include" --include_path="/Applications/ti/ccsv6/ccs_base/arm/include/CMSIS" --include_path="/Users/marybiggs/Desktop/ECE461/clock_MSP_EXP432P401R_TI_MSP432P401R" --include_path="/Applications/ti/tirtos_msp43x_2_16_00_08/products/msp432_driverlib_3_10_00_09/inc/CMSIS" --include_path="/Applications/ti/tirtos_msp43x_2_16_00_08/products/msp432_driverlib_3_10_00_09/inc" --include_path="/Applications/ti/tirtos_msp43x_2_16_00_08/products/msp432_driverlib_3_10_00_09/driverlib/MSP432P4xx" --include_path="/Applications/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/include" --advice:power_severity=suppress --advice:power=all -g --gcc --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs --define=MSP432WARE --display_error_number --diag_warning=225 --diag_warning=255 --diag_wrap=off --gen_func_subsections=on --preproc_with_compile --preproc_dependency="MSP_EXP432P401R.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

clock.obj: ../clock.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"/Applications/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="/Applications/ti/ccsv6/ccs_base/arm/include" --include_path="/Applications/ti/ccsv6/ccs_base/arm/include/CMSIS" --include_path="/Users/marybiggs/Desktop/ECE461/clock_MSP_EXP432P401R_TI_MSP432P401R" --include_path="/Applications/ti/tirtos_msp43x_2_16_00_08/products/msp432_driverlib_3_10_00_09/inc/CMSIS" --include_path="/Applications/ti/tirtos_msp43x_2_16_00_08/products/msp432_driverlib_3_10_00_09/inc" --include_path="/Applications/ti/tirtos_msp43x_2_16_00_08/products/msp432_driverlib_3_10_00_09/driverlib/MSP432P4xx" --include_path="/Applications/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/include" --advice:power_severity=suppress --advice:power=all -g --gcc --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs --define=MSP432WARE --display_error_number --diag_warning=225 --diag_warning=255 --diag_wrap=off --gen_func_subsections=on --preproc_with_compile --preproc_dependency="clock.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: ../clock.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"/Applications/ti/xdctools_3_31_01_33_core/xs" --xdcpath="/Applications/ti/tirtos_msp43x_2_16_00_08/packages;/Applications/ti/tirtos_msp43x_2_16_00_08/products/bios_6_45_01_29/packages;/Applications/ti/tirtos_msp43x_2_16_00_08/products/tidrivers_msp43x_2_16_00_08/packages;/Applications/ti/tirtos_msp43x_2_16_00_08/products/uia_2_00_05_50/packages;/Applications/ti/ccsv6/ccs_base;" xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M4F -p ti.platforms.msp432:MSP432P401R -r release -c "/Applications/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6" --compileOptions "-mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path=\"/Applications/ti/ccsv6/ccs_base/arm/include\" --include_path=\"/Applications/ti/ccsv6/ccs_base/arm/include/CMSIS\" --include_path=\"/Users/marybiggs/Desktop/ECE461/clock_MSP_EXP432P401R_TI_MSP432P401R\" --include_path=\"/Applications/ti/tirtos_msp43x_2_16_00_08/products/msp432_driverlib_3_10_00_09/inc/CMSIS\" --include_path=\"/Applications/ti/tirtos_msp43x_2_16_00_08/products/msp432_driverlib_3_10_00_09/inc\" --include_path=\"/Applications/ti/tirtos_msp43x_2_16_00_08/products/msp432_driverlib_3_10_00_09/driverlib/MSP432P4xx\" --include_path=\"/Applications/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/include\" --advice:power_severity=suppress --advice:power=all -g --gcc --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs --define=MSP432WARE --display_error_number --diag_warning=225 --diag_warning=255 --diag_wrap=off --gen_func_subsections=on  " "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/compiler.opt: | configPkg/linker.cmd
configPkg/: | configPkg/linker.cmd

