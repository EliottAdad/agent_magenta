
CC=g++
CFLAGS= -Wall -Wextra -MMD
LDFLAGS= -L/local/lib
LIB= 

all: main_test_SN

main_test_SN: main_test_SN.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^

main_test_SN.o: main_test_SN.cpp SN.h Printable.h
	$(CC) $(LDFLAGS) $(CFLAGS) -c $< -o $@

#%.o: %.cpp
#	$(CC) $(LDFLAGS) $(CFLAGS) -c $< -o $@


clean:
	rm *.o
	rm *.d
	rm *~
#	rm test_SN
#	rm main2
	
include $(wildcard .d)

