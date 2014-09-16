#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>

void printInt(int);
void printLong(long);
int numberFromString(char*);
