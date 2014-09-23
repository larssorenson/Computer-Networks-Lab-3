#include "ping.h"

int main(int argc, char** argv)
{
	// Argument check
	if (argc < 2)
	{
		write(2, "You must supply a port!\r\n", 25);
		return -1;
	}
	
	// Port parse and check
	int port = numberFromString(argv[1]);
	if (port < 49152 || port > 65535)
	{
		write(2, "The port must be between 49152 and 65535!\r\n", 43);
		return -1;
	}
	
	#ifdef Debug
		printInt(port);
		write(2, "\r\n", 2);
	#endif
	
	struct sockaddr clientaddr;
	socklen_t addrlen = (socklen_t)sizeof(struct sockaddr_storage);
	
	char buffer[1024];
	int msglen = 1024;
	
	// Pick up a socket
	udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if(udpSocket <= 0)
	{
		write(2, "Unable to bind socket!\r\n", 24);
		return -1;
	}
	
	// Set up my address, for port binding
	struct sockaddr_in myaddr;
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(port);
	myaddr.sin_addr.s_addr = INADDR_ANY;
	
	// Bind said port to the acquired socket
	if(bind(udpSocket, (struct sockaddr*)&myaddr, sizeof(struct sockaddr)))
	{
		perror("Bind");
		return -1;
	}
	
	int count = 0;
	int resp;
	while(1)
	{
		// Block for message
		resp = recvfrom(udpSocket, buffer, 1024, 0, &clientaddr, &addrlen);
		if(resp <= 0)
		{
			write(2, "Failed to receive message!\r\n", 28);
			break;
		}
		
		// Indicate success and determine if responding
		write(2, "Got a message!\r\n", 16);
		if(count%2)
		{
			// I'm in a good mood, so I'll respond.
			write(2, "I'll respond...this time.\r\n", 27);
			resp = sendto(udpSocket, buffer, msglen, 0, &clientaddr, addrlen);
			if(resp <= 0)
			{
				write(2, "The message could not be sent!\r\n", 32);
				break;
			}
		}
		
		else
		{
			// I'm tempermental today, so no response
			write(2, "Nope.\r\n", 7);
		}
		
		count++;
		
	}
	
	return 0;
}
