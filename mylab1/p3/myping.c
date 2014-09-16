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
	char *buffer = malloc(sizeof(char)*1025);
	if(!buffer)
	{
		write(2, "Unable to malloc for buffer!\r\n", 30);
	}
	
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
	int udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if(udpSocket <= 0)
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
	
	int resp;
		
	// Attempt to connect to the server
	resp = connect(udpSocket, (struct sockaddr*)&serveraddr, addrlen);
	
	if(resp <= -1)
	{
		write(2, "Failed to connect to the server!\r\n", 39);
		#ifdef Debug
			perror("Connect");
		#endif
		return -1;
	}
	
	
	// Timestamp before we send the packet
	struct timeval before;
	gettimeofday(&before, NULL);
	struct timeval after;
	
	// Send aforementioned packet
	resp = sendto(udpSocket, buffer, msglen, 0, (struct sockaddr*)&serveraddr, addrlen);
	
	if(resp <= 0)
	{
		write(2, "The message could not be sent!\r\n", 32);
		return -1;
	}
	
	// Busy wait for response
	while(recvfrom(udpSocket, buffer, 1024, 0, (struct sockaddr*)&serveraddr, &addrlen) <= 0)
	{}
	
	
	#ifdef Debug
		printf("\r\nReceived: %s\r\n", buffer);
	#endif
	
	// Get our after timestamp and print the results
	gettimeofday(&after, NULL);
	printf("To: %s at port %d\r\nTotal Time: %d nanoseconds\r\n", argv[1], port, (int)(after.tv_usec - before.tv_usec));

	// Close up the connection
	close(udpSocket);	
	return 0;
}
