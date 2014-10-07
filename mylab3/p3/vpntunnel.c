#include "vpntunnel.h"

int main(int argc, char** argv)
{
	if(checkArgc(argc, 5, "You must supply a VPN IP, VPN Port, Server IP, Server Port, and Secret Key!"))
	{
		return 1;
	}
	
	int serverPort = parseAndCheckPort(argv[4]);
	#ifdef Debug
		printf("Server Port: %d\r\n", serverPort);
	#endif
	
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
	struct sockaddr vpnaddr;
	struct sockaddr serveraddr;
	
	int udpSocket = bindUDPSocket();
	
	int resp = populateSockAddr(AF_INET, (struct sockaddr_in*)&vpnaddr, addrlen, vpnPort, argv[1]);
	if(resp < 0)
	{
		return 1;
	}
	
	resp = populateSockAddr(AF_INET, (struct sockaddr_in*)&serveraddr, addrlen, serverPort, argv[3]);
	if(resp < 0)
	{
		return 1;
	}
	
	strcpy(buffer, secret);
	strcat(buffer, "\r\n");
	strcat(buffer, argv[3]);
	strcat(buffer, "\r\n");
	strcat(buffer, argv[4]);
	
	if(sendto(udpSocket, buffer, msglen, 0, &vpnaddr, addrlen) <= 0)
	{
		perror("Sendto");
		return 1;
	}
	
	printf("Sent:\r\n%s\r\n", buffer);
}
