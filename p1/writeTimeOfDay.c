#include "myreminder.h"

// Grab the time of day, stamp it to STDOUT
void writeTimeOfDay()
{
	struct timeval* time = (struct timeval*)malloc(sizeof(struct timeval));
	if(time)
	{
		gettimeofday(time, NULL);
		#ifdef Debug
			printf("Time: %d\r\n", (int)time->tv_sec);
		#endif
		printInt((int)time->tv_sec);
		write(2, " ", 1);
		free(time);
	}
	
}
