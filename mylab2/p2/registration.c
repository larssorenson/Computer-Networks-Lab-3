#include "mobilereminder.h"

void registration(int sig)
{
	if(!registered)
	{
		#ifdef Debug
			printf("Sending %s\r\n", secret);
		#endif
		mySendTo(udpSocket, secret, strlen(secret), 0, registeredaddr, addrlen);
	
		alarmSet = 0;
	}
	
}
