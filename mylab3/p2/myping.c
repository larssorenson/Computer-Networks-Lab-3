#include "ping.h"

int main(int argc, char** argv)
{

	// Check argument count, need <IP> and <Port>
	if (argc < 3)
	{
		write(2, "You must supply an IP address followed by a port!\r\n", 25);
		return -1;
	}
	
	// My own string to int function
	int port = numberFromString(argv[2]);
	
	// Check the bounds of the port, following lab spec
	if (port < 49152 || port > 65535)
	{
		write(2, "The port must be between 49152 and 65535!\r\n", 43);
		return -1;
	}
	
	#ifdef Debug
		printInt(port);
	#endif
	
	// Malloc our '0' buffer
	char *buffer = mallocAndCheck(sizeof(char)*1025);
	
	// Fill it with '0''s
	for(int x = 0; x < 1024; x++)
	{
		buffer[x] = '0';
	}
	
	// Null terminate
	buffer[1024] = 0;
	int msglen = 1024;
	
	socklen_t addrlen = (socklen_t)sizeof(struct sockaddr_storage);
	
	// Pick up a socket
	int tcpSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(tcpSocket <= 0)
	{
		write(2, "Unable to bind socket!\r\n", 24);
		return -1;
	}
	
	// Struct to hold the port and address of the server
	struct sockaddr_in serveraddr;
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	
	// Parse the ipv4 address to the struct
	if(inet_pton(AF_INET, argv[1], &serveraddr.sin_addr) <= 0)
	{
		write(2, "Failed to parse IP Address!\r\n", 29);
		return -1;
	}
	
	if(connect(tcpSocket, (struct sockaddr *)&serveraddr, addrlen))
	{
		perror("Connect");
		return -1;
	}
	
	int resp;
	
	// Timestamp before we send the packet
	struct timeval before;
	gettimeofday(&before, NULL);
	struct timeval after;
	
	// Send aforementioned packet
	resp = write(tcpSocket, buffer, msglen);
	
	if(resp <= 0)
	{
		write(2, "The message could not be sent!\r\n", 32);
		return -1;
	}
	
	// Busy wait for response
	while(read(tcpSocket, buffer, 1024) <= 0)
	{}
	
	
	#ifdef Debug
		printf("\r\nReceived: %s\r\n", buffer);
	#endif
	
	// Get our after timestamp and print the results
	gettimeofday(&after, NULL);
	printf("To: %s at port %d\r\nTotal Time: %d nanoseconds\r\n", argv[1], port, (int)(after.tv_usec - before.tv_usec));

	// Close up the connection
	close(tcpSocket);	
	return 0;
}
