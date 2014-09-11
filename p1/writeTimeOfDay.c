#include "myreminder.h"

// Grab the time of day, stamp it to STDOUT
void writeTimeOfDay()
{
	struct timeval* time = (struct timeval*)malloc(sizeof(struct timeval));
	if(time)
	{
		gettimeofday(time, NULL);
		printInt((int)time->tv_sec);
		write(2, " ", 1);
	}
}
