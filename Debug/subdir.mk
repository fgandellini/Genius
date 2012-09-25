################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Arc.cpp \
../Arc_test.cpp \
../Node.cpp \
../Node_test.cpp \
../RunAllTests.cpp \
../Tour.cpp \
../Tour_test.cpp 

OBJS += \
./Arc.o \
./Arc_test.o \
./Node.o \
./Node_test.o \
./RunAllTests.o \
./Tour.o \
./Tour_test.o 

CPP_DEPS += \
./Arc.d \
./Arc_test.d \
./Node.d \
./Node_test.d \
./RunAllTests.d \
./Tour.d \
./Tour_test.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/home/fede/ae/cpputest/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


