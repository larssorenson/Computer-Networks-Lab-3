CC		=gcc
DEBUG		=-U Debug
FLAGS		=-g -Wall -std=c99 $(DEBUG)
EXECUTABLE	=vpntunneld
SOURCES		=dedicatedForwarding.c $(EXECUTABLE).c mallocAndCheck.c checkArgc.c numberFromString.c parseAndCheckPort.c bindUDPSocket.c timeToString.c
HEADERS		=vpntunnel.h globals.h types.h functions.h includes.h
OBJECTS		=$(SOURCES:.c=.o)
RM		=rm -rf

.SUFFIXES:
.SUFFIXES: .c .o

all: $(EXECUTABLE) $(SOURCES) $(HEADERS)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $@
	$(RM) *.o

.c.o:
	$(CC) $(FLAGS) -c $< -o $@
	
clean:
	$(RM) vpntunnel vpntunneld *.o *.core core *~
	
