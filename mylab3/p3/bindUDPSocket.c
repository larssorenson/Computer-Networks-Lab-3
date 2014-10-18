#include "vpntunnel.h"

int bindUDPSocket()
{
	int udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if(udpSocket <= 0)
	{
		write(2, "Unable to bind socket!\r\n", 24);
		return -1;
	}
	
	return udpSocket;
}