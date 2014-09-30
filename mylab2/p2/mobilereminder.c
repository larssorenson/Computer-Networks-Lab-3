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
	
	// Malloc space for our secret key
	secret = mallocAndCheck(sizeof(char)*strlen(argv[3]));
	
	strcpy(secret, argv[3]);
	#ifdef Debug
		printf("Secret: %s\r\n", secret);
	#endif
	
	char *buffer = mallocAndCheck(sizeof(char)*1024);
	
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
	
	registeredaddr = mallocAndCheck(addrlen);
	
	((struct sockaddr_in *)registeredaddr)->sin_family = AF_INET;
	((struct sockaddr_in *)registeredaddr)->sin_port = htons(port);
	
	// Parse the arg given to us for the IP
	if(inet_pton(AF_INET, argv[1], &((struct sockaddr_in *)registeredaddr)->sin_addr) <= 0)
	{
		write(2, "Failed to parse IP Address!\r\n", 29);
		return -1;
	}
	
	int reminders = 1;
	int registered = 0;
	int lastReminder = 0;
	setClientAlarmHandler();
	
	// While we have reminders to receive
	while(reminders)
	{
		
		for(x = 0; x < 1024; x++)
		{
			buffer[x] = '\0';
		}
		
		// If we've not registered, send a registration packet
		if(!registered)
		{
			registration(0);
		}
		
		// Busy wait for a packet
		while(recvfrom(udpSocket, buffer, msglen, 0, registeredaddr, &addrlen) <= 0)
		{
			// If we've not received a registration ACK
			// and we don't have an alarm set to send it
			// again, we'll set a timer
			if(!alarmSet)
				setClientAlarm();
		}
	
		#ifdef Debug
			printf("\r\nReceived: %s\r\n", buffer);
		#endif
		
		// Exit packet will tell us when we're done
		if(strcmp(buffer, "Exit\r\n\r\n") == 0)
		{
			write(2, "All Reminders Received!\r\n", 25);
			reminders = 0;
		}
		
		// Our registration was dropped!
		else if (strcmp(buffer, "DropRegistration\r\n\r\n") == 0)
		{
			write(2, "Registration Dropped!\r\n", 23);
			registered = 0;
		}
		
		// Our registration was accepted!
		else if (strcmp(buffer, "Registered\r\n\r\n") == 0)
		{
			write(2, "Registered!\r\n", 13);
			registered = 1;
			alarm(0);
		}
		
		// Default case
		else
		{
			int number = numberFromString(buffer);
			#ifdef Debug
				printf("Received: %d, Last: %d\r\n", number, lastReminder);
			#endif
			
			// If we've received a reminder that is more than just the increment
			// of the last one, send the resend packet
			if(number - lastReminder > 1)
			{
				// WE LOST A PACKET!
				char* resend = mallocAndCheck(sizeof(char)*8 + sizeof(int));
				memset(resend, 0, sizeof(char)*8 + sizeof(int));
				strcpy(resend, "Resend\t");
				strcat(resend, timeToString(lastReminder+1));
				mySendTo(udpSocket, resend, strlen(resend), 0, registeredaddr, addrlen);
			}
			
			// Otherwise, cancel our registration alarm if we've had one
			// and update our last received reminder.
			// Display the reminder packet;
			else
			{
				alarm(0);
				alarmSet = 0;
				lastReminder = number;
				write(2, buffer, strlen(buffer));
				write(2, "\r\n", 2);
			}
			
		}
		
	}
	
	return 0;
}
