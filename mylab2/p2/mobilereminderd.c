#include "mobilereminder.h"

int main(int argc, char** argv)
{
	// Need the file to read from
	if(argc < 4)
	{
		write(2, "You must supply a file name to read from, a port to listen on, and a secret key\r\n", 43);
		return 1;
	}
	
	char* secret = mallocAndCheck(sizeof(char)*strlen(argv[3]));
	int alarm_flag = 0;
	
	addrlen = (socklen_t)sizeof(struct sockaddr_storage);
	registeredaddr = mallocAndCheck(addrlen);
	
	strcpy(secret, argv[3]);
		
	// Set the alarm handler for SIGALRM
	if(setAlarmHandler())
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
		
		int valid = 0;
		int lastReminder = -1;
		int registered = 0;
		while(currentAlarm != NULL)
		{
			memset(buffer, 0, 1024);
			// Block for message
			while(recvfrom(udpSocket, buffer, 1024, 0, &clientaddr, &addrlen) <= 0 && currentAlarm != NULL)
			{ }
			
			if(currentAlarm == NULL)
				continue;
			
			// Indicate success and determine if responding
			write(2, "Got a message from ", 19);
			write(2, inet_ntoa(((struct sockaddr_in *)&clientaddr)->sin_addr), strlen(inet_ntoa(((struct sockaddr_in *)&clientaddr)->sin_addr)));
			write(2, "\r\n", 2);
			#ifdef Debug
				printf("Packet: %s\r\n", buffer);
			#endif
			#ifndef Debug
				write(2, "Packet: ", 8);
				write(2, buffer, strlen(buffer));
				write(2, "\r\n", 2);
			#endif
			// Check our packet for validity.
			// For the sake of reliability
			// it will accept [a-zA-Z0-9\t]
			valid = checkForValidity(buffer);
			#ifdef Debug
				printf("Valid? %s\r\n", (valid ? "True" : "False"));
			#endif
			
			// If the packet is valid and it has our secret
			if(valid && strstr(buffer, secret))
			{
				// Indicate registration!
				write(2, "Got a valid registration!\r\n", 27);
				
				// If we already had a client, we drop them.
				if(registered)
				{
					mySendTo(udpSocket, "DropRegistration\r\n\r\n", (int)20, 0, registeredaddr, addrlen);
				}
				
				// Copy our new address over our old address
				memcpy(registeredaddr, &clientaddr, addrlen);
				
				// Send our new registration packet
				mySendTo(udpSocket, "Registered\r\n\r\n", (int)14, 0, registeredaddr, addrlen);
				
				// If we haven't set an alarm before, we set one
				if(!alarm_flag)
				{
					setAlarm();				
					alarm_flag = 1;
				}
				
				// Otherwise, we rewind to the first alarm and start again
				else
				{
					rewindAlarms(0);
					setAlarm();				
					alarm_flag = 1;
					
				}
				
			}
			
			// If our received packet is invalid, we discard it
			else if (!valid)
			{
				write(2, "Invalid. Discarding\r\n", 21);
				continue; 
			}
			
			// If we've received a Resend packet, we will rewind
			// to the specified reminder and resend it.
			else if (strstr(buffer, "Resend\t"))
			{
				lastReminder = numberFromString(buffer+7);
				#ifdef Debug
					printf("Rewind to: %d\r\n", lastReminder);
				#endif
				rewindAlarms(lastReminder);
				#ifdef Debug
					printf("Rewinded to: %d\r\n", currentAlarm->reminderNumber);
				#endif
				sendPacket();
			}
			
			// Valid packet with invalid secret key
			// Let the client know they failed
			else
			{
				mySendTo(udpSocket, "Invalid Secret Key.\r\n", 22, 0, &clientaddr, addrlen);
				write(2, "Invalid Secret Key.\r\n", 21);
				continue;
			}
		
		}
		
		writeAlarm(0);
		
	}
	
	return 0;
}
