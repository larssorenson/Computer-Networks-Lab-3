#include "mobilereminder.h"

Alarm* parse(char* file)
{
	// If we have a proper file name
	if(file)
	{
		// Declare our single byte buffer
		char buffer[2];
		buffer[1] = '\0';
		int fd = open(file, O_RDONLY);
		int c = 1;
		int resp;
		int timeFlag = 0;
		int msgCount = 0;
		
		// If we have a proper file descriptor
		if(fd > 1)
		{
			currentAlarm = (Alarm*)malloc(sizeof(Alarm));
			currentAlarm->prev = NULL;
			
			// While we've read a byte
			while(c != 0)
			{
				c = read(fd, buffer, 1);
				if(c <= 0)
					continue;
				
				
				// Null terminator character signals end of parsing
				// We alloc a new link at the end of parsing a line
				// so it should be empty
				if(buffer[0] == '\0')
				{
					// Move back a step
					currentAlarm = currentAlarm->prev;
					
					// Cut off the current link
					currentAlarm->next->prev = NULL;
					
					// Free up memory if it's being used
					if(currentAlarm->next->reminder)
						free(currentAlarm->next->reminder);
						
					// Free the dangling link
					free(currentAlarm->next);
					
					// Cap off the list
					currentAlarm->next = NULL;
					c = 0;
					continue;
				}
				
				#ifdef Debug
					write(2, "Read: ", 6);
					write(2, buffer, 1);
					write(2, "\r\n", 2);
				#endif
				
				// Flag to indicate if we're parsing time or message
				if(!timeFlag)
				{
				
					// first space should only come after time
					if(buffer[0] == ' ')
					{
					
						// Flip the flag, we're parsing message now
						timeFlag = 1;
						
						#ifdef Debug
							char* currentTime = timeToString(currentAlarm->time);
							if(currentTime)
							{
								write(2, "Done parsing time! Final: ", 26);
								write(2, currentTime, strlen(currentTime));
								write(2, "\r\n", 2);
								free(currentTime);
							}
							
						#endif
						
						// Malloc space for the current reminder and zero it
						currentAlarm->reminder = (char*)malloc(sizeof(char)*1024);
						memset(currentAlarm->reminder, 0, 1024);
					}
					
					else
					{
						// If we're parsing time, continually update the time of the current alarm
						resp = addTimeToAlarm(buffer[0]);
						if(resp)
						{
							write(2, "Error! Failed to update alarm's time! Check input of file\r\n", 59);
							return NULL;
						}
						
					}
					
				}
				
				else
				{
					// If we're done parsing time, as long as we're not reading new line or EOL, update the message
					if(buffer[0] != '\r' && buffer[0] != '\n' && buffer[0] != '\0' && msgCount < 1024)
					{
						strcat(currentAlarm->reminder, buffer);
						msgCount++;
					}
					
					else
					{
						timeFlag = 0;
						msgCount = 0;
						#ifdef Debug
							if(currentAlarm->reminder)
							{
								write(2, "Done parsing line! Result: ", 27);
								write(2, currentAlarm->reminder, strlen(currentAlarm->reminder));
								write(2, "\r\n", 2);
							}
							
							else
							{
								write(2, "Error reading Reminder!\r\n", 25);
							}
						#endif
						// Alloc space for the next alarm
						currentAlarm->next = (Alarm*)malloc(sizeof(Alarm));
						
						// Maintain the chain
						currentAlarm->next->prev = currentAlarm;
						
						// Move forward
						currentAlarm = currentAlarm->next;
					}
					
				}
				
			}
			
			// Double check that the list is properly maintained
			currentAlarm->next = NULL;
			
			// Move the pointer back to the beginning of the list, as we operate on this list globally
			while(currentAlarm->prev != NULL)
			{
				// If the last alarm does not have an actual reminder, then we should clip off the link
				if(currentAlarm->next && !currentAlarm->next->reminder)
				{
					Alarm* last = currentAlarm->next;
					if(currentAlarm->next->next)
					{
						currentAlarm->next = currentAlarm->next->next;
						currentAlarm->next->next->prev = currentAlarm;
					}
					else
						currentAlarm->next = NULL;
					
					free(last);
				}
				
				currentAlarm = currentAlarm->prev;
			}
			
			// Indicate that we successfully parsed the file
			return currentAlarm;
		}
		
	}
	
	return NULL;
}

// Modular testing
#ifdef Testing
int main(int argc, char** argv)
{
		if(argc > 0 && argv[1])
		{
			parse(argv[1]);
			if(currentAlarm)
			{
				while(currentAlarm->next != NULL)
				{
					char* currentTime = timeToString(currentAlarm->time);
					if(currentTime)
					{
						write(2, currentTime, strlen(currentTime));
						write(2, ": ", 2);
						write(2, currentAlarm->reminder, strlen(currentAlarm->reminder));
						write(2, "\r\n", 2);
						free(currentTime);
					}
					
					currentAlarm = currentAlarm->next;
				}
			
			}
			
		}
	
	return 1;
}
#endif
