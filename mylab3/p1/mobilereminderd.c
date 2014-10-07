#include "mobilereminder.h"

int main(int argc, char** argv)
{
	// Need the file to read from
	if(argc < 4)
	{
		write(2, "You must supply a file name to read from, a port to listen on, and a secret key\r\n", 43);
		return 1;
	}
	
	char* secret = malloc(sizeof(char)*strlen(argv[3]));
	int alarm_flag = 0;
	
	addrlen = (socklen_t)sizeof(struct sockaddr_storage);
	registeredaddr = malloc(addrlen);
	
	strcpy(secret, argv[3]);
		
	// Set the alarm handler for SIGALRM
	int resp = setAlarmHandler();
	if(resp)
	{
		write(2, "Error! Could not set Signal Alarm Handler!\r\n", 44);
		return 1;
	}
	
	// Parse the file passed in
	if(parse(argv[1]))
	{
	
		// Port parse and check
		int port = numberFromString(argv[2]);
		if (port < 49152 || port > 65535)
		{
			write(2, "The port must be between 49152 and 65535!\r\n", 43);
			return -1;
		}
	
		#ifdef Debug
			printf("%d\r\n", port);
		#endif
	
		struct sockaddr clientaddr;
	
		char buffer[1024];
	
		// Pick up a socket
		udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
		if(udpSocket <= 0)
		{
			write(2, "Unable to bind socket!\r\n", 24);
			return -1;
		}
	
		// Set up my address, for port binding
		struct sockaddr_in myaddr;
		myaddr.sin_family = AF_INET;
		myaddr.sin_port = htons(port);
		myaddr.sin_addr.s_addr = INADDR_ANY;
	
		// Bind said port to the acquired socket
		if(bind(udpSocket, (struct sockaddr*)&myaddr, sizeof(struct sockaddr)))
		{
			perror("Bind");
			return -1;
		}
		
		int resp;
		int valid = 0;
		while(currentAlarm != NULL)
		{
			memset(buffer, 0, 1024);
			// Block for message
			while(recvfrom(udpSocket, buffer, 1024, 0, &clientaddr, &addrlen) <= 0 && currentAlarm != NULL)
			{ }
			
			if(currentAlarm == NULL)
				continue;
			
			// Indicate success and determine if responding
			write(2, "Got a message!\r\n", 16);
			#ifdef Debug
				printf("Packet: %s\r\n", buffer);
			#endif
			valid = checkForValidity(buffer);
			#ifdef Debug
				printf("Valid? %s\r\n", (valid ? "True" : "False"));
			#endif
			if(valid && strstr(buffer, secret))
			{
				write(2, "Got a valid registration!\r\n", 27);
				sendto(udpSocket, "DropRegistration\r\n\r\n", 20, 0, registeredaddr, addrlen);
				memcpy(registeredaddr, &clientaddr, addrlen);
				sendto(udpSocket, "Registered\r\n\r\n", 14, 0, registeredaddr, addrlen);
				if(!alarm_flag)
				{
					alarm_flag = 1;
					if(currentAlarm->time <= 0)
					{
						writeAlarm(0);
					}
	
					else
					{
						// Set the first alarm
						alarm(currentAlarm->time);
					}
				}
			}
			
			else if (!valid)
			{
				write(2, "Invalid. Discarding\r\n", 21);
				continue; 
			}
			
			else
			{
				sendto(udpSocket, "Invalid Secret Key.\r\n", 22, 0, &clientaddr, addrlen);
				sendto(udpSocket, "Exit\r\n\r\n",8, 0, &clientaddr, addrlen);
				write(2, "Invalid Secret Key.\r\n", 21);
				continue;
			}
		
		}
		
		writeAlarm(0);
		
	}
	
	return 0;
}
