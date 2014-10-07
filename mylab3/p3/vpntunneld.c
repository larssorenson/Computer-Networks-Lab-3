#include "vpntunnel.h"

int main(int argc, char** argv)
{
	if(checkArgc(argc, 2, "You must supply a VPN Port and Secret Key!"))
	{
		return 1;
	}
	
	int port = parseAndCheckPort(argv[1]);
	#ifdef Debug
		printf("Port: %d\r\n", port);
	#endif
	
	char* secret = mallocAndCheck(sizeof(char)*strlen(argv[2]));
	int x;
	for(x = 0; x < strlen(argv[2]); x++)
		secret[x] = 0;
	
	strcpy(secret, argv[2]);
	#ifdef Debug
		printf("Secret: %s\r\n", secret);
	#endif
	
	char* buffer = mallocAndCheck(1024);
	memset(buffer, 0, 1024);
	
	socklen_t addrlen = (socklen_t)sizeof(struct sockaddr_storage);
	struct sockaddr *vpnaddr = NULL;
	
	int udpSocket = bindUDPSocket();
	
	struct sockaddr clientaddr;
	// Set up my address, for port binding
	struct sockaddr_in myaddr;
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(port);
	myaddr.sin_addr.s_addr = INADDR_ANY;
	
	// Bind said port to the acquired socket
	if(bind(udpSocket, (struct sockaddr*)&myaddr, addrlen))
	{
		perror("Bind");
		return -1;
	}
	
	while(recvfrom(udpSocket, buffer, 1024, 0, &clientaddr, &addrlen) <= 0)
	{ }
	
	printf("Packet:\r\n%s\r\n", buffer);
	
}
