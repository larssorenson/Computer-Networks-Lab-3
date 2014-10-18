#include "vpntunnel.h"

int main(int argc, char** argv)
{
	if(checkArgc(argc, 5, "You must supply a VPN IP, VPN Port, Server IP, and Server Port!"))
	{
		return 1;
	}
	
	
	int vpnPort = parseAndCheckPort(argv[2]);
	#ifdef Debug
		printf("VPN Port: %d\r\n", vpnPort);
	#endif
	
	int msglen = strlen(argv[3]) + strlen(argv[4]) + 4;
	int x;
	
	char *buffer = mallocAndCheck(sizeof(char)*msglen);
	for(x = 0; x < msglen; x++)
		buffer[x] = 0;
	
	socklen_t addrlen = (socklen_t)sizeof(struct sockaddr_storage);
	
	int udpSocket = bindUDPSocket();
	
	struct sockaddr_in vpnaddr;
	vpnaddr.sin_family = AF_INET;
	vpnaddr.sin_port = htons(vpnPort);
	
	// Parse the arg given to us for the IP
	if(inet_pton(AF_INET, argv[1], &(vpnaddr.sin_addr)) <= 0)
	{
		write(2, "Failed to parse IP Address!\r\n", 29);
		return -1;
	}
	
	#ifdef Debug
		printf("Server Address: %s\r\n", inet_ntoa(vpnaddr.sin_addr));
	#endif
	
	strcpy(buffer, argv[3]);
	strcat(buffer, "\r\n");
	strcat(buffer, argv[4]);
	strcat(buffer, "\r\n");
	
	if(sendto(udpSocket, buffer, msglen, 0, (struct sockaddr *)&vpnaddr, addrlen) <= 0)
	{
		perror("Sendto");
		return 1;
	}
	
	printf("Sent:\r\n%s\r\n", buffer);
	
	memset(buffer, 0, 1024);
	
	while(recvfrom(udpSocket, buffer, 1024, 0, (struct sockaddr *)&vpnaddr, &addrlen) <= 0)
	{ }
	
	printf("VPN Port: %d\r\n", numberFromString(buffer));
}
