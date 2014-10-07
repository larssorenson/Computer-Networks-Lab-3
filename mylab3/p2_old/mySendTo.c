#include "mobilereminder.h"

ssize_t mySendTo(int socket, char* buffer, size_t length, int flag, struct sockaddr *address, socklen_t len)
{
	if (sendToFlag%2 == 0)
	{
		#ifdef Debug
			printf("Sending %s\r\n", buffer);
		#endif
		sendToFlag++;
		return sendto(socket, buffer, length, flag, address, len);
	}
	
	#ifdef Debug
		else
		{
			printf("NOT sending: %s\r\n", buffer);
		}
	#endif
	
	sendToFlag++;
	return 0;
}
