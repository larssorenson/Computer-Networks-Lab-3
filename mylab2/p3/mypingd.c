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
	
	// Struct for the incoming connection
	struct sockaddr clientaddr;
	socklen_t addrlen = (socklen_t)sizeof(struct sockaddr_storage);
	
	char buffer[1024];
	int msglen = 1024;
	
	
	// Socket alloc
	int udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if(udpSocket <= 0)
	{
		write(2, "Unable to bind socket!\r\n", 24);
		return -1;
	}
	
	// My own address struct, choosing any possible IN ADDRESS
	struct sockaddr_in myaddr;
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(port);
	myaddr.sin_addr.s_addr = INADDR_ANY;
	
	// Bind up the socket to myself
	if(bind(udpSocket, (struct sockaddr*)&myaddr, sizeof(struct sockaddr)))
	{
		perror("Bind");
		return -1;
	}
	
	// Infinite response
	int resp;
	while(1)
	{
		// receive the message
		resp = recvfrom(udpSocket, buffer, 1024, 0, &clientaddr, &addrlen);
		if(resp <= 0)
		{
			write(2, "Failed to receive message!\r\n", 28);
			break;
		}
		
		// Indicate our success
		write(2, "Got a message!\r\n", 16);
		
		// FORK!
		int pid = fork();
		#ifdef Debug
			printf("PID: %d\r\n", pid);
		#endif
		// Child process
		if(pid == 0)
		{
			// Send it right back to them, round trip baby!
			resp = sendto(udpSocket, buffer, msglen, 0, &clientaddr, addrlen);
			if(resp <= 0)
			{
				write(2, "The message could not be sent!\r\n", 32);
				break;
			}
		}
		// Failed to fork	
		else if (pid == -1)
		{
			perror("Fork failed");
			break;
		}
		// We're the parent, so we do nothing.
		else
		{
			
		}
		
	}
	
	return 0;
}
