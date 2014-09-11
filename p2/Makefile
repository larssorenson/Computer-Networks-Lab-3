CC		=gcc
FLAGS		=-g -Wall -std=c99
EXECUTABLE	=mychecksum2
SOURCES		=checksum.c $(EXECUTABLE).c reverseLong.c reverseChecksum.c printInt.c printLong.c printUnsignedLongLong.c
HEADERS		=mychecksum.h
OBJECTS		=$(SOURCES:.c=.o)
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
	
