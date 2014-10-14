#include "vpntunnel.h"

int main(int argc, char** argv)
{
	if(checkArgc(argc, 5, "You must supply a VPN IP, VPN Port, Server IP, Server Port, and Secret Key!"))
	{
		return 1;
	}
	
	
	int vpnPort = parseAndCheckPort(argv[2]);
	#ifdef Debug
		printf("VPN Port: %d\r\n", vpnPort);
	#endif
	
	char* secret = mallocAndCheck(sizeof(char)*strlen(argv[5]));
	int x;
	for(x = 0; x < strlen(argv[5]); x++)
		secret[x] = 0;
	
	strcpy(secret, argv[5]);
	#ifdef Debug
		printf("Secret: %s\r\n", secret);
	#endif
	
	int msglen = strlen(secret) + 4 + strlen(argv[3]) + strlen(argv[4]);
	char *buffer = mallocAndCheck(sizeof(char)*msglen);
	for(x = 0; x < msglen; x++)
		buffer[x] = 0;
	
	socklen_t addrlen = (socklen_t)sizeof(struct sockaddr_storage);
	struct sockaddr_in vpnaddr;
	
	int udpSocket = bindUDPSocket();
	
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
	
	strcpy(buffer, secret);
	strcat(buffer, "\r\n");
	strcat(buffer, argv[3]);
	strcat(buffer, "\r\n");
	strcat(buffer, argv[4]);
	strcat(buffer, "\r\n");
	
	if(sendto(udpSocket, buffer, msglen, 0, (struct sockaddr *)&vpnaddr, addrlen) <= 0)
	{
		perror("Sendto");
		return 1;
	}
	
	printf("Sent:\r\n%s\r\n", buffer);
}
