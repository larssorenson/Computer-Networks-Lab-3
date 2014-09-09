#include <fcntl.h>
#include <unistd.h>

#undef Debug

#ifdef Debug
	#include <stdio.h>
#endif
unsigned long long checksum(int);
unsigned long long reverseLong (unsigned long long);
