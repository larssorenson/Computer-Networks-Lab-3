#include "vpntunnel.h"

int dedicatedForward()
{
	int pid = fork()
	if(pid == -1)
	{
		perror("Fork");
		exit(1);
	}
	else if(pid == 0)
	{
		while(1)
		{
			
		}
		
	}
	
}
