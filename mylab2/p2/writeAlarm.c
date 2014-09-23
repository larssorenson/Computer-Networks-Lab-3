#include "mobilereminder.h"

// Output the time of day, followed by the current Alarm's reminder
// Then set an alarm for the next reminder
void writeAlarm(int sig)
{
	if(registeredaddr != (struct sockaddr *)NULL)
	{
		
		char* buffer;
		int length;
		if(currentAlarm == NULL)
		{
			length = 9;
			buffer = malloc(sizeof(char)*length);
			memset(buffer, 0, length);
			strcpy(buffer, "Exit\r\n\r\n");
		}
		else
		{
			length = (strlen(currentAlarm->reminder)+10+3);
			buffer = malloc(sizeof(char)*length);
			if(!buffer)
			{
				printf("Failed to malloc for writing alarm to packet!\r\n");
				exit(-1);
			}
		
			memset(buffer, 0, length);
			writeTimeOfDay(buffer);
			strcat(buffer, currentAlarm->reminder);
			strcat(buffer, "\r\n");
			#ifdef Debug
				printf("Packet: %s\r\n", buffer);
			#endif
		}
		
		sendto(udpSocket, buffer, length, 0, registeredaddr, addrlen);
		if(currentAlarm != NULL)
		{
			currentAlarm = currentAlarm->next;
			setAlarm();
		}
		
	}
	
}
