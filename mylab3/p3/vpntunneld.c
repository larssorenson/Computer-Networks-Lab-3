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
	struct sockaddr vpnaddr;
	
	int udpSocket = bindUDPSocket();
	
	struct sockaddr clientaddr;
	struct sockaddr_in serveraddr;
	
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
	
	while(1)
	{
		while(recvfrom(udpSocket, buffer, 1024, 0, &clientaddr, &addrlen) <= 0)
		{ }
	
		printf("Packet:\r\n%s\r\n", buffer);
		int c;
		
		char* secret;
		int secretLen = 0;
		int secretFlag = 0;
		
		char* ip;
		int ipLen = 0;
		int ipFlag = 0;
		
		char* recPort;
		int portLen = 0;
		
		for(c = 0; c < strlen(buffer); c++)
		{
			if(!secretFlag)
			{
				if(buffer[c] != '\n')
					secretLen++;
				else
				{
					secret = mallocAndCheck(secretLen+1);
					strncpy(secret, buffer, secretLen);
					secret[secretLen] = '\0';
					secretFlag = 1;
					#ifdef Debug
						printf("Secret Received: %s\r\n", secret);
					#endif
				}
				
			}
			
			else if (!ipFlag)
			{
				if(buffer[c] != '\n')
					ipLen++;
				else
				{
					ip = mallocAndCheck(ipLen+1);
					strncpy(ip, buffer+(secretLen+1), ipLen);
					ip[ipLen] = '\0';
					ipFlag = 1;
					#ifdef Debug
						printf("IP Received: %s\r\n", ip);
					#endif
				}
				
			}
			
			else
			{
				if(buffer[c] != '\n')
					portLen++;
			}
			
		}
		
		recPort = mallocAndCheck(portLen+1);
		strncpy(recPort, buffer+(secretLen+1)+(ipLen+1), portLen);
		recPort[portLen] = '\0';
		#ifdef Debug
			printf("Port Received: %s\r\n", recPort);
		#endif
	
		int serverPort = parseAndCheckPort(recPort);
		#ifdef Debug
			printf("Server Port: %d\r\n", serverPort);
		#endif
	
		serveraddr.sin_family = AF_INET;
		serveraddr.sin_port = htons(serverPort);
		
		// Parse the IP
		if(inet_pton(AF_INET, ip, &(serveraddr.sin_addr.s_addr)) <= 0)
		{
			write(2, "Failed to parse IP Address!\r\n", 29);
			return -1;
		}
	
	}
	
}
