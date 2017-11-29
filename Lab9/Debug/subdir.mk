################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Broker.cpp \
../Dispatcher.cpp \
../Server.cpp \
../main.cpp 

OBJS += \
./Broker.o \
./Dispatcher.o \
./Server.o \
./main.o 

CPP_DEPS += \
./Broker.d \
./Dispatcher.d \
./Server.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/user/workspace/SocketUtil" -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


