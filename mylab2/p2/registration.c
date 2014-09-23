#include "mobilereminder.h"

void registration(int sig)
{
	if(!registered)
	{
		int resp; 
		#ifdef Debug
			printf("Sending %s\r\n", secret);
		#endif
		resp = sendto(udpSocket, secret, strlen(secret), 0, registeredaddr, addrlen);
	
		if(resp <= 0)
		{
			perror("Registration");
			write(2, "The registration message could not be sent!\r\n", 32);
			return;
		}
	
		alarmSet = 0;
	}
	
}
