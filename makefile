-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
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
all: calc

# Tool invocations
calc: $(OBJS) $(USER_OBJS) $(PROG_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	g++  -o "calc" $(OBJS) $(USER_OBJS) $(PROG_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	
tstOperandStream: $(OBJS) $(USER_OBJS) tstOperandStream.o
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	g++  -o $@ $(OBJS) $(USER_OBJS) tstOperandStream.o $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '


tstEngineDivide: $(OBJS) $(USER_OBJS) tstEngineDivide.o
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	g++  -o $@ $(OBJS) $(USER_OBJS) tstEngineDivide.o $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '


# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS)$(PROG_OBJS)$(PROG_CC_DEPS)$(TST_OBJS) calc
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
