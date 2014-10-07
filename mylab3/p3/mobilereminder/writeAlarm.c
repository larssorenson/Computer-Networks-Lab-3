#include "mobilereminder.h"

// Output the time of day, followed by the current Alarm's reminder
// Then set an alarm for the next reminder
void writeAlarm(int sig)
{
	if(registeredaddr != (struct sockaddr *)NULL)
	{
		
		sendPacket();
		if(currentAlarm != NULL)
		{
			currentAlarm = currentAlarm->next;
			setAlarm();
		}
		
	}
	
}
