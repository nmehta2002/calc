# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
EngineFactory.cc \
EngineDivide.cc \
EngineMultiply.cc \
OperandStreamFile.cc \
OperandStreamString.cc \
calc.cc \
tstOperandStream.cc \
tstEngineDivide.cc


OBJS += \
./EngineFactory.o \
./EngineDivide.o \
./EngineMultiply.o \
./OperandStreamFile.o \
./OperandStreamString.o \

PROG_OBJS += \
./calc.o 

CC_DEPS += \
./EngineFactory.d \
./EngineDivide.d \
./EngineMultiply.d \
./OperandStreamFile.d \
./OperandStreamString.d \

PROG_CC_DEPS += \
./calc.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: %.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -std=c++11 -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


