
############
# Makefile #
############

# Parameters
CC		= g++
CFLAGS	= -Wall -Wextra -MMD
# CFLAGS is for -I
LDLIBS	= -lboost_unit_test_framework -lSDL2
LDFLAGS	=
#LDFLAGS is for -L
# -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio
#SRCS =
#OBJS =
# Phonies
.PHONY = all clean create_build_dir display_info
# Options
DEBUG			= no
#NORMALBUILD		= no
#EXPERIMENTAL	= yes


all: create_build_dir main_tests main_game
#


# Create build directory
create_build_dir:
	$(shell mkdir ./build)

# Display info
display_info:
	$(shell echo 'Debug:' $(DEBUG))




ifeq ($(DEBUG), yes)
	$(CFLAGS)+= -lboost_unit_test_framework
	$(CFLAGS)+= --log_level=message
endif


# Linking main_game
main_game: main.o Material.o TimeSensitive.o Physics.o functions.o functions_display.o Printable.o
	$(MAKE) create_build_dir
#	$(MAKE) display_info
	$(CC) $(CFLAGS) $(addprefix build/, $^) $(LDFLAGS) $(LDLIBS) -o build/$@


#
# Linking main_tests
TESTS = SN.test.o Point3D.test.o Mobile.test.o Displayable.test.o Particle3D.test.o Game.test.o Physics.test.o Oct.test.o Physics.o TimeSensitive.o Printable.o functions.o functions_display.o
main_tests: tests.o $(TESTS)
	$(CC) $(CFLAGS) $(addprefix build/, $^) $(LDFLAGS) $(LDLIBS) -o build/$@


# Compile main.cpp
main.o: src/main.cpp
	$(CC) -o build/$@ -c $^ $(CFLAGS)


# Compile tests.cpp
tests.o: test/tests.cpp
	$(CC) -o build/$@ -c $^ $(CFLAGS)

# /////////////////////////////TESTS//////////////////////////////////// #

# Compile %.test.cpp
%.test.o: test/%.test.cpp
	$(CC) -o build/$@ -c $^ $(CFLAGS)

# //////////////////////////COMPILATION///////////////////////////////// #
# Compile Printables
Printable.o: src/utilities/Printable.cpp
	$(CC) -o build/$@ -c $^ $(CFLAGS)

# Compile functions
functions.o: src/utilities/functions.cpp
	$(CC) -o build/$@ -c $^ $(CFLAGS)

# Compile functions
functions_display.o: src/utilities/functions_display.cpp
	$(CC) -o build/$@ -c $^ $(CFLAGS)

# Compile functions
Physics.o: src/core/Physics.cpp
	$(CC) -o build/$@ -c $^ $(CFLAGS)

# Compile functions
TimeSensitive.o: src/core/TimeSensitive.cpp
	$(CC) -o build/$@ -c $^ $(CFLAGS)

# Compile functions
Material.o: src/display/Material.cpp
	$(CC) -o build/$@ -c $^ $(CFLAGS)









# Cleaning options

#Finds all the .d, .o and executables files in subdirectories
clean:
	$(RM) -f *.o *.d main_game main_tests -r ./doc ./build


include $(wildcard .d)    #handle header dependencies
