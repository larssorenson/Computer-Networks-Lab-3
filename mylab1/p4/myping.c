#include "ping.h"

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		write(2, "You must supply an IP address followed by a port!\r\n", 25);
		return -1;
	}
	
	int port = numberFromString(argv[2]);
	if (port < 49152 || port > 65535)
	{
		write(2, "The port must be between 49152 and 65535!\r\n", 43);
		return -1;
	}
	
	#ifdef Debug
		printInt(port);
	#endif
	
	char *buffer = malloc(sizeof(char)*1024);
	if(!buffer)
	{
		write(2, "Unable to malloc for buffer!\r\n", 30);
	}
	
	int x;
	for(x = 0; x < 1024; x++)
	{
		buffer[x] = '0';
	}
	
	int msglen = 1024;
	
	setAlarmHandler();
	
	socklen_t addrlen = (socklen_t)sizeof(struct sockaddr_storage);
	
	udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if(udpSocket <= 0)
	{
		write(2, "Unable to bind socket!\r\n", 24);
		return -1;
	}
	
	struct sockaddr_in serveraddr;
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	
	if(inet_pton(AF_INET, argv[1], &serveraddr.sin_addr) <= 0)
	{
		write(2, "Failed to parse IP Address!\r\n", 29);
		return -1;
	}
	
	int resp;
	
	
	struct timeval before;
	gettimeofday(&before, NULL);
	struct timeval after;
	
	resp = sendto(udpSocket, buffer, msglen, 0, (struct sockaddr*)&serveraddr, addrlen);
	
	if(resp <= 0)
	{
		write(2, "The message could not be sent!\r\n", 32);
		return -1;
	}
	
	setAlarm(5);
	
	while(recvfrom(udpSocket, buffer, 1024, 0, (struct sockaddr*)&serveraddr, &addrlen) <= 0)
	{}
	
	close(udpSocket);
	
	#ifdef Debug
		printf("\r\nReceived: %s\r\n", buffer);
	#endif
	
	gettimeofday(&after, NULL);
	printf("To: %s at port %d\r\nTotal Time: %d nanoseconds\r\n", argv[1], port, (int)(after.tv_usec - before.tv_usec));
	
	return 0;
}
