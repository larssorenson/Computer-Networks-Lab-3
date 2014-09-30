CC		=gcc
DEBUG		=-U Debug
FLAGS		=-g -Wall -std=c99 $(DEBUG)
EXECUTABLE	=mypingd
SOURCES		=$(EXECUTABLE).c printInt.c numberFromString.c mallocAndCheck.c
HEADERS		=ping.h
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
	$(RM) myping mypingd *.o *.core core *~
	
