#include "mobilereminder.h"

void sendPacket()
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
		strcpy(buffer, timeToString(currentAlarm->reminderNumber));
		strcat(buffer, " ");
		writeTimeOfDay(buffer);
		strcat(buffer, currentAlarm->reminder);
		strcat(buffer, "\r\n");
		#ifdef Debug
			printf("Packet: %s\r\n", buffer);
		#endif
	}
	
	mySendTo(udpSocket, buffer, length, 0, registeredaddr, addrlen);
}
