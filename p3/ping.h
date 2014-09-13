#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#ifdef Debug
	#include <stdio.h>
#endif

void printInt(int);
int numberFromString(char*);
