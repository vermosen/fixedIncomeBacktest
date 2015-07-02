################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/server/recordset/instrumentRecordset/instrumentRecordset.cpp 

OBJS += \
./src/server/recordset/instrumentRecordset/instrumentRecordset.o 

CPP_DEPS += \
./src/server/recordset/instrumentRecordset/instrumentRecordset.d 


# Each subdirectory must supply rules for building sources it contributes
src/server/recordset/instrumentRecordset/%.o: ../src/server/recordset/instrumentRecordset/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/fixedIncomeBacktest/src" -I"/home/vermosen/git/fixedIncomeBacktest/src" -O0 -g3 -Wall -c -fmessage-length=0 `pkg-config --cflags gtkmm-3.0` -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


