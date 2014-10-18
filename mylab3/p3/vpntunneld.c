#include "vpntunnel.h"

int main(int argc, char** argv)
{
	if(checkArgc(argc, 2, "You must supply a VPN Port!"))
	{
		return 1;
	}
	
	int port = parseAndCheckPort(argv[1]);
	#ifdef Debug
		printf("Port: %d\r\n", port);
	#endif
	
	char* buffer = mallocAndCheck(1024);
	memset(buffer, 0, 1024);
	
	socklen_t addrlen = (socklen_t)sizeof(struct sockaddr_storage);
	
	int udpSocket = bindUDPSocket();
	
	struct sockaddr_in clientaddr;
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
		while(recvfrom(udpSocket, buffer, 1024, 0, (struct sockaddr *)&clientaddr, &addrlen) <= 0)
		{ }
	
		printf("Packet:\r\n%s\r\n", buffer);
		int c;
		
		char* ip;
		int ipLen = 0;
		int ipFlag = 0;
		
		char* recPort;
		int portLen = 0;
		
		// Parse the packet for our IP address, port and secret.
		// This will allow us to redirect packets back to the client
		for(c = 0; c < strlen(buffer); c++)
		{
			if (!ipFlag)
			{
				if(buffer[c] != '\n')
					ipLen++;
				else
				{
					ip = mallocAndCheck(ipLen+1);
					strncpy(ip, buffer, ipLen);
					ip[ipLen-1] = '\0';
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
		strncpy(recPort, buffer+(ipLen+1), portLen);
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
		if(inet_pton(AF_INET, ip, &(serveraddr.sin_addr)) < 0)
		{
			perror("IP Parse");
			return -1;
		}
		
		printf("Parsed IP: %s\r\n", inet_ntoa(serveraddr.sin_addr));
		
		int newPort = ntohs(((struct sockaddr_in *)&serveraddr)->sin_port)-1;
		
		// Fork for this port and ip
		dedicatedForwarding(serveraddr, clientaddr, myaddr, newPort);
		
		char* message = mallocAndCheck(8);
		memset(message, 0, 8);
		
		char* portPacket = timeToString(newPort);
		
		printf("Sending port %s to client\r\n", portPacket);
		
		if(sendto(udpSocket, portPacket, strlen(portPacket), 0, (struct sockaddr *)&clientaddr, addrlen) <= 0)
		{
			perror("Sendto");
			return 1;
		}
	
	}
	
}
