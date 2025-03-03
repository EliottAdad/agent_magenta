
############
# Makefile #
############

# Parameters
CC		:= g++
# CFLAGS is for -I
CFLAGS	:= -Wall -Wextra -MMD -std=c++20
LDLIBS	:= -lboost_unit_test_framework -lSDL2
#LDFLAGS is for -L
LDFLAGS	:=
# -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio
# Phonies
.PHONY 	:= all
# Configuration
DEBUG	:=yes
TEST	:=yes




all: create_build_dir main_game



####################### Options

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
	mkdir -p ./build

# Run tests
run_test:
	./build/main_test




####################### Main
# Linking main_game
main_game: main_game.o
	$(CC) $(CFLAGS) $(addprefix build/, $^) $(LDFLAGS) $(LDLIBS) -o build/$@

# Compile main_draft.cpp
main_game.o: src/main.cpp
	$(CC) -o build/$@ -c $^ $(CFLAGS)

####################### Test
# Linking
TFILES := $(shell find test -name '*.test.cpp')
TOFILES = $(patsubst %.cpp, %.o, $(notdir $(TFILES)))
#$(TOFILES)
#Works:
#Point3D.test.o Particle3D.test.o PropertySet.test.o Display3D.test.o
#Doesn't work
#Oct.test.o 
main_test: main.test.o SN.test.o
	$(CC) $(CFLAGS) $(addprefix build/, $^) $(LDFLAGS) $(LDLIBS) -o build/$@


# Compile main.test.cpp
main.test.o: test/main.test.cpp
	$(CC) -o build/$@ -c $^ $(CFLAGS)

####################### Draft
# Linking main_draft
main_draft: main_draft.o
	$(CC) $(CFLAGS) $(addprefix build/, $^) $(LDFLAGS) $(LDLIBS) -o build/$@


# Compile main_draft.cpp
main_draft.o: src/main_draft.cpp
	$(CC) -o build/$@ -c $^ $(CFLAGS)



####################### Compilation


# Compile
%.test.o: test/%.test.cpp
	$(CC) -o build/$@ -c $^ $(CFLAGS)





####################### Cleaning options

#Finds all the .d, .o and executables files in subdirectories
clean:
	$(RM) -f *.o *.d main_game main_test main_draft -r ./doc ./build


include $(wildcard /build/*.d)    #handle header dependencies
