#include "mobilereminder.h"

// Set the sig handler for SIGALRM
int setClientAlarmHandler()
{
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	
	sa.sa_handler = &registration;
	
	return sigaction(SIGALRM, &sa, NULL);
}
