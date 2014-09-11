#include <fcntl.h>
#include <unistd.h>

#define Debug

#ifdef Debug
	#include <stdio.h>
#endif
unsigned long long checksum(int);
unsigned long long reverseLong (unsigned long long);
unsigned long long reverseChecksum(int, int);
void printInt(int);
void printLong(long);
void printUnsignedLongLong(unsigned long long);
