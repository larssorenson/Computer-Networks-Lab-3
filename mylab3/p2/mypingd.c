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
	
	int msglen = 1024;
	char buffer[msglen];
	
	// Socket alloc
	int tcpSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(tcpSocket <= 0)
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
	if(bind(tcpSocket, (struct sockaddr*)&myaddr, sizeof(struct sockaddr)))
	{
		perror("Bind");
		return -1;
	}
	
	if(listen(tcpSocket, 1) != 0)
	{
		perror("Listen");
		return -1;
	}
	
	int new_socket;
	// Infinite response
	int resp;
	while(1)
	{
		if((new_socket = accept(tcpSocket, &clientaddr, &addrlen)) < 0)
		{
			perror("Accept");
			return -1;
		}

		// receive the message
		while(read(new_socket, buffer, msglen) <= 0)
		{}
		
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
			resp = write(new_socket, buffer, msglen);
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
