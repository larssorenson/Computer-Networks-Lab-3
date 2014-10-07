#include "vpntunnel.h"

int populateSockAddr(short family, struct sockaddr_in *addr, socklen_t addrlen, int port, char* IP)
{	
	addr->sin_family = family;
	addr->sin_port = htons(port);
	
	// Parse the arg given to us for the IP
	if(inet_pton(family, IP, &addr->sin_addr) <= 0)
	{
		write(2, "Failed to parse IP Address!\r\n", 29);
		return -1;
	}
	
	return 0;
	
}
