#include "mobilereminder.h"

int main(int argc, char**argv)
{
	if (argc < 4)
	{
		write(2, "You must supply an IP address, a port, and a secret key!\r\n", 25);
		return -1;
	}
	
	#ifdef Debug
		printf("Argv[1]: %s\r\nArgv[2]: %s\r\nArgv[3]: %s\r\n", argv[1], argv[2], argv[3]);
	#endif
	
	int port = numberFromString(argv[2]);
	if (port < 49152 || port > 65535)
	{
		write(2, "The port must be between 49152 and 65535!\r\n", 43);
		return -1;
	}
	
	#ifdef Debug
		printf("Port: %d\r\n", port);
	#endif
	
	secret = malloc(sizeof(char)*strlen(argv[3]));
	if(!secret)
	{
		write(2, "Failed to malloc space for secret key!\r\n", 40);
		return -1;
	}
	
	strcpy(secret, argv[3]);
	#ifdef Debug
		printf("Secret: %s\r\n", secret);
	#endif
	
	char *buffer = malloc(sizeof(char)*1024);
	if(!buffer)
	{
		write(2, "Unable to malloc for buffer!\r\n", 30);
	}
	
	int x;
	for(x = 0; x < 1024; x++)
	{
		buffer[x] = '\0';
	}
	
	int msglen = 1024;
	
	addrlen = (socklen_t)sizeof(struct sockaddr_storage);
	
	udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if(udpSocket <= 0)
	{
		write(2, "Unable to bind socket!\r\n", 24);
		return -1;
	}
	
	registeredaddr = malloc(addrlen);
	
	((struct sockaddr_in *)registeredaddr)->sin_family = AF_INET;
	((struct sockaddr_in *)registeredaddr)->sin_port = htons(port);
	
	if(inet_pton(AF_INET, argv[1], &((struct sockaddr_in *)registeredaddr)->sin_addr) <= 0)
	{
		write(2, "Failed to parse IP Address!\r\n", 29);
		return -1;
	}
	
	int reminders = 1;
	int registered = 0;
	setClientAlarmHandler();
	while(reminders)
	{
		
		for(x = 0; x < 1024; x++)
		{
			buffer[x] = '\0';
		}
		
		if(!registered)
		{
			registration(0);
		}
		
		while(recvfrom(udpSocket, buffer, msglen, 0, registeredaddr, &addrlen) <= 0)
		{
			if(!alarmSet)
				setClientAlarm();
		}
	
		#ifdef Debug
			printf("\r\nReceived: %s\r\n", buffer);
		#endif
		if(strcmp(buffer, "Exit\r\n\r\n") == 0)
		{
			write(2, "All Reminders Received!\r\n", 25);
			reminders = 0;
		}
		
		else if (strcmp(buffer, "DropRegistration\r\n\r\n") == 0)
		{
			write(2, "Registration Dropped!\r\n", 23);
			registered = 0;
		}
		
		else if (strcmp(buffer, "Registered\r\n\r\n") == 0)
		{
			write(2, "Registered!\r\n", 13);
			registered = 1;
		}
		
		else
		{
			write(2, buffer, strlen(buffer));
		}
		
	}
	
	return 0;
}
