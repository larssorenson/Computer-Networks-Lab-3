#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#undef Debug

typedef struct Alarm Alarm;
struct Alarm
{
	int time;
	char* reminder;
	Alarm* next;
	Alarm* prev;
};

Alarm* currentAlarm;

Alarm* parse(char*);
void writeTimeOfDay();
int addTimeToAlarm(char);
char* timeToString(int);
int setAlarmHandler();
void setAlarm();
void writeAlarm(int);

