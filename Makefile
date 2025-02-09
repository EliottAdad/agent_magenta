
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
.PHONY = all clean
# Options
DEBUG			= no
#NORMALBUILD		= no
#EXPERIMENTAL	= yes


all: main_game main_tests



# Display info
display_info:
	a = $(shell echo 'Debug:' $(DEBUG))
	$(info $(a))




ifeq ($(DEBUG), yes)
$(CFLAGS)+= -lboost_unit_test_framework

endif


# Linking main_game
main_game: main.o Game.o Material.o TimeSensitive.o Physics.o functions.o functions_display.o Printable.o
	$(CC) $(CFLAGS) $(addprefix build/, $^) $(LDFLAGS) $(LDLIBS) -o build/$@



# Linking main_tests
main_tests: tests.o SN.test.o Point3D.test.o Printable.o functions.o Printable.o
	$(CC) $(CFLAGS) $(addprefix build/, $^) $(LDFLAGS) $(LDLIBS) -o build/$@


# Compile main.cpp
main.o: src/main.cpp
	$(CC) -o build/$@ -c $^ $(CFLAGS)


# Compile tests.cpp
tests.o: test/tests.cpp
	$(CC) -o build/$@ -c $^ $(CFLAGS)

# ///////TESTS/////// #
# Compile SN.test.cpp
SN.test.o: test/SN.test.cpp
	$(CC) -o build/$@ -c $^ $(CFLAGS)

# Compile Point3D.test.cpp
Point3D.test.o: test/Point3D.test.cpp
	$(CC) -o build/$@ -c $^ $(CFLAGS)

# Compile Vector3D.test.cpp
#Vector3D.test.o: test/Vector3D.test.cpp
#	$(CC) -o build/$@ -c $^ $(CFLAGS)

# ///////COMPILATION/////// #
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

# Compile functions
Game.o: src/utilities/Game.cpp
	$(CC) -o build/$@ -c $^ $(CFLAGS)












# Cleaning options

#Finds all the .d, .o and executables files in subdirectories
TOCLEANFOLDERS = src test build
DFILES := $(shell find $(TOCLEANFOLDERS) -name '*.d')
OFILES := $(shell find $(TOCLEANFOLDERS) -name '*.o')
EXECUTABLES := $(shell find $(TOCLEANFOLDERS)  -name 'main_game')
EXECUTABLES += $(shell find $(TOCLEANFOLDERS)  -name 'main_tests')


clean:
	rm $(DFILES) $(OFILES) $(EXECUTABLES) *.o *.d
#	rm src/**.o src/**.d src/**~ *.o *.d src/core/*.o


include $(wildcard .d)    #handle header dependencies
