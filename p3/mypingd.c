#include "ping.h"

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		write(2, "You must supply a port!\r\n", 25);
		return -1;
	}
	
	int port = numberFromString(argv[1]);
	if (port < 49152 || port > 65535)
	{
		write(2, "The port must be between 49152 and 65535!\r\n", 43);
		return -1;
	}
	
	#ifdef Debug
		printInt(port);
	#endif
	
	//struct hostent *server;
	struct sockaddr clientaddr;
	char buffer[1024];
	char* message = "Hello!";
	int msglen = 7;
	
	socklen_t addrlen = (socklen_t)sizeof(struct sockaddr_storage);
	
	int udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
	int resp;
	while(1)
	{
		resp = recvfrom(udpSocket, buffer, 2014, 0, &clientaddr, &addrlen);
		if(resp <= 0)
		{
			write(2, "Failed to receive message!\r\n", 28);
			break;
		}
		
		resp = connect(udpSocket, &clientaddr, addrlen);
		
		if(resp <= 0)
		{
			write(2, "Failed to connect back to the client!\r\n", 39);
			break;
		}
		
		resp = sendto(udpSocket, message, msglen, 0, &clientaddr, addrlen);
		
		if(resp <= 0)
		{
			write(2, "The message could not be sent!\r\n", 32);
			break;
		}
		
	}
	
	return 0;
}
