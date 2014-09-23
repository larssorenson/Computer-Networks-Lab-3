#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>

int udpSocket;

void printInt(int);
void printLong(long);
int numberFromString(char*);
void setAlarm(int);
int setAlarmHandler();
void crash(int);
