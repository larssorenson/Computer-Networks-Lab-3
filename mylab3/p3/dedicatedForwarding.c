#include "vpntunnel.h"

int dedicatedForwarding(struct sockaddr_in serveraddr_in, struct sockaddr_in clientaddr, struct sockaddr_in vpnaddr, int port)
{
	socklen_t addrlen = (socklen_t)sizeof(struct sockaddr_storage);
	struct sockaddr_in inaddr;
	
	struct sockaddr_in * serveraddr = mallocAndCheck(sizeof(struct sockaddr_in));
	memset(serveraddr, 0, (ssize_t)addrlen);
	memcpy(serveraddr, &serveraddr_in, (ssize_t)addrlen);
	
	
	
	int pid = fork();
	if(pid == -1)
	{
		perror("Fork");
		exit(1);
	}
	else if(pid == 0)
	{
		struct sockaddr_in myaddr;
		myaddr.sin_family = AF_INET;
		myaddr.sin_addr.s_addr = ((struct sockaddr_in *)&vpnaddr)->sin_addr.s_addr;
		myaddr.sin_port = htons(port);
		
		int forwarding = bindUDPSocket();
		
		struct sockaddr_in *received = mallocAndCheck(sizeof(struct sockaddr_in));
		memset(received, 0, sizeof(struct sockaddr_in));
		memcpy(received, &clientaddr, (ssize_t)addrlen);
		
		if(bind(forwarding, (struct sockaddr*)&myaddr, addrlen))
		{
			perror("Bind");
			return -1;
		}
		
		#ifdef Debug
			printf("Listening from %s:%d and %s:%d\r\n", inet_ntoa(((struct sockaddr_in *)&clientaddr)->sin_addr), ntohs(((struct sockaddr_in *)&clientaddr)->sin_port), inet_ntoa(((struct sockaddr_in *)serveraddr)->sin_addr), ntohs(((struct sockaddr_in *)serveraddr)->sin_port));
		#endif
		while(1)
		{
			char* buffer = mallocAndCheck(1024);
			memset(buffer, 0, 1024);
			
			while(recvfrom(forwarding, buffer, 1024, 0, (struct sockaddr *)&inaddr, &addrlen) <= 0)
			{ }
			
			#ifdef Debug
				printf("Received packet: %s from %s:%d\r\n", buffer, inet_ntoa(inaddr.sin_addr), ntohs(inaddr.sin_port));
			#endif
			
			// If we received a packet from the server, we send it to the client.
			// And vice versa.
			if (inaddr.sin_port == serveraddr->sin_port && inaddr.sin_addr.s_addr == serveraddr->sin_addr.s_addr)
			{
				#ifdef Debug
					printf("Sending packet to client: %s:%d\r\n", inet_ntoa(received->sin_addr), ntohs(received->sin_port));
				#endif
				if(sendto(forwarding, buffer, 1024, 0, (struct sockaddr *)received, addrlen) <= 0)
				{
					perror("Sendto");
					return 1;
				}
				
			}
			// The port could be the same or different as the server address
			// And the IP could be the same as the server, but the port and IP cannot be the same at the same time
			else if((inaddr.sin_port != serveraddr->sin_port && inaddr.sin_addr.s_addr != serveraddr->sin_addr.s_addr)
			|| (inaddr.sin_port == serveraddr->sin_port && inaddr.sin_addr.s_addr != serveraddr->sin_addr.s_addr)
			|| (inaddr.sin_port != serveraddr->sin_port && inaddr.sin_addr.s_addr == serveraddr->sin_addr.s_addr))
			{
				#ifdef Debug
					printf("Old address: %s:%d\r\n", inet_ntoa(received->sin_addr), ntohs(received->sin_port));
				#endif
				memcpy(received, &inaddr, (ssize_t)addrlen);
				#ifdef Debug
					printf("Sending packet to server: %s:%d\r\n", inet_ntoa(serveraddr->sin_addr), ntohs(serveraddr->sin_port));
					printf("New address: %s:%d\r\n", inet_ntoa(received->sin_addr), ntohs(received->sin_port));
				#endif
				
				if(sendto(forwarding, buffer, 1024, 0, (struct sockaddr *)serveraddr, addrlen) <= 0)
				{
					perror("Sendto");
					return 1;
				}
				
			}
			
		}
		
	}
	
	return 0;
	
}
