#include "mobilereminder.h"

void setAlarm()
{
	alarm(0);
	// If we have an alarm available that can be set
	if(currentAlarm)
	{
		if(currentAlarm->prev != NULL)
		{
			// If we are out of time for the reminder, output it immediately!
			if(currentAlarm->time - currentAlarm->prev->time <= 0)
				writeAlarm(0);
			else
				// Otherwise, schedule it for the future
				alarm(currentAlarm->time - currentAlarm->prev->time);
		}
		
		else
		{
			if(currentAlarm->time <= 0)
				writeAlarm(0);
			else
				alarm(currentAlarm->time);
		}
		
	}
	
}
