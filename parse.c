#include "myreminder.h"

Alarm* parse(char* file)
{
	if(file)
	{
		char buffer[2];
		buffer[1] = '\0';
		int fd = open(file, O_RDONLY);
		int c = 1;
		int timeFlag = 0;
		if(fd > 1)
		{
			Alarm* currentAlarm = (Alarm*)malloc(sizeof(Alarm));
			currentAlarm->prev = NULL;
			
			while(c != 0)
			{
				c = read(fd, buffer, 1);
				if(c <= 0)
					continue;
				
				if(buffer[0] == '\0')
				{
					currentAlarm = currentAlarm->prev;
					free(currentAlarm->next);
					c = 0;
					continue;
				}
				
				#ifdef Debug
					printf("Read: %c\r\n", buffer[0]);
				#endif
				
				if(!timeFlag)
				{
					if(buffer[0] == ' ')
					{
						timeFlag = 1;
						#ifdef Debug
							printf("Done parsing time! Final: %d\r\n", currentAlarm->time);
						#endif
						currentAlarm->reminder = (char*)malloc(sizeof(char)*1024);
						memset(currentAlarm->reminder, 0, 1024);
					}
					
					else
					{
						int resp = addTimeToAlarm(currentAlarm, buffer[0]);
						if(resp)
							printf("Error! Failed to update alarm's time! Check input of file");
						
					}
					
				}
				
				else
				{
					if(buffer[0] != '\r' && buffer[0] != '\n' && buffer[0] != '\0')
					{
						strcat(currentAlarm->reminder, buffer);
					}
					
					else
					{
						timeFlag = 0;
						#ifdef Debug
							printf("Done parsing line! Result: %s\r\n", currentAlarm->reminder);
						#endif
						currentAlarm->next = (Alarm*)malloc(sizeof(Alarm));
						currentAlarm->next->prev = currentAlarm;
						currentAlarm = currentAlarm->next;
					}
					
				}
				
			}
			
			currentAlarm->next = NULL;
			while(currentAlarm->prev != NULL)
				currentAlarm = currentAlarm->prev;
			return currentAlarm;
			
		}
		
		
	}
	
	return NULL;
	
}

#ifdef Debug
int main(int argc, char** argv)
{
		if(argc > 0 && argv[1])
		{
			Alarm* alarms = parse(argv[1]);
			while(alarms->next != NULL)
			{
				printf("%d: %s\r\n", alarms->time, alarms->reminder);
				alarms = alarms->next;
			}
			
		}
	
	return 1;
}
#endif
