#include "mobilereminder.h"

// Grab the time of day, add to buffer
void writeTimeOfDay(char* buffer)
{
	struct timeval* time = (struct timeval*)malloc(sizeof(struct timeval));
	if(time)
	{
		gettimeofday(time, NULL);
		#ifdef Debug
			printf("Time: %ld\r\n", (long)time->tv_sec);
		#endif
		printLongInt((long int)time->tv_sec, buffer);
		#ifdef Debug
			printf("After: %s\r\n", buffer);
		#endif
		strcat(buffer, " ");
	}
	
}
