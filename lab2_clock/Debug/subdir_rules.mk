################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
lab2_clock_startup_msp432p401r_ccs.obj: ../lab2_clock_startup_msp432p401r_ccs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"/Applications/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="/Applications/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/include" --include_path="/Users/marybiggs/Desktop/ECE461/lab2_clock/driverlib" --include_path="/Applications/ti/ccsv6/ccs_base/arm/include" --include_path="/Applications/ti/ccsv6/ccs_base/arm/include/CMSIS" -g --gcc --define=TARGET_IS_MSP432P4XX --define=ccs --define=__MSP432P401R__ --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="lab2_clock_startup_msp432p401r_ccs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

lab2_clock_system.obj: ../lab2_clock_system.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"/Applications/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="/Applications/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/include" --include_path="/Users/marybiggs/Desktop/ECE461/lab2_clock/driverlib" --include_path="/Applications/ti/ccsv6/ccs_base/arm/include" --include_path="/Applications/ti/ccsv6/ccs_base/arm/include/CMSIS" -g --gcc --define=TARGET_IS_MSP432P4XX --define=ccs --define=__MSP432P401R__ --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="lab2_clock_system.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

system_msp432p401r.obj: ../system_msp432p401r.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"/Applications/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="/Applications/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.6/include" --include_path="/Users/marybiggs/Desktop/ECE461/lab2_clock/driverlib" --include_path="/Applications/ti/ccsv6/ccs_base/arm/include" --include_path="/Applications/ti/ccsv6/ccs_base/arm/include/CMSIS" -g --gcc --define=TARGET_IS_MSP432P4XX --define=ccs --define=__MSP432P401R__ --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="system_msp432p401r.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


