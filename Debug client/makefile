################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/server/recordset/instrumentRecordset/subdir.mk
-include src/client/tcpClient/subdir.mk
-include src/client/mainWindow/testBoost/subdir.mk
-include src/client/mainWindow/scrolledLogWindow/subdir.mk
-include src/client/mainWindow/mainNotebook/subdir.mk
-include src/client/mainWindow/entryBox/subdir.mk
-include src/client/mainWindow/controlBox/subdir.mk
-include src/client/mainWindow/subdir.mk
-include src/client/clientSettings/subdir.mk
-include src/client/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: fixedIncomeBacktest

# Tool invocations
fixedIncomeBacktest: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -o  "fixedIncomeBacktest" $(OBJS) $(USER_OBJS) $(LIBS) -L"/usr/lib" -L"/usr/lib/x86_64-linux-gnu" `pkg-config --libs gtkmm-3.0`
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) fixedIncomeBacktest
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
