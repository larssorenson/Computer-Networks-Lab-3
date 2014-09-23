CC		=gcc
DEBUG		=-U Debug
FLAGS		=-g -Wall $(DEBUG)
SOURCES		=writeTimeOfDay.c $(EXECUTABLE).c setAlarmHandler.c setAlarm.c timeToString.c writeAlarm.c parse.c addTimeToAlarm.c numberFromString.c checkForValidity.c printLongInt.c setClientAlarmHandler.c registration.c setClientAlarm.c
HEADERS		=mobilereminder.h
OBJECTS		=$(SOURCES:.c=.o)
EXECUTABLE	=mobilereminder
RM		=rm -rf

.SUFFIXES:
.SUFFIXES: .c .o

all: $(EXECUTABLE) $(SOURCES) $(HEADERS)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(FLAGS) -c $< -o $@
	
clean:
	$(RM) $(EXECUTABLE) *.o *.core core *~
	
