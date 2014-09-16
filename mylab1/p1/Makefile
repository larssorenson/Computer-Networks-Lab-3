CC		=gcc
DEBUG		=-U Debug
FLAGS		=-g -Wall $(DEBUG)
SOURCES		=writeTimeOfDay.c main.c setAlarmHandler.c setAlarm.c timeToString.c writeAlarm.c parse.c addTimeToAlarm.c printInt.c
HEADERS		=myreminder.h
OBJECTS		=$(SOURCES:.c=.o)
EXECUTABLE	=myreminder
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
	
