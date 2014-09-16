#include "ping.h"

// Set the sig handler for SIGALRM
int setAlarmHandler()
{
	struct sigaction sa;
	memset(&sa, 0, sizeof(struct sigaction));
	
	sa.sa_handler = &crash;
	
	return sigaction(SIGALRM, &sa, NULL);
}
