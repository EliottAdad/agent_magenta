
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
# Phonies
.PHONY = all

DEBUG=yes
TEST=yes

all: create_build_dir main_game

# Activates Debug
ifeq ($(DEBUG),yes)
CFLAGS+=-g
endif


# Activates Testing
ifeq ($(TEST),yes)
all: main_test run_test
endif



# Create build directory
create_build_dir:
	$(shell mkdir ./build)

# Run tests
run_test:
	./build/main_test




#######################Main
# Linking main_game
main_game: main_game.o
	$(MAKE) create_build_dir
	$(CC) $(CFLAGS) $(addprefix build/, $^) $(LDFLAGS) $(LDLIBS) -o build/$@

# Compile main_draft.cpp
main_game.o: src/main.cpp
	$(CC) -o build/$@ -c $^ $(CFLAGS)

#######################Test
# Linking main_test Game3D.test.o Display1.test.o Oct.test.o SN.test.o Point3D.test.o
main_test: main.test.o
	$(MAKE) create_build_dir
	$(CC) $(CFLAGS) $(addprefix build/, $^) $(LDFLAGS) $(LDLIBS) -o build/$@


# Compile main.test.cpp
main.test.o: test/main.test.cpp
	$(CC) -o build/$@ -c $^ $(CFLAGS)
#	$(CC) -o build/$@ -c $^ $(CFLAGS)

#######################Draft
# Linking main_draft
main_draft: main_draft.o
	$(MAKE) create_build_dir
	$(CC) $(CFLAGS) $(addprefix build/, $^) $(LDFLAGS) $(LDLIBS) -o build/$@


# Compile main_draft.cpp
main_draft.o: src/main_draft.cpp
	$(CC) -o build/$@ -c $^ $(CFLAGS)



################### Compilation


# Compile
#%.o: %o.cpp
#	$(CC) -o build/$@ -c $^ $(CFLAGS)

# Compile
%.test.o: test/%.test.cpp
	$(CC) -o build/$@ -c $^ $(CFLAGS)





# Cleaning options

#Finds all the .d, .o and executables files in subdirectories
clean:
	$(RM) -f *.o *.d main_game main_test main_draft -r ./doc ./build


include $(wildcard .d)    #handle header dependencies
