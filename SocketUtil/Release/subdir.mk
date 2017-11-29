################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../File.cpp \
../FileInterface.cpp \
../MThread.cpp \
../MultipleTCPSocketListener.cpp \
../P2PClient.cpp \
../P2PServer.cpp \
../Socket.cpp \
../TCPSocket.cpp \
../Tcpp2pMessenger.cpp \
../UDPSocket.cpp 

OBJS += \
./File.o \
./FileInterface.o \
./MThread.o \
./MultipleTCPSocketListener.o \
./P2PClient.o \
./P2PServer.o \
./Socket.o \
./TCPSocket.o \
./Tcpp2pMessenger.o \
./UDPSocket.o 

CPP_DEPS += \
./File.d \
./FileInterface.d \
./MThread.d \
./MultipleTCPSocketListener.d \
./P2PClient.d \
./P2PServer.d \
./Socket.d \
./TCPSocket.d \
./Tcpp2pMessenger.d \
./UDPSocket.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


