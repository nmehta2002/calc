# Add inputs and outputs from these tool invocations to the build variables 

ENGINES += \
./EngineDivide.o \
./EngineMultiply.o 

OBJS += \
./EngineFactory.o \
./OperandStreamFile.o \
./OperandStreamString.o 

OBJS += $(ENGINES)

PROG_OBJS += \
./calc.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: %.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -std=c++11 -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


