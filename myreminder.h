#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Alarm Alarm;
struct Alarm
{
	int time;
	char* reminder;
	Alarm* next;
	Alarm* prev;
};

Alarm* parse(char*);
int addTimeToAlarm(Alarm*, char);
