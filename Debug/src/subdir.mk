################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Camera.cpp \
../src/Cube.cpp \
../src/Display1.cpp \
../src/Figure3D.cpp \
../src/LSN.cpp \
../src/Line3D.cpp \
../src/Mesh3D.cpp \
../src/Moveable.cpp \
../src/Particle3D.cpp \
../src/ParticleSystem3D.cpp \
../src/Physics.cpp \
../src/Point3D.cpp \
../src/Polyhedron.cpp \
../src/Printable.cpp \
../src/TimeLoop.cpp \
../src/TimeSensitive.cpp \
../src/Triangle.cpp \
../src/Vector3D.cpp \
../src/VectorField.cpp \
../src/VectorFieldUnidirectional.cpp \
../src/VectorFieldVortex.cpp \
../src/WeightedPoint3D.cpp \
../src/functions.cpp \
../src/main.cpp 

CPP_DEPS += \
./src/Camera.d \
./src/Cube.d \
./src/Display1.d \
./src/Figure3D.d \
./src/LSN.d \
./src/Line3D.d \
./src/Mesh3D.d \
./src/Moveable.d \
./src/Particle3D.d \
./src/ParticleSystem3D.d \
./src/Physics.d \
./src/Point3D.d \
./src/Polyhedron.d \
./src/Printable.d \
./src/TimeLoop.d \
./src/TimeSensitive.d \
./src/Triangle.d \
./src/Vector3D.d \
./src/VectorField.d \
./src/VectorFieldUnidirectional.d \
./src/VectorFieldVortex.d \
./src/WeightedPoint3D.d \
./src/functions.d \
./src/main.d 

OBJS += \
./src/Camera.o \
./src/Cube.o \
./src/Display1.o \
./src/Figure3D.o \
./src/LSN.o \
./src/Line3D.o \
./src/Mesh3D.o \
./src/Moveable.o \
./src/Particle3D.o \
./src/ParticleSystem3D.o \
./src/Physics.o \
./src/Point3D.o \
./src/Polyhedron.o \
./src/Printable.o \
./src/TimeLoop.o \
./src/TimeSensitive.o \
./src/Triangle.o \
./src/Vector3D.o \
./src/VectorField.o \
./src/VectorFieldUnidirectional.o \
./src/VectorFieldVortex.o \
./src/WeightedPoint3D.o \
./src/functions.o \
./src/main.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/share/qt5/doc/global/includes/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Camera.d ./src/Camera.o ./src/Cube.d ./src/Cube.o ./src/Display1.d ./src/Display1.o ./src/Figure3D.d ./src/Figure3D.o ./src/LSN.d ./src/LSN.o ./src/Line3D.d ./src/Line3D.o ./src/Mesh3D.d ./src/Mesh3D.o ./src/Moveable.d ./src/Moveable.o ./src/Particle3D.d ./src/Particle3D.o ./src/ParticleSystem3D.d ./src/ParticleSystem3D.o ./src/Physics.d ./src/Physics.o ./src/Point3D.d ./src/Point3D.o ./src/Polyhedron.d ./src/Polyhedron.o ./src/Printable.d ./src/Printable.o ./src/TimeLoop.d ./src/TimeLoop.o ./src/TimeSensitive.d ./src/TimeSensitive.o ./src/Triangle.d ./src/Triangle.o ./src/Vector3D.d ./src/Vector3D.o ./src/VectorField.d ./src/VectorField.o ./src/VectorFieldUnidirectional.d ./src/VectorFieldUnidirectional.o ./src/VectorFieldVortex.d ./src/VectorFieldVortex.o ./src/WeightedPoint3D.d ./src/WeightedPoint3D.o ./src/functions.d ./src/functions.o ./src/main.d ./src/main.o

.PHONY: clean-src

