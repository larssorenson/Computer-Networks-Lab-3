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

typedef struct Alarm Alarm;
struct Alarm
{
	int time;
	char* reminder;
	Alarm* next;
	Alarm* prev;
};

Alarm* currentAlarm;
int udpSocket;
struct sockaddr *registeredaddr;
socklen_t addrlen;

void printLongInt(long int number, char* buffer);
Alarm* parse(char*);
void writeTimeOfDay(char *);
int addTimeToAlarm(char);
char* timeToString(int);
int setAlarmHandler();
void setAlarm();
void writeAlarm(int);
int checkForValidity(char* in);
int numberFromString(char* str);
