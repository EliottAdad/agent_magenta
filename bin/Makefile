
# Makefile

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
.PHONY = all clean doit
# Options
DEBUG			= yes
#NORMALBUILD		= no
#EXPERIMENTAL	= yes


# Display info
ifeq (1, 1)
	a = $(shell echo 'Debug:' $(DEBUG))
	$(info $(a))
#	a = $(shell echo 'Normal build:' $(NORMALBUILD))
#	$(info $(a))
endif




all: main

ifeq ($(DEBUG), yes)
$(CFLAGS)+= -lboost_unit_test_framework
all: test run_test
endif

obj/main: obj/main.o
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(LDLIBS) -o $@

obj/main.o: src/core/main.cpp
	$(CC) -o $@ -c $^ $(CFLAGS)













SOURCEDIR= src test
SOURCES := $(shell find $(SOURCEDIR) -name '*.cpp')
OBJECTS = $(patsubst %.cpp, obj/%.o, $(notdir $(SOURCES)))
a = $(shell echo $(SOURCES))
$(info $(a))
a = $(shell echo $(OBJECTS))
$(info $(a))


#SRC_DIRS = $(sort $(dir $(wildcard ../src/*/)))
#vpath %.c $(SRC_DIRS)

#obj/%.o: %.c
#	$(CC) - $(CFLAGS) -c $< -o $@



# WORKS
doit:
	$(foreach var, $(SOURCES), $(shell $(CC) -o $(patsubst %.cpp, obj/%.o, $(notdir $(var))) -c $(var) $(CFLAGS)))
#	$(var:.c=.o) 


# Experimental build 
ifeq ($(EXPERIMENTAL), yes)

# Links all .o files into an executable
all: obj/main
#obj/main: obj/main.o
#obj/main: $(OBJECTS)
#obj/main: obj/%.o
obj/main: obj/%.o
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(LDLIBS) -o $@

# Compiles all .cpp in .o doesn't work
#$(OBJECTS)&: $(SOURCES)
#$(SOURCES:.c=.o): $(SOURCES)
#	echo $^
#	$(CC) -c $^ $(CFLAGS)


#	$(foreach var, $(OBJECTS), $(CC) -o $(var) -c $(var:.o=.c) $(CFLAGS))
#	$(CC) -o $@ -c $^ $(CFLAGS)

#src/core/Physics.o: src/core/Physics.cpp
#	$(CC) -o $@ -c $^ $(CFLAGS)

endif






# Normal build
ifeq ($(NORMALBUILD), yes)

#echo 'Launching normal mode'

all: src/main

# Linking for main
src/main: src/main.o
	$(CC) -o $@ $^ $(LDLIBS)


endif






# Debugging build
ifeq ($(DEBUG), yes)
#	echo 'Launching debug mode'
	$(CFLAGS)+= -lboost_unit_test_framework

all: test/SN.test


# Linking for debug
test/SN.test: test/SN.test.o src/utilities/Printable.o src/utilities/functions.o
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(LDLIBS) -o $@


# Compiling for debug
test/SN.test.o: test/SN.test.cpp
	$(CC) -o $@ -c $^ $(CFLAGS)

src/utilities/Printable.o: src/utilities/Printable.cpp
	$(CC) -o $@ -c $^ $(CFLAGS)

src/utilities/functions.o: src/utilities/functions.cpp
	$(CC) -o $@ -c $^ $(CFLAGS)


endif




# General rule
#%.o: %.cpp
#	$(CC) -o $@ -c $^ $(CFLAGS)




# Cleaning options

#Finds all the .d and .o files in subdirectories
DFILES := $(shell find src test obj -name '*.d')
OFILES := $(shell find src test obj -name '*.o')
EXECUTABLES := $(shell find src test obj  -name 'main')
EXECUTABLES += $(shell find src test obj  -name 'SN.test')

a = $(shell echo $(EXECUTABLES))
$(info $(a))

clean:
	rm $(DFILES) $(OFILES) $(EXECUTABLES) *.o *.d
#	rm src/**.o src/**.d src/**~ *.o *.d src/core/*.o


include $(wildcard .d)    #handle header dependencies
