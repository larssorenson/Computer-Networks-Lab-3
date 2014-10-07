#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>

void* mallocAndCheck(size_t size);
int checkArgc(int argc, int count, char* message);
int parseAndCheckPort(char* port);
int numberFromString(char* str);
int bindUDPSocket();
int populateSockAddr(short family, struct sockaddr_in *addr, socklen_t addrlen, int port, char* IP);
