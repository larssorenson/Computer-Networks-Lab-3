CC		=gcc
FLAGS		=-g -Wall -std=c99
SOURCES		=checksum.c main.c reverseLong.c
HEADERS		=mychecksum1.h
OBJECTS		=$(SOURCES:.c=.o)
EXECUTABLE	=mychecksum1
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
	
