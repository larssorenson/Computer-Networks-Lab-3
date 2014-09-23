CC		=gcc
DEBUG		=-U Debug
FLAGS		=-g -Wall -std=c99 $(DEBUG)
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
	$(RM) *.o

.c.o:
	$(CC) $(FLAGS) -c $< -o $@
	
clean:
	$(RM) mychecksum1 mychecksum2 *.o *.core core *~
	
