################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/main.cpp \
../src/main2.cpp \
../src/main3.cpp \
../src/main4.cpp \
../src/main5.cpp 

CPP_DEPS += \
./src/main.d \
./src/main2.d \
./src/main3.d \
./src/main4.d \
./src/main5.d 

OBJS += \
./src/main.o \
./src/main2.o \
./src/main3.o \
./src/main4.o \
./src/main5.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/share/qt5/doc/global/includes/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/main.d ./src/main.o ./src/main2.d ./src/main2.o ./src/main3.d ./src/main3.o ./src/main4.d ./src/main4.o ./src/main5.d ./src/main5.o

.PHONY: clean-src

