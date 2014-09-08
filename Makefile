CC		=gcc
DFLAGS		=-D Debug
FLAGS		=-g -Wall $(DFLAGS)
SOURCES		=parse.c addTimeToAlarm.c
HEADERS		=myreminder.h
OBJECTS		=$(SOURCES:.c=.o)
EXECUTABLE	=myreminder
RM		=rm -rf

.SUFFIXES:
.SUFFIXES: .c .o

#all: clean myreminder

#myreminder: parse.o addTimeToAlarm.o
#	$(CC) $(FLAGS) parse.o addTimeToAlarm.o -o $@ 
	
#addTimeToAlarm.o: addTimeToAlarm.c
#	$(CC) $(FLAGS) -c addTimeToAlarm.c -o $@
	
#parse.o: parse.c
#	$(CC) $(FLAGS) -c parse.c -o $@
	
all: $(EXECUTABLE) $(SOURCES)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(FLAGS) -c $< -o $@
	
clean:
	$(RM) $(EXECUTABLE) *.o *.core core *~
	
