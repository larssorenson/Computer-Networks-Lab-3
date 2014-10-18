#include "vpntunnel.h"

int serverToClient(struct sockaddr_in serveraddr, struct sockaddr_in clientaddr)
{
	socklen_t addrlen = (socklen_t)sizeof(struct sockaddr_storage);
	struct sockaddr inaddr;
	int pid = fork();
	if(pid == -1)
	{
		perror("Fork");
		exit(1);
	}
	else if(pid == 0)
	{
		/*int serverToClient = bindUDPSocket();
		
		if(bind(serverToClient, (struct sockaddr*)&serveraddr, addrlen))
		{
			perror("Bind");
			return -1;
		}*/
		
		while(1)
		{
			char* buffer = mallocAndCheck(1024);
			memset(buffer, 0, 1024);
			while(recvfrom(serverToClient, buffer, 1024, 0, &inaddr, &addrlen) <= 0)
			{ }
			
			if(sendto(serverToClient, buffer, 1024, 0, (struct sockaddr*)&clientaddr, addrlen) <= 0)
			{
				perror("Sendto");
				return 1;
			}
			
		}
		
	}
	
	return 0;
	
}
