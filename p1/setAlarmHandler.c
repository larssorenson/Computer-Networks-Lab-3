#include "myreminder.h"

int setAlarmHandler()
{

	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	
	sa.sa_handler = &writeAlarm;
	
	return sigaction(SIGALRM, &sa, NULL);
}
