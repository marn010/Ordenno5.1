################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Ordenno5.1.c" \

ASM_SRCS += \
../Sources/asm_main.asm \

C_SRCS += \
../Sources/Ordenno5.1.c \

ASM_SRCS_QUOTED += \
"../Sources/asm_main.asm" \

OBJS += \
./Sources/Ordenno5_1_c.obj \
./Sources/asm_main_asm.obj \

ASM_DEPS += \
./Sources/asm_main_asm.d \

OBJS_QUOTED += \
"./Sources/Ordenno5_1_c.obj" \
"./Sources/asm_main_asm.obj" \

C_DEPS += \
./Sources/Ordenno5_1_c.d \

ASM_DEPS_QUOTED += \
"./Sources/asm_main_asm.d" \

C_DEPS_QUOTED += \
"./Sources/Ordenno5_1_c.d" \

OBJS_OS_FORMAT += \
./Sources/Ordenno5_1_c.obj \
./Sources/asm_main_asm.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/Ordenno5_1_c.obj: ../Sources/Ordenno5.1.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/Ordenno5.1.args" -ObjN="Sources/Ordenno5_1_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/asm_main_asm.obj: ../Sources/asm_main.asm
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: HCS08 Assembler'
	"$(HC08ToolsEnv)/ahc08" -ArgFile"Sources/asm_main.args" -Objn"Sources/asm_main_asm.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.asm
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


