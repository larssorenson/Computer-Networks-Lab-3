#include "myreminder.h"

// Grab the time of day, stamp it to STDOUT
void writeTimeOfDay()
{
	struct timeval* time = (struct timeval*)malloc(sizeof(struct timeval));
	if(time)
	{
		gettimeofday(time, NULL);
		char* strTime = timeToString((int)(time->tv_sec));
		write(2, strTime, strlen(strTime));
		write(2, " ", 1);
		free(strTime);
	}
}
