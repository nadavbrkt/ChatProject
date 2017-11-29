################################################################################
# Automatically-generated file. Do not edit!
################################################################################

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
all: Lab9

dependents:
	-cd /home/user/workspace/SocketUtil/Debug && $(MAKE) all
	-cd /home/user/workspace/Lab9/Release && $(MAKE) all

# Tool invocations
Lab9: $(OBJS) $(USER_OBJS) /home/user/workspace/SocketUtil/Debug/libSocketUtil.a /home/user/workspace/Lab9/Release/Lab9
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	g++ -L"/home/user/workspace/SocketUtil/Debug" -L/home/user/workspace/SocketUtil/Debug -o "Lab9" $(OBJS) $(USER_OBJS) $(LIBS) -lpthread
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) Lab9
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
/home/user/workspace/SocketUtil/Debug/libSocketUtil.a:
/home/user/workspace/Lab9/Release/Lab9:

-include ../makefile.targets
